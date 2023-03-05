/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-COMMON-IEs"
 * 	found in "e2sm_kpm_v02.03_modified.asn1"
 * 	`asn1c -gen-PER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D asn`
 */

#ifndef	_InterfaceType_H_
#define	_InterfaceType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum InterfaceType {
	InterfaceType_nG	= 0,
	InterfaceType_xn	= 1,
	InterfaceType_f1	= 2,
	InterfaceType_e1	= 3,
	InterfaceType_s1	= 4,
	InterfaceType_x2	= 5,
	InterfaceType_w1	= 6
	/*
	 * Enumeration is extensible
	 */
} e_InterfaceType;

/* InterfaceType */
typedef long	 InterfaceType_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_InterfaceType;
asn_struct_free_f InterfaceType_free;
asn_struct_print_f InterfaceType_print;
asn_constr_check_f InterfaceType_constraint;
ber_type_decoder_f InterfaceType_decode_ber;
der_type_encoder_f InterfaceType_encode_der;
xer_type_decoder_f InterfaceType_decode_xer;
xer_type_encoder_f InterfaceType_encode_xer;
per_type_decoder_f InterfaceType_decode_uper;
per_type_encoder_f InterfaceType_encode_uper;
per_type_decoder_f InterfaceType_decode_aper;
per_type_encoder_f InterfaceType_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _InterfaceType_H_ */
#include <asn_internal.h>
