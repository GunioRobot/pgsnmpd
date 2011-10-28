/*-------------------------------------------------------------------------
 * rdbmsSrvTable_data_get.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvTable_data_get.c,v 1.4 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsSrvTable.h"


/** @defgroup data_get data_get: Routines to get data
 *
 * TODO:230:M: Implement rdbmsSrvTable get routines.
 * TODO:240:M: Implement rdbmsSrvTable mapping routines (if any).
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
 *** Table rdbmsSrvTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvTable is subid 5 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.5, length: 9
*/

/* ---------------------------------------------------------------------
 * TODO:200:r: Implement rdbmsSrvTable data context functions.
 */

/*---------------------------------------------------------------------
 * APPLICATION-MIB::applEntry.applIndex
 * applIndex is subid 1 of applEntry.
 * Its status is Current, and its access level is NoAccess.
 * OID: .1.3.6.1.2.1.27.1.1.1
 * Description:
An index to uniquely identify the network service
          application.
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
 * NOTE: NODE applIndex IS NOT ACCESSIBLE
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
 * default-node-applIndex.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
applIndex_map(long *mib_applIndex_val_ptr, long raw_applIndex_val)
{
    netsnmp_assert(NULL != mib_applIndex_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsSrvTable:applIndex_map","called\n"));

    /*
     * TODO:241:o: |-> Implement applIndex mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_applIndex_val_ptr) = raw_applIndex_val;

    return MFD_SUCCESS;
} /* applIndex_map */


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
rdbmsSrvTable_indexes_set_tbl_idx(rdbmsSrvTable_mib_index *tbl_idx, long applIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvTable_indexes_set_tbl_idx","called\n"));

    /* applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->applIndex = applIndex_val;


    return MFD_SUCCESS;
} /* rdbmsSrvTable_indexes_set_tbl_idx */

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
rdbmsSrvTable_indexes_set(rdbmsSrvTable_rowreq_ctx *rowreq_ctx, long applIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvTable_indexes_set","called\n"));

    if(MFD_SUCCESS != rdbmsSrvTable_indexes_set_tbl_idx(&rowreq_ctx->tbl_idx
                                   , applIndex_val
           ))
        return MFD_ERROR;

    /*
     * convert mib index to oid index
     */
    rowreq_ctx->oid_idx.len = sizeof(rowreq_ctx->oid_tmp) / sizeof(oid);
    if(0 != rdbmsSrvTable_index_to_oid(&rowreq_ctx->oid_idx,
                                    &rowreq_ctx->tbl_idx)) {
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* rdbmsSrvTable_indexes_set */


/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvEntry.rdbmsSrvPrivateMibOID
 * rdbmsSrvPrivateMibOID is subid 1 of rdbmsSrvEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.5.1.1
 * Description:
The authoritative identification for the private MIB for this
           server, presumably based on the vendor, e.g., { enterprises
           111 <optional subidentifiers>} for Oracle servers, {
           enterprises 757 <optional subidentifiers>} for Ingres
           servers, { enterprises 897 <optional subidentifiers>} for
           Sybase servers, etc.

           If no OBJECT IDENTIFIER exists for the private MIB, attempts
           to access this object will return noSuchName (SNMPv1)
           or noSuchInstance (SNMPv2).
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is OBJECTID (based on perltype OBJECTID)
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
 * default-node-rdbmsSrvPrivateMibOID.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvPrivateMibOID_map(oid **mib_rdbmsSrvPrivateMibOID_val_ptr_ptr, size_t *mib_rdbmsSrvPrivateMibOID_val_ptr_len_ptr, oid *raw_rdbmsSrvPrivateMibOID_val_ptr, size_t raw_rdbmsSrvPrivateMibOID_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsSrvPrivateMibOID_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsSrvPrivateMibOID_val_ptr_ptr) && (NULL != mib_rdbmsSrvPrivateMibOID_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvPrivateMibOID_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsSrvPrivateMibOID non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsSrvPrivateMibOID_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsSrvPrivateMibOID_val_ptr_ptr) || (*mib_rdbmsSrvPrivateMibOID_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsSrvPrivateMibOID_val_ptr_ptr = realloc( *mib_rdbmsSrvPrivateMibOID_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsSrvPrivateMibOID_val_ptr_ptr));
        if(NULL == *mib_rdbmsSrvPrivateMibOID_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsSrvPrivateMibOID_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsSrvPrivateMibOID_val_ptr_ptr, raw_rdbmsSrvPrivateMibOID_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsSrvPrivateMibOID_map */

/**
 * Extract the current value of the rdbmsSrvPrivateMibOID data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvPrivateMibOID_val_ptr_ptr
 *        Pointer to storage for a oid variable
 * @param rdbmsSrvPrivateMibOID_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsSrvPrivateMibOID.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsSrvPrivateMibOID_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsSrvPrivateMibOID_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsSrvPrivateMibOID_get( rdbmsSrvTable_rowreq_ctx *rowreq_ctx, oid **rdbmsSrvPrivateMibOID_val_ptr_ptr, size_t *rdbmsSrvPrivateMibOID_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsSrvPrivateMibOID_val_ptr_ptr) && (NULL != *rdbmsSrvPrivateMibOID_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsSrvPrivateMibOID_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvPrivateMibOID_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvPrivateMibOID data.
 * set (* rdbmsSrvPrivateMibOID_val_ptr_ptr ) and (* rdbmsSrvPrivateMibOID_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsSrvPrivateMibOID data
     */
    if ((NULL == (* rdbmsSrvPrivateMibOID_val_ptr_ptr )) ||
        ((* rdbmsSrvPrivateMibOID_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsSrvPrivateMibOID_len * sizeof((* rdbmsSrvPrivateMibOID_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsSrvPrivateMibOID data
         */
        (* rdbmsSrvPrivateMibOID_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsSrvPrivateMibOID_len * sizeof((* rdbmsSrvPrivateMibOID_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsSrvPrivateMibOID_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsSrvPrivateMibOID_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsSrvPrivateMibOID_len * sizeof((* rdbmsSrvPrivateMibOID_val_ptr_ptr )[0]);
    memcpy( (* rdbmsSrvPrivateMibOID_val_ptr_ptr ), rowreq_ctx->data.rdbmsSrvPrivateMibOID, (* rdbmsSrvPrivateMibOID_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsSrvPrivateMibOID_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvEntry.rdbmsSrvVendorName
 * rdbmsSrvVendorName is subid 2 of rdbmsSrvEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.5.1.2
 * Description:
The name of the vendor whose RDBMS manages this database,
           for informational purposes.
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
 * default-node-rdbmsSrvVendorName.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvVendorName_map(char **mib_rdbmsSrvVendorName_val_ptr_ptr, size_t *mib_rdbmsSrvVendorName_val_ptr_len_ptr, char *raw_rdbmsSrvVendorName_val_ptr, size_t raw_rdbmsSrvVendorName_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsSrvVendorName_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsSrvVendorName_val_ptr_ptr) && (NULL != mib_rdbmsSrvVendorName_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvVendorName_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsSrvVendorName non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsSrvVendorName_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsSrvVendorName_val_ptr_ptr) || (*mib_rdbmsSrvVendorName_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsSrvVendorName_val_ptr_ptr = realloc( *mib_rdbmsSrvVendorName_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsSrvVendorName_val_ptr_ptr));
        if(NULL == *mib_rdbmsSrvVendorName_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsSrvVendorName_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsSrvVendorName_val_ptr_ptr, raw_rdbmsSrvVendorName_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsSrvVendorName_map */

/**
 * Extract the current value of the rdbmsSrvVendorName data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvVendorName_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsSrvVendorName_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsSrvVendorName.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsSrvVendorName_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsSrvVendorName_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsSrvVendorName_get( rdbmsSrvTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvVendorName_val_ptr_ptr, size_t *rdbmsSrvVendorName_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsSrvVendorName_val_ptr_ptr) && (NULL != *rdbmsSrvVendorName_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsSrvVendorName_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvVendorName_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvVendorName data.
 * set (* rdbmsSrvVendorName_val_ptr_ptr ) and (* rdbmsSrvVendorName_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsSrvVendorName data
     */
    if ((NULL == (* rdbmsSrvVendorName_val_ptr_ptr )) ||
        ((* rdbmsSrvVendorName_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsSrvVendorName_len * sizeof((* rdbmsSrvVendorName_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsSrvVendorName data
         */
        (* rdbmsSrvVendorName_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsSrvVendorName_len * sizeof((* rdbmsSrvVendorName_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsSrvVendorName_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsSrvVendorName_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsSrvVendorName_len * sizeof((* rdbmsSrvVendorName_val_ptr_ptr )[0]);
    memcpy( (* rdbmsSrvVendorName_val_ptr_ptr ), rowreq_ctx->data.rdbmsSrvVendorName, (* rdbmsSrvVendorName_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsSrvVendorName_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvEntry.rdbmsSrvProductName
 * rdbmsSrvProductName is subid 3 of rdbmsSrvEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.5.1.3
 * Description:
The product name of this server.  This is normally the
           vendor's formal name for the product, in product specific
           format.
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
 * default-node-rdbmsSrvProductName.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvProductName_map(char **mib_rdbmsSrvProductName_val_ptr_ptr, size_t *mib_rdbmsSrvProductName_val_ptr_len_ptr, char *raw_rdbmsSrvProductName_val_ptr, size_t raw_rdbmsSrvProductName_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsSrvProductName_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsSrvProductName_val_ptr_ptr) && (NULL != mib_rdbmsSrvProductName_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvProductName_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsSrvProductName non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsSrvProductName_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsSrvProductName_val_ptr_ptr) || (*mib_rdbmsSrvProductName_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsSrvProductName_val_ptr_ptr = realloc( *mib_rdbmsSrvProductName_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsSrvProductName_val_ptr_ptr));
        if(NULL == *mib_rdbmsSrvProductName_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsSrvProductName_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsSrvProductName_val_ptr_ptr, raw_rdbmsSrvProductName_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsSrvProductName_map */

/**
 * Extract the current value of the rdbmsSrvProductName data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvProductName_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsSrvProductName_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsSrvProductName.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsSrvProductName_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsSrvProductName_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsSrvProductName_get( rdbmsSrvTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvProductName_val_ptr_ptr, size_t *rdbmsSrvProductName_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsSrvProductName_val_ptr_ptr) && (NULL != *rdbmsSrvProductName_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsSrvProductName_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvProductName_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvProductName data.
 * set (* rdbmsSrvProductName_val_ptr_ptr ) and (* rdbmsSrvProductName_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsSrvProductName data
     */
    if ((NULL == (* rdbmsSrvProductName_val_ptr_ptr )) ||
        ((* rdbmsSrvProductName_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsSrvProductName_len * sizeof((* rdbmsSrvProductName_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsSrvProductName data
         */
        (* rdbmsSrvProductName_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsSrvProductName_len * sizeof((* rdbmsSrvProductName_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsSrvProductName_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsSrvProductName_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsSrvProductName_len * sizeof((* rdbmsSrvProductName_val_ptr_ptr )[0]);
    memcpy( (* rdbmsSrvProductName_val_ptr_ptr ), rowreq_ctx->data.rdbmsSrvProductName, (* rdbmsSrvProductName_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsSrvProductName_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsSrvEntry.rdbmsSrvContact
 * rdbmsSrvContact is subid 4 of rdbmsSrvEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.6.1.2.1.39.1.5.1.4
 * Description:
The textual identification of the contact person for this
           managed server, together with information on how to contact
           this person.

           Note: if there is no active server associated with this
           object, an agent may need to keep this in other persistent
           storage, e.g., a configuration file.

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
 * default-node-rdbmsSrvContact.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsSrvContact_map(char **mib_rdbmsSrvContact_val_ptr_ptr, size_t *mib_rdbmsSrvContact_val_ptr_len_ptr, char *raw_rdbmsSrvContact_val_ptr, size_t raw_rdbmsSrvContact_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsSrvContact_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsSrvContact_val_ptr_ptr) && (NULL != mib_rdbmsSrvContact_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvContact_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsSrvContact non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsSrvContact_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsSrvContact_val_ptr_ptr) || (*mib_rdbmsSrvContact_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsSrvContact_val_ptr_ptr = realloc( *mib_rdbmsSrvContact_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsSrvContact_val_ptr_ptr));
        if(NULL == *mib_rdbmsSrvContact_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsSrvContact_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsSrvContact_val_ptr_ptr, raw_rdbmsSrvContact_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsSrvContact_map */

/**
 * Extract the current value of the rdbmsSrvContact data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsSrvContact_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsSrvContact_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsSrvContact.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsSrvContact_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsSrvContact_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsSrvContact_get( rdbmsSrvTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvContact_val_ptr_ptr, size_t *rdbmsSrvContact_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsSrvContact_val_ptr_ptr) && (NULL != *rdbmsSrvContact_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsSrvContact_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvContact_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsSrvContact data.
 * set (* rdbmsSrvContact_val_ptr_ptr ) and (* rdbmsSrvContact_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsSrvContact data
     */
    if ((NULL == (* rdbmsSrvContact_val_ptr_ptr )) ||
        ((* rdbmsSrvContact_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsSrvContact_len * sizeof((* rdbmsSrvContact_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsSrvContact data
         */
        (* rdbmsSrvContact_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsSrvContact_len * sizeof((* rdbmsSrvContact_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsSrvContact_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsSrvContact_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsSrvContact_len * sizeof((* rdbmsSrvContact_val_ptr_ptr )[0]);
    memcpy( (* rdbmsSrvContact_val_ptr_ptr ), rowreq_ctx->data.rdbmsSrvContact, (* rdbmsSrvContact_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsSrvContact_get */



/** @} */
