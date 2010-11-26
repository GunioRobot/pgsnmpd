/*-------------------------------------------------------------------------
 * rdbmsRelTable_data_get.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsRelTable_data_get.c,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "rdbmsRelTable.h"


/** @defgroup data_get data_get: Routines to get data
 *
 * TODO:230:M: Implement rdbmsRelTable get routines.
 * TODO:240:M: Implement rdbmsRelTable mapping routines (if any).
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
 *** Table rdbmsRelTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsRelTable is subid 9 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.9, length: 9
*/

/* ---------------------------------------------------------------------
 * TODO:200:r: Implement rdbmsRelTable data context functions.
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
rdbmsRelTable_indexes_set_tbl_idx(rdbmsRelTable_mib_index *tbl_idx, long rdbmsDbIndex_val, long applIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelTable_indexes_set_tbl_idx","called\n"));

    /* rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->rdbmsDbIndex = rdbmsDbIndex_val;
    
    /* applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    tbl_idx->applIndex = applIndex_val;
    

    return MFD_SUCCESS;
} /* rdbmsRelTable_indexes_set_tbl_idx */

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
rdbmsRelTable_indexes_set(rdbmsRelTable_rowreq_ctx *rowreq_ctx, long rdbmsDbIndex_val, long applIndex_val)
{
    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelTable_indexes_set","called\n"));

    if(MFD_SUCCESS != rdbmsRelTable_indexes_set_tbl_idx(&rowreq_ctx->tbl_idx
                                   , rdbmsDbIndex_val
                                   , applIndex_val
           ))
        return MFD_ERROR;

    /*
     * convert mib index to oid index
     */
    rowreq_ctx->oid_idx.len = sizeof(rowreq_ctx->oid_tmp) / sizeof(oid);
    if(0 != rdbmsRelTable_index_to_oid(&rowreq_ctx->oid_idx,
                                    &rowreq_ctx->tbl_idx)) {
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* rdbmsRelTable_indexes_set */


/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsRelEntry.rdbmsRelState
 * rdbmsRelState is subid 1 of rdbmsRelEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.9.1.1
 * Description:
The state of this server's access to this database.
           Active(2) means the server is actively using the database.
           Available(3) means the server could use the database if
           necessary.  Restricted(4) means the database is in some
           administratively determined state of less-than-complete
           availability.  Unavailable(5) means the database is not
           available through this server.  Other(1) means the
           database/server is in some other condition, possibly
           described in the vendor private MIB.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  1      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 * Enum range: 3/8. Values:  other(1), active(2), available(3), restricted(4), unavailable(5)
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
 * default-node-rdbmsRelState.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsRelState_map(u_long *mib_rdbmsRelState_val_ptr, u_long raw_rdbmsRelState_val)
{
    netsnmp_assert(NULL != mib_rdbmsRelState_val_ptr);
    
    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelState_map","called\n"));
    
    /*
     * TODO:241:o: |-> Implement rdbmsRelState enum mapping.
     * uses INTERNAL_* macros defined in the header files
     */
    switch(raw_rdbmsRelState_val) {
        case INTERNAL_RDBMSRELSTATE_OTHER:
             *mib_rdbmsRelState_val_ptr = RDBMSRELSTATE_OTHER;
             break;

        case INTERNAL_RDBMSRELSTATE_ACTIVE:
             *mib_rdbmsRelState_val_ptr = RDBMSRELSTATE_ACTIVE;
             break;

        case INTERNAL_RDBMSRELSTATE_AVAILABLE:
             *mib_rdbmsRelState_val_ptr = RDBMSRELSTATE_AVAILABLE;
             break;

        case INTERNAL_RDBMSRELSTATE_RESTRICTED:
             *mib_rdbmsRelState_val_ptr = RDBMSRELSTATE_RESTRICTED;
             break;

        case INTERNAL_RDBMSRELSTATE_UNAVAILABLE:
             *mib_rdbmsRelState_val_ptr = RDBMSRELSTATE_UNAVAILABLE;
             break;

             default:
                 snmp_log(LOG_ERR, "couldn't map value %ld for rdbmsRelState\n", raw_rdbmsRelState_val );
                 return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* rdbmsRelState_map */

/**
 * Extract the current value of the rdbmsRelState data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsRelState_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
rdbmsRelState_get( rdbmsRelTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsRelState_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != rdbmsRelState_val_ptr );


    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelState_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the rdbmsRelState data.
 * set (* rdbmsRelState_val_ptr ) from rowreq_ctx->data
 */
    (* rdbmsRelState_val_ptr ) = rowreq_ctx->data.rdbmsRelState;

    return MFD_SUCCESS;
} /* rdbmsRelState_get */

/*---------------------------------------------------------------------
 * RDBMS-MIB::rdbmsRelEntry.rdbmsRelActiveTime
 * rdbmsRelActiveTime is subid 2 of rdbmsRelEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.39.1.9.1.2
 * Description:
The time the database was made active by the server.  If an
           instance of rdbmsRelState is not active(1), then attempts to
           access the corresponding instance of this object may result
           in either noSuchName (SNMPv1) or noSuchInstance (SNMPv2)
           being returned by the agent.
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
 * default-node-rdbmsRelActiveTime.m2d :
 *   @eval $m2c_node_skip_mapping = 1@
 *
 * @remark
 *  If the values for your data type don't exactly match the
 *  possible values defined by the mib, you should map them here.
 *  Otherwise, just do a direct copy.
 */
int
rdbmsRelActiveTime_map(char **mib_rdbmsRelActiveTime_val_ptr_ptr, size_t *mib_rdbmsRelActiveTime_val_ptr_len_ptr, char *raw_rdbmsRelActiveTime_val_ptr, size_t raw_rdbmsRelActiveTime_val_ptr_len, int allow_realloc)
{
    int converted_len;

    netsnmp_assert(NULL != raw_rdbmsRelActiveTime_val_ptr);
    netsnmp_assert((NULL != mib_rdbmsRelActiveTime_val_ptr_ptr) && (NULL != mib_rdbmsRelActiveTime_val_ptr_len_ptr));
    
    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelActiveTime_map","called\n"));
    
    /*
     * TODO:241:r: |-> Implement rdbmsRelActiveTime non-integer mapping
     * it is hard to autogenerate code for mapping types that are not simple
     * integers, so here is an idea of what you might need to do. It will
     * probably need some tweaking to get right.
     */
    /*
     * if the length of the raw data doesn't directly correspond with
     * the length of the mib data, set converted_len to the
     * space required.
     */
    converted_len = raw_rdbmsRelActiveTime_val_ptr_len; /* assume equal */
    if((NULL == *mib_rdbmsRelActiveTime_val_ptr_ptr) || (*mib_rdbmsRelActiveTime_val_ptr_len_ptr < converted_len)) {
        if(! allow_realloc) {
            snmp_log(LOG_ERR,"not enough space for value mapping\n");
            return SNMP_ERR_GENERR;
        }
        *mib_rdbmsRelActiveTime_val_ptr_ptr = realloc( *mib_rdbmsRelActiveTime_val_ptr_ptr, converted_len * sizeof(**mib_rdbmsRelActiveTime_val_ptr_ptr));
        if(NULL == *mib_rdbmsRelActiveTime_val_ptr_ptr) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return SNMP_ERR_GENERR;
        }
    }
    *mib_rdbmsRelActiveTime_val_ptr_len_ptr = converted_len;
    memcpy( *mib_rdbmsRelActiveTime_val_ptr_ptr, raw_rdbmsRelActiveTime_val_ptr, converted_len );

    return MFD_SUCCESS;
} /* rdbmsRelActiveTime_map */

/**
 * Extract the current value of the rdbmsRelActiveTime data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param rdbmsRelActiveTime_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param rdbmsRelActiveTime_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by rdbmsRelActiveTime.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*rdbmsRelActiveTime_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update rdbmsRelActiveTime_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
rdbmsRelActiveTime_get( rdbmsRelTable_rowreq_ctx *rowreq_ctx, char **rdbmsRelActiveTime_val_ptr_ptr, size_t *rdbmsRelActiveTime_val_ptr_len_ptr )
{
	int rc;
   /** we should have a pointer and enough storage */
   netsnmp_assert( (NULL != rdbmsRelActiveTime_val_ptr_ptr) && (NULL != *rdbmsRelActiveTime_val_ptr_ptr));
   netsnmp_assert( (NULL != rdbmsRelActiveTime_val_ptr_len_ptr) && ((* rdbmsRelActiveTime_val_ptr_len_ptr) >= 11));

   /*
    * TODO:231:o: |-> copy rdbmsRelActiveTime data.
    * get the date from your context pointer.
    */

   /* call convenience function to set data */
   rc = netsnmp_dateandtime_set_buf_from_vars((u_char *)*rdbmsRelActiveTime_val_ptr_ptr, rdbmsRelActiveTime_val_ptr_len_ptr,
	rowreq_ctx->data.activeTimeYear,
	rowreq_ctx->data.activeTimeMonth,
	rowreq_ctx->data.activeTimeDay,
	rowreq_ctx->data.activeTimeHour,
	rowreq_ctx->data.activeTimeMinutes,
	rowreq_ctx->data.activeTimeSeconds,
	rowreq_ctx->data.activeTimeDeciSeconds,
	rowreq_ctx->data.activeTimeUtcOffsetDirection,
	rowreq_ctx->data.activeTimeUtcOffsetHours,
	rowreq_ctx->data.activeTimeUtcOffsetMinutes);
   if(rc != SNMP_ERR_NOERROR)
      return rc;


    return MFD_SUCCESS;
} /* rdbmsRelActiveTime_get */



/** @} */
