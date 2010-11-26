/*-------------------------------------------------------------------------
 * rdbmsDbInfoTable_data_get.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbInfoTable_data_get.c,v 1.5 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */
/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsDbInfoTable.h"


/** @defgroup data_get data_get: Routines to get data
 *
 * TODO:230:M: Implement rdbmsDbInfoTable get routines.
 * TODO:240:M: Implement rdbmsDbInfoTable mapping routines (if any).
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
 *** Table rdbmsDbInfoTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbInfoTable is subid 2 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.2, length: 9
*/

/* ---------------------------------------------------------------------
 * TODO:200:r: Implement rdbmsDbInfoTable data context functions.
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
rdbmsDbInfoTable_indexes_set_tbl_idx(rdbmsDbInfoTable_mib_index *tbl_idx, long rdbmsDbIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoTable_indexes_set_tbl_idx","called\n"));

    /* rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->rdbmsDbIndex = rdbmsDbIndex_val;
    

    return MFD_SUCCESS;
} /* rdbmsDbInfoTable_indexes_set_tbl_idx */

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
rdbmsDbInfoTable_indexes_set(rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, long rdbmsDbIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoTable_indexes_set","called\n"));

    if(MFD_SUCCESS != rdbmsDbInfoTable_indexes_set_tbl_idx(&rowreq_ctx->tbl_idx
                                   , rdbmsDbIndex_val
           ))
        return MFD_ERROR;

    /*
     * convert mib index to oid index
     */
    rowreq_ctx->oid_idx.len = sizeof(rowreq_ctx->oid_tmp) / sizeof(oid);
    if(0 != rdbmsDbInfoTable_index_to_oid(&rowreq_ctx->oid_idx,
                                    &rowreq_ctx->tbl_idx)) {
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* rdbmsDbInfoTable_indexes_set */


/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbInfoEntry.rdbmsDbInfoProductName
 * rdbmsDbInfoProductName is subid 1 of rdbmsDbInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.2.1.1
 * Description:
The textual product name of the server that created or last
           restructured this database.  The format is product specific.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 1      hashint   1
 *   settable   0
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
 * default-node-rdbmsDbInfoProductName.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbInfoProductName_map(char **mib_rdbmsDbInfoProductName_val_ptr_ptr, size_t *mib_rdbmsDbInfoProductName_val_ptr_len_ptr, char *raw_rdbmsDbInfoProductName_val_ptr, size_t raw_rdbmsDbInfoProductName_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbInfoProductName_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbInfoProductName_val_ptr_ptr) && (NULL != mib_rdbmsDbInfoProductName_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoProductName_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsDbInfoProductName non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbInfoProductName_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbInfoProductName_val_ptr_ptr) || (*mib_rdbmsDbInfoProductName_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbInfoProductName_val_ptr_ptr = realloc( *mib_rdbmsDbInfoProductName_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbInfoProductName_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbInfoProductName_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbInfoProductName_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbInfoProductName_val_ptr_ptr, raw_rdbmsDbInfoProductName_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbInfoProductName_map */

/**
 * Extract the current value of the rdbmsDbInfoProductName data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbInfoProductName_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsDbInfoProductName_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbInfoProductName.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbInfoProductName_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbInfoProductName_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbInfoProductName_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbInfoProductName_val_ptr_ptr, size_t *rdbmsDbInfoProductName_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbInfoProductName_val_ptr_ptr) && (NULL != *rdbmsDbInfoProductName_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbInfoProductName_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoProductName_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbInfoProductName data.
 * set (* rdbmsDbInfoProductName_val_ptr_ptr ) and (* rdbmsDbInfoProductName_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbInfoProductName data
     */
    if ((NULL == (* rdbmsDbInfoProductName_val_ptr_ptr )) ||
        ((* rdbmsDbInfoProductName_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbInfoProductName_len * sizeof((* rdbmsDbInfoProductName_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbInfoProductName data
         */
        (* rdbmsDbInfoProductName_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbInfoProductName_len * sizeof((* rdbmsDbInfoProductName_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbInfoProductName_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbInfoProductName_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbInfoProductName_len * sizeof((* rdbmsDbInfoProductName_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbInfoProductName_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbInfoProductName, (* rdbmsDbInfoProductName_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbInfoProductName_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbInfoEntry.rdbmsDbInfoVersion
 * rdbmsDbInfoVersion is subid 2 of rdbmsDbInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.2.1.2
 * Description:
The version number of the server that created or last
           restructured this database.  The format is product specific.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 1      hashint   1
 *   settable   0
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
 * default-node-rdbmsDbInfoVersion.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbInfoVersion_map(char **mib_rdbmsDbInfoVersion_val_ptr_ptr, size_t *mib_rdbmsDbInfoVersion_val_ptr_len_ptr, char *raw_rdbmsDbInfoVersion_val_ptr, size_t raw_rdbmsDbInfoVersion_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbInfoVersion_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbInfoVersion_val_ptr_ptr) && (NULL != mib_rdbmsDbInfoVersion_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoVersion_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsDbInfoVersion non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbInfoVersion_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbInfoVersion_val_ptr_ptr) || (*mib_rdbmsDbInfoVersion_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbInfoVersion_val_ptr_ptr = realloc( *mib_rdbmsDbInfoVersion_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbInfoVersion_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbInfoVersion_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbInfoVersion_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbInfoVersion_val_ptr_ptr, raw_rdbmsDbInfoVersion_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbInfoVersion_map */

/**
 * Extract the current value of the rdbmsDbInfoVersion data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbInfoVersion_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsDbInfoVersion_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbInfoVersion.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbInfoVersion_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbInfoVersion_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbInfoVersion_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbInfoVersion_val_ptr_ptr, size_t *rdbmsDbInfoVersion_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbInfoVersion_val_ptr_ptr) && (NULL != *rdbmsDbInfoVersion_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbInfoVersion_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoVersion_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbInfoVersion data.
 * set (* rdbmsDbInfoVersion_val_ptr_ptr ) and (* rdbmsDbInfoVersion_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbInfoVersion data
     */
    if ((NULL == (* rdbmsDbInfoVersion_val_ptr_ptr )) ||
        ((* rdbmsDbInfoVersion_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbInfoVersion_len * sizeof((* rdbmsDbInfoVersion_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbInfoVersion data
         */
        (* rdbmsDbInfoVersion_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbInfoVersion_len * sizeof((* rdbmsDbInfoVersion_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbInfoVersion_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbInfoVersion_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbInfoVersion_len * sizeof((* rdbmsDbInfoVersion_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbInfoVersion_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbInfoVersion, (* rdbmsDbInfoVersion_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbInfoVersion_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbInfoEntry.rdbmsDbInfoSizeUnits
 * rdbmsDbInfoSizeUnits is subid 3 of rdbmsDbInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.2.1.3
 * Description:
Identification of the units used to measure the size of this
           database in rdbmsDbInfoSizeAllocated and rdbmsDbInfoSizeUsed.
           bytes(1) indicates individual bytes, kbytes(2) indicates
           units of kilobytes, mbytes(3) indicates units of megabytes,
           gbytes(4) indicates units of gigabytes, and tbytes(5)
           indicates units of terabytes.  All are binary multiples -- 1K
           = 1024.  If writable, changes here are reflected in the get
           values of the associated objects.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  1      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 * Enum range: 4/8. Values:  bytes(1), kbytes(2), mbytes(3), gbytes(4), tbytes(5)
 *
 * Its syntax is INTEGER (based on perltype INTEGER)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (u_long)
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
 * default-node-rdbmsDbInfoSizeUnits.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbInfoSizeUnits_map(u_long *mib_rdbmsDbInfoSizeUnits_val_ptr, u_long raw_rdbmsDbInfoSizeUnits_val)
{
    netsnmp_assert(NULL != mib_rdbmsDbInfoSizeUnits_val_ptr);
    
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoSizeUnits_map","called\n"));
    
    /*
     * TODO:241:o: |-> Implement rdbmsDbInfoSizeUnits enum mapping.
     * uses INTERNAL_* macros defined in the header files
     */
    switch(raw_rdbmsDbInfoSizeUnits_val) {
        case INTERNAL_RDBMSDBINFOSIZEUNITS_BYTES:
             *mib_rdbmsDbInfoSizeUnits_val_ptr = RDBMSDBINFOSIZEUNITS_BYTES;
             break;

        case INTERNAL_RDBMSDBINFOSIZEUNITS_KBYTES:
             *mib_rdbmsDbInfoSizeUnits_val_ptr = RDBMSDBINFOSIZEUNITS_KBYTES;
             break;

        case INTERNAL_RDBMSDBINFOSIZEUNITS_MBYTES:
             *mib_rdbmsDbInfoSizeUnits_val_ptr = RDBMSDBINFOSIZEUNITS_MBYTES;
             break;

        case INTERNAL_RDBMSDBINFOSIZEUNITS_GBYTES:
             *mib_rdbmsDbInfoSizeUnits_val_ptr = RDBMSDBINFOSIZEUNITS_GBYTES;
             break;

        case INTERNAL_RDBMSDBINFOSIZEUNITS_TBYTES:
             *mib_rdbmsDbInfoSizeUnits_val_ptr = RDBMSDBINFOSIZEUNITS_TBYTES;
             break;

             default:
                 snmp_log(LOG_ERR, "couldn't map value %ld for rdbmsDbInfoSizeUnits\n", raw_rdbmsDbInfoSizeUnits_val );
                 return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* rdbmsDbInfoSizeUnits_map */

/**
 * Extract the current value of the rdbmsDbInfoSizeUnits data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbInfoSizeUnits_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsDbInfoSizeUnits_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsDbInfoSizeUnits_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsDbInfoSizeUnits_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoSizeUnits_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbInfoSizeUnits data.
 * set (* rdbmsDbInfoSizeUnits_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsDbInfoSizeUnits_val_ptr ) = rowreq_ctx->data.rdbmsDbInfoSizeUnits;

    return MFD_SUCCESS;
} /* rdbmsDbInfoSizeUnits_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbInfoEntry.rdbmsDbInfoSizeAllocated
 * rdbmsDbInfoSizeAllocated is subid 4 of rdbmsDbInfoEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.6.1.2.1.39.1.2.1.4
 * Description:
The estimated size of this database (in
           rdbmsDbInfoSizeUnits), which is the disk space that has been
           allocated to it and is no longer available to users on this
           host.  rdbmsDbInfoSize does not necessarily indicate the
           amount of space actually in use for database data.  Some
           databases may support extending allocated size, and others
           may not.

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
 * default-node-rdbmsDbInfoSizeAllocated.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbInfoSizeAllocated_map(long *mib_rdbmsDbInfoSizeAllocated_val_ptr, long raw_rdbmsDbInfoSizeAllocated_val)
{
    netsnmp_assert(NULL != mib_rdbmsDbInfoSizeAllocated_val_ptr);
    
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoSizeAllocated_map","called\n"));
    
    /*
     * TODO:241:o: |-> Implement rdbmsDbInfoSizeAllocated mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsDbInfoSizeAllocated_val_ptr) = raw_rdbmsDbInfoSizeAllocated_val;

    return MFD_SUCCESS;
} /* rdbmsDbInfoSizeAllocated_map */

/**
 * Extract the current value of the rdbmsDbInfoSizeAllocated data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbInfoSizeAllocated_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsDbInfoSizeAllocated_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, long * rdbmsDbInfoSizeAllocated_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsDbInfoSizeAllocated_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoSizeAllocated_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbInfoSizeAllocated data.
 * set (* rdbmsDbInfoSizeAllocated_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsDbInfoSizeAllocated_val_ptr ) = rowreq_ctx->data.rdbmsDbInfoSizeAllocated;

    return MFD_SUCCESS;
} /* rdbmsDbInfoSizeAllocated_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbInfoEntry.rdbmsDbInfoSizeUsed
 * rdbmsDbInfoSizeUsed is subid 5 of rdbmsDbInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.2.1.5
 * Description:
The estimated size of this database, in rdbmsDbInfoSizeUnits,
           which is actually in use for database data.
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
 * default-node-rdbmsDbInfoSizeUsed.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbInfoSizeUsed_map(long *mib_rdbmsDbInfoSizeUsed_val_ptr, long raw_rdbmsDbInfoSizeUsed_val)
{
    netsnmp_assert(NULL != mib_rdbmsDbInfoSizeUsed_val_ptr);
    
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoSizeUsed_map","called\n"));
    
    /*
     * TODO:241:o: |-> Implement rdbmsDbInfoSizeUsed mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsDbInfoSizeUsed_val_ptr) = raw_rdbmsDbInfoSizeUsed_val;

    return MFD_SUCCESS;
} /* rdbmsDbInfoSizeUsed_map */

/**
 * Extract the current value of the rdbmsDbInfoSizeUsed data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbInfoSizeUsed_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsDbInfoSizeUsed_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, long * rdbmsDbInfoSizeUsed_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsDbInfoSizeUsed_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoSizeUsed_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbInfoSizeUsed data.
 * set (* rdbmsDbInfoSizeUsed_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsDbInfoSizeUsed_val_ptr ) = rowreq_ctx->data.rdbmsDbInfoSizeUsed;

    return MFD_SUCCESS;
} /* rdbmsDbInfoSizeUsed_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbInfoEntry.rdbmsDbInfoLastBackup
 * rdbmsDbInfoLastBackup is subid 6 of rdbmsDbInfoEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.2.1.6
 * Description:
The date and time that the latest complete or partial backup
           of the database was taken. If a database has never been
           backed up, then attempts to access this object will
           result in either noSuchName (SNMPv1) or noSuchInstance
           (SNMPv2).
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
 * default-node-rdbmsDbInfoLastBackup.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbInfoLastBackup_map(char **mib_rdbmsDbInfoLastBackup_val_ptr_ptr, size_t *mib_rdbmsDbInfoLastBackup_val_ptr_len_ptr, char *raw_rdbmsDbInfoLastBackup_val_ptr, size_t raw_rdbmsDbInfoLastBackup_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbInfoLastBackup_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbInfoLastBackup_val_ptr_ptr) && (NULL != mib_rdbmsDbInfoLastBackup_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoLastBackup_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsDbInfoLastBackup non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbInfoLastBackup_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbInfoLastBackup_val_ptr_ptr) || (*mib_rdbmsDbInfoLastBackup_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbInfoLastBackup_val_ptr_ptr = realloc( *mib_rdbmsDbInfoLastBackup_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbInfoLastBackup_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbInfoLastBackup_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbInfoLastBackup_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbInfoLastBackup_val_ptr_ptr, raw_rdbmsDbInfoLastBackup_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbInfoLastBackup_map */

/**
 * Extract the current value of the rdbmsDbInfoLastBackup data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbInfoLastBackup_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsDbInfoLastBackup_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbInfoLastBackup.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbInfoLastBackup_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbInfoLastBackup_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbInfoLastBackup_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbInfoLastBackup_val_ptr_ptr, size_t *rdbmsDbInfoLastBackup_val_ptr_len_ptr )
{
   /* temporary storage for date. If you have any of this data available
      directly, use it instead. */
/*   int year, month, day, hour, minutes, seconds, deci_seconds;
 *   int rc, utc_offset_direction, utc_offset_hours, utc_offset_minutes; */
   int rc;

   /** we should have a pointer and enough storage */
   /* Josh changed mib2c's template from rdbmsDbInfoLastBackup_ptr_ptr and rdbmsDbInfoLastBackup_len_ptr to rdbmsDbInfoLastBackup_val_ptr_ptr and
    * rdbmsDbInfoLastBackup_val_ptr_len_ptr respectively, both here and in the call to netsnmp_dateandtime_set_buf_from_vars. I'm not sure this was
    * the right thing to do, but it does appear to work */
   netsnmp_assert( (NULL != rdbmsDbInfoLastBackup_val_ptr_ptr) && (NULL != *rdbmsDbInfoLastBackup_val_ptr_ptr));
   netsnmp_assert( (NULL != rdbmsDbInfoLastBackup_val_ptr_len_ptr) && ((* rdbmsDbInfoLastBackup_val_ptr_len_ptr) >= 11));

   /*
    * TODO:231:o: |-> copy rdbmsDbInfoLastBackup data.
    * get the date from your context pointer.
    */
   /*return MFD_SKIP; * TODO:234:M: |-> Remove SKIP once you've set rdbmsDbInfoLastBackup data */

   /* call convenience function to set data */
   rc = netsnmp_dateandtime_set_buf_from_vars((u_char *)*rdbmsDbInfoLastBackup_val_ptr_ptr, rdbmsDbInfoLastBackup_val_ptr_len_ptr,
   rowreq_ctx->data.lastBackupYear, 
   rowreq_ctx->data.lastBackupMonth, 
   rowreq_ctx->data.lastBackupDay, 
   rowreq_ctx->data.lastBackupHour, 
   rowreq_ctx->data.lastBackupMinutes, 
   rowreq_ctx->data.lastBackupSeconds, 
   rowreq_ctx->data.lastBackupDeciSeconds, 
   rowreq_ctx->data.utc_offset_direction, 
   rowreq_ctx->data.utc_offset_hours, 
   rowreq_ctx->data.utc_offset_minutes );
   if(rc != SNMP_ERR_NOERROR)
      return rc;

    return MFD_SUCCESS;
} /* rdbmsDbInfoLastBackup_get */



/** @} */
