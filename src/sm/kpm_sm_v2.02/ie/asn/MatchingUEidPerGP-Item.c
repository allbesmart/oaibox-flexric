/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "e2sm_kpm_v02.03.asn1"
 * 	`asn1c -gen-PER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D asn`
 */

#include "MatchingUEidPerGP-Item.h"

#include "MatchingUEidList-PerGP.h"
/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_per_constraints_t asn_PER_type_noUEmatched_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  0,  0,  0,  0 }	/* (0..0,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_matchedPerGP_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  1,  1,  0,  1 }	/* (0..1,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_noUEmatched_value2enum_3[] = {
	{ 0,	4,	"true" }
	/* This list is extensible */
};
static const unsigned int asn_MAP_noUEmatched_enum2value_3[] = {
	0	/* true(0) */
	/* This list is extensible */
};
static const asn_INTEGER_specifics_t asn_SPC_noUEmatched_specs_3 = {
	asn_MAP_noUEmatched_value2enum_3,	/* "tag" => N; sorted by tag */
	asn_MAP_noUEmatched_enum2value_3,	/* N => "tag"; sorted by N */
	1,	/* Number of elements in the maps */
	2,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_noUEmatched_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_noUEmatched_3 = {
	"noUEmatched",
	"noUEmatched",
	&asn_OP_NativeEnumerated,
	asn_DEF_noUEmatched_tags_3,
	sizeof(asn_DEF_noUEmatched_tags_3)
		/sizeof(asn_DEF_noUEmatched_tags_3[0]) - 1, /* 1 */
	asn_DEF_noUEmatched_tags_3,	/* Same as above */
	sizeof(asn_DEF_noUEmatched_tags_3)
		/sizeof(asn_DEF_noUEmatched_tags_3[0]), /* 2 */
	{ 0, &asn_PER_type_noUEmatched_constr_3, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_noUEmatched_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_matchedPerGP_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MatchingUEidPerGP_Item__matchedPerGP, choice.noUEmatched),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_noUEmatched_3,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"noUEmatched"
		},
	{ ATF_POINTER, 0, offsetof(struct MatchingUEidPerGP_Item__matchedPerGP, choice.oneOrMoreUEmatched),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MatchingUEidList_PerGP,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"oneOrMoreUEmatched"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_matchedPerGP_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* noUEmatched */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* oneOrMoreUEmatched */
};
static asn_CHOICE_specifics_t asn_SPC_matchedPerGP_specs_2 = {
	sizeof(struct MatchingUEidPerGP_Item__matchedPerGP),
	offsetof(struct MatchingUEidPerGP_Item__matchedPerGP, _asn_ctx),
	offsetof(struct MatchingUEidPerGP_Item__matchedPerGP, present),
	sizeof(((struct MatchingUEidPerGP_Item__matchedPerGP *)0)->present),
	asn_MAP_matchedPerGP_tag2el_2,
	2,	/* Count of tags in the map */
	0, 0,
	2	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_matchedPerGP_2 = {
	"matchedPerGP",
	"matchedPerGP",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ 0, &asn_PER_type_matchedPerGP_constr_2, CHOICE_constraint },
	asn_MBR_matchedPerGP_2,
	2,	/* Elements count */
	&asn_SPC_matchedPerGP_specs_2	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_MatchingUEidPerGP_Item_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MatchingUEidPerGP_Item, matchedPerGP),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_matchedPerGP_2,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"matchedPerGP"
		},
};
static const ber_tlv_tag_t asn_DEF_MatchingUEidPerGP_Item_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_MatchingUEidPerGP_Item_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* matchedPerGP */
};
asn_SEQUENCE_specifics_t asn_SPC_MatchingUEidPerGP_Item_specs_1 = {
	sizeof(struct MatchingUEidPerGP_Item),
	offsetof(struct MatchingUEidPerGP_Item, _asn_ctx),
	asn_MAP_MatchingUEidPerGP_Item_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_MatchingUEidPerGP_Item = {
	"MatchingUEidPerGP-Item",
	"MatchingUEidPerGP-Item",
	&asn_OP_SEQUENCE,
	asn_DEF_MatchingUEidPerGP_Item_tags_1,
	sizeof(asn_DEF_MatchingUEidPerGP_Item_tags_1)
		/sizeof(asn_DEF_MatchingUEidPerGP_Item_tags_1[0]), /* 1 */
	asn_DEF_MatchingUEidPerGP_Item_tags_1,	/* Same as above */
	sizeof(asn_DEF_MatchingUEidPerGP_Item_tags_1)
		/sizeof(asn_DEF_MatchingUEidPerGP_Item_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_MatchingUEidPerGP_Item_1,
	1,	/* Elements count */
	&asn_SPC_MatchingUEidPerGP_Item_specs_1	/* Additional specs */
};

