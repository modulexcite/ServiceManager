#include <limits.h>
#include <stdlib.h>

#include "manager.h"
#include "dirwatch.h"

DirWatch * dirwatch_find (unsigned id)
{
    for (dirwatch_list_iterator it = dirwatch_list_begin (Manager.dirwatches);
         it != NULL; dirwatch_list_iterator_next (&it))
    {
        if (it->val->id == id)
        {
            return it->val;
        }
    }
    return 0;
}

void dirwatch_del (unsigned id)
{
    DirWatch * toDel;
    struct kevent ev;

    if ((toDel = dirwatch_find (id)))
    {
        dirwatch_list_del (Manager.dirwatches, toDel);
        s16mem_free (toDel);
    }
}

unsigned dirwatch_add (const char * path, void * userData,
                       void (*cb) (void *, unsigned))
{
    return 0;
}
