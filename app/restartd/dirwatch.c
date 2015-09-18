#include <fcntl.h>
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

    EV_SET (&ev, id, EVFILT_VNODE, EV_DELETE, 0, 0, 0);

    kevent (Manager.kq, &ev, 1, NULL, 0, NULL);

    if ((toDel = dirwatch_find (id)))
    {
        dirwatch_list_del (Manager.dirwatches, toDel);
        s16mem_free (toDel);
    }
}

unsigned dirwatch_add (const char * path, void * userData,
                       void (*cb) (void *, struct kevent ev))
{
    struct kevent ev;
    DirWatch * newDirWatch;
    int i, ident = open (path, O_RDONLY);

    if (ident == -1)
        return 0;

    printf ("Path: %s\n", path);

    EV_SET (&ev, ident, EVFILT_VNODE, EV_ADD | EV_ENABLE | EV_CLEAR,
            NOTE_EXTEND | NOTE_WRITE, 0, 0);

    i = kevent (Manager.kq, &ev, 1, NULL, 0, NULL);

    if (i == -1)
    {
        perror ("DirWatch kevent! (add)");
        return 0;
    }

    newDirWatch = s16mem_alloc (sizeof (DirWatch));

    newDirWatch->id = ident;
    newDirWatch->userData = userData;
    newDirWatch->cb = cb;

    dirwatch_list_add (Manager.dirwatches, newDirWatch);
    return ident;
}
