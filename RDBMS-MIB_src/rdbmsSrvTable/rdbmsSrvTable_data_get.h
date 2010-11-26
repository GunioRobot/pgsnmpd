/*-------------------------------------------------------------------------
 * rdbmsSrvTable_data_get.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvTable_data_get.h,v 1.4 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVTABLE_DATA_GET_H
#define RDBMSSRVTABLE_DATA_GET_H

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
 *** Table rdbmsSrvTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvTable is subid 5 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.5, length: 9
*/
    /*
     * indexes
     */
    int applIndex_map(long *mib_applIndex_val_ptr, long raw_applIndex_val);

    int rdbmsSrvPrivateMibOID_map(oid **mib_rdbmsSrvPrivateMibOID_val_ptr_ptr, size_t *mib_rdbmsSrvPrivateMibOID_val_ptr_len_ptr, oid *raw_rdbmsSrvPrivateMibOID_val_ptr, size_t raw_rdbmsSrvPrivateMibOID_val_ptr_len, int allow_realloc);
    int rdbmsSrvPrivateMibOID_get( rdbmsSrvTable_rowreq_ctx *rowreq_ctx, oid **rdbmsSrvPrivateMibOID_val_ptr_ptr, size_t *rdbmsSrvPrivateMibOID_val_ptr_len_ptr );
    int rdbmsSrvVendorName_map(char **mib_rdbmsSrvVendorName_val_ptr_ptr, size_t *mib_rdbmsSrvVendorName_val_ptr_len_ptr, char *raw_rdbmsSrvVendorName_val_ptr, size_t raw_rdbmsSrvVendorName_val_ptr_len, int allow_realloc);
    int rdbmsSrvVendorName_get( rdbmsSrvTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvVendorName_val_ptr_ptr, size_t *rdbmsSrvVendorName_val_ptr_len_ptr );
    int rdbmsSrvProductName_map(char **mib_rdbmsSrvProductName_val_ptr_ptr, size_t *mib_rdbmsSrvProductName_val_ptr_len_ptr, char *raw_rdbmsSrvProductName_val_ptr, size_t raw_rdbmsSrvProductName_val_ptr_len, int allow_realloc);
    int rdbmsSrvProductName_get( rdbmsSrvTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvProductName_val_ptr_ptr, size_t *rdbmsSrvProductName_val_ptr_len_ptr );
    int rdbmsSrvContact_map(char **mib_rdbmsSrvContact_val_ptr_ptr, size_t *mib_rdbmsSrvContact_val_ptr_len_ptr, char *raw_rdbmsSrvContact_val_ptr, size_t raw_rdbmsSrvContact_val_ptr_len, int allow_realloc);
    int rdbmsSrvContact_get( rdbmsSrvTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvContact_val_ptr_ptr, size_t *rdbmsSrvContact_val_ptr_len_ptr );


int rdbmsSrvTable_indexes_set_tbl_idx(rdbmsSrvTable_mib_index *tbl_idx, long applIndex_val);
int rdbmsSrvTable_indexes_set(rdbmsSrvTable_rowreq_ctx *rowreq_ctx, long applIndex_val);




#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVTABLE_DATA_GET_H */
/** @} */
