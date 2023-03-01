/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-COMMON-IEs"
 * 	found in "e2sm_kpm_v02.03.asn1"
 * 	`asn1c -gen-PER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D asn`
 */

#include "UEID-NG-ENB-DU.h"

asn_TYPE_member_t asn_MBR_UEID_NG_ENB_DU_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UEID_NG_ENB_DU, ng_eNB_CU_UE_W1AP_ID),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NGENB_CU_UE_W1AP_ID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ng-eNB-CU-UE-W1AP-ID"
		},
};
static const ber_tlv_tag_t asn_DEF_UEID_NG_ENB_DU_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_UEID_NG_ENB_DU_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* ng-eNB-CU-UE-W1AP-ID */
};
asn_SEQUENCE_specifics_t asn_SPC_UEID_NG_ENB_DU_specs_1 = {
	sizeof(struct UEID_NG_ENB_DU),
	offsetof(struct UEID_NG_ENB_DU, _asn_ctx),
	asn_MAP_UEID_NG_ENB_DU_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_UEID_NG_ENB_DU = {
	"UEID-NG-ENB-DU",
	"UEID-NG-ENB-DU",
	&asn_OP_SEQUENCE,
	asn_DEF_UEID_NG_ENB_DU_tags_1,
	sizeof(asn_DEF_UEID_NG_ENB_DU_tags_1)
		/sizeof(asn_DEF_UEID_NG_ENB_DU_tags_1[0]), /* 1 */
	asn_DEF_UEID_NG_ENB_DU_tags_1,	/* Same as above */
	sizeof(asn_DEF_UEID_NG_ENB_DU_tags_1)
		/sizeof(asn_DEF_UEID_NG_ENB_DU_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_UEID_NG_ENB_DU_1,
	1,	/* Elements count */
	&asn_SPC_UEID_NG_ENB_DU_specs_1	/* Additional specs */
};

