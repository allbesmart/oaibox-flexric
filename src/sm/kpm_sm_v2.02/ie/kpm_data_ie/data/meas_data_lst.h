#ifndef KPM_V2_MEASUREMENT_DATA_LIST_H
#define KPM_V2_MEASUREMENT_DATA_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct {
    enum {MeasRecord_int=1, MeasRecord_real,  MeasRecord_noval} type;
	unsigned long   int_val;
	double	        real_val;
} meas_record_lst_t;

typedef struct {
    size_t                    measRecord_len; // 1..
	meas_record_lst_t        *measRecord; 
	long	                 *incompleteFlag;	// OPTIONAL: true(0) value indicates that the measurements record 
                                            // is not reliable asn we pass to ASN this info, -1 means that the flag is not present
} meas_data_lst_t;


#ifdef __cplusplus
}
#endif

#endif