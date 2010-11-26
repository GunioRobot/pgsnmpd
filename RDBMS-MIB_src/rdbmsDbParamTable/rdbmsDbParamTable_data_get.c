/*-------------------------------------------------------------------------
 * rdbmsDbParamTable_data_get.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbParamTable_data_get.c,v 1.3 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsDbParamTable.h"


/** @defgroup data_get data_get: Routines to get data
 *
 * TODO:230:M: Implement rdbmsDbParamTable get routines.
 * TODO:240:M: Implement rdbmsDbParamTable mapping routines (if any).
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
 *** Table rdbmsDbParamTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbParamTable is subid 3 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.3, length: 9
*/

/* ---------------------------------------------------------------------
 * TODO:200:r: Implement rdbmsDbParamTable data context functions.
 */


/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbParamEntry.rdbmsDbParamName
 * rdbmsDbParamName is subid 1 of rdbmsDbParamEntry.
 * Its status is Current, and its access level is NoAccess.
 * OID: .1.3.6.1.2.1.39.1.3.1.1
 * Description:
The name of a configuration parameter for a database.  This
           name is product-specific.  The length is limited to 64
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
 * NOTE: NODE rdbmsDbParamName IS NOT ACCESSIBLE
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
 * default-node-rdbmsDbParamName.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbParamName_map(char **mib_rdbmsDbParamName_val_ptr_ptr, size_t *mib_rdbmsDbParamName_val_ptr_len_ptr, char *raw_rdbmsDbParamName_val_ptr, size_t raw_rdbmsDbParamName_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbParamName_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbParamName_val_ptr_ptr) && (NULL != mib_rdbmsDbParamName_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamName_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsDbParamName non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbParamName_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbParamName_val_ptr_ptr) || (*mib_rdbmsDbParamName_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbParamName_val_ptr_ptr = realloc( *mib_rdbmsDbParamName_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbParamName_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbParamName_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbParamName_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbParamName_val_ptr_ptr, raw_rdbmsDbParamName_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbParamName_map */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbParamEntry.rdbmsDbParamSubIndex
 * rdbmsDbParamSubIndex is subid 2 of rdbmsDbParamEntry.
 * Its status is Current, and its access level is NoAccess.
 * OID: .1.3.6.1.2.1.39.1.3.1.2
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
 * NOTE: NODE rdbmsDbParamSubIndex IS NOT ACCESSIBLE
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
 * default-node-rdbmsDbParamSubIndex.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbParamSubIndex_map(long *mib_rdbmsDbParamSubIndex_val_ptr, long raw_rdbmsDbParamSubIndex_val)
{
    netsnmp_assert(NULL != mib_rdbmsDbParamSubIndex_val_ptr);
    
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamSubIndex_map","called\n"));
    
    /*
     * TODO:241:o: |-> Implement rdbmsDbParamSubIndex mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsDbParamSubIndex_val_ptr) = raw_rdbmsDbParamSubIndex_val;

    return MFD_SUCCESS;
} /* rdbmsDbParamSubIndex_map */


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
rdbmsDbParamTable_indexes_set_tbl_idx(rdbmsDbParamTable_mib_index *tbl_idx, long rdbmsDbIndex_val, char *rdbmsDbParamName_val_ptr,  size_t rdbmsDbParamName_val_ptr_len, long rdbmsDbParamSubIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamTable_indexes_set_tbl_idx","called\n"));

    /* rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->rdbmsDbIndex = rdbmsDbIndex_val;
    
    /* rdbmsDbParamName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H */
     tbl_idx->rdbmsDbParamName_len = sizeof(tbl_idx->rdbmsDbParamName);
    /*
     * make sure there is enough space for rdbmsDbParamName data
     */
    if ((NULL == tbl_idx->rdbmsDbParamName) ||
        (tbl_idx->rdbmsDbParamName_len < (rdbmsDbParamName_val_ptr_len * sizeof(tbl_idx->rdbmsDbParamName[0])))) {
        snmp_log(LOG_ERR,"not enough space for value\n");
        return MFD_ERROR;
    }
    tbl_idx->rdbmsDbParamName_len = rdbmsDbParamName_val_ptr_len * sizeof(tbl_idx->rdbmsDbParamName[0]);
    memcpy( tbl_idx->rdbmsDbParamName, rdbmsDbParamName_val_ptr, tbl_idx->rdbmsDbParamName_len );
    
    /* rdbmsDbParamSubIndex(2)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->rdbmsDbParamSubIndex = rdbmsDbParamSubIndex_val;
    

    return MFD_SUCCESS;
} /* rdbmsDbParamTable_indexes_set_tbl_idx */

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
rdbmsDbParamTable_indexes_set(rdbmsDbParamTable_rowreq_ctx *rowreq_ctx, long rdbmsDbIndex_val, char *rdbmsDbParamName_val_ptr,  size_t rdbmsDbParamName_val_ptr_len, long rdbmsDbParamSubIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamTable_indexes_set","called\n"));

    if(MFD_SUCCESS != rdbmsDbParamTable_indexes_set_tbl_idx(&rowreq_ctx->tbl_idx
                                   , rdbmsDbIndex_val
                                   , rdbmsDbParamName_val_ptr, rdbmsDbParamName_val_ptr_len
                                   , rdbmsDbParamSubIndex_val
           ))
        return MFD_ERROR;

    /*
     * convert mib index to oid index
     */
    rowreq_ctx->oid_idx.len = sizeof(rowreq_ctx->oid_tmp) / sizeof(oid);
    if(0 != rdbmsDbParamTable_index_to_oid(&rowreq_ctx->oid_idx,
                                    &rowreq_ctx->tbl_idx)) {
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* rdbmsDbParamTable_indexes_set */


/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbParamEntry.rdbmsDbParamID
 * rdbmsDbParamID is subid 3 of rdbmsDbParamEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.3.1.3
 * Description:
The ID of the parameter which may be described in some other
           MIB (e.g., an enterprise-specific MIB module).  If there is
           no ID for this rdbmsDbParamName, attempts to access this
           object will return noSuchName (SNMPv1) or noSuchInstance
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
 * default-node-rdbmsDbParamID.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbParamID_map(oid **mib_rdbmsDbParamID_val_ptr_ptr, size_t *mib_rdbmsDbParamID_val_ptr_len_ptr, oid *raw_rdbmsDbParamID_val_ptr, size_t raw_rdbmsDbParamID_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbParamID_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbParamID_val_ptr_ptr) && (NULL != mib_rdbmsDbParamID_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamID_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsDbParamID non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbParamID_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbParamID_val_ptr_ptr) || (*mib_rdbmsDbParamID_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbParamID_val_ptr_ptr = realloc( *mib_rdbmsDbParamID_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbParamID_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbParamID_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbParamID_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbParamID_val_ptr_ptr, raw_rdbmsDbParamID_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbParamID_map */

/**
 * Extract the current value of the rdbmsDbParamID data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbParamID_val_ptr_ptr
 *        Pointer to storage for a oid variable
 * @param rdbmsDbParamID_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbParamID.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbParamID_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbParamID_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbParamID_get( rdbmsDbParamTable_rowreq_ctx *rowreq_ctx, oid **rdbmsDbParamID_val_ptr_ptr, size_t *rdbmsDbParamID_val_ptr_len_ptr )
{
   /* Until we have a parameter with multiple values that won't fit into
    * a 255 character string when rendered as a comma-separated list, we 
    * don't need a value at this OID */
   return MFD_SKIP;
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbParamID_val_ptr_ptr) && (NULL != *rdbmsDbParamID_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbParamID_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamID_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbParamID data.
 * set (* rdbmsDbParamID_val_ptr_ptr ) and (* rdbmsDbParamID_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbParamID data
     */
    if ((NULL == (* rdbmsDbParamID_val_ptr_ptr )) ||
        ((* rdbmsDbParamID_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbParamID_len * sizeof((* rdbmsDbParamID_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbParamID data
         */
        (* rdbmsDbParamID_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbParamID_len * sizeof((* rdbmsDbParamID_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbParamID_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbParamID_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbParamID_len * sizeof((* rdbmsDbParamID_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbParamID_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbParamID, (* rdbmsDbParamID_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbParamID_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbParamEntry.rdbmsDbParamCurrValue
 * rdbmsDbParamCurrValue is subid 4 of rdbmsDbParamEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.6.1.2.1.39.1.3.1.4
 * Description:
The value for a configuration parameter now in effect, the
           actual setting for the database.  While there may multiple
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
 * default-node-rdbmsDbParamCurrValue.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbParamCurrValue_map(char **mib_rdbmsDbParamCurrValue_val_ptr_ptr, size_t *mib_rdbmsDbParamCurrValue_val_ptr_len_ptr, char *raw_rdbmsDbParamCurrValue_val_ptr, size_t raw_rdbmsDbParamCurrValue_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbParamCurrValue_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbParamCurrValue_val_ptr_ptr) && (NULL != mib_rdbmsDbParamCurrValue_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamCurrValue_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsDbParamCurrValue non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbParamCurrValue_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbParamCurrValue_val_ptr_ptr) || (*mib_rdbmsDbParamCurrValue_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbParamCurrValue_val_ptr_ptr = realloc( *mib_rdbmsDbParamCurrValue_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbParamCurrValue_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbParamCurrValue_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbParamCurrValue_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbParamCurrValue_val_ptr_ptr, raw_rdbmsDbParamCurrValue_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbParamCurrValue_map */

/**
 * Extract the current value of the rdbmsDbParamCurrValue data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbParamCurrValue_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsDbParamCurrValue_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbParamCurrValue.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbParamCurrValue_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbParamCurrValue_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbParamCurrValue_get( rdbmsDbParamTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbParamCurrValue_val_ptr_ptr, size_t *rdbmsDbParamCurrValue_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbParamCurrValue_val_ptr_ptr) && (NULL != *rdbmsDbParamCurrValue_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbParamCurrValue_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamCurrValue_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbParamCurrValue data.
 * set (* rdbmsDbParamCurrValue_val_ptr_ptr ) and (* rdbmsDbParamCurrValue_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbParamCurrValue data
     */
    if ((NULL == (* rdbmsDbParamCurrValue_val_ptr_ptr )) ||
        ((* rdbmsDbParamCurrValue_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbParamCurrValue_len * sizeof((* rdbmsDbParamCurrValue_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbParamCurrValue data
         */
        (* rdbmsDbParamCurrValue_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbParamCurrValue_len * sizeof((* rdbmsDbParamCurrValue_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbParamCurrValue_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbParamCurrValue_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbParamCurrValue_len * sizeof((* rdbmsDbParamCurrValue_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbParamCurrValue_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbParamCurrValue, (* rdbmsDbParamCurrValue_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbParamCurrValue_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbParamEntry.rdbmsDbParamComment
 * rdbmsDbParamComment is subid 5 of rdbmsDbParamEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.6.1.2.1.39.1.3.1.5
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
 * default-node-rdbmsDbParamComment.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbParamComment_map(char **mib_rdbmsDbParamComment_val_ptr_ptr, size_t *mib_rdbmsDbParamComment_val_ptr_len_ptr, char *raw_rdbmsDbParamComment_val_ptr, size_t raw_rdbmsDbParamComment_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbParamComment_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbParamComment_val_ptr_ptr) && (NULL != mib_rdbmsDbParamComment_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamComment_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsDbParamComment non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbParamComment_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbParamComment_val_ptr_ptr) || (*mib_rdbmsDbParamComment_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbParamComment_val_ptr_ptr = realloc( *mib_rdbmsDbParamComment_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbParamComment_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbParamComment_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbParamComment_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbParamComment_val_ptr_ptr, raw_rdbmsDbParamComment_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbParamComment_map */

/**
 * Extract the current value of the rdbmsDbParamComment data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbParamComment_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsDbParamComment_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbParamComment.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbParamComment_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbParamComment_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbParamComment_get( rdbmsDbParamTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbParamComment_val_ptr_ptr, size_t *rdbmsDbParamComment_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbParamComment_val_ptr_ptr) && (NULL != *rdbmsDbParamComment_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbParamComment_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamComment_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbParamComment data.
 * set (* rdbmsDbParamComment_val_ptr_ptr ) and (* rdbmsDbParamComment_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbParamComment data
     */
    if ((NULL == (* rdbmsDbParamComment_val_ptr_ptr )) ||
        ((* rdbmsDbParamComment_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbParamComment_len * sizeof((* rdbmsDbParamComment_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbParamComment data
         */
        (* rdbmsDbParamComment_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbParamComment_len * sizeof((* rdbmsDbParamComment_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbParamComment_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbParamComment_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbParamComment_len * sizeof((* rdbmsDbParamComment_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbParamComment_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbParamComment, (* rdbmsDbParamComment_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbParamComment_get */



/** @} */
