#include <assert.h>
#include <stdio.h>

#include "fill_ind_msg_frm_1.h"

void fill_kpm_ind_msg_frm_1(kpm_ind_msg_format_1_t * msg)
{
    assert(msg != NULL);

    // Measurement Data
    msg->meas_data_lst_len = 4;

    msg->meas_data_lst = calloc(msg->meas_data_lst_len, sizeof(meas_data_lst_t));
    assert(msg->meas_data_lst != NULL && "Memory exhausted" );

    for (size_t i = 0; i < msg->meas_data_lst_len; i++)
    {
        // Incomplete Flag
        msg->meas_data_lst[i].incomplete_flag = NULL;

        // Measurement Record
        msg->meas_data_lst[i].meas_record_len = 2;
        msg->meas_data_lst[i].meas_record_lst = calloc(msg->meas_data_lst[i].meas_record_len, sizeof(meas_record_lst_t));
        assert(msg->meas_data_lst[i].meas_record_lst != NULL && "Memory exhausted" );

        for (size_t j = 0; j < msg->meas_data_lst[i].meas_record_len; i++)
        {
            msg->meas_data_lst[i].meas_record_lst[j].no_value = INTEGER_MEAS_VALUE;
            msg->meas_data_lst[i].meas_record_lst[j].int_val = i+j;
        }
    }


    // Granularity Period - OPTIONAL
    msg->gran_period_ms = NULL;


    // Measurement Information - OPTIONAL
    msg->meas_info_lst_len = 4;
    msg->meas_info_lst = calloc(msg->meas_info_lst_len, sizeof(meas_info_format_1_lst_t));
    assert(msg->meas_info_lst != NULL && "Memory exhausted" );

    for (size_t i = 0; i < msg->meas_info_lst_len; i++)
    {
        // Measurement Type
        msg->meas_info_lst[i].meas_type.type = NAME_MEAS_TYPE;
        char s[100];
        snprintf(s, 100, "RNTI %04x PrbDlUsage", (unsigned) (1111*i + 1111));
        msg->meas_info_lst[i].meas_type.name.buf = calloc(strlen(s) + 1, sizeof(char));
        memcpy(msg->meas_info_lst[i].meas_type.name.buf, s, strlen(s));
        msg->meas_info_lst[i].meas_type.name.len = strlen(s);


        // Label Information
        msg->meas_info_lst[i].label_info_lst_len = 2;
        msg->meas_info_lst[i].label_info_lst = calloc(msg->meas_info_lst[i].label_info_lst_len, sizeof(label_info_lst_t));
        assert(msg->meas_info_lst[i].label_info_lst != NULL && "Memory exhausted" );

        for (size_t j = 0; j < msg->meas_info_lst[i].label_info_lst_len; j++)
        {
            msg->meas_info_lst[i].label_info_lst[j].plmn_id = malloc(sizeof(plmn_t));
            *msg->meas_info_lst[i].label_info_lst[j].plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
        }

    }


}