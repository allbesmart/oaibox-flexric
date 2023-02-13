#include <assert.h>

#include "fill_kpm_action_def_frm_1.h"

void fill_kpm_action_def_frm_1(kpm_act_def_format_1_t * action_def)
{
    assert(action_def != NULL);

    // Measurement Information
    // [1, 65535]
    action_def->meas_info_lst_len = (rand()%  65535) + 1;
    action_def->meas_info_lst = calloc(action_def->meas_info_lst_len, sizeof(meas_info_format_1_lst_t));
    assert(action_def->meas_info_lst != NULL && "Memory exhausted" );

    for (size_t i = 0; i < action_def->meas_info_lst_len; i++)
    {
        // Measurement Type
        action_def->meas_info_lst[i].meas_type.type = NAME_MEAS_TYPE;
        action_def->meas_info_lst[i].meas_type.name.buf = calloc(strlen("test") + 1, sizeof(char));
        memcpy(action_def->meas_info_lst[i].meas_type.name.buf, "test", strlen("test"));
        action_def->meas_info_lst[i].meas_type.name.len = strlen("test");


        // Label Information
        // [1, 2147483647]
        action_def->meas_info_lst[i].label_info_lst_len = (rand() %  2147483647) + 1;
        action_def->meas_info_lst[i].label_info_lst = calloc(action_def->meas_info_lst[i].label_info_lst_len, sizeof(label_info_lst_t));
        assert(action_def->meas_info_lst[i].label_info_lst != NULL && "Memory exhausted" );

        for (size_t j = 0; j < action_def->meas_info_lst[i].label_info_lst_len; j++)
        {
            // action_def->meas_info_lst[i].label_info_lst[j].plmn_id = malloc(sizeof(plmn_t));
            // *action_def->meas_info_lst[i].label_info_lst[j].plmn_id = (plmn_t) {.mcc = 505, .mnc = 1, .mnc_digit_len = 2};
            action_def->meas_info_lst[i].label_info_lst[j].noLabel = malloc(sizeof(enum_value_e));
            assert(action_def->meas_info_lst[i].label_info_lst[j].noLabel != NULL && "Memory exhausted"); 

            *action_def->meas_info_lst[i].label_info_lst[j].noLabel = TRUE_ENUM_VALUE;
        }

    }

    // Granularity Period
    action_def->gran_period_ms = rand();

    // Cell Global ID - OPTIONAL
    action_def->cell_global_id = NULL;

    // Measurement Bin Range - OPTIONAL
    action_def->meas_bin_range_info_lst_len = 0;
    action_def->meas_bin_info_lst = NULL;
}
