/*-------------------------------------------------------------------------
 * rdbmsDbTable.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable.c,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsDbTable.h"
#include "rdbmsDbTable_interface.h"

oid rdbmsDbTable_oid[] = { RDBMSDBTABLE_OID };
int rdbmsDbTable_oid_size = OID_LENGTH(rdbmsDbTable_oid);

void initialize_table_rdbmsDbTable(void);


/**
 * Initializes the rdbmsDbTable module
 */
void
init_rdbmsDbTable(void)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:init_rdbmsDbTable","called\n"));

    /*
     * TODO:300:o: Perform rdbmsDbTable one-time module initialization.
     */

    /*
     * here we initialize all the tables we're planning on supporting
     */
    if (should_init("rdbmsDbTable"))
        initialize_table_rdbmsDbTable();

} /* init_rdbmsDbTable */

/**
 * Initialize the table rdbmsDbTable
 *    (Define its contents and how it's structured)
 */
void
initialize_table_rdbmsDbTable(void)
{
    rdbmsDbTable_registration_ptr user_context;
    u_long flags;

    DEBUGMSGTL(("verbose:rdbmsDbTable:initialize_table_rdbmsDbTable","called\n"));

    /*
     * TODO:301:o: Perform rdbmsDbTable one-time table initialization.
     */

    /*
     * TODO:302:o: |->Initialize rdbmsDbTable user context
     * if you'd like to pass in a pointer to some data for this
     * table, allocate or set it up here.
     */
    /*
     * a netsnmp_data_list is a simple way to store void pointers. A simple
     * string token is used to add, find or remove pointers.
     */
    user_context = netsnmp_create_data_list("rdbmsDbTable", NULL, NULL);

    /*
     * No support for any flags yet, but in the future you would
     * set any flags here.
     */
    flags = 0;

    /*
     * call interface initialization code
     */
    _rdbmsDbTable_initialize_interface(user_context, flags);
} /* initialize_table_rdbmsDbTable */

/**
 * pre-request callback
 *
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_ERROR                : other error
 */
int
rdbmsDbTable_pre_request(rdbmsDbTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_pre_request","called\n"));

    /*
     * TODO:510:o: Perform rdbmsDbTable pre-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsDbTable_pre_request */

/**
 * post-request callback
 *
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : other error (ignored)
 */
int
rdbmsDbTable_post_request(rdbmsDbTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_post_request","called\n"));

    /*
     * TODO:511:o: Perform rdbmsDbTable pos-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsDbTable_post_request */


/** @{ */
