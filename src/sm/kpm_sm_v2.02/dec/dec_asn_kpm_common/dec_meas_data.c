#include <assert.h>
#include <stdbool.h>
#include "../../ie/asn/asn_constant.h"

#include "dec_meas_data.h"
#include "../../ie/asn/MeasurementDataItem.h"
#include "../../ie/asn/MeasurementRecordItem.h"

meas_data_lst_t * kpm_dec_meas_data_asn(const MeasurementData_t meas_data_asn, const size_t meas_data_len)
{
    meas_data_lst_t * meas_data = calloc(1,sizeof(meas_data_lst_t));
    assert(meas_data != NULL && "Memory exhausted");

    for (size_t i = 0; i<meas_data_len; i++)
    {
        MeasurementDataItem_t * data_item_asn = meas_data_asn.list.array[i];
        
        // Measurement Record : [1, 2147483647]
        meas_data->meas_record_len = data_item_asn->measRecord.list.count;
        assert(meas_data->meas_record_len >= 1 && meas_data->meas_record_len <= maxnoofMeasurementValue);
        
        for (size_t j = 0; j<meas_data[i].meas_record_len; j++)
        {
            MeasurementRecordItem_t * record_item_asn = data_item_asn->measRecord.list.array[j];

            switch (record_item_asn->present)
            {
            case MeasurementRecordItem_PR_integer:
                meas_data->meas_record_lst->value = INTEGER_MEAS_VALUE;
                meas_data->meas_record_lst->int_val = record_item_asn->choice.integer;
                break;

            case MeasurementRecordItem_PR_real:
                meas_data->meas_record_lst->value = REAL_MEAS_VALUE;
                meas_data->meas_record_lst->real_val = record_item_asn->choice.real;
                break;

            case MeasurementRecordItem_PR_noValue:
                meas_data->meas_record_lst->value = NO_VALUE_MEAS_VALUE;
                meas_data->meas_record_lst->no_value = NULL;
                break;
            
            default:
                assert(false && "Non valid Measurement Record type");
            }
        }


        // Incomplete Flag - OPTIONAL
        if (data_item_asn->incompleteFlag == 0)
        {
            meas_data->incomplete_flag = malloc(sizeof(*meas_data->incomplete_flag));
            assert(meas_data->incomplete_flag != NULL && "Memory exhausted");
            meas_data->incomplete_flag = TRUE_ENUM_VALUE;
        }
        else
        {
            assert(meas_data->incomplete_flag == TRUE_ENUM_VALUE && "has only one value (true)");
        }


    }
    
    return &meas_data;
}