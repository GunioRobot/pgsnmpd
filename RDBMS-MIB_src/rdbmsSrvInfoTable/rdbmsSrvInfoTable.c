/*-------------------------------------------------------------------------
 * rdbmsSrvInfoTable.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvInfoTable.c,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsSrvInfoTable.h"

/*#include <net-snmp/agent/mib_modules.h> */

#include "rdbmsSrvInfoTable_interface.h"

oid rdbmsSrvInfoTable_oid[] = { RDBMSSRVINFOTABLE_OID };
int rdbmsSrvInfoTable_oid_size = OID_LENGTH(rdbmsSrvInfoTable_oid);

void initialize_table_rdbmsSrvInfoTable(void);


/**
 * Initializes the rdbmsSrvInfoTable module
 */
void
init_rdbmsSrvInfoTable(void)
{
    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:init_rdbmsSrvInfoTable","called\n"));

    /*
     * TODO:300:o: Perform rdbmsSrvInfoTable one-time module initialization.
     */
     
    /*
     * here we initialize all the tables we're planning on supporting
     */
    if (should_init("rdbmsSrvInfoTable"))
        initialize_table_rdbmsSrvInfoTable();

} /* init_rdbmsSrvInfoTable */

/**
 * Initialize the table rdbmsSrvInfoTable 
 *    (Define its contents and how it's structured)
 */
void
initialize_table_rdbmsSrvInfoTable(void)
{
    rdbmsSrvInfoTable_registration_ptr user_context;
    u_long flags;

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:initialize_table_rdbmsSrvInfoTable","called\n"));

    /*
     * TODO:301:o: Perform rdbmsSrvInfoTable one-time table initialization.
     */

    /*
     * TODO:302:o: |->Initialize rdbmsSrvInfoTable user context
     * if you'd like to pass in a pointer to some data for this
     * table, allocate or set it up here.
     */
    /*
     * a netsnmp_data_list is a simple way to store void pointers. A simple
     * string token is used to add, find or remove pointers.
     */
    user_context = netsnmp_create_data_list("rdbmsSrvInfoTable", NULL, NULL);
    
    /*
     * No support for any flags yet, but in the future you would
     * set any flags here.
     */
    flags = 0;
    
    /*
     * call interface initialization code
     */
    _rdbmsSrvInfoTable_initialize_interface(user_context, flags);
} /* initialize_table_rdbmsSrvInfoTable */

/**
 * pre-request callback
 *
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_ERROR                : other error
 */
int
rdbmsSrvInfoTable_pre_request(rdbmsSrvInfoTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_pre_request","called\n"));

    /*
     * TODO:510:o: Perform rdbmsSrvInfoTable pre-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvInfoTable_pre_request */

/**
 * post-request callback
 *
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : other error (ignored)
 */
int
rdbmsSrvInfoTable_post_request(rdbmsSrvInfoTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_post_request","called\n"));

    /*
     * TODO:511:o: Perform rdbmsSrvInfoTable pos-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvInfoTable_post_request */


/** @{ */
