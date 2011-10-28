/*-------------------------------------------------------------------------
 * rdbmsSrvTable.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvTable.c,v 1.4 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsSrvTable.h"

#include <net-snmp/agent/mib_modules.h>

#include "rdbmsSrvTable_interface.h"

oid rdbmsSrvTable_oid[] = { RDBMSSRVTABLE_OID };
int rdbmsSrvTable_oid_size = OID_LENGTH(rdbmsSrvTable_oid);

void initialize_table_rdbmsSrvTable(void);


/**
 * Initializes the rdbmsSrvTable module
 */
void
init_rdbmsSrvTable(void)
{
    DEBUGMSGTL(("verbose:rdbmsSrvTable:init_rdbmsSrvTable","called\n"));

    /*
     * TODO:300:o: Perform rdbmsSrvTable one-time module initialization.
     */

    /*
     * here we initialize all the tables we're planning on supporting
     */
    if (should_init("rdbmsSrvTable"))
        initialize_table_rdbmsSrvTable();

} /* init_rdbmsSrvTable */

/**
 * Initialize the table rdbmsSrvTable
 *    (Define its contents and how it's structured)
 */
void
initialize_table_rdbmsSrvTable(void)
{
    rdbmsSrvTable_registration_ptr user_context;
    u_long flags;

    DEBUGMSGTL(("verbose:rdbmsSrvTable:initialize_table_rdbmsSrvTable","called\n"));

    /*
     * TODO:301:o: Perform rdbmsSrvTable one-time table initialization.
     */

    /*
     * TODO:302:o: |->Initialize rdbmsSrvTable user context
     * if you'd like to pass in a pointer to some data for this
     * table, allocate or set it up here.
     */
    /*
     * a netsnmp_data_list is a simple way to store void pointers. A simple
     * string token is used to add, find or remove pointers.
     */
    user_context = netsnmp_create_data_list("rdbmsSrvTable", NULL, NULL);

    /*
     * No support for any flags yet, but in the future you would
     * set any flags here.
     */
    flags = 0;

    /*
     * call interface initialization code
     */
    _rdbmsSrvTable_initialize_interface(user_context, flags);
} /* initialize_table_rdbmsSrvTable */

/**
 * pre-request callback
 *
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_ERROR                : other error
 */
int
rdbmsSrvTable_pre_request(rdbmsSrvTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvTable_pre_request","called\n"));

    /*
     * TODO:510:o: Perform rdbmsSrvTable pre-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvTable_pre_request */

/**
 * post-request callback
 *
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : other error (ignored)
 */
int
rdbmsSrvTable_post_request(rdbmsSrvTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvTable_post_request","called\n"));

    /*
     * TODO:511:o: Perform rdbmsSrvTable pos-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvTable_post_request */


/** @{ */
