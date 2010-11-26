/*-------------------------------------------------------------------------
 * rdbmsSrvInfoTable_data_get.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvInfoTable_data_get.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVINFOTABLE_DATA_GET_H
#define RDBMSSRVINFOTABLE_DATA_GET_H

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
 *** Table rdbmsSrvInfoTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvInfoTable is subid 6 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.6, length: 9
*/
    /*
     * indexes
     */
    int applIndex_map(long *mib_applIndex_val_ptr, long raw_applIndex_val);

    int rdbmsSrvInfoStartupTime_map(char **mib_rdbmsSrvInfoStartupTime_val_ptr_ptr, size_t *mib_rdbmsSrvInfoStartupTime_val_ptr_len_ptr, char *raw_rdbmsSrvInfoStartupTime_val_ptr, size_t raw_rdbmsSrvInfoStartupTime_val_ptr_len, int allow_realloc);
    int rdbmsSrvInfoStartupTime_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, char **rdbmsSrvInfoStartupTime_val_ptr_ptr, size_t *rdbmsSrvInfoStartupTime_val_ptr_len_ptr );
    int rdbmsSrvInfoFinishedTransactions_map(u_long *mib_rdbmsSrvInfoFinishedTransactions_val_ptr, u_long raw_rdbmsSrvInfoFinishedTransactions_val);
    int rdbmsSrvInfoFinishedTransactions_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoFinishedTransactions_val_ptr );
    int rdbmsSrvInfoDiskReads_map(u_long *mib_rdbmsSrvInfoDiskReads_val_ptr, u_long raw_rdbmsSrvInfoDiskReads_val);
    int rdbmsSrvInfoDiskReads_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoDiskReads_val_ptr );
    int rdbmsSrvInfoLogicalReads_map(u_long *mib_rdbmsSrvInfoLogicalReads_val_ptr, u_long raw_rdbmsSrvInfoLogicalReads_val);
    int rdbmsSrvInfoLogicalReads_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoLogicalReads_val_ptr );
    int rdbmsSrvInfoDiskWrites_map(u_long *mib_rdbmsSrvInfoDiskWrites_val_ptr, u_long raw_rdbmsSrvInfoDiskWrites_val);
    int rdbmsSrvInfoDiskWrites_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoDiskWrites_val_ptr );
    int rdbmsSrvInfoLogicalWrites_map(u_long *mib_rdbmsSrvInfoLogicalWrites_val_ptr, u_long raw_rdbmsSrvInfoLogicalWrites_val);
    int rdbmsSrvInfoLogicalWrites_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoLogicalWrites_val_ptr );
    int rdbmsSrvInfoPageReads_map(u_long *mib_rdbmsSrvInfoPageReads_val_ptr, u_long raw_rdbmsSrvInfoPageReads_val);
    int rdbmsSrvInfoPageReads_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoPageReads_val_ptr );
    int rdbmsSrvInfoPageWrites_map(u_long *mib_rdbmsSrvInfoPageWrites_val_ptr, u_long raw_rdbmsSrvInfoPageWrites_val);
    int rdbmsSrvInfoPageWrites_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoPageWrites_val_ptr );
    int rdbmsSrvInfoDiskOutOfSpaces_map(u_long *mib_rdbmsSrvInfoDiskOutOfSpaces_val_ptr, u_long raw_rdbmsSrvInfoDiskOutOfSpaces_val);
    int rdbmsSrvInfoDiskOutOfSpaces_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoDiskOutOfSpaces_val_ptr );
    int rdbmsSrvInfoHandledRequests_map(u_long *mib_rdbmsSrvInfoHandledRequests_val_ptr, u_long raw_rdbmsSrvInfoHandledRequests_val);
    int rdbmsSrvInfoHandledRequests_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoHandledRequests_val_ptr );
    int rdbmsSrvInfoRequestRecvs_map(u_long *mib_rdbmsSrvInfoRequestRecvs_val_ptr, u_long raw_rdbmsSrvInfoRequestRecvs_val);
    int rdbmsSrvInfoRequestRecvs_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoRequestRecvs_val_ptr );
    int rdbmsSrvInfoRequestSends_map(u_long *mib_rdbmsSrvInfoRequestSends_val_ptr, u_long raw_rdbmsSrvInfoRequestSends_val);
    int rdbmsSrvInfoRequestSends_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoRequestSends_val_ptr );
    int rdbmsSrvInfoHighwaterInboundAssociations_map(u_long *mib_rdbmsSrvInfoHighwaterInboundAssociations_val_ptr, u_long raw_rdbmsSrvInfoHighwaterInboundAssociations_val);
    int rdbmsSrvInfoHighwaterInboundAssociations_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoHighwaterInboundAssociations_val_ptr );
    int rdbmsSrvInfoMaxInboundAssociations_map(u_long *mib_rdbmsSrvInfoMaxInboundAssociations_val_ptr, u_long raw_rdbmsSrvInfoMaxInboundAssociations_val);
    int rdbmsSrvInfoMaxInboundAssociations_get( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, u_long * rdbmsSrvInfoMaxInboundAssociations_val_ptr );


int rdbmsSrvInfoTable_indexes_set_tbl_idx(rdbmsSrvInfoTable_mib_index *tbl_idx, long applIndex_val);
int rdbmsSrvInfoTable_indexes_set(rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, long applIndex_val);




#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVINFOTABLE_DATA_GET_H */
/** @} */
