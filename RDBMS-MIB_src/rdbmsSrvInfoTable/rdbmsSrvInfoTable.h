/*-------------------------------------------------------------------------
 * rdbmsSrvInfoTable.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvInfoTable.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVINFOTABLE_H
#define RDBMSSRVINFOTABLE_H

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
config_require(RDBMS-MIB/rdbmsSrvInfoTable/rdbmsSrvInfoTable_interface);
config_require(RDBMS-MIB/rdbmsSrvInfoTable/rdbmsSrvInfoTable_data_access);
config_require(RDBMS-MIB/rdbmsSrvInfoTable/rdbmsSrvInfoTable_data_get);
config_require(RDBMS-MIB/rdbmsSrvInfoTable/rdbmsSrvInfoTable_data_set);
    /* *INDENT-ON*  */

/* OID and column number definitions for  */
#include "rdbmsSrvInfoTable_oids.h"

/* enum definions */
#include "rdbmsSrvInfoTable_enums.h"

/* *********************************************************************
 * function declarations
 */
void init_rdbmsSrvInfoTable(void);

/* *********************************************************************
 * Table declarations
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
/* *********************************************************************
 * When you register your mib, you get to provide a generic
 * pointer that will be passed back to you for most of the
 * functions calls.
 *
 * TODO:100:r: Review all context structures
 */
    /*
     * TODO:101:o: |-> Review rdbmsSrvInfoTable registration context.
     */
typedef netsnmp_data_list * rdbmsSrvInfoTable_registration_ptr;

/**********************************************************************/
/*
 * TODO:110:r: |-> Review rdbmsSrvInfoTable data context structure.
 * This structure is used to represent the data for rdbmsSrvInfoTable.
 */
/*
 * This structure contains storage for all the columns defined in the
 * rdbmsSrvInfoTable.
 */
typedef struct rdbmsSrvInfoTable_data_s {

        /*
         * rdbmsSrvInfoStartupTime(1)/DateAndTime/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
         */
/*   char   rdbmsSrvInfoStartupTime[11];
size_t      rdbmsSrvInfoStartupTime_len; *//* # of char elements, not bytes */
	int startupYear;
	int startupMonth;
	int startupDay;
	int startupHour;
	int startupMinutes;
	int startupSeconds;
	int startupDeciSeconds;
	int startupUtcOffsetDirection;
	int startupUtcOffsetHours;
	int startupUtcOffsetMinutes;

        /*
         * rdbmsSrvInfoFinishedTransactions(2)/GAUGE/ASN_GAUGE/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoFinishedTransactions;

        /*
         * rdbmsSrvInfoDiskReads(3)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoDiskReads;

        /*
         * rdbmsSrvInfoLogicalReads(4)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoLogicalReads;

        /*
         * rdbmsSrvInfoDiskWrites(5)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoDiskWrites;

        /*
         * rdbmsSrvInfoLogicalWrites(6)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoLogicalWrites;

        /*
         * rdbmsSrvInfoPageReads(7)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoPageReads;

        /*
         * rdbmsSrvInfoPageWrites(8)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoPageWrites;

        /*
         * rdbmsSrvInfoDiskOutOfSpaces(9)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoDiskOutOfSpaces;

        /*
         * rdbmsSrvInfoHandledRequests(10)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoHandledRequests;

        /*
         * rdbmsSrvInfoRequestRecvs(11)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoRequestRecvs;

        /*
         * rdbmsSrvInfoRequestSends(12)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoRequestSends;

        /*
         * rdbmsSrvInfoHighwaterInboundAssociations(13)/GAUGE/ASN_GAUGE/u_long(u_long)//l/A/w/e/r/d/h
         */
   u_long   rdbmsSrvInfoHighwaterInboundAssociations;

        /*
         * rdbmsSrvInfoMaxInboundAssociations(14)/GAUGE/ASN_GAUGE/u_long(u_long)//l/A/W/e/r/d/h
         */
   u_long   rdbmsSrvInfoMaxInboundAssociations;

} rdbmsSrvInfoTable_data;


/*
 * TODO:120:r: |-> Review rdbmsSrvInfoTable mib index.
 * This structure is used to represent the index for rdbmsSrvInfoTable.
 */
typedef struct rdbmsSrvInfoTable_mib_index_s {

        /*
         * applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   applIndex;


} rdbmsSrvInfoTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review rdbmsSrvInfoTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
*/
#define MAX_rdbmsSrvInfoTable_IDX_LEN     1


/* *********************************************************************
 * TODO:130:o: |-> Review rdbmsSrvInfoTable Row request (rowreq) context.
 * When your functions are called, you will be passed a
 * rdbmsSrvInfoTable_rowreq_ctx pointer.
 */
typedef struct rdbmsSrvInfoTable_rowreq_ctx_s {

    /** this must be first for container compare to work */
    netsnmp_index        oid_idx;
    oid                  oid_tmp[MAX_rdbmsSrvInfoTable_IDX_LEN];

    rdbmsSrvInfoTable_mib_index        tbl_idx;

    rdbmsSrvInfoTable_data              data;

    /*
     * flags per row. Currently, the first (lower) 8 bits are reserved
     * for the user. See mfd.h for other flags.
     */
    u_int                       rowreq_flags;

    /*
     * implementor's context pointer (provided during registration)
     */
    rdbmsSrvInfoTable_registration_ptr rdbmsSrvInfoTable_reg;

    /*
     * TODO:131:o: |   |-> Add useful data to rdbmsSrvInfoTable rowreq context.
     */

    /*
     * storage for future expansion
     */
    netsnmp_data_list             *rdbmsSrvInfoTable_data_list;

} rdbmsSrvInfoTable_rowreq_ctx;

typedef struct rdbmsSrvInfoTable_ref_rowreq_ctx_s {
    rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx;
} rdbmsSrvInfoTable_ref_rowreq_ctx;

/* *********************************************************************
 * function prototypes
 */
    int rdbmsSrvInfoTable_pre_request(rdbmsSrvInfoTable_registration_ptr user_context);
    int rdbmsSrvInfoTable_post_request(rdbmsSrvInfoTable_registration_ptr user_context);


extern oid rdbmsSrvInfoTable_oid[];
extern int rdbmsSrvInfoTable_oid_size;


#include "rdbmsSrvInfoTable_interface.h"
#include "rdbmsSrvInfoTable_data_access.h"
#include "rdbmsSrvInfoTable_data_get.h"
#include "rdbmsSrvInfoTable_data_set.h"

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

#endif /* RDBMSSRVINFOTABLE_H */
