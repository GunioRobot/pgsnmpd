/*-------------------------------------------------------------------------
 * rdbmsSrvParamTable_data_get.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvParamTable_data_get.c,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsSrvParamTable.h"


/** @defgroup data_get data_get: Routines to get data
 *
 * TODO:230:M: Implement rdbmsSrvParamTable get routines.
 * TODO:240:M: Implement rdbmsSrvParamTable mapping routines (if any).
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
 *** Table rdbmsSrvParamTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvParamTable is subid 7 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.7, length: 9
*/

/* ---------------------------------------------------------------------
 * TODO:200:r: Implement rdbmsSrvParamTable data context functions.
 */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvParamEntry.rdbmsSrvParamName
 * rdbmsSrvParamName is subid 1 of rdbmsSrvParamEntry.
 * Its status is Current, and its access level is NoAccess.
 * OID: .1.3.6.1.2.1.39.1.7.1.1
 * Description:
The name of a configuration parameter for a server.  This
           name is product-specific. The length is limited to 64
           characters to constrain the number of sub-identifiers needed
           for instance identification (and to minimize network
           traffic).
 *
 * Attributes:
 *   accessible 0     isscalar 0     enums  0      hasdefval 0
 *   readable   0     iscolumn 1     ranges 1      hashint   1
 *   settable   0
 *   hint: 255a
 *
 * Ranges:  1 - 64;
 *
 * Its syntax is DisplayString (based on perltype OCTETSTR)
 * The net-snmp type is ASN_OCTET_STR. The C type decl is char (char)
 * This data type requires a length.  (Max 64)
 *
 *
 *
 * NOTE: NODE rdbmsSrvParamName IS NOT ACCESSIBLE
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
 * default-node-rdbmsSrvParamName.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvParamName_map(char **mib_rdbmsSrvParamName_val_ptr_ptr, size_t *mib_rdbmsSrvParamName_val_ptr_len_ptr, char *raw_rdbmsSrvParamName_val_ptr, size_t raw_rdbmsSrvParamName_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsSrvParamName_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsSrvParamName_val_ptr_ptr) && (NULL != mib_rdbmsSrvParamName_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamName_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsSrvParamName non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsSrvParamName_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsSrvParamName_val_ptr_ptr) || (*mib_rdbmsSrvParamName_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsSrvParamName_val_ptr_ptr = realloc( *mib_rdbmsSrvParamName_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsSrvParamName_val_ptr_ptr));
        if(NULL == *mib_rdbmsSrvParamName_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsSrvParamName_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsSrvParamName_val_ptr_ptr, raw_rdbmsSrvParamName_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsSrvParamName_map */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvParamEntry.rdbmsSrvParamSubIndex
 * rdbmsSrvParamSubIndex is subid 2 of rdbmsSrvParamEntry.
 * Its status is Current, and its access level is NoAccess.
 * OID: .1.3.6.1.2.1.39.1.7.1.2
 * Description:
The subindex value for this parameter.  If the parameter is
           naturally considered to contain a variable number of members
           of a class, e.g.  members of the DBA user group, or files
           which are part of the database, then it must be presented as
           a set of rows.  If, on the other hand, the parameter
           represents a set of choices from a class, e.g. the
           permissions on a file or the options chosen out of the set of
           all options allowed, AND is guaranteed to always fit in the
           255 character length of a DisplayString, then it may be
           presented as a comma separated list with a subindex value of
           one.  Zero may not be used as a value.
 *
 * Attributes:
 *   accessible 0     isscalar 0     enums  0      hasdefval 0
 *   readable   0     iscolumn 1     ranges 1      hashint   0
 *   settable   0
 *
 * Ranges:  1 - 2147483647;
 *
 * Its syntax is INTEGER (based on perltype INTEGER)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (long)
 *
 *
 *
 * NOTE: NODE rdbmsSrvParamSubIndex IS NOT ACCESSIBLE
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
 * default-node-rdbmsSrvParamSubIndex.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvParamSubIndex_map(long *mib_rdbmsSrvParamSubIndex_val_ptr, long raw_rdbmsSrvParamSubIndex_val)
{
    netsnmp_assert(NULL != mib_rdbmsSrvParamSubIndex_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamSubIndex_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsSrvParamSubIndex mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsSrvParamSubIndex_val_ptr) = raw_rdbmsSrvParamSubIndex_val;

    return MFD_SUCCESS;
} /* rdbmsSrvParamSubIndex_map */


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
rdbmsSrvParamTable_indexes_set_tbl_idx(rdbmsSrvParamTable_mib_index *tbl_idx, long applIndex_val, char *rdbmsSrvParamName_val_ptr,  size_t rdbmsSrvParamName_val_ptr_len, long rdbmsSrvParamSubIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_indexes_set_tbl_idx","called\n"));

    /* applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->applIndex = applIndex_val;

    /* rdbmsSrvParamName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H */
     tbl_idx->rdbmsSrvParamName_len = sizeof(tbl_idx->rdbmsSrvParamName);
    /*
     * make sure there is enough space for rdbmsSrvParamName data
     */
    if ((NULL == tbl_idx->rdbmsSrvParamName) ||
        (tbl_idx->rdbmsSrvParamName_len < (rdbmsSrvParamName_val_ptr_len * sizeof(tbl_idx->rdbmsSrvParamName[0])))) {
        snmp_log(LOG_ERR,"not enough space for value\n");
        return MFD_ERROR;
    }
    tbl_idx->rdbmsSrvParamName_len = rdbmsSrvParamName_val_ptr_len * sizeof(tbl_idx->rdbmsSrvParamName[0]);
    memcpy( tbl_idx->rdbmsSrvParamName, rdbmsSrvParamName_val_ptr, tbl_idx->rdbmsSrvParamName_len );

    /* rdbmsSrvParamSubIndex(2)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->rdbmsSrvParamSubIndex = rdbmsSrvParamSubIndex_val;


    return MFD_SUCCESS;
} /* rdbmsSrvParamTable_indexes_set_tbl_idx */

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
rdbmsSrvParamTable_indexes_set(rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx, long applIndex_val, char *rdbmsSrvParamName_val_ptr,  size_t rdbmsSrvParamName_val_ptr_len, long rdbmsSrvParamSubIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_indexes_set","called\n"));

    if(MFD_SUCCESS != rdbmsSrvParamTable_indexes_set_tbl_idx(&rowreq_ctx->tbl_idx
                                   , applIndex_val
                                   , rdbmsSrvParamName_val_ptr, rdbmsSrvParamName_val_ptr_len
                                   , rdbmsSrvParamSubIndex_val
           ))
        return MFD_ERROR;

    /*
     * convert mib index to oid index
     */
    rowreq_ctx->oid_idx.len = sizeof(rowreq_ctx->oid_tmp) / sizeof(oid);
    if(0 != rdbmsSrvParamTable_index_to_oid(&rowreq_ctx->oid_idx,
                                    &rowreq_ctx->tbl_idx)) {
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* rdbmsSrvParamTable_indexes_set */


/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvParamEntry.rdbmsSrvParamID
 * rdbmsSrvParamID is subid 3 of rdbmsSrvParamEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.7.1.3
 * Description:
The ID of the parameter which may be described in some
           other MIB.  If there is no ID for this rdbmsSrvParamName,
           attempts to access this object will return noSuchName
           (SNMPv1) or noSuchInstance (SNMPv2).
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is AutonomousType (based on perltype OBJECTID)
 * The net-snmp type is ASN_OBJECT_ID. The C type decl is oid (oid)
 * This data type requires a length.  (Max 2147483647)
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
 * default-node-rdbmsSrvParamID.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvParamID_map(oid **mib_rdbmsSrvParamID_val_ptr_ptr, size_t *mib_rdbmsSrvParamID_val_ptr_len_ptr, oid *raw_rdbmsSrvParamID_val_ptr, size_t raw_rdbmsSrvParamID_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsSrvParamID_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsSrvParamID_val_ptr_ptr) && (NULL != mib_rdbmsSrvParamID_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamID_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsSrvParamID non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsSrvParamID_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsSrvParamID_val_ptr_ptr) || (*mib_rdbmsSrvParamID_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsSrvParamID_val_ptr_ptr = realloc( *mib_rdbmsSrvParamID_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsSrvParamID_val_ptr_ptr));
        if(NULL == *mib_rdbmsSrvParamID_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsSrvParamID_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsSrvParamID_val_ptr_ptr, raw_rdbmsSrvParamID_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsSrvParamID_map */

/**
 * Extract the current value of the rdbmsSrvParamID data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvParamID_val_ptr_ptr
 *        Pointer to storage for a oid variable
 * @param rdbmsSrvParamID_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsSrvParamID.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsSrvParamID_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsSrvParamID_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsSrvParamID_get( rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx, oid **rdbmsSrvParamID_val_ptr_ptr, size_t *rdbmsSrvParamID_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   return MFD_SKIP;
   netsnmp_assert( (NULL != rdbmsSrvParamID_val_ptr_ptr) && (NULL != *rdbmsSrvParamID_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsSrvParamID_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamID_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvParamID data.
 * set (* rdbmsSrvParamID_val_ptr_ptr ) and (* rdbmsSrvParamID_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsSrvParamID data
     */
    if ((NULL == (* rdbmsSrvParamID_val_ptr_ptr )) ||
        ((* rdbmsSrvParamID_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsSrvParamID_len * sizeof((* rdbmsSrvParamID_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsSrvParamID data
         */
        (* rdbmsSrvParamID_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsSrvParamID_len * sizeof((* rdbmsSrvParamID_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsSrvParamID_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsSrvParamID_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsSrvParamID_len * sizeof((* rdbmsSrvParamID_val_ptr_ptr )[0]);
    memcpy( (* rdbmsSrvParamID_val_ptr_ptr ), rowreq_ctx->data.rdbmsSrvParamID, (* rdbmsSrvParamID_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsSrvParamID_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvParamEntry.rdbmsSrvParamCurrValue
 * rdbmsSrvParamCurrValue is subid 4 of rdbmsSrvParamEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.6.1.2.1.39.1.7.1.4
 * Description:
The value for a configuration parameter now in effect, the
           actual setting for the server.  While there may multiple
           values in the temporal domain of interest (for instance, the
           value to take effect at the next restart), this is the
           current setting.

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
 * default-node-rdbmsSrvParamCurrValue.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvParamCurrValue_map(char **mib_rdbmsSrvParamCurrValue_val_ptr_ptr, size_t *mib_rdbmsSrvParamCurrValue_val_ptr_len_ptr, char *raw_rdbmsSrvParamCurrValue_val_ptr, size_t raw_rdbmsSrvParamCurrValue_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsSrvParamCurrValue_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsSrvParamCurrValue_val_ptr_ptr) && (NULL != mib_rdbmsSrvParamCurrValue_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamCurrValue_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsSrvParamCurrValue non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsSrvParamCurrValue_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsSrvParamCurrValue_val_ptr_ptr) || (*mib_rdbmsSrvParamCurrValue_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsSrvParamCurrValue_val_ptr_ptr = realloc( *mib_rdbmsSrvParamCurrValue_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsSrvParamCurrValue_val_ptr_ptr));
        if(NULL == *mib_rdbmsSrvParamCurrValue_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsSrvParamCurrValue_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsSrvParamCurrValue_val_ptr_ptr, raw_rdbmsSrvParamCurrValue_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsSrvParamCurrValue_map */

/**
 * Extract the current value of the rdbmsSrvParamCurrValue data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvParamCurrValue_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsSrvParamCurrValue_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsSrvParamCurrValue.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsSrvParamCurrValue_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsSrvParamCurrValue_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsSrvParamCurrValue_get( rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvParamCurrValue_val_ptr_ptr, size_t *rdbmsSrvParamCurrValue_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsSrvParamCurrValue_val_ptr_ptr) && (NULL != *rdbmsSrvParamCurrValue_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsSrvParamCurrValue_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamCurrValue_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvParamCurrValue data.
 * set (* rdbmsSrvParamCurrValue_val_ptr_ptr ) and (* rdbmsSrvParamCurrValue_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsSrvParamCurrValue data
     */
    if ((NULL == (* rdbmsSrvParamCurrValue_val_ptr_ptr )) ||
        ((* rdbmsSrvParamCurrValue_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsSrvParamCurrValue_len * sizeof((* rdbmsSrvParamCurrValue_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsSrvParamCurrValue data
         */
        (* rdbmsSrvParamCurrValue_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsSrvParamCurrValue_len * sizeof((* rdbmsSrvParamCurrValue_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsSrvParamCurrValue_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsSrvParamCurrValue_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsSrvParamCurrValue_len * sizeof((* rdbmsSrvParamCurrValue_val_ptr_ptr )[0]);
    memcpy( (* rdbmsSrvParamCurrValue_val_ptr_ptr ), rowreq_ctx->data.rdbmsSrvParamCurrValue, (* rdbmsSrvParamCurrValue_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsSrvParamCurrValue_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvParamEntry.rdbmsSrvParamComment
 * rdbmsSrvParamComment is subid 5 of rdbmsSrvParamEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.6.1.2.1.39.1.7.1.5
 * Description:
Annotation which describes the purpose of a configuration
           parameter or the reason for a particular parameter's
           setting.

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
 * default-node-rdbmsSrvParamComment.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvParamComment_map(char **mib_rdbmsSrvParamComment_val_ptr_ptr, size_t *mib_rdbmsSrvParamComment_val_ptr_len_ptr, char *raw_rdbmsSrvParamComment_val_ptr, size_t raw_rdbmsSrvParamComment_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsSrvParamComment_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsSrvParamComment_val_ptr_ptr) && (NULL != mib_rdbmsSrvParamComment_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamComment_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsSrvParamComment non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsSrvParamComment_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsSrvParamComment_val_ptr_ptr) || (*mib_rdbmsSrvParamComment_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsSrvParamComment_val_ptr_ptr = realloc( *mib_rdbmsSrvParamComment_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsSrvParamComment_val_ptr_ptr));
        if(NULL == *mib_rdbmsSrvParamComment_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsSrvParamComment_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsSrvParamComment_val_ptr_ptr, raw_rdbmsSrvParamComment_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsSrvParamComment_map */

/**
 * Extract the current value of the rdbmsSrvParamComment data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvParamComment_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsSrvParamComment_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsSrvParamComment.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsSrvParamComment_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsSrvParamComment_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsSrvParamComment_get( rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvParamComment_val_ptr_ptr, size_t *rdbmsSrvParamComment_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsSrvParamComment_val_ptr_ptr) && (NULL != *rdbmsSrvParamComment_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsSrvParamComment_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamComment_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvParamComment data.
 * set (* rdbmsSrvParamComment_val_ptr_ptr ) and (* rdbmsSrvParamComment_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsSrvParamComment data
     */
    if ((NULL == (* rdbmsSrvParamComment_val_ptr_ptr )) ||
        ((* rdbmsSrvParamComment_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsSrvParamComment_len * sizeof((* rdbmsSrvParamComment_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsSrvParamComment data
         */
        (* rdbmsSrvParamComment_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsSrvParamComment_len * sizeof((* rdbmsSrvParamComment_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsSrvParamComment_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsSrvParamComment_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsSrvParamComment_len * sizeof((* rdbmsSrvParamComment_val_ptr_ptr )[0]);
    memcpy( (* rdbmsSrvParamComment_val_ptr_ptr ), rowreq_ctx->data.rdbmsSrvParamComment, (* rdbmsSrvParamComment_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsSrvParamComment_get */



/** @} */
