#ifndef KPM_V2_LABEL_INFO_LIST_H
#define KPM_V2_LABEL_INFO_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../../util/byte_array.h"
#include "../../../../lib/ap/e2ap_types/common/e2ap_plmn.h"

typedef struct S_NSSAI {
    byte_array_t	  sST;
	byte_array_t	  *sD;	/* OPTIONAL */
} S_NSSAI_t;

/* 
 * Structure 'label_info_lst_t' defines the values of the subcounters that are applicable to an associated measurement type
 * identified by measName or measID. All the fields are indicated as optional. If value is != NULL, it means presence of the optional 
 * field.
 */

typedef struct{
    long	                    *noLabel;	/* OPTIONAL: looks like this is an enumeration datatype that accepts only true (0) */
	plmn_t                      *plmn_id;  /* OPTIONAL */
	S_NSSAI_t       	        *sliceID;	/* OPTIONAL */
	long            	        *fiveQI;	/* OPTIONAL */
	long                      	*qFI;	    /* OPTIONAL */
	long        	            *qCI;	    /* OPTIONAL */
	long        	            *qCImax;	/* OPTIONAL */
	long        	            *qCImin;	/* OPTIONAL */
	long	                    *aRPmax;	/* OPTIONAL */
	long	                    *aRPmin;	/* OPTIONAL */
	long	                    *bitrateRange;/* OPTIONAL */
	long	                    *layerMU_MIMO;/* OPTIONAL */
	long	                    *sUM;	    /* OPTIONAL */
	long                        *distBinX;/* OPTIONAL */
	long	                    *distBinY;/* OPTIONAL */
	long	                    *distBinZ;/* OPTIONAL */
	long	                    *preLabelOverride;/* OPTIONAL */
	long	                    *startEndInd;	/* OPTIONAL */
	long	                    *min;	    /* OPTIONAL */
	long	                    *max;	    /* OPTIONAL */
	long                        *avg;	    /* OPTIONAL */

} label_info_lst_t;
// ask Mikel: why is everything defined as long?
// e.g, qCI is an integer(0,..,255)


void cp_label_info(label_info_lst_t *dst, label_info_lst_t const *src);
void free_label_info(label_info_lst_t *l);


#ifdef __cplusplus
}
#endif

#endif