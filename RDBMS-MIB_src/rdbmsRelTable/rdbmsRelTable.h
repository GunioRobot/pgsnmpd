/*-------------------------------------------------------------------------
 * rdbmsRelTable.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsRelTable.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSRELTABLE_H
#define RDBMSRELTABLE_H

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
config_require(RDBMS-MIB/rdbmsRelTable/rdbmsRelTable_interface);
config_require(RDBMS-MIB/rdbmsRelTable/rdbmsRelTable_data_access);
config_require(RDBMS-MIB/rdbmsRelTable/rdbmsRelTable_data_get);
config_require(RDBMS-MIB/rdbmsRelTable/rdbmsRelTable_data_set);
    /* *INDENT-ON*  */

/* OID and column number definitions for  */
#include "rdbmsRelTable_oids.h"

/* enum definions */
#include "rdbmsRelTable_enums.h"

/* *********************************************************************
 * function declarations
 */
void init_rdbmsRelTable(void);

/* *********************************************************************
 * Table declarations
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table rdbmsRelTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsRelTable is subid 9 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.9, length: 9
*/
/* *********************************************************************
 * When you register your mib, you get to provide a generic
 * pointer that will be passed back to you for most of the
 * functions calls.
 *
 * TODO:100:r: Review all context structures
 */
    /*
     * TODO:101:o: |-> Review rdbmsRelTable registration context.
     */
typedef netsnmp_data_list * rdbmsRelTable_registration_ptr;

/**********************************************************************/
/*
 * TODO:110:r: |-> Review rdbmsRelTable data context structure.
 * This structure is used to represent the data for rdbmsRelTable.
 */
/*
 * This structure contains storage for all the columns defined in the
 * rdbmsRelTable.
 */
typedef struct rdbmsRelTable_data_s {

        /*
         * rdbmsRelState(1)/INTEGER/ASN_INTEGER/long(u_long)//l/A/w/E/r/d/h
         */
   u_long   rdbmsRelState;

        /*
         * rdbmsRelActiveTime(2)/DateAndTime/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
         */
	int activeTimeYear;
	int activeTimeMonth;
	int activeTimeDay;
	int activeTimeHour;
	int activeTimeMinutes;
	int activeTimeSeconds;
	int activeTimeDeciSeconds;
	int activeTimeUtcOffsetDirection;
	int activeTimeUtcOffsetHours;
	int activeTimeUtcOffsetMinutes;

} rdbmsRelTable_data;


/*
 * TODO:120:r: |-> Review rdbmsRelTable mib index.
 * This structure is used to represent the index for rdbmsRelTable.
 */
typedef struct rdbmsRelTable_mib_index_s {

        /*
         * rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   rdbmsDbIndex;

        /*
         * applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   applIndex;


} rdbmsRelTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review rdbmsRelTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
*/
#define MAX_rdbmsRelTable_IDX_LEN     2


/* *********************************************************************
 * TODO:130:o: |-> Review rdbmsRelTable Row request (rowreq) context.
 * When your functions are called, you will be passed a
 * rdbmsRelTable_rowreq_ctx pointer.
 */
typedef struct rdbmsRelTable_rowreq_ctx_s {

    /** this must be first for container compare to work */
    netsnmp_index        oid_idx;
    oid                  oid_tmp[MAX_rdbmsRelTable_IDX_LEN];

    rdbmsRelTable_mib_index        tbl_idx;

    rdbmsRelTable_data              data;

    /*
     * flags per row. Currently, the first (lower) 8 bits are reserved
     * for the user. See mfd.h for other flags.
     */
    u_int                       rowreq_flags;

    /*
     * implementor's context pointer (provided during registration)
     */
    rdbmsRelTable_registration_ptr rdbmsRelTable_reg;

    /*
     * TODO:131:o: |   |-> Add useful data to rdbmsRelTable rowreq context.
     */

    /*
     * storage for future expansion
     */
    netsnmp_data_list             *rdbmsRelTable_data_list;

} rdbmsRelTable_rowreq_ctx;

typedef struct rdbmsRelTable_ref_rowreq_ctx_s {
    rdbmsRelTable_rowreq_ctx *rowreq_ctx;
} rdbmsRelTable_ref_rowreq_ctx;

/* *********************************************************************
 * function prototypes
 */
    int rdbmsRelTable_pre_request(rdbmsRelTable_registration_ptr user_context);
    int rdbmsRelTable_post_request(rdbmsRelTable_registration_ptr user_context);


extern oid rdbmsRelTable_oid[];
extern int rdbmsRelTable_oid_size;


#include "rdbmsRelTable_interface.h"
#include "rdbmsRelTable_data_access.h"
#include "rdbmsRelTable_data_get.h"
#include "rdbmsRelTable_data_set.h"

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

#endif /* RDBMSRELTABLE_H */
