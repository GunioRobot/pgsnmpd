/*-------------------------------------------------------------------------
 * rdbmsSrvParamTable_data_get.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvParamTable_data_get.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVPARAMTABLE_DATA_GET_H
#define RDBMSSRVPARAMTABLE_DATA_GET_H

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
 *** Table rdbmsSrvParamTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvParamTable is subid 7 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.7, length: 9
*/
    /*
     * indexes
     */
    int applIndex_map(long *mib_applIndex_val_ptr, long raw_applIndex_val);
    int rdbmsSrvParamName_map(char **mib_rdbmsSrvParamName_val_ptr_ptr, size_t *mib_rdbmsSrvParamName_val_ptr_len_ptr, char *raw_rdbmsSrvParamName_val_ptr, size_t raw_rdbmsSrvParamName_val_ptr_len, int allow_realloc);
    int rdbmsSrvParamSubIndex_map(long *mib_rdbmsSrvParamSubIndex_val_ptr, long raw_rdbmsSrvParamSubIndex_val);

    int rdbmsSrvParamID_map(oid **mib_rdbmsSrvParamID_val_ptr_ptr, size_t *mib_rdbmsSrvParamID_val_ptr_len_ptr, oid *raw_rdbmsSrvParamID_val_ptr, size_t raw_rdbmsSrvParamID_val_ptr_len, int allow_realloc);
    int rdbmsSrvParamID_get( rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx, oid **rdbmsSrvParamID_val_ptr_ptr, size_t *rdbmsSrvParamID_val_ptr_len_ptr );
    int rdbmsSrvParamCurrValue_map(char **mib_rdbmsSrvParamCurrValue_val_ptr_ptr, size_t *mib_rdbmsSrvParamCurrValue_val_ptr_len_ptr, char *raw_rdbmsSrvParamCurrValue_val_ptr, size_t raw_rdbmsSrvParamCurrValue_val_ptr_len, int allow_realloc);
    int rdbmsSrvParamCurrValue_get( rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvParamCurrValue_val_ptr_ptr, size_t *rdbmsSrvParamCurrValue_val_ptr_len_ptr );
    int rdbmsSrvParamComment_map(char **mib_rdbmsSrvParamComment_val_ptr_ptr, size_t *mib_rdbmsSrvParamComment_val_ptr_len_ptr, char *raw_rdbmsSrvParamComment_val_ptr, size_t raw_rdbmsSrvParamComment_val_ptr_len, int allow_realloc);
    int rdbmsSrvParamComment_get( rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvParamComment_val_ptr_ptr, size_t *rdbmsSrvParamComment_val_ptr_len_ptr );


int rdbmsSrvParamTable_indexes_set_tbl_idx(rdbmsSrvParamTable_mib_index *tbl_idx, long applIndex_val, char *rdbmsSrvParamName_val_ptr,  size_t rdbmsSrvParamName_val_ptr_len, long rdbmsSrvParamSubIndex_val);
int rdbmsSrvParamTable_indexes_set(rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx, long applIndex_val, char *rdbmsSrvParamName_val_ptr,  size_t rdbmsSrvParamName_val_ptr_len, long rdbmsSrvParamSubIndex_val);




#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVPARAMTABLE_DATA_GET_H */
/** @} */
