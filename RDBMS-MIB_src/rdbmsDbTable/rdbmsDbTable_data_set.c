/*-------------------------------------------------------------------------
 * rdbmsDbTable_data_set.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable_data_set.c,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsDbTable.h"


/** @defgroup data_set data_set: Routines to set data
 *
 * These routines are used to set the value for individual objects. The
 * row context is passed, along with the new value.
 * 
 * @{
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table rdbmsDbTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbTable is subid 1 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.1, length: 9
*/
    /*
     * NOTE: if you update this chart, please update the versions in
     *       local/mib2c-conf.d/parent-set.m2i
     *       agent/mibgroup/helpers/baby_steps.c
     * while you're at it.
     */
    /*
     ***********************************************************************
     * Baby Steps Flow Chart (2004.06.05)                                  *
     *                                                                     *
     * +--------------+    +================+    U = unconditional path    *
     * |optional state|    ||required state||    S = path for success      *
     * +--------------+    +================+    E = path for error        *
     ***********************************************************************
     *
     *                        +--------------+
     *                        |     pre      |
     *                        |   request    |
     *                        +--------------+
     *                               | U
     *                        +==============+
     *       +----------------||  object    ||
     *       |              E ||  lookup    ||
     *       |                +==============+
     *       |                       | S
     *       |                +==============+
     *       |              E ||   check    ||
     *       |<---------------||   values   ||
     *       |                +==============+
     *       |                       | S
     *       |                +==============+
     *       |       +<-------||   undo     ||
     *       |       |      E ||   setup    ||
     *       |       |        +==============+
     *       |       |               | S
     *       |       |        +==============+
     *       |       |        ||    set     ||-------------------------->+
     *       |       |        ||   value    || E                         |
     *       |       |        +==============+                           |
     *       |       |               | S                                 |
     *       |       |        +--------------+                           |
     *       |       |        |    check     |-------------------------->|
     *       |       |        |  consistency | E                         |
     *       |       |        +--------------+                           |
     *       |       |               | S                                 |
     *       |       |        +==============+         +==============+  |
     *       |       |        ||   commit   ||-------->||     undo   ||  |
     *       |       |        ||            || E       ||    commit  ||  |
     *       |       |        +==============+         +==============+  |
     *       |       |               | S                     U |<--------+
     *       |       |        +--------------+         +==============+
     *       |       |        | irreversible |         ||    undo    ||
     *       |       |        |    commit    |         ||     set    ||
     *       |       |        +--------------+         +==============+
     *       |       |               | U                     U |
     *       |       +-------------->|<------------------------+
     *       |                +==============+
     *       |                ||   undo     ||
     *       |                ||  cleanup   ||
     *       |                +==============+
     *       +---------------------->| U
     *                        +--------------+
     *                        |    post      |
     *                        |   request    |
     *                        +--------------+
     *
     */

/**
 * Setup up context with information needed to undo a set request.
 *
 * This function will be called before the individual node undo setup
 * functions are called. If you need to do any undo setup that is not
 * related to a specific column, you can do it here.
 *
 * Note that an individual node's undo_setup function will only be called
 * if that node is being set to a new value.
 *
 * If there is any setup specific to a particular column (e.g. allocating
 * memory for a string), you should do that setup in the node's undo_setup
 * function, so it won't be done unless it is necessary.
 *
 * @param rowreq_ctx
 *        Pointer to the table context (rdbmsDbTable_rowreq_ctx)
 *
 * @retval MFD_SUCCESS : success
 * @retval MFD_ERROR   : error. set will fail.
 */
int
rdbmsDbTable_undo_setup( rdbmsDbTable_rowreq_ctx *rowreq_ctx)
{
    int rc = MFD_SUCCESS;

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_undo_setup","called\n"));

    /** we should have a non-NULL pointer */
    netsnmp_assert( NULL != rowreq_ctx );

    /*
     * TODO:451:M: |-> Setup rdbmsDbTable undo.
     * set up rdbmsDbTable undo information, in preparation for a set.
     */

    return rc;
} /* rdbmsDbTable_undo_setup */

/**
 * Cleanup up context undo information.
 *
 * This function will be called after set/commit processing. If you
 * allocated any resources in undo_setup, this is the place to release
 * those resources.
 *
 * This function is called regardless of the success or failure of the set
 * request. If you need to perform different steps for cleanup depending
 * on success or failure, you can add a flag to the rowreq_ctx.
 *
 * @param rowreq_ctx
 *        Pointer to the table context (rdbmsDbTable_rowreq_ctx)
 *
 * @retval MFD_SUCCESS : success
 * @retval MFD_ERROR   : error
 */
int
rdbmsDbTable_undo_cleanup( rdbmsDbTable_rowreq_ctx *rowreq_ctx)
{
    int rc = MFD_SUCCESS;

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_undo_cleanup","called\n"));

    /** we should have a non-NULL pointer */
    netsnmp_assert( NULL != rowreq_ctx );

    /*
     * TODO:452:M: |-> Cleanup rdbmsDbTable undo.
     */

    return rc;
} /* rdbmsDbTable_undo_cleanup */

/**
 * commit new values.
 *
 * At this point, you should have done everything you can to ensure that
 * this commit will not fail.
 *
 * Should you need different behavior depending on which columns were
 * set, rowreq_ctx->column_set_flags will indicate which writeable columns were
 * set. The definitions for the FLAG_* bits can be found in
 * rdbmsDbTable_oids.h.
 * A new row will have the MFD_ROW_CREATED bit set in rowreq_flags.
 *
 * @param rdbmsDbTable_rowreq_ctx
 *        Pointer to the users context.
 *
 * @retval MFD_SUCCESS : success
 * @retval MFD_ERROR   : error
 */
int
rdbmsDbTable_commit( rdbmsDbTable_rowreq_ctx *rowreq_ctx)
{
    int rc = MFD_SUCCESS;
    int             save_flags;

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_commit","called\n"));

    /** we should have a non-NULL pointer */
    netsnmp_assert( NULL != rowreq_ctx );

    /*
     * save flags, then clear until we actually do something
     */
    save_flags = rowreq_ctx->column_set_flags;
    rowreq_ctx->column_set_flags = 0;

    /*
     * commit rdbmsDbTable data
     * 1) check the column's flag in save_flags to see if it was set.
     * 2) clear the flag when you handle that column
     * 3) set the column's flag in column_set_flags if it needs undo
     *    processing in case of a failure.
     */
    if (save_flags & FLAG_RDBMSDBCONTACT) {
       save_flags &= ~FLAG_RDBMSDBCONTACT; /* clear rdbmsDbContact */
       /*
        * TODO:482:o: |-> commit column rdbmsDbContact.
        */
       rc = -1;
       if(-1 == rc) {
           snmp_log(LOG_ERR,"rdbmsDbTable column rdbmsDbContact commit failed\n");
       }
       else {
            /*
             * set flag, in case we need to undo rdbmsDbContact
             */
            rowreq_ctx->column_set_flags |= FLAG_RDBMSDBCONTACT;
       }
    }

    if (save_flags) {
       snmp_log(LOG_ERR, "unhandled columns (0x%x) in commit\n", save_flags);
       return MFD_ERROR;
    }

    return rc;
} /* rdbmsDbTable_commit */

/**
 * undo commit new values.
 *
 * Should you need different behavior depending on which columns were
 * set, rowreq_ctx->column_set_flags will indicate which writeable columns were
 * set. The definitions for the FLAG_* bits can be found in
 * rdbmsDbTable_oids.h.
 * A new row will have the MFD_ROW_CREATED bit set in rowreq_flags.
 *
 * @param rdbmsDbTable_rowreq_ctx
 *        Pointer to the users context.
 *
 * @retval MFD_SUCCESS : success
 * @retval MFD_ERROR   : error
 */
int
rdbmsDbTable_undo_commit( rdbmsDbTable_rowreq_ctx *rowreq_ctx)
{
    int rc = MFD_SUCCESS;

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_undo_commit","called\n"));

    /** we should have a non-NULL pointer */
    netsnmp_assert( NULL != rowreq_ctx );

    /*
     * TODO:485:M: |-> Undo rdbmsDbTable commit.
     * check the column's flag in rowreq_ctx->column_set_flags to see
     * if it was set during commit, then undo it.
     *
     * eg: if (rowreq_ctx->column_set_flags & FLAG_) {}
     */

    return rc;
} /* rdbmsDbTable_undo_commit */

/*
 * TODO:420:r: Implement rdbmsDbTable index validation.
 */
/*
 * TODO:440:M: Implement rdbmsDbTable node value checks.
 * TODO:450:M: Implement rdbmsDbTable undo functions.
 * TODO:460:M: Implement rdbmsDbTable set functions.
 * TODO:480:M: Implement rdbmsDbTable commit functions.
 */
/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbEntry.rdbmsDbContact
 * rdbmsDbContact is subid 5 of rdbmsDbEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.6.1.2.1.39.1.1.1.5
 * Description:
The textual identification of the contact person for this
           managed database, together with information on how to contact
           this person.

           Note: if there is no server associated with this database, an
           agent may need to keep this in other persistent storage,
           e.g., a configuration file.

           Note that a compliant agent does not need to
           allow write access to this object.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 1      hashint   1
 *   settable   1
 *   hint: 255a
 *
 * Ranges:  0 - 255;
 *
 * Its syntax is DisplayString (based on perltype OCTETSTR)
 * The net-snmp type is ASN_OCTET_STR. The C type decl is char (char)
 * This data type requires a length.  (Max 255)
 */
/**
 * Check that the proposed new value is potentially valid.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbContact_val_ptr
 *        A char containing the new value.
 * @param rdbmsDbContact_val_ptr_len
 *        The size (in bytes) of the data pointed to by rdbmsDbContact_val_ptr
 *
 * @retval MFD_SUCCESS        : incoming value is legal
 * @retval MFD_NOT_VALID_NOW  : incoming value is not valid now
 * @retval MFD_NOT_VALID_EVER : incoming value is never valid
 *
 * This is the place to check for requirements that are not
 * expressed in the mib syntax (for example, a requirement that
 * is detailed in the description for an object).
 *
 * You should check that the requested change between the undo value and the
 * new value is legal (ie, the transistion from one value to another
 * is legal).
 *      
 *@note
 * This check is only to determine if the new value
 * is \b potentially valid. This is the first check of many, and
 * is one of the simplest ones.
 * 
 *@note
 * this is not the place to do any checks for values
 * which depend on some other value in the mib. Those
 * types of checks should be done in the
 * rdbmsDbTable_check_dependencies() function.
 *
 * The following checks have already been done for you:
 *    The syntax is ASN_OCTET_STR
 *    The length is in (one of) the range set(s):  0 - 255
 *
 * If there a no other checks you need to do, simply return MFD_SUCCESS.
 *
 */
int
rdbmsDbContact_check_value( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char *rdbmsDbContact_val_ptr,  size_t rdbmsDbContact_val_ptr_len)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbContact_check_value","called\n"));

    /** should never get a NULL pointer */
    netsnmp_assert(NULL != rowreq_ctx);
    netsnmp_assert(NULL != rdbmsDbContact_val_ptr);

    /*
     * TODO:441:o: |-> Check for valid rdbmsDbContact value.
     */

    return MFD_SUCCESS; /* rdbmsDbContact value not illegal */
} /* rdbmsDbContact_check_value */

/**
 * Save old value information
 *
 * @param rowreq_ctx
 *        Pointer to the table context (rdbmsDbTable_rowreq_ctx)
 *
 * @retval MFD_SUCCESS : success
 * @retval MFD_ERROR   : error. set will fail.
 *
 * This function will be called after the table level undo setup function
 * rdbmsDbTable_undo_setup has been called.
 *
 *@note
 * this function will only be called if a new value is set for this column.
 *
 * If there is any setup specific to a particular column (e.g. allocating
 * memory for a string), you should do that setup in this function, so it
 * won't be done unless it is necessary.
 */
int
rdbmsDbContact_undo_setup( rdbmsDbTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbContact_undo_setup","called\n"));

    /** should never get a NULL pointer */
    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:455:o: |-> Setup rdbmsDbContact undo.
     */
    /*
     * copy rdbmsDbContact and rdbmsDbContact_len data
     * set rowreq_ctx->undo->rdbmsDbContact from rowreq_ctx->data.rdbmsDbContact
     */
    memcpy( rowreq_ctx->undo->rdbmsDbContact, rowreq_ctx->data.rdbmsDbContact,
            (rowreq_ctx->data.rdbmsDbContact_len * sizeof(rowreq_ctx->undo->rdbmsDbContact[0])));
    rowreq_ctx->undo->rdbmsDbContact_len = rowreq_ctx->data.rdbmsDbContact_len;


    return MFD_SUCCESS;
} /* rdbmsDbContact_undo_setup */

/**
 * Set the new value.
 *
 * @param rowreq_ctx
 *        Pointer to the users context. You should know how to
 *        manipulate the value from this object.
 * @param rdbmsDbContact_val_ptr
 *        A char containing the new value.
 * @param rdbmsDbContact_val_ptr_len
 *        The size (in bytes) of the data pointed to by rdbmsDbContact_val_ptr
 */
int
rdbmsDbContact_set( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char *rdbmsDbContact_val_ptr,  size_t rdbmsDbContact_val_ptr_len )
{

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbContact_set","called\n"));

    /** should never get a NULL pointer */
    netsnmp_assert(NULL != rowreq_ctx);
    netsnmp_assert(NULL != rdbmsDbContact_val_ptr);

/*
 * TODO:245:o: |-> Implement rdbmsDbContact reverse mapping.
 * If the values for your data type don't exactly match the
 * possible values defined by the mib, you should map them here.
 */
    /*
     * TODO:461:M: |-> Set rdbmsDbContact value.
     * set rdbmsDbContact value in rowreq_ctx->data
     */
    memcpy( rowreq_ctx->data.rdbmsDbContact, rdbmsDbContact_val_ptr, rdbmsDbContact_val_ptr_len );
    rowreq_ctx->data.rdbmsDbContact_len = rdbmsDbContact_val_ptr_len / sizeof(rdbmsDbContact_val_ptr[0]);

    return MFD_SUCCESS;
} /* rdbmsDbContact_set */

/**
 * undo the previous set.
 *
 * @param rowreq_ctx
 *        Pointer to the users context.
 */
int
rdbmsDbContact_undo( rdbmsDbTable_rowreq_ctx *rowreq_ctx)
{

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbContact_undo","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:456:o: |-> Clean up rdbmsDbContact undo.
     */
    /*
     * copy rdbmsDbContact and rdbmsDbContact_len data
     * set rowreq_ctx->data.rdbmsDbContact from rowreq_ctx->undo->rdbmsDbContact
     */
    memcpy( rowreq_ctx->data.rdbmsDbContact, rowreq_ctx->undo->rdbmsDbContact,
            (rowreq_ctx->undo->rdbmsDbContact_len * sizeof(rowreq_ctx->data.rdbmsDbContact[0])));
    rowreq_ctx->data.rdbmsDbContact_len = rowreq_ctx->undo->rdbmsDbContact_len;

    
    return MFD_SUCCESS;
} /* rdbmsDbContact_undo */

/**
 * check dependencies
 *
 * This is useful for for tables which have dependencies between columns
 * (or rows, or tables). For example, two columns allocating a percentage
 * of something add up 100%.
 *
 * Should you need different behavior depending on which columns were
 * set, rowreq_ctx->column_set_flags will indicate which writeable columns were
 * set. The definitions for the FLAG_* bits can be found in
 * rdbmsDbTable_oids.h.
 * A new row will have the MFD_ROW_CREATED bit set in rowreq_flags.
 *
 * @retval MFD_SUCCESS all the changes to the row are legal
 * @retval MFD_ERROR   one or more changes are not legal
 *
 * (see README-table-rdbmsDbTable if you don't have dependencies)
 */
int
rdbmsDbTable_check_dependencies(rdbmsDbTable_rowreq_ctx *rowreq_ctx)
{
    int rc = MFD_SUCCESS;
    
    DEBUGMSGTL(("internal:rdbmsDbTable:rdbmsDbTable_check_dependencies","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:470:o: Check rdbmsDbTable row dependencies.
     * check that all new value are legal and consistent with each other
     */
    return rc;
} /* rdbmsDbTable_check_dependencies */

/** @} */
