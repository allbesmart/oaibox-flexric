#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie.h"
#include "../../src/sm/kpm_sm_v2.02/enc/kpm_enc_asn.h"
#include "../../src/sm/kpm_sm_v2.02/dec/kpm_dec_asn.h"

void test_indication_message()
{
    /* definition of measurement data */ 
    const size_t meas_Data_len = 2;

    MeasDataItem_t *meas_Data = calloc(meas_Data_len, sizeof(MeasDataItem_t));
    
    for (size_t i = 0; i < meas_Data_len; i++)
    {
        meas_Data[i].incompleteFlag = NULL; // the flag is not present

        meas_Data[i].measRecord_len = 1; // enough for the test
        meas_Data[i].measRecord = calloc(meas_Data[i].measRecord_len, sizeof(MeasRecord_t));

        meas_Data[i].measRecord[0].int_val = i + 1;
        meas_Data[i].measRecord[0].type = MeasRecord_int;
    }
    

   
    /* definition of measurement information */ 
    const size_t meas_Info_len = 3;

    MeasInfo_t *meas_Info = calloc(meas_Info_len, sizeof(MeasInfo_t));

    for (size_t i = 0; i < meas_Info_len; ++i)
    {
        memset(&meas_Info[i].meas_name, 0, sizeof(byte_array_t));
        const char* meas_name_str = "This is the measurement name";
        meas_Info[i].meas_name.buf = calloc(strlen(meas_name_str) + 1, sizeof(char));
        memcpy(meas_Info[i].meas_name.buf, meas_name_str, strlen(meas_name_str));
        meas_Info[i].meas_name.len = strlen(meas_name_str);

        meas_Info[i].meas_type = KPM_V2_MEASUREMENT_TYPE_NAME;

        meas_Info[i].labelInfo_len = 1; // enough for the test

        meas_Info[i].labelInfo = calloc(meas_Info[i].labelInfo_len, sizeof(LabelInformationItem_t));

        //meas_Info[i].labelInfo[0].noLabel = malloc(sizeof(*meas_Info[i].labelInfo[0].noLabel));
        //*meas_Info[i].labelInfo[0].noLabel = 0; // there is no other parameters in label_info defined

        meas_Info[i].labelInfo[0].plmn_id = malloc(sizeof(*meas_Info[i].labelInfo[0].plmn_id));
        *meas_Info[i].labelInfo[0].plmn_id = (plmn_t) {
            .mcc = 200,
            .mnc = 1,
            .mnc_digit_len = 2,
        };

        // OTHER LABELS ARE NOT YET IMPLEMENTED !

        // meas_Info[i].labelInfo[0].sliceID = malloc(sizeof(*meas_Info[i].labelInfo[0].sliceID));
        // meas_Info[i].labelInfo[0].sliceID->sST.buf = calloc(strlen("2") + 1, sizeof(char));
        // memcpy(meas_Info[i].labelInfo[0].sliceID->sST.buf, "2", strlen("2")); // setting the slice/service type to URLLC
        // meas_Info[i].labelInfo[0].sliceID->sST.len = strlen("2");
        // meas_Info[i].labelInfo[0].sliceID->sD = NULL; // s-nssai contains just standard values

    }
    
    
    unsigned long *granularity_Period = NULL; // if != NULL => assert("decoding not implemented yet")


    kpm_ind_msg_t kpm_ind_message = {
        .MeasData_len = meas_Data_len,
        .MeasData = meas_Data,
        .MeasInfo_len = meas_Info_len,
        .MeasInfo = meas_Info,
        .granulPeriod = granularity_Period,
    };

    byte_array_t kpm_ind_message_enc = kpm_enc_ind_msg_asn(&kpm_ind_message);
    kpm_ind_msg_t kpm_ind_message_dec = kpm_dec_ind_msg_asn(kpm_ind_message_enc.len, kpm_ind_message_enc.buf);

    free_byte_array(kpm_ind_message_enc);

    assert(eq_kpm_ind_msg(&kpm_ind_message, &kpm_ind_message_dec) == true);

    free_kpm_ind_msg(&kpm_ind_message);
    free_kpm_ind_msg(&kpm_ind_message_dec);

}

int main()
{
    test_indication_message();

    puts("Success running the encoding/decoding test");
    return 0;
}