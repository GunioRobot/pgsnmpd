/*-------------------------------------------------------------------------
 * rdbmsDbTable.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBTABLE_H
#define RDBMSDBTABLE_H

#ifdef __cplusplus
extern "C" {
#endif


/** @defgroup misc misc: Miscelaneous routines
 *
 * @{
 */
#include <net-snmp/library/asn1.h>

/* other required module components */
    /* *INDENT-OFF*  */
config_require(RDBMS-MIB/rdbmsDbTable/rdbmsDbTable_interface);
config_require(RDBMS-MIB/rdbmsDbTable/rdbmsDbTable_data_access);
config_require(RDBMS-MIB/rdbmsDbTable/rdbmsDbTable_data_get);
config_require(RDBMS-MIB/rdbmsDbTable/rdbmsDbTable_data_set);
    /* *INDENT-ON*  */

/* OID and column number definitions for  */
#include "rdbmsDbTable_oids.h"

/* enum definions */
#include "rdbmsDbTable_enums.h"

/* *********************************************************************
 * function declarations
 */
void init_rdbmsDbTable(void);

/* *********************************************************************
 * Table declarations
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
/* *********************************************************************
 * When you register your mib, you get to provide a generic
 * pointer that will be passed back to you for most of the
 * functions calls.
 *
 * TODO:100:r: Review all context structures
 */
    /*
     * TODO:101:o: |-> Review rdbmsDbTable registration context.
     */
typedef netsnmp_data_list * rdbmsDbTable_registration_ptr;

/**********************************************************************/
/*
 * TODO:110:r: |-> Review rdbmsDbTable data context structure.
 * This structure is used to represent the data for rdbmsDbTable.
 */
/*
 * This structure contains storage for all the columns defined in the
 * rdbmsDbTable.
 */
typedef struct rdbmsDbTable_data_s {

        /*
         * rdbmsDbPrivateMibOID(2)/OBJECTID/ASN_OBJECT_ID/oid(oid)//L/A/w/e/r/d/h
         */
   oid   rdbmsDbPrivateMibOID[128];
size_t      rdbmsDbPrivateMibOID_len; /* # of oid elements, not bytes */

        /*
         * rdbmsDbVendorName(3)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
         */
   char   rdbmsDbVendorName[255];
size_t      rdbmsDbVendorName_len; /* # of char elements, not bytes */

        /*
         * rdbmsDbName(4)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
         */
   char   rdbmsDbName[255];
size_t      rdbmsDbName_len; /* # of char elements, not bytes */

        /*
         * rdbmsDbContact(5)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H
         */
   char   rdbmsDbContact[255];
size_t      rdbmsDbContact_len; /* # of char elements, not bytes */

} rdbmsDbTable_data;


/* *********************************************************************
 * TODO:115:o: |-> Review rdbmsDbTable undo context.
 * We're just going to use the same data structure for our
 * undo_context. If you want to do something more efficent,
 * define your typedef here.
 */
typedef rdbmsDbTable_data rdbmsDbTable_undo_data;

/*
 * TODO:120:r: |-> Review rdbmsDbTable mib index.
 * This structure is used to represent the index for rdbmsDbTable.
 */
typedef struct rdbmsDbTable_mib_index_s {

        /*
         * rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   rdbmsDbIndex;


} rdbmsDbTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review rdbmsDbTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
*/
#define MAX_rdbmsDbTable_IDX_LEN     1


/* *********************************************************************
 * TODO:130:o: |-> Review rdbmsDbTable Row request (rowreq) context.
 * When your functions are called, you will be passed a
 * rdbmsDbTable_rowreq_ctx pointer.
 */
typedef struct rdbmsDbTable_rowreq_ctx_s {

    /** this must be first for container compare to work */
    netsnmp_index        oid_idx;
    oid                  oid_tmp[MAX_rdbmsDbTable_IDX_LEN];

    rdbmsDbTable_mib_index        tbl_idx;

    rdbmsDbTable_data              data;
    rdbmsDbTable_undo_data       * undo;
    unsigned int                column_set_flags; /* flags for set columns */


    /*
     * flags per row. Currently, the first (lower) 8 bits are reserved
     * for the user. See mfd.h for other flags.
     */
    u_int                       rowreq_flags;

    /*
     * implementor's context pointer (provided during registration)
     */
    rdbmsDbTable_registration_ptr rdbmsDbTable_reg;

    /*
     * TODO:131:o: |   |-> Add useful data to rdbmsDbTable rowreq context.
     */

    /*
     * storage for future expansion
     */
    netsnmp_data_list             *rdbmsDbTable_data_list;

} rdbmsDbTable_rowreq_ctx;

typedef struct rdbmsDbTable_ref_rowreq_ctx_s {
    rdbmsDbTable_rowreq_ctx *rowreq_ctx;
} rdbmsDbTable_ref_rowreq_ctx;

/* *********************************************************************
 * function prototypes
 */
    int rdbmsDbTable_pre_request(rdbmsDbTable_registration_ptr user_context);
    int rdbmsDbTable_post_request(rdbmsDbTable_registration_ptr user_context);

    int rdbmsDbTable_check_dependencies(rdbmsDbTable_rowreq_ctx * rowreq_ctx);
    int rdbmsDbTable_commit(rdbmsDbTable_rowreq_ctx * rowreq_ctx);

    void initialize_table_rdbmsDbTable(void);

extern oid rdbmsDbTable_oid[];
extern int rdbmsDbTable_oid_size;


#include "rdbmsDbTable_interface.h"
#include "rdbmsDbTable_data_access.h"
#include "rdbmsDbTable_data_get.h"
#include "rdbmsDbTable_data_set.h"

/*
 * DUMMY markers, ignore
 *
 * TODO:099:x: *************************************************************
 * TODO:199:x: *************************************************************
 * TODO:299:x: *************************************************************
 * TODO:399:x: *************************************************************
 * TODO:499:x: *************************************************************
 */

#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBTABLE_H */
