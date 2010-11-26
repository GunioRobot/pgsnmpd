/*-------------------------------------------------------------------------
 * rdbmsDbLimitedResourceTable_data_get.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbLimitedResourceTable_data_get.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBLIMITEDRESOURCETABLE_DATA_GET_H
#define RDBMSDBLIMITEDRESOURCETABLE_DATA_GET_H

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
 *** Table rdbmsDbLimitedResourceTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbLimitedResourceTable is subid 4 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.4, length: 9
*/
    /*
     * indexes
     */
    int rdbmsDbIndex_map(long *mib_rdbmsDbIndex_val_ptr, long raw_rdbmsDbIndex_val);
    int rdbmsDbLimitedResourceName_map(char **mib_rdbmsDbLimitedResourceName_val_ptr_ptr, size_t *mib_rdbmsDbLimitedResourceName_val_ptr_len_ptr, char *raw_rdbmsDbLimitedResourceName_val_ptr, size_t raw_rdbmsDbLimitedResourceName_val_ptr_len, int allow_realloc);

    int rdbmsDbLimitedResourceID_map(oid **mib_rdbmsDbLimitedResourceID_val_ptr_ptr, size_t *mib_rdbmsDbLimitedResourceID_val_ptr_len_ptr, oid *raw_rdbmsDbLimitedResourceID_val_ptr, size_t raw_rdbmsDbLimitedResourceID_val_ptr_len, int allow_realloc);
    int rdbmsDbLimitedResourceID_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, oid **rdbmsDbLimitedResourceID_val_ptr_ptr, size_t *rdbmsDbLimitedResourceID_val_ptr_len_ptr );
    int rdbmsDbLimitedResourceLimit_map(long *mib_rdbmsDbLimitedResourceLimit_val_ptr, long raw_rdbmsDbLimitedResourceLimit_val);
    int rdbmsDbLimitedResourceLimit_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, long * rdbmsDbLimitedResourceLimit_val_ptr );
    int rdbmsDbLimitedResourceCurrent_map(long *mib_rdbmsDbLimitedResourceCurrent_val_ptr, long raw_rdbmsDbLimitedResourceCurrent_val);
    int rdbmsDbLimitedResourceCurrent_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, long * rdbmsDbLimitedResourceCurrent_val_ptr );
    int rdbmsDbLimitedResourceHighwater_map(long *mib_rdbmsDbLimitedResourceHighwater_val_ptr, long raw_rdbmsDbLimitedResourceHighwater_val);
    int rdbmsDbLimitedResourceHighwater_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, long * rdbmsDbLimitedResourceHighwater_val_ptr );
    int rdbmsDbLimitedResourceFailures_map(u_long *mib_rdbmsDbLimitedResourceFailures_val_ptr, u_long raw_rdbmsDbLimitedResourceFailures_val);
    int rdbmsDbLimitedResourceFailures_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsDbLimitedResourceFailures_val_ptr );
    int rdbmsDbLimitedResourceDescription_map(char **mib_rdbmsDbLimitedResourceDescription_val_ptr_ptr, size_t *mib_rdbmsDbLimitedResourceDescription_val_ptr_len_ptr, char *raw_rdbmsDbLimitedResourceDescription_val_ptr, size_t raw_rdbmsDbLimitedResourceDescription_val_ptr_len, int allow_realloc);
    int rdbmsDbLimitedResourceDescription_get( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbLimitedResourceDescription_val_ptr_ptr, size_t *rdbmsDbLimitedResourceDescription_val_ptr_len_ptr );


int rdbmsDbLimitedResourceTable_indexes_set_tbl_idx(rdbmsDbLimitedResourceTable_mib_index *tbl_idx, long rdbmsDbIndex_val, char *rdbmsDbLimitedResourceName_val_ptr,  size_t rdbmsDbLimitedResourceName_val_ptr_len);
int rdbmsDbLimitedResourceTable_indexes_set(rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx, long rdbmsDbIndex_val, char *rdbmsDbLimitedResourceName_val_ptr,  size_t rdbmsDbLimitedResourceName_val_ptr_len);




#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBLIMITEDRESOURCETABLE_DATA_GET_H */
/** @} */
