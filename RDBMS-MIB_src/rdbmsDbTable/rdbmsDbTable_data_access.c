/*-------------------------------------------------------------------------
 * rdbmsDbTable_data_access.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable_data_access.c,v 1.5 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsDbTable.h"
#include "rdbmsDbTable_data_access.h"

/** @defgroup data_access data_access: Routines to access data
 *
 * These routines are used to locate the data used to satisfy
 * requests.
 *
 * @{
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

/**
 * initialization for rdbmsDbTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param rdbmsDbTable_reg
 *        Pointer to rdbmsDbTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
rdbmsDbTable_init_data(rdbmsDbTable_registration_ptr rdbmsDbTable_reg)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_init_data","called\n"));

    return MFD_SUCCESS;
} /* rdbmsDbTable_init_data */

/**
 * container-cached overview
 *
 */

/***********************************************************************
 *
 * cache
 *
 ***********************************************************************/
/**
 * container initialization
 *
 * @param container_ptr_ptr A pointer to a container pointer. If you
 *        create a custom container, use this parameter to return it
 *        to the MFD helper. If set to NULL, the MFD helper will
 *        allocate a container for you.
 * @param  cache A pointer to a cache structure. You can set the timeout
 *         and other cache flags using this pointer.
 *
 *  This function is called at startup to allow you to customize certain
 *  aspects of the access method. For the most part, it is for advanced
 *  users. The default code should suffice for most cases. If no custom
 *  container is allocated, the MFD code will create one for your.
 *
 *  This is also the place to set up cache behavior. The default, to
 *  simply set the cache timeout, will work well with the default
 *  container. If you are using a custom container, you may want to
 *  look at the cache helper documentation to see if there are any
 *  flags you want to set.
 *
 * @remark
 *  This would also be a good place to do any initialization needed
 *  for you data source. For example, opening a connection to another
 *  process that will supply the data, opening a database, etc.
 */
void
rdbmsDbTable_container_init(netsnmp_container **container_ptr_ptr,
                        netsnmp_cache *cache)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_container_init","called\n"));

    if((NULL == cache) || (NULL == container_ptr_ptr)) {
        snmp_log(LOG_ERR,"bad params to rdbmsDbTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    /*
     * TODO:345:A: Set up rdbmsDbTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper. To completely disable caching, set
     * cache->enabled to 0.
     */
    cache->timeout = RDBMSDBTABLE_CACHE_TIMEOUT; /* seconds */

    /* JWT-TODO: Initialize cache with cache->flags here */
} /* rdbmsDbTable_container_init */

/**
 * load cache data
 *
 * TODO:350:M: Implement rdbmsDbTable cache load
 *
 * @param container container to which items should be inserted
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_RESOURCE_UNAVAILABLE : Can't access data source
 * @retval MFD_ERROR                : other error.
 *
 *  This function is called to cache the index(es) (and data, optionally)
 *  for the every row in the data set.
 *
 * @remark
 *  While loading the cache, the only important thing is the indexes.
 *  If access to your data is cheap/fast (e.g. you have a pointer to a
 *  structure in memory), it would make sense to update the data here.
 *  If, however, the accessing the data invovles more work (e.g. parsing
 *  some other existing data, or peforming calculations to derive the data),
 *  then you can limit yourself to setting the indexes and saving any
 *  information you will need later. Then use the saved information in
 *  rdbmsDbTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
rdbmsDbTable_cache_load(netsnmp_container *container)
{
    rdbmsDbTable_rowreq_ctx *rowreq_ctx;
    oid rdbmsDbPrivateMibOID[128] = { 1,3,6,1,4,1,27645 };
    int i, resultCount, errorcode = MFD_SUCCESS, tmpInt;
    PGresult *pg_db_qry, *pgsnmpd_tbl_qry;
    char *tmpString, *db_oid, *vendor_name, *contact_name;
    int vendor_name_len, contact_name_len;

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_cache_load","called\n"));

    /*
     * TODO:351:M: |-> Load/update data in the rdbmsDbTable container.
     * loop over your rdbmsDbTable data, allocate a rowreq context,
     * set the index(es) [and data, optionally] and insert into
     * the container. */

    if (PQstatus(dbconn) == CONNECTION_OK)
	    pg_db_qry = PQexec(dbconn, "SELECT oid, datname FROM pg_database");
    else {
	    snmp_log(LOG_ERR, "Can't get connected to the database");
	    return MFD_RESOURCE_UNAVAILABLE;
    }
    if (PQresultStatus(pg_db_qry) != PGRES_TUPLES_OK) {
	    snmp_log(LOG_ERR, "Didn't get any results from the database");
	    PQclear(pg_db_qry);
	    /*PQfinish(dbconn); */
	    /* It's probably an error if I didn't find *any* databases */
	    return MFD_RESOURCE_UNAVAILABLE;
    }

    resultCount = PQntuples(pg_db_qry);

    for (i = 0; i < resultCount; i++) {

        /*
         * TODO:352:M: |   |-> set indexes in new rdbmsDbTable rowreq context.
         */
        rowreq_ctx = rdbmsDbTable_allocate_rowreq_ctx();
        if (NULL == rowreq_ctx) {
            snmp_log(LOG_ERR, "memory allocation failed\n");
            errorcode = MFD_RESOURCE_UNAVAILABLE;
	    break;
        }
	db_oid = PQgetvalue(pg_db_qry, i, 0);
        if(MFD_SUCCESS != rdbmsDbTable_indexes_set(rowreq_ctx
                               ,atol(db_oid)
               )) {
            snmp_log(LOG_ERR,"error setting index while loading "
                     "rdbmsDbTable cache.\n");
            rdbmsDbTable_release_rowreq_ctx(rowreq_ctx);
            continue;
        }

        /*
         * TODO:352:r: |   |-> populate rdbmsDbTable data context.
         * Populate data context here. (optionally, delay until row prep)
         */

	rowreq_ctx->data.rdbmsDbPrivateMibOID_len = 128;
	rowreq_ctx->data.rdbmsDbVendorName_len    = 255;
	rowreq_ctx->data.rdbmsDbName_len          = 255;
	rowreq_ctx->data.rdbmsDbContact_len       = 255;

	contact_name = NULL;
	contact_name_len = 0;
	vendor_name = NULL;
	vendor_name_len = 0;

	/* Note that this queries pgsnmpd_rdbmsDbTable once per database. This could
	 * be more efficient by only querying once if it can't find the table (being
	 * sure that the table didn't exist, as opposed to simply an entry for that
	 * database not existing in the table). It could also be rewritten so that
	 * only one query is issued, joining pg_database and pgsnmpd_rdbmsDbTable, but
	 * that would have to be smart enough to know of the pgsnmpd table existed
	 * and not do the join if it didn't */
	pgsnmpd_tbl_qry = NULL;
	tmpInt = sizeof("SELECT vendor_name, contact_name FROM pgsnmpd_rdbmsDbTable WHERE database_oid = ") + sizeof(*db_oid);
	tmpString = calloc(tmpInt, sizeof(char*));
	if (tmpString == NULL) snmp_log(LOG_ERR, "Couldn't allocate memory to query pgsnmpd-specific database table\n");
	else {
		snmp_log(LOG_INFO, "Gathering rdbmsDbTable information from pgsnmpd_rdbmsDbTable\n");
		snprintf(tmpString, sizeof(char*) * tmpInt, "SELECT vendor_name, contact_name FROM pgsnmpd_rdbmsDbTable WHERE database_oid = %s", db_oid);
		pgsnmpd_tbl_qry = PQexec(dbconn, tmpString);
		/* Ignore errors so that pgsnmpd will run without this table being available */
		if (PQresultStatus(pgsnmpd_tbl_qry) == PGRES_TUPLES_OK && PQntuples(pgsnmpd_tbl_qry) > 0) {
			vendor_name = PQgetvalue(pgsnmpd_tbl_qry, 0, 0);
			vendor_name_len = strlen(vendor_name);
			contact_name = PQgetvalue(pgsnmpd_tbl_qry, 0, 1);
			contact_name_len = strlen(contact_name);
		}
		/* Note that this error is INFO level, instead of something higher, because we're designed to work without this table */
		else snmp_log(LOG_INFO, "Unable to find relevant data in pgsnmpd_rdbmsDbTable\n");
	}

    /*
     * TODO:246:r: |-> Define rdbmsDbPrivateMibOID mapping.
     * Map values between raw/native values and MIB values
     *
     * if(MFD_SUCCESS !=
     *    rdbmsDbPrivateMibOID_map(&rowreq_ctx->data.rdbmsDbPrivateMibOID, &rowreq_ctx->data.rdbmsDbPrivateMibOID_len,
     *                rdbmsDbPrivateMibOID, rdbmsDbPrivateMibOID_len, 0)) {
     *    return MFD_ERROR;
     * }
     */
    if ((NULL == rowreq_ctx->data.rdbmsDbPrivateMibOID) ||
        (rowreq_ctx->data.rdbmsDbPrivateMibOID_len < (1 * sizeof(rowreq_ctx->data.rdbmsDbPrivateMibOID[0])))) {
        snmp_log(LOG_ERR,"not enough space for rdbmsDbTable.rdbmsDbPrivateMibOID value.\n");
        errorcode = MFD_ERROR;
	break;
    }
    rowreq_ctx->data.rdbmsDbPrivateMibOID_len = 8;
    rdbmsDbPrivateMibOID[7] = (oid) atoi(PQgetvalue(pg_db_qry, i, 0));
    memcpy( rowreq_ctx->data.rdbmsDbPrivateMibOID, rdbmsDbPrivateMibOID, 8 * sizeof(rdbmsDbPrivateMibOID[0]));

    /*
     * TODO:246:r: |-> Define rdbmsDbVendorName mapping.
     */
    if ((NULL == rowreq_ctx->data.rdbmsDbVendorName) ||
        (rowreq_ctx->data.rdbmsDbVendorName_len < (10 * sizeof(rowreq_ctx->data.rdbmsDbVendorName[0])))) {
        snmp_log(LOG_ERR,"not enough space for rdbmsDbTable.rdbmsDbVendorName value\n");
        errorcode = MFD_ERROR;
	break;
    }
    rowreq_ctx->data.rdbmsDbVendorName_len = vendor_name_len;
    memcpy( rowreq_ctx->data.rdbmsDbVendorName, vendor_name, vendor_name_len);

    /*
     * TODO:246:r: |-> Define rdbmsDbName mapping.
     */
    if ((NULL == rowreq_ctx->data.rdbmsDbName) ||
        (rowreq_ctx->data.rdbmsDbName_len < (100 * sizeof(rowreq_ctx->data.rdbmsDbName[0])))) {
        snmp_log(LOG_ERR,"not enough space for rdbmsDbTable.rdbmsDbName value\n");
        errorcode = MFD_ERROR;
	break;
    }
    tmpString = PQgetvalue(pg_db_qry, i, 1);
    rowreq_ctx->data.rdbmsDbName_len = strlen(tmpString) * sizeof(rowreq_ctx->data.rdbmsDbName[0]);
    strncpy(rowreq_ctx->data.rdbmsDbName, tmpString, rowreq_ctx->data.rdbmsDbName_len);

    /*
     * TODO:246:r: |-> Define rdbmsDbContact mapping.
     */
    if ((NULL == rowreq_ctx->data.rdbmsDbContact) ||
        (rowreq_ctx->data.rdbmsDbContact_len < (100 * sizeof(rowreq_ctx->data.rdbmsDbContact[0])))) {
        snmp_log(LOG_ERR,"not enough space for rdbmsDbTable.rdbmsDbContact value\n");
        errorcode = MFD_ERROR;
	break;
    }
    rowreq_ctx->data.rdbmsDbContact_len = contact_name_len;
    memcpy( rowreq_ctx->data.rdbmsDbContact, contact_name, contact_name_len);


        /*
         * insert into table container
         */
        CONTAINER_INSERT(container, rowreq_ctx);

	if (pgsnmpd_tbl_qry != NULL) PQclear(pgsnmpd_tbl_qry);
    }

    DEBUGMSGT(("verbose:rdbmsDbTable:rdbmsDbTable_cache_load",
               "inserted some records\n"));

    PQclear(pg_db_qry);
    return errorcode;
} /* rdbmsDbTable_cache_load */

/**
 * cache clean up
 *
 * @param container container with all current items
 *
 *  This optional callback is called prior to all
 *  item's being removed from the container. If you
 *  need to do any processing before that, do it here.
 *
 * @note
 *  The MFD helper will take care of releasing all the row contexts.
 *
 */
void
rdbmsDbTable_cache_free(netsnmp_container *container)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_cache_free","called\n"));

    /*
     * TODO:380:M: Free rdbmsDbTable cache.
     */
} /* rdbmsDbTable_cache_free */

/**
 * prepare row for processing.
 *
 *  When the agent has located the row for a request, this function is
 *  called to prepare the row for processing. If you fully populated
 *  the data context during the index setup phase, you may not need to
 *  do anything.
 *
 * @param rowreq_ctx pointer to a context.
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 */
int
rdbmsDbTable_row_prep( rdbmsDbTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_row_prep","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
} /* rdbmsDbTable_row_prep */

/** @} */
