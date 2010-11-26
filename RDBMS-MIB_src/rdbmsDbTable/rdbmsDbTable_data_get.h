/*-------------------------------------------------------------------------
 * rdbmsDbTable_data_get.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable_data_get.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBTABLE_DATA_GET_H
#define RDBMSDBTABLE_DATA_GET_H

#ifdef __cplusplus
extern "C" {
#endif

/* *********************************************************************
 * GET function declarations
 */

/* *********************************************************************
 * GET Table declarations
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
     * indexes
     */
    int rdbmsDbIndex_map(long *mib_rdbmsDbIndex_val_ptr, long raw_rdbmsDbIndex_val);

    int rdbmsDbPrivateMibOID_map(oid **mib_rdbmsDbPrivateMibOID_val_ptr_ptr, size_t *mib_rdbmsDbPrivateMibOID_val_ptr_len_ptr, oid *raw_rdbmsDbPrivateMibOID_val_ptr, size_t raw_rdbmsDbPrivateMibOID_val_ptr_len, int allow_realloc);
    int rdbmsDbPrivateMibOID_get( rdbmsDbTable_rowreq_ctx *rowreq_ctx, oid **rdbmsDbPrivateMibOID_val_ptr_ptr, size_t *rdbmsDbPrivateMibOID_val_ptr_len_ptr );
    int rdbmsDbVendorName_map(char **mib_rdbmsDbVendorName_val_ptr_ptr, size_t *mib_rdbmsDbVendorName_val_ptr_len_ptr, char *raw_rdbmsDbVendorName_val_ptr, size_t raw_rdbmsDbVendorName_val_ptr_len, int allow_realloc);
    int rdbmsDbVendorName_get( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbVendorName_val_ptr_ptr, size_t *rdbmsDbVendorName_val_ptr_len_ptr );
    int rdbmsDbName_map(char **mib_rdbmsDbName_val_ptr_ptr, size_t *mib_rdbmsDbName_val_ptr_len_ptr, char *raw_rdbmsDbName_val_ptr, size_t raw_rdbmsDbName_val_ptr_len, int allow_realloc);
    int rdbmsDbName_get( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbName_val_ptr_ptr, size_t *rdbmsDbName_val_ptr_len_ptr );
    int rdbmsDbContact_map(char **mib_rdbmsDbContact_val_ptr_ptr, size_t *mib_rdbmsDbContact_val_ptr_len_ptr, char *raw_rdbmsDbContact_val_ptr, size_t raw_rdbmsDbContact_val_ptr_len, int allow_realloc);
    int rdbmsDbContact_get( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbContact_val_ptr_ptr, size_t *rdbmsDbContact_val_ptr_len_ptr );


int rdbmsDbTable_indexes_set_tbl_idx(rdbmsDbTable_mib_index *tbl_idx, long rdbmsDbIndex_val);
int rdbmsDbTable_indexes_set(rdbmsDbTable_rowreq_ctx *rowreq_ctx, long rdbmsDbIndex_val);




#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBTABLE_DATA_GET_H */
/** @} */
