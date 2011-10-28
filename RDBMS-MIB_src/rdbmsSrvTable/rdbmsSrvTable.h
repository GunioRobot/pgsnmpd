/*-------------------------------------------------------------------------
 * rdbmsSrvTable.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvTable.h,v 1.4 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVTABLE_H
#define RDBMSSRVTABLE_H

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
config_require(RDBMS-MIB/rdbmsSrvTable/rdbmsSrvTable_interface);
config_require(RDBMS-MIB/rdbmsSrvTable/rdbmsSrvTable_data_access);
config_require(RDBMS-MIB/rdbmsSrvTable/rdbmsSrvTable_data_get);
config_require(RDBMS-MIB/rdbmsSrvTable/rdbmsSrvTable_data_set);
    /* *INDENT-ON*  */

/* OID and column number definitions for  */
#include "rdbmsSrvTable_oids.h"

/* enum definions */
#include "rdbmsSrvTable_enums.h"

/* *********************************************************************
 * function declarations
 */
void init_rdbmsSrvTable(void);

/* *********************************************************************
 * Table declarations
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table rdbmsSrvTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvTable is subid 5 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.5, length: 9
*/
/* *********************************************************************
 * When you register your mib, you get to provide a generic
 * pointer that will be passed back to you for most of the
 * functions calls.
 *
 * TODO:100:r: Review all context structures
 */
    /*
     * TODO:101:o: |-> Review rdbmsSrvTable registration context.
     */
typedef netsnmp_data_list * rdbmsSrvTable_registration_ptr;

/**********************************************************************/
/*
 * TODO:110:r: |-> Review rdbmsSrvTable data context structure.
 * This structure is used to represent the data for rdbmsSrvTable.
 */
/*
 * This structure contains storage for all the columns defined in the
 * rdbmsSrvTable.
 */
typedef struct rdbmsSrvTable_data_s {

        /*
         * rdbmsSrvPrivateMibOID(1)/OBJECTID/ASN_OBJECT_ID/oid(oid)//L/A/w/e/r/d/h
         */
   oid   rdbmsSrvPrivateMibOID[128];
size_t      rdbmsSrvPrivateMibOID_len; /* # of oid elements, not bytes */

        /*
         * rdbmsSrvVendorName(2)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
         */
   char   rdbmsSrvVendorName[255];
size_t      rdbmsSrvVendorName_len; /* # of char elements, not bytes */

        /*
         * rdbmsSrvProductName(3)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
         */
   char   rdbmsSrvProductName[255];
size_t      rdbmsSrvProductName_len; /* # of char elements, not bytes */

        /*
         * rdbmsSrvContact(4)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H
         */
   char   rdbmsSrvContact[255];
size_t      rdbmsSrvContact_len; /* # of char elements, not bytes */

} rdbmsSrvTable_data;


/*
 * TODO:120:r: |-> Review rdbmsSrvTable mib index.
 * This structure is used to represent the index for rdbmsSrvTable.
 */
typedef struct rdbmsSrvTable_mib_index_s {

        /*
         * applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   applIndex;


} rdbmsSrvTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review rdbmsSrvTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
*/
#define MAX_rdbmsSrvTable_IDX_LEN     1


/* *********************************************************************
 * TODO:130:o: |-> Review rdbmsSrvTable Row request (rowreq) context.
 * When your functions are called, you will be passed a
 * rdbmsSrvTable_rowreq_ctx pointer.
 */
typedef struct rdbmsSrvTable_rowreq_ctx_s {

    /** this must be first for container compare to work */
    netsnmp_index        oid_idx;
    oid                  oid_tmp[MAX_rdbmsSrvTable_IDX_LEN];

    rdbmsSrvTable_mib_index        tbl_idx;

    rdbmsSrvTable_data              data;

    /*
     * flags per row. Currently, the first (lower) 8 bits are reserved
     * for the user. See mfd.h for other flags.
     */
    u_int                       rowreq_flags;

    /*
     * implementor's context pointer (provided during registration)
     */
    rdbmsSrvTable_registration_ptr rdbmsSrvTable_reg;

    /*
     * TODO:131:o: |   |-> Add useful data to rdbmsSrvTable rowreq context.
     */

    /*
     * storage for future expansion
     */
    netsnmp_data_list             *rdbmsSrvTable_data_list;

} rdbmsSrvTable_rowreq_ctx;

typedef struct rdbmsSrvTable_ref_rowreq_ctx_s {
    rdbmsSrvTable_rowreq_ctx *rowreq_ctx;
} rdbmsSrvTable_ref_rowreq_ctx;

/* *********************************************************************
 * function prototypes
 */
    int rdbmsSrvTable_pre_request(rdbmsSrvTable_registration_ptr user_context);
    int rdbmsSrvTable_post_request(rdbmsSrvTable_registration_ptr user_context);


extern oid rdbmsSrvTable_oid[];
extern int rdbmsSrvTable_oid_size;


#include "rdbmsSrvTable_interface.h"
#include "rdbmsSrvTable_data_access.h"
#include "rdbmsSrvTable_data_get.h"
#include "rdbmsSrvTable_data_set.h"

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

#endif /* RDBMSSRVTABLE_H */
