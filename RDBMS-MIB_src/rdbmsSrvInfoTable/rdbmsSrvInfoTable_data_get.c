/*-------------------------------------------------------------------------
 * rdbmsSrvInfoTable_data_get.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvInfoTable_data_get.c,v 1.4 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsSrvInfoTable.h"


/** @defgroup data_get data_get: Routines to get data
 *
 * TODO:230:M: Implement rdbmsSrvInfoTable get routines.
 * TODO:240:M: Implement rdbmsSrvInfoTable mapping routines (if any).
 *
 * These routine are used to get the value for individual objects. The
 * row context is passed, along with a pointer to the memory where the
 * value should be copied.
 *
 * @{
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table rdbmsSrvInfoTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvInfoTable is subid 6 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.6, length: 9
*/

/* ---------------------------------------------------------------------
 * TODO:200:r: Implement rdbmsSrvInfoTable data context functions.
 */

/**
 * set mib index(es)
 *
 * @param tbl_idx mib index structure
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 *
 * @remark
 *  This convenience function is useful for setting all the MIB index
 *  components with a single function call. It is assume that the C values
 *  have already been mapped from their native/rawformat to the MIB format.
 */
int
rdbmsSrvInfoTable_indexes_set_tbl_idx(rdbmsSrvInfoTable_mib_index *tbl_idx, long applIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_indexes_set_tbl_idx","called\n"));

    /* applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->applIndex = applIndex_val;


    return MFD_SUCCESS;
} /* rdbmsSrvInfoTable_indexes_set_tbl_idx */

/**
 * @internal
 * set row context indexes
 *
 * @param reqreq_ctx the row context that needs updated indexes
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 *
 * @remark
 *  This function sets the mib indexs, then updates the oid indexs
 *  from the mib index.
 */
int
rdbmsSrvInfoTable_indexes_set(rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, long applIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_indexes_set","called\n"));

    if(MFD_SUCCESS != rdbmsSrvInfoTable_indexes_set_tbl_idx(&rowreq_ctx->tbl_idx
                                   , applIndex_val
           ))
        return MFD_ERROR;

    /*
     * convert mib index to oid index
     */
    rowreq_ctx->oid_idx.len = sizeof(rowreq_ctx->oid_tmp) / sizeof(oid);
    if(0 != rdbmsSrvInfoTable_index_to_oid(&rowreq_ctx->oid_idx,
                                    &rowreq_ctx->tbl_idx)) {
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* rdbmsSrvInfoTable_indexes_set */


/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoStartupTime
 * rdbmsSrvInfoStartupTime is subid 1 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.1
 * Description:
The date and time at which this server was last started.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 1      hashint   1
 *   settable   0
 *   hint: 2d-1d-1d,1d:1d:1d.1d,1a1d:1d
 *
 * Ranges:  8, 11;
 *
 * Its syntax is DateAndTime (based on perltype OCTETSTR)
 * The net-snmp type is ASN_OCTET_STR. The C type decl is char (char)
 * This data type requires a length.  (Max 11)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoStartupTime.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoStartupTime_map(char **mib_rdbmsSrvInfoStartupTime_val_ptr_ptr, size_t *mib_rdbmsSrvInfoStartupTime_val_ptr_len_ptr, char *raw_rdbmsSrvInfoStartupTime_val_ptr, size_t raw_rdbmsSrvInfoStartupTime_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsSrvInfoStartupTime_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsSrvInfoStartupTime_val_ptr_ptr) && (NULL != mib_rdbmsSrvInfoStartupTime_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoStartupTime_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsSrvInfoStartupTime non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsSrvInfoStartupTime_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsSrvInfoStartupTime_val_ptr_ptr) || (*mib_rdbmsSrvInfoStartupTime_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsSrvInfoStartupTime_val_ptr_ptr = realloc( *mib_rdbmsSrvInfoStartupTime_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsSrvInfoStartupTime_val_ptr_ptr));
        if(NULL == *mib_rdbmsSrvInfoStartupTime_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsSrvInfoStartupTime_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsSrvInfoStartupTime_val_ptr_ptr, raw_rdbmsSrvInfoStartupTime_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsSrvInfoStartupTime_map */

/**
 * Extract the current value of the rdbmsSrvInfoStartupTime data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoStartupTime_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsSrvInfoStartupTime_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsSrvInfoStartupTime.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsSrvInfoStartupTime_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsSrvInfoStartupTime_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsSrvInfoStartupTime_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvInfoStartupTime_val_ptr_ptr, size_t *rdbmsSrvInfoStartupTime_val_ptr_len_ptr )
{
	int rc;
   /** we should have a pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsSrvInfoStartupTime_val_ptr_ptr) && (NULL != *rdbmsSrvInfoStartupTime_val_ptr_ptr));
   netsnmp_assert( (NULL != rdbmsSrvInfoStartupTime_val_ptr_len_ptr) && ((* rdbmsSrvInfoStartupTime_val_ptr_len_ptr) >= 11));

   /* call convenience function to set data */
   rc = netsnmp_dateandtime_set_buf_from_vars((u_char *)*rdbmsSrvInfoStartupTime_val_ptr_ptr, rdbmsSrvInfoStartupTime_val_ptr_len_ptr,
	rowreq_ctx->data.startupYear,
	rowreq_ctx->data.startupMonth,
	rowreq_ctx->data.startupDay,
	rowreq_ctx->data.startupHour,
	rowreq_ctx->data.startupMinutes,
	rowreq_ctx->data.startupSeconds,
	rowreq_ctx->data.startupDeciSeconds,
	rowreq_ctx->data.startupUtcOffsetDirection,
	rowreq_ctx->data.startupUtcOffsetHours,
	rowreq_ctx->data.startupUtcOffsetMinutes);
   if(rc != SNMP_ERR_NOERROR)
      return rc;


    return MFD_SUCCESS;
} /* rdbmsSrvInfoStartupTime_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoFinishedTransactions
 * rdbmsSrvInfoFinishedTransactions is subid 2 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.2
 * Description:
The number of transactions visible to this server that have
           been completed by either commit or abort.  Some database
           operations, such as read-only queries, may not result in the
           creation of a transaction.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is GAUGE (based on perltype GAUGE)
 * The net-snmp type is ASN_GAUGE. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoFinishedTransactions.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoFinishedTransactions_map(u_long *mib_rdbmsSrvInfoFinishedTransactions_val_ptr, u_long raw_rdbmsSrvInfoFinishedTransactions_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoFinishedTransactions_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoFinishedTransactions_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoFinishedTransactions mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoFinishedTransactions_val_ptr) = raw_rdbmsSrvInfoFinishedTransactions_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoFinishedTransactions_map */

/**
 * Extract the current value of the rdbmsSrvInfoFinishedTransactions data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoFinishedTransactions_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoFinishedTransactions_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoFinishedTransactions_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoFinishedTransactions_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoFinishedTransactions_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoFinishedTransactions data.
 * set (* rdbmsSrvInfoFinishedTransactions_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoFinishedTransactions_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoFinishedTransactions;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoFinishedTransactions_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoDiskReads
 * rdbmsSrvInfoDiskReads is subid 3 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.3
 * Description:
The total number of reads of database files issued to the
           operating system by this server since startup.  Numbers are
           not comparable between products.  What constitutes a
           readand how it is accounted is product-specific.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER (based on perltype COUNTER)
 * The net-snmp type is ASN_COUNTER. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoDiskReads.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoDiskReads_map(u_long *mib_rdbmsSrvInfoDiskReads_val_ptr, u_long raw_rdbmsSrvInfoDiskReads_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoDiskReads_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoDiskReads_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoDiskReads mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoDiskReads_val_ptr) = raw_rdbmsSrvInfoDiskReads_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoDiskReads_map */

/**
 * Extract the current value of the rdbmsSrvInfoDiskReads data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoDiskReads_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoDiskReads_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoDiskReads_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoDiskReads_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoDiskReads_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoDiskReads data.
 * set (* rdbmsSrvInfoDiskReads_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoDiskReads_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoDiskReads;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoDiskReads_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoLogicalReads
 * rdbmsSrvInfoLogicalReads is subid 4 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.4
 * Description:
The total number of logical reads of database files made
           internally by this server since startup.  The values of this
           object and those of rdbmsSrvInfoDiskReads reveal the effect
           of caching on read operation. Numbers are not comparable
           between products, and may only be meaningful when aggregated
           across all servers sharing a common cache.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER (based on perltype COUNTER)
 * The net-snmp type is ASN_COUNTER. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoLogicalReads.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoLogicalReads_map(u_long *mib_rdbmsSrvInfoLogicalReads_val_ptr, u_long raw_rdbmsSrvInfoLogicalReads_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoLogicalReads_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoLogicalReads_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoLogicalReads mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoLogicalReads_val_ptr) = raw_rdbmsSrvInfoLogicalReads_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoLogicalReads_map */

/**
 * Extract the current value of the rdbmsSrvInfoLogicalReads data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoLogicalReads_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoLogicalReads_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoLogicalReads_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoLogicalReads_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoLogicalReads_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoLogicalReads data.
 * set (* rdbmsSrvInfoLogicalReads_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoLogicalReads_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoLogicalReads;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoLogicalReads_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoDiskWrites
 * rdbmsSrvInfoDiskWrites is subid 5 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.5
 * Description:
The total number of writes to database files issued to the
           operating system by this server since startup.  Numbers are
           not comparable between products.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER (based on perltype COUNTER)
 * The net-snmp type is ASN_COUNTER. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoDiskWrites.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoDiskWrites_map(u_long *mib_rdbmsSrvInfoDiskWrites_val_ptr, u_long raw_rdbmsSrvInfoDiskWrites_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoDiskWrites_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoDiskWrites_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoDiskWrites mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoDiskWrites_val_ptr) = raw_rdbmsSrvInfoDiskWrites_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoDiskWrites_map */

/**
 * Extract the current value of the rdbmsSrvInfoDiskWrites data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoDiskWrites_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoDiskWrites_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoDiskWrites_val_ptr )
{
	return MFD_SKIP;
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoDiskWrites_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoDiskWrites_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoDiskWrites data.
 * set (* rdbmsSrvInfoDiskWrites_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoDiskWrites_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoDiskWrites;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoDiskWrites_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoLogicalWrites
 * rdbmsSrvInfoLogicalWrites is subid 6 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.6
 * Description:
The total number of times parts of the database files have
           been marked 'dirty' and in need of writing to the disk.  This
           value and rdbmsSrvInfoDiskWrites give some indication of the
           effect of 'write-behind' strategies in reducing the number of
           disk writes compared to database operations.  Because the
           writes may be done by servers other than those marking the
           parts of the database files dirty, these values may only be
           meaningful when aggregated across all servers sharing a
           common cache.  Numbers are not comparable between products.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER (based on perltype COUNTER)
 * The net-snmp type is ASN_COUNTER. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoLogicalWrites.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoLogicalWrites_map(u_long *mib_rdbmsSrvInfoLogicalWrites_val_ptr, u_long raw_rdbmsSrvInfoLogicalWrites_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoLogicalWrites_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoLogicalWrites_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoLogicalWrites mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoLogicalWrites_val_ptr) = raw_rdbmsSrvInfoLogicalWrites_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoLogicalWrites_map */

/**
 * Extract the current value of the rdbmsSrvInfoLogicalWrites data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoLogicalWrites_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoLogicalWrites_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoLogicalWrites_val_ptr )
{
	return MFD_SKIP;
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoLogicalWrites_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoLogicalWrites_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoLogicalWrites data.
 * set (* rdbmsSrvInfoLogicalWrites_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoLogicalWrites_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoLogicalWrites;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoLogicalWrites_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoPageReads
 * rdbmsSrvInfoPageReads is subid 7 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.7
 * Description:
The total number of pages in database files read by this
           server since startup.  'Pages' are product specific units of
           disk i/o operations.  This value, along with
           rdbmsSrvInfoDiskReads, reveals the effect of any grouping
           read-ahead that may be used to enhance performance of some
           queries, such as scans.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER (based on perltype COUNTER)
 * The net-snmp type is ASN_COUNTER. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoPageReads.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoPageReads_map(u_long *mib_rdbmsSrvInfoPageReads_val_ptr, u_long raw_rdbmsSrvInfoPageReads_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoPageReads_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoPageReads_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoPageReads mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoPageReads_val_ptr) = raw_rdbmsSrvInfoPageReads_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoPageReads_map */

/**
 * Extract the current value of the rdbmsSrvInfoPageReads data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoPageReads_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoPageReads_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoPageReads_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoPageReads_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoPageReads_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoPageReads data.
 * set (* rdbmsSrvInfoPageReads_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoPageReads_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoPageReads;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoPageReads_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoPageWrites
 * rdbmsSrvInfoPageWrites is subid 8 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.8
 * Description:
The total number of pages in database files written by this
           server since startup.  Pages are product-specific units of
           disk I/O.  This value, with rdbmsSrvInfoDiskWrites, shows the
           effect of write strategies that collapse logical writes of
           contiguous pages into single calls to the operating system.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER (based on perltype COUNTER)
 * The net-snmp type is ASN_COUNTER. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoPageWrites.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoPageWrites_map(u_long *mib_rdbmsSrvInfoPageWrites_val_ptr, u_long raw_rdbmsSrvInfoPageWrites_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoPageWrites_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoPageWrites_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoPageWrites mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoPageWrites_val_ptr) = raw_rdbmsSrvInfoPageWrites_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoPageWrites_map */

/**
 * Extract the current value of the rdbmsSrvInfoPageWrites data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoPageWrites_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoPageWrites_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoPageWrites_val_ptr )
{
	return MFD_SKIP;
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoPageWrites_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoPageWrites_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoPageWrites data.
 * set (* rdbmsSrvInfoPageWrites_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoPageWrites_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoPageWrites;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoPageWrites_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoDiskOutOfSpaces
 * rdbmsSrvInfoDiskOutOfSpaces is subid 9 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.9
 * Description:
The total number of times the server has been unable to
           obtain disk space that it wanted, since server startup.  This
           would be inspected by an agent on receipt of an
           rdbmsOutOfSpace trap.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER (based on perltype COUNTER)
 * The net-snmp type is ASN_COUNTER. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoDiskOutOfSpaces.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoDiskOutOfSpaces_map(u_long *mib_rdbmsSrvInfoDiskOutOfSpaces_val_ptr, u_long raw_rdbmsSrvInfoDiskOutOfSpaces_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoDiskOutOfSpaces_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoDiskOutOfSpaces_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoDiskOutOfSpaces mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoDiskOutOfSpaces_val_ptr) = raw_rdbmsSrvInfoDiskOutOfSpaces_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoDiskOutOfSpaces_map */

/**
 * Extract the current value of the rdbmsSrvInfoDiskOutOfSpaces data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoDiskOutOfSpaces_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoDiskOutOfSpaces_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoDiskOutOfSpaces_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoDiskOutOfSpaces_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoDiskOutOfSpaces_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoDiskOutOfSpaces data.
 * set (* rdbmsSrvInfoDiskOutOfSpaces_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoDiskOutOfSpaces_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoDiskOutOfSpaces;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoDiskOutOfSpaces_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoHandledRequests
 * rdbmsSrvInfoHandledRequests is subid 10 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.10
 * Description:
The total number of requests made to the server on inbound
           associations.  The meaning of 'requests' is product specific,
           and is not comparable between products.

           This is intended to encapsulate high level semantic
           operations between clients and servers, or between peers.
           For instance, one request might correspond to a 'select' or
           an 'insert' statement.  It is not intended to capture disk
           i/o described in rdbmsSrvInfoDiskReads and
           rdbmsSrvInfoDiskWrites.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER (based on perltype COUNTER)
 * The net-snmp type is ASN_COUNTER. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoHandledRequests.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoHandledRequests_map(u_long *mib_rdbmsSrvInfoHandledRequests_val_ptr, u_long raw_rdbmsSrvInfoHandledRequests_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoHandledRequests_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoHandledRequests_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoHandledRequests mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoHandledRequests_val_ptr) = raw_rdbmsSrvInfoHandledRequests_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoHandledRequests_map */

/**
 * Extract the current value of the rdbmsSrvInfoHandledRequests data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoHandledRequests_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoHandledRequests_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoHandledRequests_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoHandledRequests_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoHandledRequests_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoHandledRequests data.
 * set (* rdbmsSrvInfoHandledRequests_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoHandledRequests_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoHandledRequests;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoHandledRequests_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoRequestRecvs
 * rdbmsSrvInfoRequestRecvs is subid 11 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.11
 * Description:
The number of receive operations made processing any requests
           on inbound associations. The meaning of operations is product
           specific, and is not comparable between products.

           This is intended to capture lower-level i/o operations than
           shown by HandledRequests, between clients and servers, or
           between peers.  For instance, it might roughly correspond to
           the amount of data given with an 'insert' statement.  It is
           not intended to capture disk i/o described in
           rdbmsSrvInfoDiskReads and rdbmsSrvInfoDiskWrites.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER (based on perltype COUNTER)
 * The net-snmp type is ASN_COUNTER. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoRequestRecvs.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoRequestRecvs_map(u_long *mib_rdbmsSrvInfoRequestRecvs_val_ptr, u_long raw_rdbmsSrvInfoRequestRecvs_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoRequestRecvs_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoRequestRecvs_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoRequestRecvs mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoRequestRecvs_val_ptr) = raw_rdbmsSrvInfoRequestRecvs_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoRequestRecvs_map */

/**
 * Extract the current value of the rdbmsSrvInfoRequestRecvs data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoRequestRecvs_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoRequestRecvs_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoRequestRecvs_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoRequestRecvs_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoRequestRecvs_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoRequestRecvs data.
 * set (* rdbmsSrvInfoRequestRecvs_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoRequestRecvs_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoRequestRecvs;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoRequestRecvs_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoRequestSends
 * rdbmsSrvInfoRequestSends is subid 12 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.12
 * Description:
The number of send operations made processing requests
           handled on inbound associations.  The meaning of operations
           is product specific, and is not comparable between products.

           This is intended to capture lower-level i/o operations than
           shown by HandledRequests, between between clients and
           servers, or between peers.  It might roughly correspond to
           the number of rows returned by a 'select' statement.  It is
           not intended to capture disk i/o described in DiskReads.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER (based on perltype COUNTER)
 * The net-snmp type is ASN_COUNTER. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoRequestSends.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoRequestSends_map(u_long *mib_rdbmsSrvInfoRequestSends_val_ptr, u_long raw_rdbmsSrvInfoRequestSends_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoRequestSends_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoRequestSends_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoRequestSends mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoRequestSends_val_ptr) = raw_rdbmsSrvInfoRequestSends_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoRequestSends_map */

/**
 * Extract the current value of the rdbmsSrvInfoRequestSends data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoRequestSends_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoRequestSends_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoRequestSends_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoRequestSends_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoRequestSends_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoRequestSends data.
 * set (* rdbmsSrvInfoRequestSends_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoRequestSends_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoRequestSends;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoRequestSends_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoHighwaterInboundAssociations
 * rdbmsSrvInfoHighwaterInboundAssociations is subid 13 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.6.1.13
 * Description:
The greatest number of inbound associations that have been
           simultaneously open to this server since startup.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is GAUGE (based on perltype GAUGE)
 * The net-snmp type is ASN_GAUGE. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoHighwaterInboundAssociations.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoHighwaterInboundAssociations_map(u_long *mib_rdbmsSrvInfoHighwaterInboundAssociations_val_ptr, u_long raw_rdbmsSrvInfoHighwaterInboundAssociations_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoHighwaterInboundAssociations_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoHighwaterInboundAssociations_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoHighwaterInboundAssociations mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoHighwaterInboundAssociations_val_ptr) = raw_rdbmsSrvInfoHighwaterInboundAssociations_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoHighwaterInboundAssociations_map */

/**
 * Extract the current value of the rdbmsSrvInfoHighwaterInboundAssociations data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoHighwaterInboundAssociations_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoHighwaterInboundAssociations_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoHighwaterInboundAssociations_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoHighwaterInboundAssociations_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoHighwaterInboundAssociations_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoHighwaterInboundAssociations data.
 * set (* rdbmsSrvInfoHighwaterInboundAssociations_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoHighwaterInboundAssociations_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoHighwaterInboundAssociations;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoHighwaterInboundAssociations_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvInfoEntry.rdbmsSrvInfoMaxInboundAssociations
 * rdbmsSrvInfoMaxInboundAssociations is subid 14 of rdbmsSrvInfoEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.6.1.2.1.39.1.6.1.14
 * Description:
The greatest number of inbound associations that can be
           simultaneously open with this server.  If there is no limit,
           then the value should be zero.

           Note that a compliant agent does not need to
           allow write access to this object.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   1
 *
 *
 * Its syntax is GAUGE (based on perltype GAUGE)
 * The net-snmp type is ASN_GAUGE. The C type decl is u_long (u_long)
 */
/**
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsSrvInfoMaxInboundAssociations.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvInfoMaxInboundAssociations_map(u_long *mib_rdbmsSrvInfoMaxInboundAssociations_val_ptr, u_long raw_rdbmsSrvInfoMaxInboundAssociations_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvInfoMaxInboundAssociations_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoMaxInboundAssociations_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvInfoMaxInboundAssociations mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvInfoMaxInboundAssociations_val_ptr) = raw_rdbmsSrvInfoMaxInboundAssociations_val;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoMaxInboundAssociations_map */

/**
 * Extract the current value of the rdbmsSrvInfoMaxInboundAssociations data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvInfoMaxInboundAssociations_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsSrvInfoMaxInboundAssociations_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoMaxInboundAssociations_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsSrvInfoMaxInboundAssociations_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoMaxInboundAssociations_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvInfoMaxInboundAssociations data.
 * set (* rdbmsSrvInfoMaxInboundAssociations_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsSrvInfoMaxInboundAssociations_val_ptr ) = rowreq_ctx->data.rdbmsSrvInfoMaxInboundAssociations;

    return MFD_SUCCESS;
} /* rdbmsSrvInfoMaxInboundAssociations_get */



/** @} */
