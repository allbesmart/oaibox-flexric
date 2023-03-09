#ifndef RAN_FUNCTION_NAME_h
#define RAN_FUNCTION_NAME_h

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../util/byte_array.h"


typedef struct {
    byte_array_t	 short_name;
	byte_array_t	 E2SM_OID;
	byte_array_t	 description;
	long	        *instance;	/* OPTIONAL: it is suggested to be used when E2 Node declares
                                   multiple RAN Function ID supporting the same  E2SM specification   ask Mikel */
} ran_function_name_t;

void free_kpm_ran_function_name(ran_function_name_t* src);

bool eq_kpm_ran_function_name(ran_function_name_t const * m0, ran_function_name_t const * m1);

#ifdef __cplusplus
}
#endif

#endif

// done
