/*-------------------------------------------------------------------------
 * rdbmsSrvParamTable.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvParamTable.c,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsSrvParamTable.h"

#include <net-snmp/agent/mib_modules.h>

#include "rdbmsSrvParamTable_interface.h"

oid rdbmsSrvParamTable_oid[] = { RDBMSSRVPARAMTABLE_OID };
int rdbmsSrvParamTable_oid_size = OID_LENGTH(rdbmsSrvParamTable_oid);

void initialize_table_rdbmsSrvParamTable(void);


/**
 * Initializes the rdbmsSrvParamTable module
 */
void
init_rdbmsSrvParamTable(void)
{
    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:init_rdbmsSrvParamTable","called\n"));

    /*
     * TODO:300:o: Perform rdbmsSrvParamTable one-time module initialization.
     */

    /*
     * here we initialize all the tables we're planning on supporting
     */
    if (should_init("rdbmsSrvParamTable"))
        initialize_table_rdbmsSrvParamTable();

} /* init_rdbmsSrvParamTable */

/**
 * Initialize the table rdbmsSrvParamTable
 *    (Define its contents and how it's structured)
 */
void
initialize_table_rdbmsSrvParamTable(void)
{
    rdbmsSrvParamTable_registration_ptr user_context;
    u_long flags;

    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:initialize_table_rdbmsSrvParamTable","called\n"));

    /*
     * TODO:301:o: Perform rdbmsSrvParamTable one-time table initialization.
     */

    /*
     * TODO:302:o: |->Initialize rdbmsSrvParamTable user context
     * if you'd like to pass in a pointer to some data for this
     * table, allocate or set it up here.
     */
    /*
     * a netsnmp_data_list is a simple way to store void pointers. A simple
     * string token is used to add, find or remove pointers.
     */
    user_context = netsnmp_create_data_list("rdbmsSrvParamTable", NULL, NULL);

    /*
     * No support for any flags yet, but in the future you would
     * set any flags here.
     */
    flags = 0;

    /*
     * call interface initialization code
     */
    _rdbmsSrvParamTable_initialize_interface(user_context, flags);
} /* initialize_table_rdbmsSrvParamTable */

/**
 * pre-request callback
 *
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_ERROR                : other error
 */
int
rdbmsSrvParamTable_pre_request(rdbmsSrvParamTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_pre_request","called\n"));

    /*
     * TODO:510:o: Perform rdbmsSrvParamTable pre-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvParamTable_pre_request */

/**
 * post-request callback
 *
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : other error (ignored)
 */
int
rdbmsSrvParamTable_post_request(rdbmsSrvParamTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_post_request","called\n"));

    /*
     * TODO:511:o: Perform rdbmsSrvParamTable pos-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvParamTable_post_request */


/** @{ */
