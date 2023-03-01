/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "e2sm_kpm_v02.03.asn1"
 * 	`asn1c -gen-PER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D asn`
 */

#ifndef	_MatchingCondItem_Choice_H_
#define	_MatchingCondItem_Choice_H_


#include <asn_application.h>

/* Including external dependencies */
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MatchingCondItem_Choice_PR {
	MatchingCondItem_Choice_PR_NOTHING,	/* No components present */
	MatchingCondItem_Choice_PR_measLabel,
	MatchingCondItem_Choice_PR_testCondInfo
	/* Extensions may appear below */
	
} MatchingCondItem_Choice_PR;

/* Forward declarations */
struct MeasurementLabel;
struct TestCondInfo;

/* MatchingCondItem-Choice */
typedef struct MatchingCondItem_Choice {
	MatchingCondItem_Choice_PR present;
	union MatchingCondItem_Choice_u {
		struct MeasurementLabel	*measLabel;
		struct TestCondInfo	*testCondInfo;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MatchingCondItem_Choice_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MatchingCondItem_Choice;
extern asn_CHOICE_specifics_t asn_SPC_MatchingCondItem_Choice_specs_1;
extern asn_TYPE_member_t asn_MBR_MatchingCondItem_Choice_1[2];
extern asn_per_constraints_t asn_PER_type_MatchingCondItem_Choice_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _MatchingCondItem_Choice_H_ */
#include <asn_internal.h>
