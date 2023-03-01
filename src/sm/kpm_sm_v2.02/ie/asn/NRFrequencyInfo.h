/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-COMMON-IEs"
 * 	found in "e2sm_kpm_v02.03.asn1"
 * 	`asn1c -gen-PER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D asn`
 */

#ifndef	_NRFrequencyInfo_H_
#define	_NRFrequencyInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include "NR-ARFCN.h"
#include "NRFrequencyBand-List.h"
#include "NRFrequencyShift7p5khz.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NRFrequencyInfo */
typedef struct NRFrequencyInfo {
	NR_ARFCN_t	 nrARFCN;
	NRFrequencyBand_List_t	 frequencyBand_List;
	NRFrequencyShift7p5khz_t	*frequencyShift7p5khz;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NRFrequencyInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NRFrequencyInfo;

#ifdef __cplusplus
}
#endif

#endif	/* _NRFrequencyInfo_H_ */
#include <asn_internal.h>
