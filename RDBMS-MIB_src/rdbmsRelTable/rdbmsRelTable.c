/*-------------------------------------------------------------------------
 * rdbmsRelTable.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsRelTable.c,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsRelTable.h"

#include <net-snmp/agent/mib_modules.h>

#include "rdbmsRelTable_interface.h"

oid rdbmsRelTable_oid[] = { RDBMSRELTABLE_OID };
int rdbmsRelTable_oid_size = OID_LENGTH(rdbmsRelTable_oid);

void initialize_table_rdbmsRelTable(void);


/**
 * Initializes the rdbmsRelTable module
 */
void
init_rdbmsRelTable(void)
{
    DEBUGMSGTL(("verbose:rdbmsRelTable:init_rdbmsRelTable","called\n"));

    /*
     * TODO:300:o: Perform rdbmsRelTable one-time module initialization.
     */
     
    /*
     * here we initialize all the tables we're planning on supporting
     */
    if (should_init("rdbmsRelTable"))
        initialize_table_rdbmsRelTable();

} /* init_rdbmsRelTable */

/**
 * Initialize the table rdbmsRelTable 
 *    (Define its contents and how it's structured)
 */
void
initialize_table_rdbmsRelTable(void)
{
    rdbmsRelTable_registration_ptr user_context;
    u_long flags;

    DEBUGMSGTL(("verbose:rdbmsRelTable:initialize_table_rdbmsRelTable","called\n"));

    /*
     * TODO:301:o: Perform rdbmsRelTable one-time table initialization.
     */

    /*
     * TODO:302:o: |->Initialize rdbmsRelTable user context
     * if you'd like to pass in a pointer to some data for this
     * table, allocate or set it up here.
     */
    /*
     * a netsnmp_data_list is a simple way to store void pointers. A simple
     * string token is used to add, find or remove pointers.
     */
    user_context = netsnmp_create_data_list("rdbmsRelTable", NULL, NULL);
    
    /*
     * No support for any flags yet, but in the future you would
     * set any flags here.
     */
    flags = 0;
    
    /*
     * call interface initialization code
     */
    _rdbmsRelTable_initialize_interface(user_context, flags);
} /* initialize_table_rdbmsRelTable */

/**
 * pre-request callback
 *
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_ERROR                : other error
 */
int
rdbmsRelTable_pre_request(rdbmsRelTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelTable_pre_request","called\n"));

    /*
     * TODO:510:o: Perform rdbmsRelTable pre-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsRelTable_pre_request */

/**
 * post-request callback
 *
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : other error (ignored)
 */
int
rdbmsRelTable_post_request(rdbmsRelTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelTable_post_request","called\n"));

    /*
     * TODO:511:o: Perform rdbmsRelTable pos-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsRelTable_post_request */


/** @{ */
