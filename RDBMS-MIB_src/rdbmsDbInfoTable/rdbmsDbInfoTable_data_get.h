/*-------------------------------------------------------------------------
 * rdbmsDbInfoTable_data_get.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbInfoTable_data_get.h,v 1.3 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBINFOTABLE_DATA_GET_H
#define RDBMSDBINFOTABLE_DATA_GET_H

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
 *** Table rdbmsDbInfoTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbInfoTable is subid 2 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.2, length: 9
*/
    /*
     * indexes
     */
    int rdbmsDbIndex_map(long *mib_rdbmsDbIndex_val_ptr, long raw_rdbmsDbIndex_val);

    int rdbmsDbInfoProductName_map(char **mib_rdbmsDbInfoProductName_val_ptr_ptr, size_t *mib_rdbmsDbInfoProductName_val_ptr_len_ptr, char *raw_rdbmsDbInfoProductName_val_ptr, size_t raw_rdbmsDbInfoProductName_val_ptr_len, int allow_realloc);
    int rdbmsDbInfoProductName_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbInfoProductName_val_ptr_ptr, size_t *rdbmsDbInfoProductName_val_ptr_len_ptr );
    int rdbmsDbInfoVersion_map(char **mib_rdbmsDbInfoVersion_val_ptr_ptr, size_t *mib_rdbmsDbInfoVersion_val_ptr_len_ptr, char *raw_rdbmsDbInfoVersion_val_ptr, size_t raw_rdbmsDbInfoVersion_val_ptr_len, int allow_realloc);
    int rdbmsDbInfoVersion_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbInfoVersion_val_ptr_ptr, size_t *rdbmsDbInfoVersion_val_ptr_len_ptr );
    int rdbmsDbInfoSizeUnits_map(u_long *mib_rdbmsDbInfoSizeUnits_val_ptr, u_long raw_rdbmsDbInfoSizeUnits_val);
    int rdbmsDbInfoSizeUnits_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsDbInfoSizeUnits_val_ptr );
    int rdbmsDbInfoSizeAllocated_map(long *mib_rdbmsDbInfoSizeAllocated_val_ptr, long raw_rdbmsDbInfoSizeAllocated_val);
    int rdbmsDbInfoSizeAllocated_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, long * rdbmsDbInfoSizeAllocated_val_ptr );
    int rdbmsDbInfoSizeUsed_map(long *mib_rdbmsDbInfoSizeUsed_val_ptr, long raw_rdbmsDbInfoSizeUsed_val);
    int rdbmsDbInfoSizeUsed_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, long * rdbmsDbInfoSizeUsed_val_ptr );
    int rdbmsDbInfoLastBackup_map(char **mib_rdbmsDbInfoLastBackup_val_ptr_ptr, size_t *mib_rdbmsDbInfoLastBackup_val_ptr_len_ptr, char *raw_rdbmsDbInfoLastBackup_val_ptr, size_t raw_rdbmsDbInfoLastBackup_val_ptr_len, int allow_realloc);
    int rdbmsDbInfoLastBackup_get( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbInfoLastBackup_val_ptr_ptr, size_t *rdbmsDbInfoLastBackup_val_ptr_len_ptr );


int rdbmsDbInfoTable_indexes_set_tbl_idx(rdbmsDbInfoTable_mib_index *tbl_idx, long rdbmsDbIndex_val);
int rdbmsDbInfoTable_indexes_set(rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx, long rdbmsDbIndex_val);




#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBINFOTABLE_DATA_GET_H */
/** @} */
