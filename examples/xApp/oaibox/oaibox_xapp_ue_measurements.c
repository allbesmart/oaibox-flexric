#include "../../../src/xApp/e42_xapp_api.h"
#include "../../../src/util/alg_ds/alg/defer.h"
#include "../../../src/util/time_now_us.h"
#include "../../../src/util/hashtable/hashtable.h"

#include <arpa/inet.h> // inet_addr()
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()


#define TICK_INTERVAL 10
#define UPDATE_INTERVAL 1000
#define MAX_MOBILES_PER_GNB 40

int16_t ticker = 0;
uint64_t    current_timestamp;
struct timeval  localized_timestamp;

int sockfd;
#define ADDRESS "127.0.0.1"
#define PORT 6969

static bool keepRunning = true;
void intHandler() {
    keepRunning = false;
}

static pthread_mutex_t mac_stats_mutex;
hash_table_t *ue_mac_stats_by_rnti_ht;

void write_mac_stats(char * buffer, mac_ue_stats_impl_t ue_mac_stats) {
    sprintf(&buffer[strlen(buffer)], "\"rnti\": \"%04x\",\"dlBytes\": %lu,\"dlMcs\": %d,\"dlBler\": %f,\"ulBytes\": %lu,"
                                     "\"ulMcs\": %d,\"ulBler\": %f,\"ri\": %d,\"pmi\": \"(%d,%d)\",\"phr\": %d,\"pcmax\": %d,",
            ue_mac_stats.rnti, ue_mac_stats.dl_aggr_tbs,ue_mac_stats.dl_mcs1,ue_mac_stats.dl_bler,ue_mac_stats.ul_aggr_tbs,
            ue_mac_stats.ul_mcs1,ue_mac_stats.ul_bler,ue_mac_stats.pmi_cqi_ri,ue_mac_stats.pmi_cqi_X1,ue_mac_stats.pmi_cqi_X2,
            ue_mac_stats.phr,ue_mac_stats.pcmax);
}

static void sm_cb_mac(sm_ag_if_rd_t const* rd)
{
    assert(rd != NULL);
    assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
    assert(rd->ind.type == MAC_STATS_V0);

    for (u_int32_t i = 0; i < rd->ind.mac.msg.len_ue_stats; i++) {
        pthread_mutex_lock(&mac_stats_mutex);
        mac_ue_stats_impl_t *ue_mac_stats = malloc(sizeof(*ue_mac_stats));
        *ue_mac_stats = rd->ind.mac.msg.ue_stats[i];
        hashtable_insert(ue_mac_stats_by_rnti_ht, rd->ind.mac.msg.ue_stats[i].rnti, ue_mac_stats);
        pthread_mutex_unlock(&mac_stats_mutex);
    }
}

static void sm_cb_gtp(sm_ag_if_rd_t const* rd)
{
    assert(rd != NULL);
    assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
    assert(rd->ind.type == GTP_STATS_V0);

    ticker += TICK_INTERVAL;
    if(ticker >= UPDATE_INTERVAL) {
        ticker = 0;
        for (uint32_t ue_idx = 0; ue_idx < rd->ind.gtp.msg.len; ue_idx++) {
            // Get updated mac stats of UE by RNTI
            pthread_mutex_lock(&mac_stats_mutex);
            void *data = NULL;
            hashtable_rc_t ret = hashtable_get(ue_mac_stats_by_rnti_ht, rd->ind.gtp.msg.ngut[ue_idx].ue_context_rnti_t, &data);
            pthread_mutex_unlock(&mac_stats_mutex);

            if ( ret == HASH_TABLE_OK ) {
                int64_t now = time_now_us();
                mac_ue_stats_impl_t ue_mac_stats = *(mac_ue_stats_impl_t *)data;

                char buffer[8191] = {0};
                sprintf(buffer, "{\"ue_id\": %u,\"timestamp\": %ju,", rd->ind.gtp.msg.ngut[ue_idx].ue_context_rrc_ue_id, now / 1000);

                write_mac_stats(buffer, ue_mac_stats);

                double rsrq = NAN;
                double sinr = NAN;
                long rsrp = ue_mac_stats.rsrp;
                uint8_t cqi = ue_mac_stats.cqi;
                float rssi = -1 * ue_mac_stats.raw_rssi;
                float pucch_snr = ue_mac_stats.pucch_snr;
                float pusch_snr = ue_mac_stats.pusch_snr;

                if (rd->ind.gtp.msg.ngut[ue_idx].ue_context_has_mqr) {
                    rsrq = rd->ind.gtp.msg.ngut[ue_idx].ue_context_mqr_rsrp;
                    rsrq = rd->ind.gtp.msg.ngut[ue_idx].ue_context_mqr_rsrq;
                    sinr = rd->ind.gtp.msg.ngut[ue_idx].ue_context_mqr_sinr;
                }

                if (!isnan(rsrq)) {
                    sprintf(&buffer[strlen(buffer)], "\"rsrq\": %.1f, ", rsrq);
                }

                if (!isnan(sinr)) {
                    sprintf(&buffer[strlen(buffer)], "\"sinr\": %.1f, ", sinr);
                }

                sprintf(&buffer[strlen(buffer)],"\"rsrp\": %ld,\"rssi\": %.1f,\"cqi\": %d,\"pucchSnr\": %.1f,\"puschSnr\": %.1f",
                        rsrp,rssi,cqi,pucch_snr,pusch_snr);

                sprintf(&buffer[strlen(buffer)], "}\n");

                printf("%s\n", buffer);
                ret = write(sockfd, buffer, strlen(buffer));
            }
        }
    }
}

int main(int argc, char* argv[])
{
    fr_args_t args = init_fr_args(argc, argv);

    struct sigaction act;
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);

    pthread_mutexattr_t attr = {0};
    pthread_mutex_init(&mac_stats_mutex, &attr);
    ue_mac_stats_by_rnti_ht = hashtable_create(MAX_MOBILES_PER_GNB, NULL, free);


    // TODO: please GOD make this verify if connection goes down...
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("OAIBOX: socket creation failed...\n");
    } else {
        printf("OAIBOX: socket successfully created\n");

        struct sockaddr_in server_addr;
        bzero((char *) &server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(ADDRESS);
        server_addr.sin_port = htons(PORT);

        // Connect the client socket to server socket
        if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
            printf("OAIBOX: connection with the server failed...\n");
        }
    }

    // Init the xApp
    init_xapp_api(&args);
    sleep(1);

    e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
    defer({ free_e2_node_arr_xapp(&nodes); });

    assert(nodes.len > 0);

    printf("Connected E2 nodes = %d\n", nodes.len);

    // MAC indication
    const char* i_0 = "10_ms";
    sm_ans_xapp_t* mac_handle = NULL;
    // GTP indication
    const char* i_3 = "10_ms";
    sm_ans_xapp_t* gtp_handle = NULL;

    if (nodes.len > 0) {
        mac_handle = calloc( nodes.len, sizeof(sm_ans_xapp_t) );
        assert(mac_handle  != NULL);
        gtp_handle = calloc( nodes.len, sizeof(sm_ans_xapp_t) );
        assert(gtp_handle  != NULL);
    }

    for (int i = 0; i < nodes.len; i++) {
        e2_node_connected_xapp_t* n = &nodes.n[i];
        for (size_t j = 0; j < n->len_rf; j++)
            printf("Registered node %d ran func id = %d \n ", i, n->rf[j].id);

        if (n->id.type == ngran_gNB) {
            mac_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 142, (void*)i_0, sm_cb_mac);
            assert(mac_handle[i].success == true);
            gtp_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 148, (void*)i_3, sm_cb_gtp);
            assert(gtp_handle[i].success == true);
        } else if (n->id.type == ngran_gNB_CU) {
            gtp_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 148, (void*)i_3, sm_cb_gtp);
            assert(gtp_handle[i].success == true);
        } else if (n->id.type == ngran_gNB_DU) {
            mac_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 142, (void*)i_0, sm_cb_mac);
            assert(mac_handle[i].success == true);
        }
    }

    while (keepRunning) {
    }

    for (int i = 0; i < nodes.len; ++i) {
        // Remove the handle previously returned
        if(mac_handle[i].u.handle != 0 )
            rm_report_sm_xapp_api(mac_handle[i].u.handle);
        if(gtp_handle[i].u.handle != 0)
            rm_report_sm_xapp_api(gtp_handle[i].u.handle);
    }

    if (nodes.len > 0) {
        free(mac_handle);
        free(gtp_handle);
    }

    hashtable_destroy(&ue_mac_stats_by_rnti_ht);

    // Stop the xApp
    while (try_stop_xapp_api() == false)
        usleep(1000);

    pthread_mutex_destroy(&mac_stats_mutex);

    printf("OAIBOX UE Measurements xAPP Completed\n");
}
