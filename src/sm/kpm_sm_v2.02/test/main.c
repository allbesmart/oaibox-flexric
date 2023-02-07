#include <assert.h>
#include <stdlib.h>

#include "../ie/kpm_data_ie/kpm_ric_info/kpm_ric_event_trigger_def.h"
#include "../../../util/alg_ds/alg/defer.h"
#include "../../../util/byte_array.h"
#include "../../../sm/kpm_sm_v2.02/enc/kpm_enc_asn.h"
#include "../../../sm/kpm_sm_v2.02/dec/kpm_dec_asn.h"
#include "fill_rnd_data_kpm.h"

#include <time.h>

void test_kpm_ric_event_trigger_def_asn(void)
{
  kpm_event_trigger_def_t msg = fill_kpm_event_trigger_def();
  defer({ free_kpm_event_trigger_def(&msg); }); 

  byte_array_t ba = kpm_enc_event_trigger_asn(&msg);
  defer({ free_byte_array(ba); }); 

  kpm_event_trigger_def_t out = kpm_dec_event_trigger_asn(ba.len, ba.buf);
  defer({ free_kpm_event_trigger_def(&out); }); 

  assert(eq_kpm_event_trigger_def(&msg, &out ) == true);
}


int main()
{
  time_t t;
  srand((unsigned) time(&t));


  // Test off all the functions
  test_kpm_ric_event_trigger_def_asn();

  // Other test for all the functions...
  //
  return EXIT_SUCCESS;
}
