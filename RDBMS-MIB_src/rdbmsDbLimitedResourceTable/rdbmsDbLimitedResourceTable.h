/*-------------------------------------------------------------------------
 * rdbmsDbLimitedResourceTable.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbLimitedResourceTable.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBLIMITEDRESOURCETABLE_H
#define RDBMSDBLIMITEDRESOURCETABLE_H

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
config_require(RDBMS-MIB/rdbmsDbLimitedResourceTable/rdbmsDbLimitedResourceTable_interface);
config_require(RDBMS-MIB/rdbmsDbLimitedResourceTable/rdbmsDbLimitedResourceTable_data_access);
config_require(RDBMS-MIB/rdbmsDbLimitedResourceTable/rdbmsDbLimitedResourceTable_data_get);
config_require(RDBMS-MIB/rdbmsDbLimitedResourceTable/rdbmsDbLimitedResourceTable_data_set);
    /* *INDENT-ON*  */

/* OID and column number definitions for  */
#include "rdbmsDbLimitedResourceTable_oids.h"

/* enum definions */
#include "rdbmsDbLimitedResourceTable_enums.h"

/* *********************************************************************
 * function declarations
 */
void init_rdbmsDbLimitedResourceTable(void);

/* *********************************************************************
 * Table declarations
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
/* *********************************************************************
 * When you register your mib, you get to provide a generic
 * pointer that will be passed back to you for most of the
 * functions calls.
 *
 * TODO:100:r: Review all context structures
 */
    /*
     * TODO:101:o: |-> Review rdbmsDbLimitedResourceTable registration context.
     */
typedef netsnmp_data_list * rdbmsDbLimitedResourceTable_registration_ptr;

/**********************************************************************/
/*
 * TODO:110:r: |-> Review rdbmsDbLimitedResourceTable data context structure.
 * This structure is used to represent the data for rdbmsDbLimitedResourceTable.
 */
/*
 * This structure contains storage for all the columns defined in the
 * rdbmsDbLimitedResourceTable.
 */
typedef struct rdbmsDbLimitedResourceTable_data_s {
    
        /*
         * rdbmsDbLimitedResourceID(2)/AutonomousType/ASN_OBJECT_ID/oid(oid)//L/A/w/e/r/d/h
         */
   oid   rdbmsDbLimitedResourceID[128];
size_t      rdbmsDbLimitedResourceID_len; /* # of oid elements, not bytes */
    
        /*
         * rdbmsDbLimitedResourceLimit(3)/INTEGER/ASN_INTEGER/long(long)//l/A/W/e/R/d/h
         */
   long   rdbmsDbLimitedResourceLimit;
    
        /*
         * rdbmsDbLimitedResourceCurrent(4)/INTEGER/ASN_INTEGER/long(long)//l/A/w/e/R/d/h
         */
   long   rdbmsDbLimitedResourceCurrent;
    
        /*
         * rdbmsDbLimitedResourceHighwater(5)/INTEGER/ASN_INTEGER/long(long)//l/A/w/e/R/d/h
         */
   long   rdbmsDbLimitedResourceHighwater;
    
        /*
         * rdbmsDbLimitedResourceFailures(6)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsDbLimitedResourceFailures;
    
        /*
         * rdbmsDbLimitedResourceDescription(7)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H
         */
   char   rdbmsDbLimitedResourceDescription[255];
size_t      rdbmsDbLimitedResourceDescription_len; /* # of char elements, not bytes */
    
} rdbmsDbLimitedResourceTable_data;


/*
 * TODO:120:r: |-> Review rdbmsDbLimitedResourceTable mib index.
 * This structure is used to represent the index for rdbmsDbLimitedResourceTable.
 */
typedef struct rdbmsDbLimitedResourceTable_mib_index_s {

        /*
         * rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   rdbmsDbIndex;

        /*
         * rdbmsDbLimitedResourceName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
         */
        /** 128 - 1(other indexes) - oid length(11) = 115 */
   char   rdbmsDbLimitedResourceName[115];
   size_t      rdbmsDbLimitedResourceName_len;


} rdbmsDbLimitedResourceTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review rdbmsDbLimitedResourceTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
     *
     * BE VERY CAREFUL TO TAKE INTO ACCOUNT THE MAXIMUM
     * POSSIBLE LENGHT FOR EVERY VARIABLE LENGTH INDEX!
     * Guessing 128 - col/entry(2)  - oid len(9)
*/
#define MAX_rdbmsDbLimitedResourceTable_IDX_LEN     117


/* *********************************************************************
 * TODO:130:o: |-> Review rdbmsDbLimitedResourceTable Row request (rowreq) context.
 * When your functions are called, you will be passed a
 * rdbmsDbLimitedResourceTable_rowreq_ctx pointer.
 */
typedef struct rdbmsDbLimitedResourceTable_rowreq_ctx_s {

    /** this must be first for container compare to work */
    netsnmp_index        oid_idx;
    oid                  oid_tmp[MAX_rdbmsDbLimitedResourceTable_IDX_LEN];
    
    rdbmsDbLimitedResourceTable_mib_index        tbl_idx;
    
    rdbmsDbLimitedResourceTable_data              data;

    /*
     * flags per row. Currently, the first (lower) 8 bits are reserved
     * for the user. See mfd.h for other flags.
     */
    u_int                       rowreq_flags;

    /*
     * implementor's context pointer (provided during registration)
     */
    rdbmsDbLimitedResourceTable_registration_ptr rdbmsDbLimitedResourceTable_reg;

    /*
     * TODO:131:o: |   |-> Add useful data to rdbmsDbLimitedResourceTable rowreq context.
     */
    
    /*
     * storage for future expansion
     */
    netsnmp_data_list             *rdbmsDbLimitedResourceTable_data_list;

} rdbmsDbLimitedResourceTable_rowreq_ctx;

typedef struct rdbmsDbLimitedResourceTable_ref_rowreq_ctx_s {
    rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx;
} rdbmsDbLimitedResourceTable_ref_rowreq_ctx;

/* *********************************************************************
 * function prototypes
 */
    int rdbmsDbLimitedResourceTable_pre_request(rdbmsDbLimitedResourceTable_registration_ptr user_context);
    int rdbmsDbLimitedResourceTable_post_request(rdbmsDbLimitedResourceTable_registration_ptr user_context);


extern oid rdbmsDbLimitedResourceTable_oid[];
extern int rdbmsDbLimitedResourceTable_oid_size;


#include "rdbmsDbLimitedResourceTable_interface.h"
#include "rdbmsDbLimitedResourceTable_data_access.h"
#include "rdbmsDbLimitedResourceTable_data_get.h"
#include "rdbmsDbLimitedResourceTable_data_set.h"

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

#endif /* RDBMSDBLIMITEDRESOURCETABLE_H */
