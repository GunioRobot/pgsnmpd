/*-------------------------------------------------------------------------
 * rdbmsDbLimitedResourceTable.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbLimitedResourceTable.c,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsDbLimitedResourceTable.h"

#include <net-snmp/agent/mib_modules.h>

#include "rdbmsDbLimitedResourceTable_interface.h"

oid rdbmsDbLimitedResourceTable_oid[] = { RDBMSDBLIMITEDRESOURCETABLE_OID };
int rdbmsDbLimitedResourceTable_oid_size = OID_LENGTH(rdbmsDbLimitedResourceTable_oid);

void initialize_table_rdbmsDbLimitedResourceTable(void);


/**
 * Initializes the rdbmsDbLimitedResourceTable module
 */
void
init_rdbmsDbLimitedResourceTable(void)
{
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:init_rdbmsDbLimitedResourceTable","called\n"));

    /*
     * TODO:300:o: Perform rdbmsDbLimitedResourceTable one-time module initialization.
     */

    /*
     * here we initialize all the tables we're planning on supporting
     */
    if (should_init("rdbmsDbLimitedResourceTable"))
        initialize_table_rdbmsDbLimitedResourceTable();

} /* init_rdbmsDbLimitedResourceTable */

/**
 * Initialize the table rdbmsDbLimitedResourceTable
 *    (Define its contents and how it's structured)
 */
void
initialize_table_rdbmsDbLimitedResourceTable(void)
{
    rdbmsDbLimitedResourceTable_registration_ptr user_context;
    u_long flags;

    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:initialize_table_rdbmsDbLimitedResourceTable","called\n"));

    /*
     * TODO:301:o: Perform rdbmsDbLimitedResourceTable one-time table initialization.
     */

    /*
     * TODO:302:o: |->Initialize rdbmsDbLimitedResourceTable user context
     * if you'd like to pass in a pointer to some data for this
     * table, allocate or set it up here.
     */
    /*
     * a netsnmp_data_list is a simple way to store void pointers. A simple
     * string token is used to add, find or remove pointers.
     */
    user_context = netsnmp_create_data_list("rdbmsDbLimitedResourceTable", NULL, NULL);

    /*
     * No support for any flags yet, but in the future you would
     * set any flags here.
     */
    flags = 0;

    /*
     * call interface initialization code
     */
    _rdbmsDbLimitedResourceTable_initialize_interface(user_context, flags);
} /* initialize_table_rdbmsDbLimitedResourceTable */

/**
 * pre-request callback
 *
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_ERROR                : other error
 */
int
rdbmsDbLimitedResourceTable_pre_request(rdbmsDbLimitedResourceTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceTable_pre_request","called\n"));

    /*
     * TODO:510:o: Perform rdbmsDbLimitedResourceTable pre-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceTable_pre_request */

/**
 * post-request callback
 *
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : other error (ignored)
 */
int
rdbmsDbLimitedResourceTable_post_request(rdbmsDbLimitedResourceTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceTable_post_request","called\n"));

    /*
     * TODO:511:o: Perform rdbmsDbLimitedResourceTable pos-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceTable_post_request */


/** @{ */
