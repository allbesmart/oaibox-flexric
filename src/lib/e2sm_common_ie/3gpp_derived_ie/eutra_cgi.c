#include <assert.h>
#include <stddef.h>

#include "eutra_cgi.h"

bool eq_eutra_cgi(eutra_cgi_t const * m0, eutra_cgi_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    if (eq_plmn(&m0->plmn_id, &m1->plmn_id) != true)
        return false;

      if (m0->eutra_cell_id != m1->eutra_cell_id)
        return false;

    return true;
}
