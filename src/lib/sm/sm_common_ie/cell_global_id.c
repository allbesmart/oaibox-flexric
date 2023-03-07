#include <assert.h>
#include <stddef.h>

#include "cell_global_id.h"


void free_cell_global_id(cell_global_id_t* src)
{
  assert(src != NULL);

  // CHOICE RAT type
  // Mandatory
  // rat_type_e type;

  // union{
  //  nr_cgi_t nr_cgi; // 6.2.3.7
  //  eutra_cgi_t eutra; // 6.2.3.11
  // };
}

bool eq_cell_global_id(cell_global_id_t const * m0, cell_global_id_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    if (m0->type != m1->type)
      return false;

    switch (m0->type)
    {
    case NR_CGI_RAT_TYPE:
      if (eq_nr_cgi(&m0->nr_cgi, &m1->nr_cgi) != true)
        return false;
      break;

    case EUTRA_CGI_RAT_TYPE:
      if (eq_eutra_cgi(&m0->eutra, &m1->eutra) != true)
        return false;
      break;
    
    default:
      assert(false && "Unknown Cell Global ID Type");
    }

    return true;
}


