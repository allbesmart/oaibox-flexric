/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-COMMON-IEs"
 * 	found in "e2sm_kpm_v02.03.asn1"
 * 	`asn1c -gen-PER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D asn`
 */

#include "GUMMEI.h"

asn_TYPE_member_t asn_MBR_GUMMEI_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct GUMMEI, pLMN_Identity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PLMNIdentity,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pLMN-Identity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GUMMEI, mME_Group_ID),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MME_Group_ID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"mME-Group-ID"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GUMMEI, mME_Code),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MME_Code,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"mME-Code"
		},
};
static const ber_tlv_tag_t asn_DEF_GUMMEI_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_GUMMEI_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pLMN-Identity */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* mME-Group-ID */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* mME-Code */
};
asn_SEQUENCE_specifics_t asn_SPC_GUMMEI_specs_1 = {
	sizeof(struct GUMMEI),
	offsetof(struct GUMMEI, _asn_ctx),
	asn_MAP_GUMMEI_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_GUMMEI = {
	"GUMMEI",
	"GUMMEI",
	&asn_OP_SEQUENCE,
	asn_DEF_GUMMEI_tags_1,
	sizeof(asn_DEF_GUMMEI_tags_1)
		/sizeof(asn_DEF_GUMMEI_tags_1[0]), /* 1 */
	asn_DEF_GUMMEI_tags_1,	/* Same as above */
	sizeof(asn_DEF_GUMMEI_tags_1)
		/sizeof(asn_DEF_GUMMEI_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_GUMMEI_1,
	3,	/* Elements count */
	&asn_SPC_GUMMEI_specs_1	/* Additional specs */
};

