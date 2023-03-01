/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-COMMON-IEs"
 * 	found in "e2sm_kpm_v02.03.asn1"
 * 	`asn1c -gen-PER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D asn`
 */

#include "RRCclass-LTE.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
asn_per_constraints_t asn_PER_type_RRCclass_LTE_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  4,  4,  0,  11 }	/* (0..11,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_RRCclass_LTE_value2enum_1[] = {
	{ 0,	8,	"bCCH-BCH" },
	{ 1,	13,	"bCCH-BCH-MBMS" },
	{ 2,	11,	"bCCH-DL-SCH" },
	{ 3,	14,	"bCCH-DL-SCH-BR" },
	{ 4,	16,	"bCCH-DL-SCH-MBMS" },
	{ 5,	4,	"mCCH" },
	{ 6,	4,	"pCCH" },
	{ 7,	7,	"dL-CCCH" },
	{ 8,	7,	"dL-DCCH" },
	{ 9,	7,	"uL-CCCH" },
	{ 10,	7,	"uL-DCCH" },
	{ 11,	7,	"sC-MCCH" }
	/* This list is extensible */
};
static const unsigned int asn_MAP_RRCclass_LTE_enum2value_1[] = {
	0,	/* bCCH-BCH(0) */
	1,	/* bCCH-BCH-MBMS(1) */
	2,	/* bCCH-DL-SCH(2) */
	3,	/* bCCH-DL-SCH-BR(3) */
	4,	/* bCCH-DL-SCH-MBMS(4) */
	7,	/* dL-CCCH(7) */
	8,	/* dL-DCCH(8) */
	5,	/* mCCH(5) */
	6,	/* pCCH(6) */
	11,	/* sC-MCCH(11) */
	9,	/* uL-CCCH(9) */
	10	/* uL-DCCH(10) */
	/* This list is extensible */
};
const asn_INTEGER_specifics_t asn_SPC_RRCclass_LTE_specs_1 = {
	asn_MAP_RRCclass_LTE_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_RRCclass_LTE_enum2value_1,	/* N => "tag"; sorted by N */
	12,	/* Number of elements in the maps */
	13,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_RRCclass_LTE_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_RRCclass_LTE = {
	"RRCclass-LTE",
	"RRCclass-LTE",
	&asn_OP_NativeEnumerated,
	asn_DEF_RRCclass_LTE_tags_1,
	sizeof(asn_DEF_RRCclass_LTE_tags_1)
		/sizeof(asn_DEF_RRCclass_LTE_tags_1[0]), /* 1 */
	asn_DEF_RRCclass_LTE_tags_1,	/* Same as above */
	sizeof(asn_DEF_RRCclass_LTE_tags_1)
		/sizeof(asn_DEF_RRCclass_LTE_tags_1[0]), /* 1 */
	{ 0, &asn_PER_type_RRCclass_LTE_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_RRCclass_LTE_specs_1	/* Additional specs */
};

