/*-------------------------------------------------------------------------
 * rdbmsDbParamTable_data_get.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbParamTable_data_get.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBPARAMTABLE_DATA_GET_H
#define RDBMSDBPARAMTABLE_DATA_GET_H

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
 *** Table rdbmsDbParamTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbParamTable is subid 3 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.3, length: 9
*/
    /*
     * indexes
     */
    int rdbmsDbParamName_map(char **mib_rdbmsDbParamName_val_ptr_ptr, size_t *mib_rdbmsDbParamName_val_ptr_len_ptr, char *raw_rdbmsDbParamName_val_ptr, size_t raw_rdbmsDbParamName_val_ptr_len, int allow_realloc);
    int rdbmsDbParamSubIndex_map(long *mib_rdbmsDbParamSubIndex_val_ptr, long raw_rdbmsDbParamSubIndex_val);

    int rdbmsDbParamID_map(oid **mib_rdbmsDbParamID_val_ptr_ptr, size_t *mib_rdbmsDbParamID_val_ptr_len_ptr, oid *raw_rdbmsDbParamID_val_ptr, size_t raw_rdbmsDbParamID_val_ptr_len, int allow_realloc);
    int rdbmsDbParamID_get( rdbmsDbParamTable_rowreq_ctx *rowreq_ctx, oid **rdbmsDbParamID_val_ptr_ptr, size_t *rdbmsDbParamID_val_ptr_len_ptr );
    int rdbmsDbParamCurrValue_map(char **mib_rdbmsDbParamCurrValue_val_ptr_ptr, size_t *mib_rdbmsDbParamCurrValue_val_ptr_len_ptr, char *raw_rdbmsDbParamCurrValue_val_ptr, size_t raw_rdbmsDbParamCurrValue_val_ptr_len, int allow_realloc);
    int rdbmsDbParamCurrValue_get( rdbmsDbParamTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbParamCurrValue_val_ptr_ptr, size_t *rdbmsDbParamCurrValue_val_ptr_len_ptr );
    int rdbmsDbParamComment_map(char **mib_rdbmsDbParamComment_val_ptr_ptr, size_t *mib_rdbmsDbParamComment_val_ptr_len_ptr, char *raw_rdbmsDbParamComment_val_ptr, size_t raw_rdbmsDbParamComment_val_ptr_len, int allow_realloc);
    int rdbmsDbParamComment_get( rdbmsDbParamTable_rowreq_ctx *rowreq_ctx, char **rdbmsDbParamComment_val_ptr_ptr, size_t *rdbmsDbParamComment_val_ptr_len_ptr );


int rdbmsDbParamTable_indexes_set_tbl_idx(rdbmsDbParamTable_mib_index *tbl_idx, long rdbmsDbIndex_val, char *rdbmsDbParamName_val_ptr,  size_t rdbmsDbParamName_val_ptr_len, long rdbmsDbParamSubIndex_val);
int rdbmsDbParamTable_indexes_set(rdbmsDbParamTable_rowreq_ctx *rowreq_ctx, long rdbmsDbIndex_val, char *rdbmsDbParamName_val_ptr,  size_t rdbmsDbParamName_val_ptr_len, long rdbmsDbParamSubIndex_val);




#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBPARAMTABLE_DATA_GET_H */
/** @} */
