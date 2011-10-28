/*-------------------------------------------------------------------------
 * rdbmsSrvParamTable.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvParamTable.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVPARAMTABLE_H
#define RDBMSSRVPARAMTABLE_H

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
config_require(RDBMS-MIB/rdbmsSrvParamTable/rdbmsSrvParamTable_interface);
config_require(RDBMS-MIB/rdbmsSrvParamTable/rdbmsSrvParamTable_data_access);
config_require(RDBMS-MIB/rdbmsSrvParamTable/rdbmsSrvParamTable_data_get);
config_require(RDBMS-MIB/rdbmsSrvParamTable/rdbmsSrvParamTable_data_set);
    /* *INDENT-ON*  */

/* OID and column number definitions for  */
#include "rdbmsSrvParamTable_oids.h"

/* enum definions */
#include "rdbmsSrvParamTable_enums.h"

/* *********************************************************************
 * function declarations
 */
void init_rdbmsSrvParamTable(void);

/* *********************************************************************
 * Table declarations
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
/* *********************************************************************
 * When you register your mib, you get to provide a generic
 * pointer that will be passed back to you for most of the
 * functions calls.
 *
 * TODO:100:r: Review all context structures
 */
    /*
     * TODO:101:o: |-> Review rdbmsSrvParamTable registration context.
     */
typedef netsnmp_data_list * rdbmsSrvParamTable_registration_ptr;

/**********************************************************************/
/*
 * TODO:110:r: |-> Review rdbmsSrvParamTable data context structure.
 * This structure is used to represent the data for rdbmsSrvParamTable.
 */
/*
 * This structure contains storage for all the columns defined in the
 * rdbmsSrvParamTable.
 */
typedef struct rdbmsSrvParamTable_data_s {

        /*
         * rdbmsSrvParamID(3)/AutonomousType/ASN_OBJECT_ID/oid(oid)//L/A/w/e/r/d/h
         */
   oid   rdbmsSrvParamID[128];
size_t      rdbmsSrvParamID_len; /* # of oid elements, not bytes */

        /*
         * rdbmsSrvParamCurrValue(4)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H
         */
   char   rdbmsSrvParamCurrValue[255];
size_t      rdbmsSrvParamCurrValue_len; /* # of char elements, not bytes */

        /*
         * rdbmsSrvParamComment(5)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H
         */
   char   rdbmsSrvParamComment[255];
size_t      rdbmsSrvParamComment_len; /* # of char elements, not bytes */

} rdbmsSrvParamTable_data;


/*
 * TODO:120:r: |-> Review rdbmsSrvParamTable mib index.
 * This structure is used to represent the index for rdbmsSrvParamTable.
 */
typedef struct rdbmsSrvParamTable_mib_index_s {

        /*
         * applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   applIndex;

        /*
         * rdbmsSrvParamName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
         */
   char   rdbmsSrvParamName[64];
   size_t      rdbmsSrvParamName_len;

        /*
         * rdbmsSrvParamSubIndex(2)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   rdbmsSrvParamSubIndex;


} rdbmsSrvParamTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review rdbmsSrvParamTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
     *
     * BE VERY CAREFUL TO TAKE INTO ACCOUNT THE MAXIMUM
     * POSSIBLE LENGHT FOR EVERY VARIABLE LENGTH INDEX!
     * Guessing 128 - col/entry(2)  - oid len(9)
*/
#define MAX_rdbmsSrvParamTable_IDX_LEN     67


/* *********************************************************************
 * TODO:130:o: |-> Review rdbmsSrvParamTable Row request (rowreq) context.
 * When your functions are called, you will be passed a
 * rdbmsSrvParamTable_rowreq_ctx pointer.
 */
typedef struct rdbmsSrvParamTable_rowreq_ctx_s {

    /** this must be first for container compare to work */
    netsnmp_index        oid_idx;
    oid                  oid_tmp[MAX_rdbmsSrvParamTable_IDX_LEN];

    rdbmsSrvParamTable_mib_index        tbl_idx;

    rdbmsSrvParamTable_data              data;

    /*
     * flags per row. Currently, the first (lower) 8 bits are reserved
     * for the user. See mfd.h for other flags.
     */
    u_int                       rowreq_flags;

    /*
     * implementor's context pointer (provided during registration)
     */
    rdbmsSrvParamTable_registration_ptr rdbmsSrvParamTable_reg;

    /*
     * TODO:131:o: |   |-> Add useful data to rdbmsSrvParamTable rowreq context.
     */

    /*
     * storage for future expansion
     */
    netsnmp_data_list             *rdbmsSrvParamTable_data_list;

} rdbmsSrvParamTable_rowreq_ctx;

typedef struct rdbmsSrvParamTable_ref_rowreq_ctx_s {
    rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx;
} rdbmsSrvParamTable_ref_rowreq_ctx;

/* *********************************************************************
 * function prototypes
 */
    int rdbmsSrvParamTable_pre_request(rdbmsSrvParamTable_registration_ptr user_context);
    int rdbmsSrvParamTable_post_request(rdbmsSrvParamTable_registration_ptr user_context);


extern oid rdbmsSrvParamTable_oid[];
extern int rdbmsSrvParamTable_oid_size;


#include "rdbmsSrvParamTable_interface.h"
#include "rdbmsSrvParamTable_data_access.h"
#include "rdbmsSrvParamTable_data_get.h"
#include "rdbmsSrvParamTable_data_set.h"

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

#endif /* RDBMSSRVPARAMTABLE_H */
