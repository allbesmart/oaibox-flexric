#include "ran_parameter_value.h"

#include <assert.h>

void free_ran_parameter_value(ran_parameter_value_t* src)
{
  assert(src != NULL);

  if(src->type ==  BOOLEAN_RAN_PARAMETER_VALUE){

  } else if(src->type == INTEGER_RAN_PARAMETER_VALUE ){

  } else if(src->type == REAL_RAN_PARAMETER_VALUE ){

  }else if(src->type == BIT_STRING_RAN_PARAMETER_VALUE ){
    free_byte_array(src->bit_str_ran);
  }else if(src->type ==  OCTET_STRING_RAN_PARAMETER_VALUE){
    free_byte_array(src->octet_str_ran );
  }else if(src->type == PRINTABLESTRING_RAN_PARAMETER_VALUE){
    free_byte_array(src->printable_str_ran);
  } else {
    assert(0!=0 && "Unknown type");
  }

}

bool eq_ran_parameter_value(ran_parameter_value_t const* m0, ran_parameter_value_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false; 


  if(m0->type != m1->type)
    return false;

  if(m0->type == BOOLEAN_RAN_PARAMETER_VALUE){
    if(m0->bool_ran != m1->bool_ran)
      return false;

  }else if(m0->type == INTEGER_RAN_PARAMETER_VALUE){
    if(m0->int_ran != m1->int_ran)
      return false;

  }else if(m0->type == REAL_RAN_PARAMETER_VALUE){
    if(m0->real_ran != m1->real_ran) // equality here is right, since we are just transporting bits. 
      return false;

  }else if(m0->type == BIT_STRING_RAN_PARAMETER_VALUE){
    if(eq_byte_array(&m0->bit_str_ran, &m1->bit_str_ran) == false)
      return false;

  }else if(m0->type == OCTET_STRING_RAN_PARAMETER_VALUE){
    if(eq_byte_array(&m0->octet_str_ran, &m1->octet_str_ran) == false)
      return false;

  }else if(m0->type == PRINTABLESTRING_RAN_PARAMETER_VALUE){
    if(eq_byte_array(&m0->printable_str_ran, &m1->printable_str_ran) == false)
      return false;

  } else {
    assert(0 != 0 && "Unknown type");
  }

  return true;
}

