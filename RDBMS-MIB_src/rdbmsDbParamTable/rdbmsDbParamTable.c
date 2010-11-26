/*-------------------------------------------------------------------------
 * rdbmsDbParamTable.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbParamTable.c,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsDbParamTable.h"

#include <net-snmp/agent/mib_modules.h>

#include "rdbmsDbParamTable_interface.h"

oid rdbmsDbParamTable_oid[] = { RDBMSDBPARAMTABLE_OID };
int rdbmsDbParamTable_oid_size = OID_LENGTH(rdbmsDbParamTable_oid);

void initialize_table_rdbmsDbParamTable(void);


/**
 * Initializes the rdbmsDbParamTable module
 */
void
init_rdbmsDbParamTable(void)
{
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:init_rdbmsDbParamTable","called\n"));

    /*
     * TODO:300:o: Perform rdbmsDbParamTable one-time module initialization.
     */
     
    /*
     * here we initialize all the tables we're planning on supporting
     */
    if (should_init("rdbmsDbParamTable"))
        initialize_table_rdbmsDbParamTable();

} /* init_rdbmsDbParamTable */

/**
 * Initialize the table rdbmsDbParamTable 
 *    (Define its contents and how it's structured)
 */
void
initialize_table_rdbmsDbParamTable(void)
{
    rdbmsDbParamTable_registration_ptr user_context;
    u_long flags;

    DEBUGMSGTL(("verbose:rdbmsDbParamTable:initialize_table_rdbmsDbParamTable","called\n"));

    /*
     * TODO:301:o: Perform rdbmsDbParamTable one-time table initialization.
     */

    /*
     * TODO:302:o: |->Initialize rdbmsDbParamTable user context
     * if you'd like to pass in a pointer to some data for this
     * table, allocate or set it up here.
     */
    /*
     * a netsnmp_data_list is a simple way to store void pointers. A simple
     * string token is used to add, find or remove pointers.
     */
    user_context = netsnmp_create_data_list("rdbmsDbParamTable", NULL, NULL);
    
    /*
     * No support for any flags yet, but in the future you would
     * set any flags here.
     */
    flags = 0;
    
    /*
     * call interface initialization code
     */
    _rdbmsDbParamTable_initialize_interface(user_context, flags);
} /* initialize_table_rdbmsDbParamTable */

/**
 * pre-request callback
 *
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_ERROR                : other error
 */
int
rdbmsDbParamTable_pre_request(rdbmsDbParamTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamTable_pre_request","called\n"));

    /*
     * TODO:510:o: Perform rdbmsDbParamTable pre-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsDbParamTable_pre_request */

/**
 * post-request callback
 *
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : other error (ignored)
 */
int
rdbmsDbParamTable_post_request(rdbmsDbParamTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamTable_post_request","called\n"));

    /*
     * TODO:511:o: Perform rdbmsDbParamTable pos-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsDbParamTable_post_request */


/** @{ */
