/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "e2sm_kpm_v02.01_standard.asn1"
 * 	`asn1c -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-JER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps`
 */

#ifndef	_MeasurementInfoItem_H_
#define	_MeasurementInfoItem_H_


#include <asn_application.h>

/* Including external dependencies */
#include "MeasurementType.h"
#include "LabelInfoList.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MeasurementInfoItem */
typedef struct MeasurementInfoItem {
	MeasurementType_t	 measType;
	LabelInfoList_t	 labelInfoList;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasurementInfoItem_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasurementInfoItem;
extern asn_SEQUENCE_specifics_t asn_SPC_MeasurementInfoItem_specs_1;
extern asn_TYPE_member_t asn_MBR_MeasurementInfoItem_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _MeasurementInfoItem_H_ */
#include <asn_internal.h>