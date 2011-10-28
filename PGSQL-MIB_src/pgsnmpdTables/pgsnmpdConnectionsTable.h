/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.32.2.3 $ of : mfd-top.m2c,v $
 *
 * $Id: pgsnmpdConnectionsTable.h,v 1.1 2007/10/30 11:44:41 eggyknap Exp $
 */
#ifndef PGSNMPDCONNECTIONSTABLE_H
#define PGSNMPDCONNECTIONSTABLE_H

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
config_require(PGSQL-MIB/pgsnmpdConnectionsTable/pgsnmpdConnectionsTable_interface);
config_require(PGSQL-MIB/pgsnmpdConnectionsTable/pgsnmpdConnectionsTable_data_access);
config_require(PGSQL-MIB/pgsnmpdConnectionsTable/pgsnmpdConnectionsTable_data_get);
config_require(PGSQL-MIB/pgsnmpdConnectionsTable/pgsnmpdConnectionsTable_data_set);
    /* *INDENT-ON*  */

/* OID and column number definitions for  */
#include "pgsnmpdConnectionsTable_oids.h"

/* enum definions */
#include "pgsnmpdConnectionsTable_enums.h"

/* *********************************************************************
 * function declarations
 */
void init_pgsnmpdConnectionsTable(void);

/* *********************************************************************
 * Table declarations
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table pgsnmpdConnectionsTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * pgsnmpdConnectionsTable is subid 1 of pgsnmpdTables.
 * Its status is Current.
 * OID: .1.3.6.1.4.1.27645.1.1.1, length: 10
*/
/* *********************************************************************
 * When you register your mib, you get to provide a generic
 * pointer that will be passed back to you for most of the
 * functions calls.
 *
 * TODO:100:r: Review all context structures
 */
    /*
     * TODO:101:o: |-> Review pgsnmpdConnectionsTable registration context.
     */
typedef netsnmp_data_list * pgsnmpdConnectionsTable_registration_ptr;

/**********************************************************************/
/*
 * TODO:110:r: |-> Review pgsnmpdConnectionsTable data context structure.
 * This structure is used to represent the data for pgsnmpdConnectionsTable.
 */
/*
 * This structure contains storage for all the columns defined in the
 * pgsnmpdConnectionsTable.
 */
typedef struct pgsnmpdConnectionsTable_data_s {

        /*
         * pgsnmpdConnHost(2)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
         */
   char   pgsnmpdConnHost[255];
size_t      pgsnmpdConnHost_len; /* # of char elements, not bytes */

        /*
         * pgsnmpdConnPort(3)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
         */
   char   pgsnmpdConnPort[255];
size_t      pgsnmpdConnPort_len; /* # of char elements, not bytes */

        /*
         * pgsnmpdConnDbName(4)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
         */
   char   pgsnmpdConnDbName[255];
size_t      pgsnmpdConnDbName_len; /* # of char elements, not bytes */

} pgsnmpdConnectionsTable_data;


/*
 * TODO:120:r: |-> Review pgsnmpdConnectionsTable mib index.
 * This structure is used to represent the index for pgsnmpdConnectionsTable.
 */
typedef struct pgsnmpdConnectionsTable_mib_index_s {

        /*
         * pgsnmpdConnID(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
         */
        /** 128 - 0(other indexes) - oid length(12) = 115 */
   char   pgsnmpdConnID[115];
   size_t      pgsnmpdConnID_len;


} pgsnmpdConnectionsTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review pgsnmpdConnectionsTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
     *
     * BE VERY CAREFUL TO TAKE INTO ACCOUNT THE MAXIMUM
     * POSSIBLE LENGHT FOR EVERY VARIABLE LENGTH INDEX!
     * Guessing 128 - col/entry(2)  - oid len(10)
*/
#define MAX_pgsnmpdConnectionsTable_IDX_LEN     116


/* *********************************************************************
 * TODO:130:o: |-> Review pgsnmpdConnectionsTable Row request (rowreq) context.
 * When your functions are called, you will be passed a
 * pgsnmpdConnectionsTable_rowreq_ctx pointer.
 */
typedef struct pgsnmpdConnectionsTable_rowreq_ctx_s {

    /** this must be first for container compare to work */
    netsnmp_index        oid_idx;
    oid                  oid_tmp[MAX_pgsnmpdConnectionsTable_IDX_LEN];

    pgsnmpdConnectionsTable_mib_index        tbl_idx;

    pgsnmpdConnectionsTable_data              data;

    /*
     * flags per row. Currently, the first (lower) 8 bits are reserved
     * for the user. See mfd.h for other flags.
     */
    u_int                       rowreq_flags;

    /*
     * implementor's context pointer (provided during registration)
     */
    pgsnmpdConnectionsTable_registration_ptr pgsnmpdConnectionsTable_reg;

    /*
     * TODO:131:o: |   |-> Add useful data to pgsnmpdConnectionsTable rowreq context.
     */

    /*
     * storage for future expansion
     */
    netsnmp_data_list             *pgsnmpdConnectionsTable_data_list;

} pgsnmpdConnectionsTable_rowreq_ctx;

typedef struct pgsnmpdConnectionsTable_ref_rowreq_ctx_s {
    pgsnmpdConnectionsTable_rowreq_ctx *rowreq_ctx;
} pgsnmpdConnectionsTable_ref_rowreq_ctx;

/* *********************************************************************
 * function prototypes
 */
    int pgsnmpdConnectionsTable_pre_request(pgsnmpdConnectionsTable_registration_ptr user_context);
    int pgsnmpdConnectionsTable_post_request(pgsnmpdConnectionsTable_registration_ptr user_context);


extern oid pgsnmpdConnectionsTable_oid[];
extern int pgsnmpdConnectionsTable_oid_size;


#include "pgsnmpdConnectionsTable_interface.h"
#include "pgsnmpdConnectionsTable_data_access.h"
#include "pgsnmpdConnectionsTable_data_get.h"
#include "pgsnmpdConnectionsTable_data_set.h"

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

#endif /* PGSNMPDCONNECTIONSTABLE_H */
