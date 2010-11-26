/*-------------------------------------------------------------------------
 * rdbmsDbInfoTable.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbInfoTable.h,v 1.5 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBINFOTABLE_H
#define RDBMSDBINFOTABLE_H

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
config_require(RDBMS-MIB/rdbmsDbInfoTable/rdbmsDbInfoTable_interface);
config_require(RDBMS-MIB/rdbmsDbInfoTable/rdbmsDbInfoTable_data_access);
config_require(RDBMS-MIB/rdbmsDbInfoTable/rdbmsDbInfoTable_data_get);
    /* *INDENT-ON*  */

/* OID and column number definitions for  */
#include "rdbmsDbInfoTable_oids.h"

/* enum definions */
#include "rdbmsDbInfoTable_enums.h"

/* *********************************************************************
 * function declarations
 */
void init_rdbmsDbInfoTable(void);

/* *********************************************************************
 * Table declarations
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table rdbmsDbInfoTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbInfoTable is subid 2 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.2, length: 9
*/
/* *********************************************************************
 * When you register your mib, you get to provide a generic
 * pointer that will be passed back to you for most of the
 * functions calls.
 *
 * TODO:100:r: Review all context structures
 */
    /*
     * TODO:101:o: |-> Review rdbmsDbInfoTable registration context.
     */
typedef netsnmp_data_list * rdbmsDbInfoTable_registration_ptr;

/**********************************************************************/
/*
 * TODO:110:r: |-> Review rdbmsDbInfoTable data context structure.
 * This structure is used to represent the data for rdbmsDbInfoTable.
 */
/*
 * This structure contains storage for all the columns defined in the
 * rdbmsDbInfoTable.
 */
typedef struct rdbmsDbInfoTable_data_s {
    
        /*
         * rdbmsDbInfoProductName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
         */
   char   rdbmsDbInfoProductName[255];
size_t      rdbmsDbInfoProductName_len; /* # of char elements, not bytes */
    
        /*
         * rdbmsDbInfoVersion(2)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
         */
   char   rdbmsDbInfoVersion[255];
size_t      rdbmsDbInfoVersion_len; /* # of char elements, not bytes */
    
        /*
         * rdbmsDbInfoSizeUnits(3)/INTEGER/ASN_INTEGER/long(u_long)//l/A/w/E/r/d/h
         */
   u_long   rdbmsDbInfoSizeUnits;
    
        /*
         * rdbmsDbInfoSizeAllocated(4)/INTEGER/ASN_INTEGER/long(long)//l/A/W/e/R/d/h
         */
   long   rdbmsDbInfoSizeAllocated;
    
        /*
         * rdbmsDbInfoSizeUsed(5)/INTEGER/ASN_INTEGER/long(long)//l/A/w/e/R/d/h
         */
   long   rdbmsDbInfoSizeUsed;
    
        /*
         * rdbmsDbInfoLastBackup(6)/DateAndTime/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
         */
/*   char   rdbmsDbInfoLastBackup[255];
size_t      rdbmsDbInfoLastBackup_len; *//* # of char elements, not bytes */
   int lastBackupYear;
   int lastBackupMonth;
   int lastBackupDay;
   int lastBackupHour;
   int lastBackupMinutes;
   int lastBackupSeconds;
   /* the terminology here was stolen from net-snmp */
   int lastBackupDeciSeconds;

   int utc_offset_direction;
   int utc_offset_hours;
   int utc_offset_minutes;
} rdbmsDbInfoTable_data;


/*
 * TODO:120:r: |-> Review rdbmsDbInfoTable mib index.
 * This structure is used to represent the index for rdbmsDbInfoTable.
 */
typedef struct rdbmsDbInfoTable_mib_index_s {

        /*
         * rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */
   long   rdbmsDbIndex;


} rdbmsDbInfoTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review rdbmsDbInfoTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
*/
#define MAX_rdbmsDbInfoTable_IDX_LEN     1


/* *********************************************************************
 * TODO:130:o: |-> Review rdbmsDbInfoTable Row request (rowreq) context.
 * When your functions are called, you will be passed a
 * rdbmsDbInfoTable_rowreq_ctx pointer.
 */
typedef struct rdbmsDbInfoTable_rowreq_ctx_s {

    /** this must be first for container compare to work */
    netsnmp_index        oid_idx;
    oid                  oid_tmp[MAX_rdbmsDbInfoTable_IDX_LEN];
    
    rdbmsDbInfoTable_mib_index        tbl_idx;
    
    rdbmsDbInfoTable_data              data;

    /*
     * flags per row. Currently, the first (lower) 8 bits are reserved
     * for the user. See mfd.h for other flags.
     */
    u_int                       rowreq_flags;

    /*
     * implementor's context pointer (provided during registration)
     */
    rdbmsDbInfoTable_registration_ptr rdbmsDbInfoTable_reg;

    /*
     * TODO:131:o: |   |-> Add useful data to rdbmsDbInfoTable rowreq context.
     */
    
    /*
     * storage for future expansion
     */
    netsnmp_data_list             *rdbmsDbInfoTable_data_list;

} rdbmsDbInfoTable_rowreq_ctx;

typedef struct rdbmsDbInfoTable_ref_rowreq_ctx_s {
    rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx;
} rdbmsDbInfoTable_ref_rowreq_ctx;

/* *********************************************************************
 * function prototypes
 */
    int rdbmsDbInfoTable_pre_request(rdbmsDbInfoTable_registration_ptr user_context);
    int rdbmsDbInfoTable_post_request(rdbmsDbInfoTable_registration_ptr user_context);


extern oid rdbmsDbInfoTable_oid[];
extern int rdbmsDbInfoTable_oid_size;


#include "rdbmsDbInfoTable_interface.h"
#include "rdbmsDbInfoTable_data_access.h"
#include "rdbmsDbInfoTable_data_get.h"

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

#endif /* RDBMSDBINFOTABLE_H */
