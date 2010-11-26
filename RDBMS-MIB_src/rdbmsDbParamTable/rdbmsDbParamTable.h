/*-------------------------------------------------------------------------
 * rdbmsDbParamTable.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbParamTable.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBPARAMTABLE_H
#define RDBMSDBPARAMTABLE_H

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
config_require(RDBMS-MIB/rdbmsDbParamTable/rdbmsDbParamTable_interface);
config_require(RDBMS-MIB/rdbmsDbParamTable/rdbmsDbParamTable_data_access);
config_require(RDBMS-MIB/rdbmsDbParamTable/rdbmsDbParamTable_data_get);
config_require(RDBMS-MIB/rdbmsDbParamTable/rdbmsDbParamTable_data_set);
    /* *INDENT-ON*  */

/* OID and column number definitions for  */
#include "rdbmsDbParamTable_oids.h"

/* enum definions */
#include "rdbmsDbParamTable_enums.h"

/* *********************************************************************
 * function declarations
 */
void init_rdbmsDbParamTable(void);

/* *********************************************************************
 * Table declarations
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
/* *********************************************************************
 * When you register your mib, you get to provide a generic
 * pointer that will be passed back to you for most of the
 * functions calls.
 *
 * TODO:100:r: Review all context structures
 */
    /*
     * TODO:101:o: |-> Review rdbmsDbParamTable registration context.
     */
typedef netsnmp_data_list * rdbmsDbParamTable_registration_ptr;

/**********************************************************************/
/*
 * TODO:110:r: |-> Review rdbmsDbParamTable data context structure.
 * This structure is used to represent the data for rdbmsDbParamTable.
 */
/*
 * This structure contains storage for all the columns defined in the
 * rdbmsDbParamTable.
 */
typedef struct rdbmsDbParamTable_data_s {
    
        /*
         * rdbmsDbParamID(3)/AutonomousType/ASN_OBJECT_ID/oid(oid)//L/A/w/e/r/d/h
         */
   oid   rdbmsDbParamID[128];
size_t      rdbmsDbParamID_len; /* # of oid elements, not bytes */
    
        /*
         * rdbmsDbParamCurrValue(4)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H
         */
   char   rdbmsDbParamCurrValue[255];
size_t      rdbmsDbParamCurrValue_len; /* # of char elements, not bytes */
    
        /*
         * rdbmsDbParamComment(5)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H
         */
   char   rdbmsDbParamComment[255];
size_t      rdbmsDbParamComment_len; /* # of char elements, not bytes */
    
} rdbmsDbParamTable_data;


/*
 * TODO:120:r: |-> Review rdbmsDbParamTable mib index.
 * This structure is used to represent the index for rdbmsDbParamTable.
 */
typedef struct rdbmsDbParamTable_mib_index_s {

        /*
         * rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   rdbmsDbIndex;

        /*
         * rdbmsDbParamName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
         */
   char   rdbmsDbParamName[64];
   size_t      rdbmsDbParamName_len;

        /*
         * rdbmsDbParamSubIndex(2)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   rdbmsDbParamSubIndex;


} rdbmsDbParamTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review rdbmsDbParamTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
     *
     * BE VERY CAREFUL TO TAKE INTO ACCOUNT THE MAXIMUM
     * POSSIBLE LENGHT FOR EVERY VARIABLE LENGTH INDEX!
     * Guessing 128 - col/entry(2)  - oid len(9)
*/
#define MAX_rdbmsDbParamTable_IDX_LEN     67


/* *********************************************************************
 * TODO:130:o: |-> Review rdbmsDbParamTable Row request (rowreq) context.
 * When your functions are called, you will be passed a
 * rdbmsDbParamTable_rowreq_ctx pointer.
 */
typedef struct rdbmsDbParamTable_rowreq_ctx_s {

    /** this must be first for container compare to work */
    netsnmp_index        oid_idx;
    oid                  oid_tmp[MAX_rdbmsDbParamTable_IDX_LEN];
    
    rdbmsDbParamTable_mib_index        tbl_idx;
    
    rdbmsDbParamTable_data              data;

    /*
     * flags per row. Currently, the first (lower) 8 bits are reserved
     * for the user. See mfd.h for other flags.
     */
    u_int                       rowreq_flags;

    /*
     * implementor's context pointer (provided during registration)
     */
    rdbmsDbParamTable_registration_ptr rdbmsDbParamTable_reg;

    /*
     * TODO:131:o: |   |-> Add useful data to rdbmsDbParamTable rowreq context.
     */
    
    /*
     * storage for future expansion
     */
    netsnmp_data_list             *rdbmsDbParamTable_data_list;

} rdbmsDbParamTable_rowreq_ctx;

typedef struct rdbmsDbParamTable_ref_rowreq_ctx_s {
    rdbmsDbParamTable_rowreq_ctx *rowreq_ctx;
} rdbmsDbParamTable_ref_rowreq_ctx;

/* *********************************************************************
 * function prototypes
 */
    int rdbmsDbParamTable_pre_request(rdbmsDbParamTable_registration_ptr user_context);
    int rdbmsDbParamTable_post_request(rdbmsDbParamTable_registration_ptr user_context);


extern oid rdbmsDbParamTable_oid[];
extern int rdbmsDbParamTable_oid_size;


#include "rdbmsDbParamTable_interface.h"
#include "rdbmsDbParamTable_data_access.h"
#include "rdbmsDbParamTable_data_get.h"
#include "rdbmsDbParamTable_data_set.h"

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

#endif /* RDBMSDBPARAMTABLE_H */
