/*-------------------------------------------------------------------------
 * rdbmsDbLimitedResourceTable_data_get.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbLimitedResourceTable_data_get.c,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsDbLimitedResourceTable.h"


/** @defgroup data_get data_get: Routines to get data
 *
 * TODO:230:M: Implement rdbmsDbLimitedResourceTable get routines.
 * TODO:240:M: Implement rdbmsDbLimitedResourceTable mapping routines (if any).
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
 *** Table rdbmsDbLimitedResourceTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbLimitedResourceTable is subid 4 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.4, length: 9
*/

/* ---------------------------------------------------------------------
 * TODO:200:r: Implement rdbmsDbLimitedResourceTable data context functions.
 */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbLimitedResourceEntry.rdbmsDbLimitedResourceName
 * rdbmsDbLimitedResourceName is subid 1 of rdbmsDbLimitedResourceEntry.
 * Its status is Current, and its access level is NoAccess.
 * OID: .1.3.6.1.2.1.39.1.4.1.1
 * Description:
The name of the resource, for instance 'global locks' or
           'locks for the FOO database', or 'data space on /dev/rdsk/5s0
           for FOO'. The length is limited to 64 characters to constrain
           the number of sub-identifiers needed for instance
           identification (and to minimize network traffic).
 *
 * Attributes:
 *   accessible 0     isscalar 0     enums  0      hasdefval 0
 *   readable   0     iscolumn 1     ranges 1      hashint   1
 *   settable   0
 *   hint: 255a
 *
 * Ranges:  0 - 255;
 *
 * Its syntax is DisplayString (based on perltype OCTETSTR)
 * The net-snmp type is ASN_OCTET_STR. The C type decl is char (char)
 * This data type requires a length.  (Max 255)
 *
 *
 *
 * NOTE: NODE rdbmsDbLimitedResourceName IS NOT ACCESSIBLE
 *
 *
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
 * default-node-rdbmsDbLimitedResourceName.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbLimitedResourceName_map(char **mib_rdbmsDbLimitedResourceName_val_ptr_ptr, size_t *mib_rdbmsDbLimitedResourceName_val_ptr_len_ptr, char *raw_rdbmsDbLimitedResourceName_val_ptr, size_t raw_rdbmsDbLimitedResourceName_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbLimitedResourceName_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbLimitedResourceName_val_ptr_ptr) && (NULL != mib_rdbmsDbLimitedResourceName_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceName_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsDbLimitedResourceName non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbLimitedResourceName_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbLimitedResourceName_val_ptr_ptr) || (*mib_rdbmsDbLimitedResourceName_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbLimitedResourceName_val_ptr_ptr = realloc( *mib_rdbmsDbLimitedResourceName_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbLimitedResourceName_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbLimitedResourceName_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbLimitedResourceName_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbLimitedResourceName_val_ptr_ptr, raw_rdbmsDbLimitedResourceName_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceName_map */


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
rdbmsDbLimitedResourceTable_indexes_set_tbl_idx(rdbmsDbLimitedResourceTable_mib_index *tbl_idx, long rdbmsDbIndex_val, char *rdbmsDbLimitedResourceName_val_ptr,  size_t rdbmsDbLimitedResourceName_val_ptr_len)
{
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceTable_indexes_set_tbl_idx","called\n"));

    /* rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->rdbmsDbIndex = rdbmsDbIndex_val;
    
    /* rdbmsDbLimitedResourceName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H */
     tbl_idx->rdbmsDbLimitedResourceName_len = sizeof(tbl_idx->rdbmsDbLimitedResourceName);
    /*
     * make sure there is enough space for rdbmsDbLimitedResourceName data
     */
    if ((NULL == tbl_idx->rdbmsDbLimitedResourceName) ||
        (tbl_idx->rdbmsDbLimitedResourceName_len < (rdbmsDbLimitedResourceName_val_ptr_len * sizeof(tbl_idx->rdbmsDbLimitedResourceName[0])))) {
        snmp_log(LOG_ERR,"not enough space for value\n");
        return MFD_ERROR;
    }
    tbl_idx->rdbmsDbLimitedResourceName_len = rdbmsDbLimitedResourceName_val_ptr_len * sizeof(tbl_idx->rdbmsDbLimitedResourceName[0]);
    memcpy( tbl_idx->rdbmsDbLimitedResourceName, rdbmsDbLimitedResourceName_val_ptr, tbl_idx->rdbmsDbLimitedResourceName_len );
    

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceTable_indexes_set_tbl_idx */

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
rdbmsDbLimitedResourceTable_indexes_set(rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, long rdbmsDbIndex_val, char *rdbmsDbLimitedResourceName_val_ptr,  size_t rdbmsDbLimitedResourceName_val_ptr_len)
{
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceTable_indexes_set","called\n"));

    if(MFD_SUCCESS != rdbmsDbLimitedResourceTable_indexes_set_tbl_idx(&rowreq_ctx->tbl_idx
                                   , rdbmsDbIndex_val
                                   , rdbmsDbLimitedResourceName_val_ptr, rdbmsDbLimitedResourceName_val_ptr_len
           ))
        return MFD_ERROR;

    /*
     * convert mib index to oid index
     */
    rowreq_ctx->oid_idx.len = sizeof(rowreq_ctx->oid_tmp) / sizeof(oid);
    if(0 != rdbmsDbLimitedResourceTable_index_to_oid(&rowreq_ctx->oid_idx,
                                    &rowreq_ctx->tbl_idx)) {
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceTable_indexes_set */


/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbLimitedResourceEntry.rdbmsDbLimitedResourceID
 * rdbmsDbLimitedResourceID is subid 2 of rdbmsDbLimitedResourceEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.4.1.2
 * Description:
The ID of the resource which may be described in some other
           MIB (e.g., an enterprise-specific MIB module).  If there is
           no ID for this rdbmsDbLimitedResourceName, attempts to access
           this object will return noSuchName (SNMPv1) or noSuchInstance
           (SNMPv2).
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is AutonomousType (based on perltype OBJECTID)
 * The net-snmp type is ASN_OBJECT_ID. The C type decl is oid (oid)
 * This data type requires a length.  (Max 255)
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
 * default-node-rdbmsDbLimitedResourceID.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbLimitedResourceID_map(oid **mib_rdbmsDbLimitedResourceID_val_ptr_ptr, size_t *mib_rdbmsDbLimitedResourceID_val_ptr_len_ptr, oid *raw_rdbmsDbLimitedResourceID_val_ptr, size_t raw_rdbmsDbLimitedResourceID_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbLimitedResourceID_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbLimitedResourceID_val_ptr_ptr) && (NULL != mib_rdbmsDbLimitedResourceID_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceID_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsDbLimitedResourceID non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbLimitedResourceID_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbLimitedResourceID_val_ptr_ptr) || (*mib_rdbmsDbLimitedResourceID_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbLimitedResourceID_val_ptr_ptr = realloc( *mib_rdbmsDbLimitedResourceID_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbLimitedResourceID_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbLimitedResourceID_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbLimitedResourceID_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbLimitedResourceID_val_ptr_ptr, raw_rdbmsDbLimitedResourceID_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceID_map */

/**
 * Extract the current value of the rdbmsDbLimitedResourceID data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbLimitedResourceID_val_ptr_ptr
 *        Pointer to storage for a oid variable
 * @param rdbmsDbLimitedResourceID_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbLimitedResourceID.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbLimitedResourceID_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbLimitedResourceID_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbLimitedResourceID_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, oid **rdbmsDbLimitedResourceID_val_ptr_ptr, size_t *rdbmsDbLimitedResourceID_val_ptr_len_ptr )
{
	/* Until PGSNMPD-MIB exists, there's nothing to see here */
	return MFD_SKIP;
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbLimitedResourceID_val_ptr_ptr) && (NULL != *rdbmsDbLimitedResourceID_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbLimitedResourceID_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceID_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbLimitedResourceID data.
 * set (* rdbmsDbLimitedResourceID_val_ptr_ptr ) and (* rdbmsDbLimitedResourceID_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbLimitedResourceID data
     */
    if ((NULL == (* rdbmsDbLimitedResourceID_val_ptr_ptr )) ||
        ((* rdbmsDbLimitedResourceID_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbLimitedResourceID_len * sizeof((* rdbmsDbLimitedResourceID_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbLimitedResourceID data
         */
        (* rdbmsDbLimitedResourceID_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbLimitedResourceID_len * sizeof((* rdbmsDbLimitedResourceID_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbLimitedResourceID_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbLimitedResourceID_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbLimitedResourceID_len * sizeof((* rdbmsDbLimitedResourceID_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbLimitedResourceID_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbLimitedResourceID, (* rdbmsDbLimitedResourceID_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceID_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbLimitedResourceEntry.rdbmsDbLimitedResourceLimit
 * rdbmsDbLimitedResourceLimit is subid 3 of rdbmsDbLimitedResourceEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.6.1.2.1.39.1.4.1.3
 * Description:
The maximum value the resource use may attain.

           Note that a compliant agent does not need to
           allow write access to this object.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 1      hashint   0
 *   settable   1
 *
 * Ranges:  1 - 2147483647;
 *
 * Its syntax is INTEGER (based on perltype INTEGER)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (long)
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
 * default-node-rdbmsDbLimitedResourceLimit.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbLimitedResourceLimit_map(long *mib_rdbmsDbLimitedResourceLimit_val_ptr, long raw_rdbmsDbLimitedResourceLimit_val)
{
    netsnmp_assert(NULL != mib_rdbmsDbLimitedResourceLimit_val_ptr);
    
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceLimit_map","called\n"));
    
    /*
     * TODO:241:o: |-> Implement rdbmsDbLimitedResourceLimit mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsDbLimitedResourceLimit_val_ptr) = raw_rdbmsDbLimitedResourceLimit_val;

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceLimit_map */

/**
 * Extract the current value of the rdbmsDbLimitedResourceLimit data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbLimitedResourceLimit_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsDbLimitedResourceLimit_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, long * rdbmsDbLimitedResourceLimit_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsDbLimitedResourceLimit_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceLimit_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbLimitedResourceLimit data.
 * set (* rdbmsDbLimitedResourceLimit_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsDbLimitedResourceLimit_val_ptr ) = rowreq_ctx->data.rdbmsDbLimitedResourceLimit;

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceLimit_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbLimitedResourceEntry.rdbmsDbLimitedResourceCurrent
 * rdbmsDbLimitedResourceCurrent is subid 4 of rdbmsDbLimitedResourceEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.4.1.4
 * Description:
The current value for the resource.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 1      hashint   0
 *   settable   0
 *
 * Ranges:  1 - 2147483647;
 *
 * Its syntax is INTEGER (based on perltype INTEGER)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (long)
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
 * default-node-rdbmsDbLimitedResourceCurrent.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbLimitedResourceCurrent_map(long *mib_rdbmsDbLimitedResourceCurrent_val_ptr, long raw_rdbmsDbLimitedResourceCurrent_val)
{
    netsnmp_assert(NULL != mib_rdbmsDbLimitedResourceCurrent_val_ptr);
    
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceCurrent_map","called\n"));
    
    /*
     * TODO:241:o: |-> Implement rdbmsDbLimitedResourceCurrent mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsDbLimitedResourceCurrent_val_ptr) = raw_rdbmsDbLimitedResourceCurrent_val;

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceCurrent_map */

/**
 * Extract the current value of the rdbmsDbLimitedResourceCurrent data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbLimitedResourceCurrent_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsDbLimitedResourceCurrent_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, long * rdbmsDbLimitedResourceCurrent_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsDbLimitedResourceCurrent_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceCurrent_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbLimitedResourceCurrent data.
 * set (* rdbmsDbLimitedResourceCurrent_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsDbLimitedResourceCurrent_val_ptr ) = rowreq_ctx->data.rdbmsDbLimitedResourceCurrent;

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceCurrent_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbLimitedResourceEntry.rdbmsDbLimitedResourceHighwater
 * rdbmsDbLimitedResourceHighwater is subid 5 of rdbmsDbLimitedResourceEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.4.1.5
 * Description:
The maximum value of the resource seen since applUpTime
           was reset for the earliest server which has the database
           actively opened.

           If there are two servers with the database open, and the
           oldest one dies, the proper way to invalidate the value is by
           resetting sysUpTime.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 1      hashint   0
 *   settable   0
 *
 * Ranges:  1 - 2147483647;
 *
 * Its syntax is INTEGER (based on perltype INTEGER)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (long)
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
 * default-node-rdbmsDbLimitedResourceHighwater.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbLimitedResourceHighwater_map(long *mib_rdbmsDbLimitedResourceHighwater_val_ptr, long raw_rdbmsDbLimitedResourceHighwater_val)
{
    netsnmp_assert(NULL != mib_rdbmsDbLimitedResourceHighwater_val_ptr);
    
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceHighwater_map","called\n"));
    
    /*
     * TODO:241:o: |-> Implement rdbmsDbLimitedResourceHighwater mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsDbLimitedResourceHighwater_val_ptr) = raw_rdbmsDbLimitedResourceHighwater_val;

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceHighwater_map */

/**
 * Extract the current value of the rdbmsDbLimitedResourceHighwater data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbLimitedResourceHighwater_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsDbLimitedResourceHighwater_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, long * rdbmsDbLimitedResourceHighwater_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsDbLimitedResourceHighwater_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceHighwater_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbLimitedResourceHighwater data.
 * set (* rdbmsDbLimitedResourceHighwater_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsDbLimitedResourceHighwater_val_ptr ) = rowreq_ctx->data.rdbmsDbLimitedResourceHighwater;

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceHighwater_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbLimitedResourceEntry.rdbmsDbLimitedResourceFailures
 * rdbmsDbLimitedResourceFailures is subid 6 of rdbmsDbLimitedResourceEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.4.1.6
 * Description:
The number of times the system wanted to exceed the limit of
           the resource since applUpTime was reset for the earliest
           server which has the database actively opened.

           If there are two servers with the DB open, and the
           oldest one dies, the proper way to invalidate the value is by
           resetting sysUpTime.
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
 * default-node-rdbmsDbLimitedResourceFailures.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbLimitedResourceFailures_map(u_long *mib_rdbmsDbLimitedResourceFailures_val_ptr, u_long raw_rdbmsDbLimitedResourceFailures_val)
{
    netsnmp_assert(NULL != mib_rdbmsDbLimitedResourceFailures_val_ptr);
    
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceFailures_map","called\n"));
    
    /*
     * TODO:241:o: |-> Implement rdbmsDbLimitedResourceFailures mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsDbLimitedResourceFailures_val_ptr) = raw_rdbmsDbLimitedResourceFailures_val;

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceFailures_map */

/**
 * Extract the current value of the rdbmsDbLimitedResourceFailures data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbLimitedResourceFailures_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsDbLimitedResourceFailures_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsDbLimitedResourceFailures_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsDbLimitedResourceFailures_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceFailures_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbLimitedResourceFailures data.
 * set (* rdbmsDbLimitedResourceFailures_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsDbLimitedResourceFailures_val_ptr ) = rowreq_ctx->data.rdbmsDbLimitedResourceFailures;

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceFailures_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbLimitedResourceEntry.rdbmsDbLimitedResourceDescription
 * rdbmsDbLimitedResourceDescription is subid 7 of rdbmsDbLimitedResourceEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.6.1.2.1.39.1.4.1.7
 * Description:
A description of the resource and the meaning of the integer
           units used for Limit, Current, and Highwater.

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
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsDbLimitedResourceDescription.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbLimitedResourceDescription_map(char **mib_rdbmsDbLimitedResourceDescription_val_ptr_ptr, size_t *mib_rdbmsDbLimitedResourceDescription_val_ptr_len_ptr, char *raw_rdbmsDbLimitedResourceDescription_val_ptr, size_t raw_rdbmsDbLimitedResourceDescription_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbLimitedResourceDescription_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbLimitedResourceDescription_val_ptr_ptr) && (NULL != mib_rdbmsDbLimitedResourceDescription_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceDescription_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsDbLimitedResourceDescription non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbLimitedResourceDescription_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbLimitedResourceDescription_val_ptr_ptr) || (*mib_rdbmsDbLimitedResourceDescription_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbLimitedResourceDescription_val_ptr_ptr = realloc( *mib_rdbmsDbLimitedResourceDescription_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbLimitedResourceDescription_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbLimitedResourceDescription_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbLimitedResourceDescription_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbLimitedResourceDescription_val_ptr_ptr, raw_rdbmsDbLimitedResourceDescription_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceDescription_map */

/**
 * Extract the current value of the rdbmsDbLimitedResourceDescription data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbLimitedResourceDescription_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsDbLimitedResourceDescription_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbLimitedResourceDescription.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbLimitedResourceDescription_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbLimitedResourceDescription_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbLimitedResourceDescription_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbLimitedResourceDescription_val_ptr_ptr, size_t *rdbmsDbLimitedResourceDescription_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbLimitedResourceDescription_val_ptr_ptr) && (NULL != *rdbmsDbLimitedResourceDescription_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbLimitedResourceDescription_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbLimitedResourceTable:rdbmsDbLimitedResourceDescription_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbLimitedResourceDescription data.
 * set (* rdbmsDbLimitedResourceDescription_val_ptr_ptr ) and (* rdbmsDbLimitedResourceDescription_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbLimitedResourceDescription data
     */
    if ((NULL == (* rdbmsDbLimitedResourceDescription_val_ptr_ptr )) ||
        ((* rdbmsDbLimitedResourceDescription_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbLimitedResourceDescription_len * sizeof((* rdbmsDbLimitedResourceDescription_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbLimitedResourceDescription data
         */
        (* rdbmsDbLimitedResourceDescription_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbLimitedResourceDescription_len * sizeof((* rdbmsDbLimitedResourceDescription_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbLimitedResourceDescription_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbLimitedResourceDescription_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbLimitedResourceDescription_len * sizeof((* rdbmsDbLimitedResourceDescription_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbLimitedResourceDescription_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbLimitedResourceDescription, (* rdbmsDbLimitedResourceDescription_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbLimitedResourceDescription_get */



/** @} */
