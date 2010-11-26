/*-------------------------------------------------------------------------
 * rdbmsSrvInfoTable_data_access.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvInfoTable_data_access.c,v 1.7 2009/06/06 04:12:10 eggyknap Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsSrvInfoTable.h"


#include "rdbmsSrvInfoTable_data_access.h"

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
 *** Table rdbmsSrvInfoTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvInfoTable is subid 6 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.6, length: 9
*/

/**
 * initialization for rdbmsSrvInfoTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param rdbmsSrvInfoTable_reg
 *        Pointer to rdbmsSrvInfoTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
rdbmsSrvInfoTable_init_data(rdbmsSrvInfoTable_registration_ptr rdbmsSrvInfoTable_reg)
{
    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_init_data","called\n"));

    return MFD_SUCCESS;
} /* rdbmsSrvInfoTable_init_data */

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
rdbmsSrvInfoTable_container_init(netsnmp_container **container_ptr_ptr,
                        netsnmp_cache *cache)
{
    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_container_init","called\n"));
    
    if((NULL == cache) || (NULL == container_ptr_ptr)) {
        snmp_log(LOG_ERR,"bad params to rdbmsSrvInfoTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    /*
     * TODO:345:A: Set up rdbmsSrvInfoTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper. To completely disable caching, set
     * cache->enabled to 0.
     */
    cache->timeout = RDBMSSRVINFOTABLE_CACHE_TIMEOUT; /* seconds */
} /* rdbmsSrvInfoTable_container_init */

/**
 * load cache data
 *
 * TODO:350:M: Implement rdbmsSrvInfoTable cache load
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
 *  rdbmsSrvInfoTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
rdbmsSrvInfoTable_cache_load(netsnmp_container *container)
{
    rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx;
    size_t                 count = 0;
    PGresult *pg_db_qry;
    static int maxAssociations = 0;
    
   long   applIndex;
   int resultCount, tmpInt, rdbmsSrvInfoMaxInboundAssociations = 0, i, errorCode = MFD_SUCCESS;

    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_cache_load","called\n"));

    if (PQstatus(dbconn) == CONNECTION_OK) {
	    pg_db_qry = PQexec(dbconn, "SELECT setting FROM pg_settings WHERE name = 'max_connections'");
	    if (PQresultStatus(pg_db_qry) == PGRES_TUPLES_OK) 
		    rdbmsSrvInfoMaxInboundAssociations = atoi(PQgetvalue(pg_db_qry, 0, 0));
	    PQclear(pg_db_qry);
	    pg_db_qry = PQexec(dbconn, "SELECT setting FROM pg_settings WHERE name = 'superuser_reserved_connections'");
	    if (PQresultStatus(pg_db_qry) == PGRES_TUPLES_OK) 
		    rdbmsSrvInfoMaxInboundAssociations -= atoi(PQgetvalue(pg_db_qry, 0, 0));
	    PQclear(pg_db_qry);
	    pg_db_qry = PQexec(dbconn, "SELECT count(1) FROM pg_stat_activity");
	    if (PQresultStatus(pg_db_qry) == PGRES_TUPLES_OK) {
		    tmpInt = atoi(PQgetvalue(pg_db_qry, 0, 0));
		    maxAssociations = (tmpInt > maxAssociations) ? tmpInt : maxAssociations;
	    }
	    PQclear(pg_db_qry);
	    if (PQserverVersion(dbconn) < 80100)
		    pg_db_qry = PQexec(dbconn, "SELECT datid, EXTRACT(YEAR FROM now()), EXTRACT(MONTH FROM now()), EXTRACT(DAY FROM now()), EXTRACT(HOUR FROM now()), EXTRACT(MINUTE FROM now()), EXTRACT(SECOND FROM now()), EXTRACT(MILLISECOND FROM now()), EXTRACT(TIMEZONE_HOUR FROM now()), EXTRACT(TIMEZONE_MINUTE FROM now()), xact_commit, blks_read, blks_read + blks_hit  FROM pg_stat_database");
            else
		    pg_db_qry = PQexec(dbconn, "SELECT datid, EXTRACT(YEAR FROM pg_postmaster_start_time()), EXTRACT(MONTH FROM pg_postmaster_start_time()), EXTRACT(DAY FROM pg_postmaster_start_time()), EXTRACT(HOUR FROM pg_postmaster_start_time()), EXTRACT(MINUTE FROM pg_postmaster_start_time()), EXTRACT(SECOND FROM pg_postmaster_start_time()), EXTRACT(MILLISECOND FROM pg_postmaster_start_time()), EXTRACT(TIMEZONE_HOUR FROM pg_postmaster_start_time()), EXTRACT(TIMEZONE_MINUTE FROM pg_postmaster_start_time()), xact_commit, blks_read, blks_read + blks_hit  FROM pg_stat_database");
    }
    else {
	    snmp_log(LOG_ERR, "Can't get connected to the database");
	    return -1;
    }
    if (PQresultStatus(pg_db_qry) != PGRES_TUPLES_OK) {
	    snmp_log(LOG_ERR, "Didn't get any results from the database");
	    PQclear(pg_db_qry);
	    /*PQfinish(dbconn);*/
	    return -1;
    }

    resultCount = PQntuples(pg_db_qry);

    /*
     * TODO:351:M: |-> Load/update data in the rdbmsSrvInfoTable container.
     * loop over your rdbmsSrvInfoTable data, allocate a rowreq context,
     * set the index(es) [and data, optionally] and insert into
     * the container.
     */
    for (i = 0; i < resultCount; i++) {

        /*
         * TODO:352:M: |   |-> set indexes in new rdbmsSrvInfoTable rowreq context.
         */
        rowreq_ctx = rdbmsSrvInfoTable_allocate_rowreq_ctx();
        if (NULL == rowreq_ctx) {
            snmp_log(LOG_ERR, "memory allocation failed\n");
	    errorCode = MFD_RESOURCE_UNAVAILABLE;
	    break;
        }
	applIndex = atoi(PQgetvalue(pg_db_qry, i, 0));
        if(MFD_SUCCESS != rdbmsSrvInfoTable_indexes_set(rowreq_ctx
                               , applIndex
               )) {
            snmp_log(LOG_ERR,"error setting index while loading "
                     "rdbmsSrvInfoTable cache.\n");
            rdbmsSrvInfoTable_release_rowreq_ctx(rowreq_ctx);
            continue;
        }

	rowreq_ctx->data.startupYear = atoi(PQgetvalue(pg_db_qry, i, 1));
	rowreq_ctx->data.startupMonth = atoi(PQgetvalue(pg_db_qry, i, 2));
	rowreq_ctx->data.startupDay = atoi(PQgetvalue(pg_db_qry, i, 3));
	rowreq_ctx->data.startupHour = atoi(PQgetvalue(pg_db_qry, i, 4));
	rowreq_ctx->data.startupMinutes = atoi(PQgetvalue(pg_db_qry, i, 5));
	rowreq_ctx->data.startupSeconds = atoi(PQgetvalue(pg_db_qry, i, 6));
	rowreq_ctx->data.startupDeciSeconds = atoi(PQgetvalue(pg_db_qry, i, 7));
	rowreq_ctx->data.startupUtcOffsetHours = atoi(PQgetvalue(pg_db_qry, i, 8));
	rowreq_ctx->data.startupUtcOffsetMinutes = atoi(PQgetvalue(pg_db_qry, i, 9));
	tmpInt = rowreq_ctx->data.startupUtcOffsetHours * 60 + rowreq_ctx->data.startupUtcOffsetMinutes;
	if (tmpInt == 0)
		rowreq_ctx->data.startupUtcOffsetDirection = 0;
	else 
		rowreq_ctx->data.startupUtcOffsetDirection = (tmpInt > 0 ? 1 : -1);
    
    rowreq_ctx->data.rdbmsSrvInfoFinishedTransactions = atoi(PQgetvalue(pg_db_qry, i, 10));
    
    rowreq_ctx->data.rdbmsSrvInfoDiskReads = atoi(PQgetvalue(pg_db_qry, i, 11));
    
    rowreq_ctx->data.rdbmsSrvInfoLogicalReads = atoi(PQgetvalue(pg_db_qry, i, 12));
    
    /* Skip this unless someone comes up with a way to get these data */
    /*rowreq_ctx->data.rdbmsSrvInfoDiskWrites = rdbmsSrvInfoDiskWrites;

    rowreq_ctx->data.rdbmsSrvInfoLogicalWrites = rdbmsSrvInfoLogicalWrites;  */
    
    rowreq_ctx->data.rdbmsSrvInfoPageReads = rowreq_ctx->data.rdbmsSrvInfoDiskReads;
    
    /*rowreq_ctx->data.rdbmsSrvInfoPageWrites = rdbmsSrvInfoPageWrites; */
    
    /* pgsql will have a fatal error if this happens, so the value must be 0 if we're connected to a db server */
    rowreq_ctx->data.rdbmsSrvInfoDiskOutOfSpaces = 0; 
    
    /* rowreq_ctx->data.rdbmsSrvInfoHandledRequests = rdbmsSrvInfoHandledRequests;
    
    rowreq_ctx->data.rdbmsSrvInfoRequestRecvs = rdbmsSrvInfoRequestRecvs;
    
    rowreq_ctx->data.rdbmsSrvInfoRequestSends = rdbmsSrvInfoRequestSends; */
    
    rowreq_ctx->data.rdbmsSrvInfoHighwaterInboundAssociations = maxAssociations; 
    
    rowreq_ctx->data.rdbmsSrvInfoMaxInboundAssociations = rdbmsSrvInfoMaxInboundAssociations;
    
        
        /*
         * insert into table container
         */
        CONTAINER_INSERT(container, rowreq_ctx);
        ++count;
    }


    DEBUGMSGT(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_cache_load",
               "inserted %d records\n", count));

    PQclear(pg_db_qry);
    return errorCode;
} /* rdbmsSrvInfoTable_cache_load */

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
rdbmsSrvInfoTable_cache_free(netsnmp_container *container)
{
    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_cache_free","called\n"));

    /*
     * TODO:380:M: Free rdbmsSrvInfoTable cache.
     */
} /* rdbmsSrvInfoTable_cache_free */

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
rdbmsSrvInfoTable_row_prep( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_row_prep","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvInfoTable_row_prep */

/** @} */
