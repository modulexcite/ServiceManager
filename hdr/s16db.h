#ifndef S16_DB_H_
#define S16_DB_H_

#include <string.h>
#include "s16.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SVC_IS_NULL(svc) (!svc || !strncmp (svc->name, "NULL", 4))

/* These routines below all return pointers, with one exception.
 * The exception - s16db_context_destroy - cannot fail.
 * A null pointer indicates failure in every other case. */

/* Creates an S16DB context, which is used to communicate with repositoryd.
 * Returns a handle to the context, which is the first argument to all other
 * s16db functions. */
CLIENT * s16db_context_create ();
/* Destroys an S16DB context. */
void s16db_context_destroy (CLIENT * clnt);

/* Inserts a new service in the configuration repository.
 * It is empty, except for its name. */
svc_id_t * s16db_svc_insert (CLIENT * clnt, char const * name);
/* Installs an already-created service object into the repository. */
svc_id_t * s16db_svc_install (CLIENT * clnt, svc_t * svc);

/* Deletes a service from the repository by its numeric identifier.
 * The integer pointer points to a value in memory: 1 for failure, or 0 for
 * success. */

int * s16db_svc_delete (CLIENT * clnt, svc_id_t id);
/* Retrieves a service by its identifier. */
svc_t * s16db_svc_retrieve (CLIENT * clnt, svc_id_t id);
/* Retrieves a service by its name or FMRI. */
svc_t * s16db_svc_retrieve_by_name (CLIENT * clnt, char * name);
/* Retrieves a list of all services. */
svc_list s16db_svc_retrieve_all (CLIENT * clnt);

/* Sets an integer property on a service; integer pointer points to memory
 * holding value 0 for success and 1 for failure (e.g. no such service.) */
int * s16db_svc_set_property_int (CLIENT * clnt, svc_id_t id, char const * key,
                                  long value);
/* Sets a string property on a service; return types as above. */
int * s16db_svc_set_property_string (CLIENT * clnt, svc_id_t id,
                                     char const * key, char const * value);

/* Creates a service instance for a service of identifier id;
 * return types as in svc_set_property_int. */
svc_id_t * s16db_instance_create (CLIENT * clnt, svc_id_t id,
                                  const char * name);
/* Sets the status of an instance (i_id) of a service (id). Return type
 * as above. */
int * s16db_instance_set_status (CLIENT * clnt, svc_id_t id, svc_id_t i_id,
                                 svc_state_e status);

/* Registers a handle for configuration notification.
 * Returned integer pointer points to memory holding the port number you should
 * now listen on, or 0 for failure. */
int * s16db_config_register (CLIENT * clnt);
/* As above, but with a port already specified. Make sure this port is unique
 * to you and not in the transient range. */
void * s16db_config_register_port (CLIENT * clnt, int port);
/* Register for status updates to an instance (i_id_ of a service (id).
 * Usual return format. */
int * s16db_config_subscribe_status (CLIENT * clnt, int p, svc_id_t id,
                                     svc_id_t i_id);
/* Register for new services appearing in the repository. Usual return
 * format. */
int * s16db_config_subscribe_services (CLIENT * clnt, int p);

/* Marshalling routines.
 * These are used to convert from the RPC serialisation of S16 types back to
 * the S16 types and lists thereof, and vice versa. */
rpc_property_t property_to_rpc_property (property_t * prop);
rpc_property_t * property_list_to_rpc_property_array (prop_list box);
rpc_svc_instance_t svc_instance_to_rpc_svc_instance (svc_instance_t * inst);
rpc_svc_t svc_to_rpc_svc (svc_t * svc);
rpc_svc_t * svc_list_to_rpc_svc_array (svc_list box);

property_t * rpc_property_to_property (rpc_property_t * rprop);
prop_list rpc_property_array_to_property_list (rpc_property_t rplist[],
                                               unsigned int length);
svc_instance_t * rpc_svc_instance_to_svc_instance (rpc_svc_instance_t * rinst);
svc_t * rpc_svc_to_svc (rpc_svc_t * rsvc);
svc_list rpc_svc_array_to_svc_list (rpc_svc_array_t * svcArray);

#ifdef __cplusplus
}
#endif

#endif
