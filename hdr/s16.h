#ifndef S16_H_
#define S16_H_

#include "list.h"
#include "s16_rpc.h"
#include "repositoryd_rpc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* These are the types which are central to S16.
 * Be aware that these types are not passed directly when using RPC
 * interfaces - they are translated into a more suitable format for
 * that, and then back to one of these types as appropriate. */
/* A service. */
typedef struct svc_s svc_t;
/* A service instance. */
typedef struct svc_instance_s svc_instance_t;
/* A property. */
typedef struct property_s property_t;

/* These generate the list manipulation functions for the three types
 * above. */
ListGenForNameType (svc, svc_t);
ListGenForNameType (inst, svc_instance_t);
ListGenForNameType (prop, property_t);

typedef struct svc_s
{
    /* Each of the main types has an identifier, which is randomly generated
     * upon its import to repositoryd. The identifier is used for quick RPC
     * communication, without needing to pass a full name. */
    unsigned long id;
    /* Each service has a name. The name forms a part of the FMRI. */
    char * name;
    /* A service also has a list of properties, */
    prop_list properties;
    /* and a list of instances. */
    inst_list instances;
} svc_t;

typedef struct svc_instance_s
{
    unsigned long id;
    char * name;
    /* Instances also have a property list. */
    prop_list properties;
} svc_instance_t;

typedef struct property_s
{
    unsigned long id;
    /* The key. */
    char * name;
    /* The value of the property, either a string or a long int.
     * The pval_t type is defined in s16_rpc.h. */
    pval_t value;
} property_t;

#define gen_find_id_wrapper_proto(name, type)                                  \
    type * name##_find_id (name##_list box, unsigned long keyptr);

#define gen_find_name_wrapper_proto(name, type)                                \
    type * name##_find_name (name##_list box, char const * name);

/* These are convenience functions. They search through a list of one of the
 * basic S16 types looking for an entry that matches a given identifier or
 * name, and return the match if they find one, otherwise returning 0. */

gen_find_id_wrapper_proto (svc, svc_t);
gen_find_name_wrapper_proto (svc, svc_t);

gen_find_id_wrapper_proto (inst, svc_instance_t);
gen_find_name_wrapper_proto (inst, svc_instance_t);

gen_find_id_wrapper_proto (prop, property_t);
gen_find_name_wrapper_proto (prop, property_t);

/* These are small wrapper functions.
 * perror_fatal() wraps perror() then exits with EXIT_FAILURE.
 * error_fatal() wraps fprintf(stderr, char const *, ...); and exits
 * likewise. */
void perror_fatal (const char * str);
void error_fatal (const char * fmt, ...);

/* S16 provides a safe wrapper on the system memory functions.
 * These usually pass through directly to the libc functions, but
 * in cases of memory exhaustion, they will allocate memory from
 * a static pool and call a callback function registered by s16mem_init
 * which is used to tell the program to stop everything that involves
 * allocating significant amounts of memory.
 * The first argument to this callback is either 1 for 'memory exhausted'
 * or 0 for 'memory is no longer exhausted' (i.e., allocating with malloc()
 * started working again.)
 * The second argument is user-set during the call to s16mem_init(). */

typedef void(s16memcallback_t) (int, void *);

void s16mem_init ();
void * s16mem_alloc (unsigned long nbytes);
void * s16mem_calloc (size_t cnt, unsigned long nbytes);
char * s16mem_strdup (const char * str);
void s16mem_free (void * ap);

/* Creates a new service structure and returns a pointer to it. */
svc_t * s16_svc_object_new ();
/* Creates a new service instance for service object svc with name, and
 * returns its identifier. */
svc_id_t s16_inst_object_new (svc_t * svc, const char * name);
/* Creates a new default service instance for service object svc, and returns
 * its identifier. */
svc_id_t s16_inst_object_new_default (svc_t * svc);

/* Retrieves a string properties' value for a service object.
 * Returns either the string, or 0 on failure. */
const char * svc_object_get_property_string (svc_t * Svc, const char * key);
/* As above, but for an instance object. */
const char * inst_object_get_property_string (svc_instance_t * inst,
                                              const char * key);
/* Retrieves an integer properties' value for a service object.
 * Returns a pointer to the value, or 0 on failure. */
long * svc_object_get_property_int (svc_t * Svc, const char * key);
/* As above, but for an instance object. */
long * inst_object_get_property_int (svc_instance_t * inst, const char * key);

/* Sets a string property for a service object. */
void svc_object_set_property_string (svc_t * Svc, const char * key,
                                     const char * value);
/* Sets a string property for an instance object. */
void inst_object_set_property_string (svc_instance_t * inst, const char * key,
                                      const char * value);
/* Sets an integer property for a service object. */
void svc_object_set_property_int (svc_t * Svc, const char * key, long value);
/* Sets an integer property for an instance object. */
void inst_object_set_property_int (svc_instance_t * Svc, const char * key,
                                   long value);

/* These destroy, freeing all allocated memory, the relevant S16 type. */
void destroy_property (property_t * delProperty);
void destroy_properties_list (prop_list box);
void destroy_instance (svc_instance_t * delInstance);
void destroy_svc (svc_t * delSvc);
void destroy_svcs_list (svc_list box);

#define DestroyPropIfExists(list, name)                                        \
    property_t * Prop = prop_find_name (list, name);                           \
    if (Prop)                                                                  \
    {                                                                          \
        prop_list_del (list, Prop);                                            \
        destroy_property (Prop);                                               \
    }

#define StartsWith(text, prefix) !strncmp (text, prefix, strlen (prefix))

#ifdef __cplusplus
}
#endif

#endif
