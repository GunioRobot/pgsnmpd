/*-------------------------------------------------------------------------
 * rdbmsDbTable_data_set.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable_data_set.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBTABLE_DATA_SET_H
#define RDBMSDBTABLE_DATA_SET_H

#ifdef __cplusplus
extern "C" {
#endif

/* *********************************************************************
 * SET function declarations
 */

/* *********************************************************************
 * SET Table declarations
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
int rdbmsDbIndex_check_index( rdbmsDbTable_rowreq_ctx *rowreq_ctx ); /* internal */


int rdbmsDbTable_undo_setup( rdbmsDbTable_rowreq_ctx *rowreq_ctx);
int rdbmsDbTable_undo_cleanup( rdbmsDbTable_rowreq_ctx *rowreq_ctx);
int rdbmsDbTable_commit( rdbmsDbTable_rowreq_ctx *rowreq_ctx);
int rdbmsDbTable_undo_commit( rdbmsDbTable_rowreq_ctx *rowreq_ctx);


int rdbmsDbPrivateMibOID_check_value( rdbmsDbTable_rowreq_ctx *rowreq_ctx, oid *rdbmsDbPrivateMibOID_val_ptr,  size_t rdbmsDbPrivateMibOID_val_ptr_len);
int rdbmsDbPrivateMibOID_undo_setup( rdbmsDbTable_rowreq_ctx *rowreq_ctx );
int rdbmsDbPrivateMibOID_set( rdbmsDbTable_rowreq_ctx *rowreq_ctx, oid *rdbmsDbPrivateMibOID_val_ptr,  size_t rdbmsDbPrivateMibOID_val_ptr_len );
int rdbmsDbPrivateMibOID_undo( rdbmsDbTable_rowreq_ctx *rowreq_ctx );

int rdbmsDbVendorName_check_value( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char *rdbmsDbVendorName_val_ptr,  size_t rdbmsDbVendorName_val_ptr_len);
int rdbmsDbVendorName_undo_setup( rdbmsDbTable_rowreq_ctx *rowreq_ctx );
int rdbmsDbVendorName_set( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char *rdbmsDbVendorName_val_ptr,  size_t rdbmsDbVendorName_val_ptr_len );
int rdbmsDbVendorName_undo( rdbmsDbTable_rowreq_ctx *rowreq_ctx );

int rdbmsDbName_check_value( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char *rdbmsDbName_val_ptr,  size_t rdbmsDbName_val_ptr_len);
int rdbmsDbName_undo_setup( rdbmsDbTable_rowreq_ctx *rowreq_ctx );
int rdbmsDbName_set( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char *rdbmsDbName_val_ptr,  size_t rdbmsDbName_val_ptr_len );
int rdbmsDbName_undo( rdbmsDbTable_rowreq_ctx *rowreq_ctx );

int rdbmsDbContact_check_value( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char *rdbmsDbContact_val_ptr,  size_t rdbmsDbContact_val_ptr_len);
int rdbmsDbContact_undo_setup( rdbmsDbTable_rowreq_ctx *rowreq_ctx );
int rdbmsDbContact_set( rdbmsDbTable_rowreq_ctx *rowreq_ctx, char *rdbmsDbContact_val_ptr,  size_t rdbmsDbContact_val_ptr_len );
int rdbmsDbContact_undo( rdbmsDbTable_rowreq_ctx *rowreq_ctx );


int rdbmsDbTable_check_dependencies(rdbmsDbTable_rowreq_ctx *ctx);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBTABLE_DATA_SET_H */
