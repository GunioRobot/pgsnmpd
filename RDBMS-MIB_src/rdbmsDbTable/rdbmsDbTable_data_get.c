/*-------------------------------------------------------------------------
 * rdbmsDbTable_data_get.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable_data_get.c,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsDbTable.h"


/** @defgroup data_get data_get: Routines to get data
 *
 * TODO:230:M: Implement rdbmsDbTable get routines.
 * TODO:240:M: Implement rdbmsDbTable mapping routines (if any).
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
 *** Table rdbmsDbTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbTable is subid 1 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.1, length: 9
*/

/* ---------------------------------------------------------------------
 * TODO:200:r: Implement rdbmsDbTable data context functions.
 */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbEntry.rdbmsDbIndex
 * rdbmsDbIndex is subid 1 of rdbmsDbEntry.
 * Its status is Current, and its access level is NoAccess.
 * OID: .1.3.6.1.2.1.39.1.1.1.1
 * Description:
A numeric index, unique among all the databases from all
           products on this host.  This value is a surrogate for the
           conceptually unique key, which is {PrivateMibOID,
           databasename}
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
 * NOTE: NODE rdbmsDbIndex IS NOT ACCESSIBLE
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
 * default-node-rdbmsDbIndex.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbIndex_map(long *mib_rdbmsDbIndex_val_ptr, long raw_rdbmsDbIndex_val)
{
    netsnmp_assert(NULL != mib_rdbmsDbIndex_val_ptr);

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbIndex_map","called\n"));

    /*
     * TODO:241:o: |-> Implement rdbmsDbIndex mapping.
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them here.
     */
    (*mib_rdbmsDbIndex_val_ptr) = raw_rdbmsDbIndex_val;

    return MFD_SUCCESS;
} /* rdbmsDbIndex_map */


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
rdbmsDbTable_indexes_set_tbl_idx(rdbmsDbTable_mib_index *tbl_idx, long rdbmsDbIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_indexes_set_tbl_idx","called\n"));

    /* rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->rdbmsDbIndex = rdbmsDbIndex_val;


    return MFD_SUCCESS;
} /* rdbmsDbTable_indexes_set_tbl_idx */

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
rdbmsDbTable_indexes_set(rdbmsDbTable_rowreq_ctx *rowreq_ctx, long rdbmsDbIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_indexes_set","called\n"));

    if(MFD_SUCCESS != rdbmsDbTable_indexes_set_tbl_idx(&rowreq_ctx->tbl_idx
                                   , rdbmsDbIndex_val
           ))
        return MFD_ERROR;

    /*
     * convert mib index to oid index
     */
    rowreq_ctx->oid_idx.len = sizeof(rowreq_ctx->oid_tmp) / sizeof(oid);
    if(0 != rdbmsDbTable_index_to_oid(&rowreq_ctx->oid_idx,
                                    &rowreq_ctx->tbl_idx)) {
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* rdbmsDbTable_indexes_set */


/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbEntry.rdbmsDbPrivateMibOID
 * rdbmsDbPrivateMibOID is subid 2 of rdbmsDbEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.1.1.2
 * Description:
The authoritative identification for the private MIB for
          this database, presumably based on the vendor, e.g., {
          enterprises 111 <optional subidentifiers>} for Oracle
          databases, {enterprises 757 <optional subidentifiers>} for
          Ingres databases, { enterprises 897 <optional
          subidentifiers>} for Sybase databases, etc.

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
 * default-node-rdbmsDbPrivateMibOID.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbPrivateMibOID_map(oid **mib_rdbmsDbPrivateMibOID_val_ptr_ptr, size_t *mib_rdbmsDbPrivateMibOID_val_ptr_len_ptr,
 oid *raw_rdbmsDbPrivateMibOID_val_ptr, size_t raw_rdbmsDbPrivateMibOID_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbPrivateMibOID_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbPrivateMibOID_val_ptr_ptr) && (NULL != mib_rdbmsDbPrivateMibOID_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbPrivateMibOID_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsDbPrivateMibOID non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbPrivateMibOID_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbPrivateMibOID_val_ptr_ptr) || (*mib_rdbmsDbPrivateMibOID_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbPrivateMibOID_val_ptr_ptr = realloc( *mib_rdbmsDbPrivateMibOID_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbPrivateMibOID_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbPrivateMibOID_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbPrivateMibOID_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbPrivateMibOID_val_ptr_ptr, raw_rdbmsDbPrivateMibOID_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbPrivateMibOID_map */

/**
 * Extract the current value of the rdbmsDbPrivateMibOID data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbPrivateMibOID_val_ptr_ptr
 *        Pointer to storage for a oid variable
 * @param rdbmsDbPrivateMibOID_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbPrivateMibOID.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbPrivateMibOID_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbPrivateMibOID_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbPrivateMibOID_get( rdbmsDbTable_rowreq_ctx *rowreq_ctx, oid **rdbmsDbPrivateMibOID_val_ptr_ptr, size_t *rdbmsDbPrivateMibOID_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbPrivateMibOID_val_ptr_ptr) && (NULL != *rdbmsDbPrivateMibOID_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbPrivateMibOID_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbPrivateMibOID_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbPrivateMibOID data.
 * set (* rdbmsDbPrivateMibOID_val_ptr_ptr ) and (* rdbmsDbPrivateMibOID_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbPrivateMibOID data
     */
    if ((NULL == (* rdbmsDbPrivateMibOID_val_ptr_ptr )) ||
        ((* rdbmsDbPrivateMibOID_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbPrivateMibOID_len * sizeof((* rdbmsDbPrivateMibOID_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbPrivateMibOID data
         */
        (* rdbmsDbPrivateMibOID_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbPrivateMibOID_len * sizeof((* rdbmsDbPrivateMibOID_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbPrivateMibOID_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbPrivateMibOID_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbPrivateMibOID_len * sizeof((* rdbmsDbPrivateMibOID_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbPrivateMibOID_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbPrivateMibOID, (* rdbmsDbPrivateMibOID_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbPrivateMibOID_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbEntry.rdbmsDbVendorName
 * rdbmsDbVendorName is subid 3 of rdbmsDbEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.1.1.3
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
 * default-node-rdbmsDbVendorName.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbVendorName_map(char **mib_rdbmsDbVendorName_val_ptr_ptr, size_t *mib_rdbmsDbVendorName_val_ptr_len_ptr, char *raw_rdbmsDbVendorName_val_ptr, size_t raw_rdbmsDbVendorName_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbVendorName_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbVendorName_val_ptr_ptr) && (NULL != mib_rdbmsDbVendorName_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbVendorName_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsDbVendorName non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbVendorName_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbVendorName_val_ptr_ptr) || (*mib_rdbmsDbVendorName_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbVendorName_val_ptr_ptr = realloc( *mib_rdbmsDbVendorName_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbVendorName_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbVendorName_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbVendorName_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbVendorName_val_ptr_ptr, raw_rdbmsDbVendorName_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbVendorName_map */

/**
 * Extract the current value of the rdbmsDbVendorName data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbVendorName_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsDbVendorName_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbVendorName.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbVendorName_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbVendorName_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbVendorName_get( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbVendorName_val_ptr_ptr, size_t *rdbmsDbVendorName_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbVendorName_val_ptr_ptr) && (NULL != *rdbmsDbVendorName_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbVendorName_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbVendorName_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbVendorName data.
 * set (* rdbmsDbVendorName_val_ptr_ptr ) and (* rdbmsDbVendorName_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbVendorName data
     */
    if ((NULL == (* rdbmsDbVendorName_val_ptr_ptr )) ||
        ((* rdbmsDbVendorName_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbVendorName_len * sizeof((* rdbmsDbVendorName_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbVendorName data
         */
        (* rdbmsDbVendorName_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbVendorName_len * sizeof((* rdbmsDbVendorName_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbVendorName_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbVendorName_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbVendorName_len * sizeof((* rdbmsDbVendorName_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbVendorName_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbVendorName, (* rdbmsDbVendorName_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbVendorName_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsDbEntry.rdbmsDbName
 * rdbmsDbName is subid 4 of rdbmsDbEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.1.1.4
 * Description:
The name of this database, in a product specific format.  The
           product may need to qualify the name in some way to resolve
           conflicts if it is possible for a database name to be
           duplicated on a host.  It might be necessary to construct a
           hierarchical name embedding the RDBMS instance/installation
           on the host, and/or the owner of the database.  For instance,
           '/test-installation/database-owner/database-name'.
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
 * default-node-rdbmsDbName.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbName_map(char **mib_rdbmsDbName_val_ptr_ptr, size_t *mib_rdbmsDbName_val_ptr_len_ptr, char *raw_rdbmsDbName_val_ptr, size_t raw_rdbmsDbName_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbName_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbName_val_ptr_ptr) && (NULL != mib_rdbmsDbName_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbName_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsDbName non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbName_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbName_val_ptr_ptr) || (*mib_rdbmsDbName_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbName_val_ptr_ptr = realloc( *mib_rdbmsDbName_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbName_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbName_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbName_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbName_val_ptr_ptr, raw_rdbmsDbName_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbName_map */

/**
 * Extract the current value of the rdbmsDbName data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbName_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsDbName_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbName.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbName_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbName_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbName_get( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbName_val_ptr_ptr, size_t *rdbmsDbName_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbName_val_ptr_ptr) && (NULL != *rdbmsDbName_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbName_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbName_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbName data.
 * set (* rdbmsDbName_val_ptr_ptr ) and (* rdbmsDbName_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbName data
     */
    if ((NULL == (* rdbmsDbName_val_ptr_ptr )) ||
        ((* rdbmsDbName_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbName_len * sizeof((* rdbmsDbName_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbName data
         */
        (* rdbmsDbName_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbName_len * sizeof((* rdbmsDbName_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbName_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbName_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbName_len * sizeof((* rdbmsDbName_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbName_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbName, (* rdbmsDbName_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbName_get */

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
 * map a value from its original native format to the MIB format.
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_ERROR           : Any other error
 *
 * @note parameters follow the memset convention (dest, src).
 *
 * @note generation and use of this function can be turned off by re-running
 * mib2c after adding the following line to the file
 * default-node-rdbmsDbContact.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsDbContact_map(char **mib_rdbmsDbContact_val_ptr_ptr, size_t *mib_rdbmsDbContact_val_ptr_len_ptr, char *raw_rdbmsDbContact_val_ptr, size_t raw_rdbmsDbContact_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsDbContact_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsDbContact_val_ptr_ptr) && (NULL != mib_rdbmsDbContact_val_ptr_len_ptr));

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbContact_map","called\n"));

    /*
     * TODO:241:r: |-> Implement rdbmsDbContact non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsDbContact_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsDbContact_val_ptr_ptr) || (*mib_rdbmsDbContact_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsDbContact_val_ptr_ptr = realloc( *mib_rdbmsDbContact_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsDbContact_val_ptr_ptr));
        if(NULL == *mib_rdbmsDbContact_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsDbContact_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsDbContact_val_ptr_ptr, raw_rdbmsDbContact_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsDbContact_map */

/**
 * Extract the current value of the rdbmsDbContact data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsDbContact_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsDbContact_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsDbContact.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsDbContact_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsDbContact_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsDbContact_get( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbContact_val_ptr_ptr, size_t *rdbmsDbContact_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsDbContact_val_ptr_ptr) && (NULL != *rdbmsDbContact_val_ptr_ptr));
   netsnmp_assert( NULL != rdbmsDbContact_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbContact_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsDbContact data.
 * set (* rdbmsDbContact_val_ptr_ptr ) and (* rdbmsDbContact_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for rdbmsDbContact data
     */
    if ((NULL == (* rdbmsDbContact_val_ptr_ptr )) ||
        ((* rdbmsDbContact_val_ptr_len_ptr ) < (rowreq_ctx->data.rdbmsDbContact_len * sizeof((* rdbmsDbContact_val_ptr_ptr )[0])))) {
        /*
         * allocate space for rdbmsDbContact data
         */
        (* rdbmsDbContact_val_ptr_ptr ) = malloc(rowreq_ctx->data.rdbmsDbContact_len * sizeof((* rdbmsDbContact_val_ptr_ptr )[0]));
        if(NULL == (* rdbmsDbContact_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* rdbmsDbContact_val_ptr_len_ptr ) = rowreq_ctx->data.rdbmsDbContact_len * sizeof((* rdbmsDbContact_val_ptr_ptr )[0]);
    memcpy( (* rdbmsDbContact_val_ptr_ptr ), rowreq_ctx->data.rdbmsDbContact, (* rdbmsDbContact_val_ptr_len_ptr ) );

    return MFD_SUCCESS;
} /* rdbmsDbContact_get */



/** @} */
