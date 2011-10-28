/*-------------------------------------------------------------------------
 * rdbmsRelTable_data_access.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsRelTable_data_access.c,v 1.4 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsRelTable.h"
#include "rdbmsRelTable_data_access.h"

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
 *** Table rdbmsRelTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsRelTable is subid 9 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.9, length: 9
*/

/**
 * initialization for rdbmsRelTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param rdbmsRelTable_reg
 *        Pointer to rdbmsRelTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
rdbmsRelTable_init_data(rdbmsRelTable_registration_ptr rdbmsRelTable_reg)
{
    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelTable_init_data","called\n"));

    /*
     * TODO:303:o: Initialize rdbmsRelTable data.
     */
    /*
    ***************************************************
    ***             START EXAMPLE CODE              ***
    ***---------------------------------------------***/
    /*
     * if you are the sole writer for the file, you could
     * open it here. However, as stated earlier, we are assuming
     * the worst case, which in this case means that the file is
     * written to by someone else, and might not even exist when
     * we start up. So we can't do anything here.
     */
    /*
    ***---------------------------------------------***
    ***              END  EXAMPLE CODE              ***
    ***************************************************/

    return MFD_SUCCESS;
} /* rdbmsRelTable_init_data */

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
rdbmsRelTable_container_init(netsnmp_container **container_ptr_ptr,
                        netsnmp_cache *cache)
{
    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelTable_container_init","called\n"));

    if((NULL == cache) || (NULL == container_ptr_ptr)) {
        snmp_log(LOG_ERR,"bad params to rdbmsRelTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    /*
     * TODO:345:A: Set up rdbmsRelTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper. To completely disable caching, set
     * cache->enabled to 0.
     */
    cache->timeout = RDBMSRELTABLE_CACHE_TIMEOUT; /* seconds */
} /* rdbmsRelTable_container_init */

/**
 * load cache data
 *
 * TODO:350:M: Implement rdbmsRelTable cache load
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
 *  rdbmsRelTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
rdbmsRelTable_cache_load(netsnmp_container *container)
{
    rdbmsRelTable_rowreq_ctx *rowreq_ctx;
   long   applIndex = 1;
   int resultCount, errorCode = MFD_SUCCESS, i, tmpInt, count = 0;
   PGresult *pg_db_qry;

    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelTable_cache_load","called\n"));

    /*
     * TODO:351:M: |-> Load/update data in the rdbmsRelTable container.
     * loop over your rdbmsRelTable data, allocate a rowreq context,
     * set the index(es) [and data, optionally] and insert into
     * the container.
     */

    if (PQstatus(dbconn) == CONNECTION_OK)
	    pg_db_qry = PQexec(dbconn, "SELECT datid, EXTRACT(YEAR FROM pg_postmaster_start_time()), EXTRACT(MONTH FROM pg_postmaster_start_time()), EXTRACT(DAY FROM pg_postmaster_start_time()), EXTRACT(HOUR FROM pg_postmaster_start_time()), EXTRACT(MINUTE FROM pg_postmaster_start_time()), EXTRACT(SECOND FROM pg_postmaster_start_time()), EXTRACT(MILLISECOND FROM pg_postmaster_start_time()), EXTRACT(TIMEZONE_HOUR FROM pg_postmaster_start_time()), EXTRACT(TIMEZONE_MINUTE FROM pg_postmaster_start_time()) FROM pg_stat_database");
    else {
	    snmp_log(LOG_ERR, "Can't get connected to the database");
	    return MFD_RESOURCE_UNAVAILABLE;
    }
    if (PQresultStatus(pg_db_qry) != PGRES_TUPLES_OK) {
	    snmp_log(LOG_ERR, "Didn't get any results from the database");
	    PQclear(pg_db_qry);
	    /*PQfinish(dbconn);*/
	    /* It's probably an error if I didn't find *any* databases */
	    return MFD_RESOURCE_UNAVAILABLE;
    }

    resultCount = PQntuples(pg_db_qry);

    for(i = 0; i < resultCount; i++) {

        /*
         * TODO:352:M: |   |-> set indexes in new rdbmsRelTable rowreq context.
         */
        rowreq_ctx = rdbmsRelTable_allocate_rowreq_ctx();
        if (NULL == rowreq_ctx) {
            snmp_log(LOG_ERR, "memory allocation failed\n");
            errorCode = MFD_RESOURCE_UNAVAILABLE;
	    break;
        }
	tmpInt = atoi(PQgetvalue(pg_db_qry, i, 0));
        if(MFD_SUCCESS != rdbmsRelTable_indexes_set(rowreq_ctx
                               , tmpInt
                               , applIndex
               )) {
            snmp_log(LOG_ERR,"error setting index while loading "
                     "rdbmsRelTable cache.\n");
            rdbmsRelTable_release_rowreq_ctx(rowreq_ctx);
            continue;
        }

        /*
         * TODO:352:r: |   |-> populate rdbmsRelTable data context.
         * Populate data context here. (optionally, delay until row prep)
         */

    /* All databases are active */
    if(MFD_SUCCESS !=
       rdbmsRelState_map(&rowreq_ctx->data.rdbmsRelState, INTERNAL_RDBMSRELSTATE_ACTIVE)) {
        return MFD_ERROR;
    }

	rowreq_ctx->data.activeTimeYear = atoi(PQgetvalue(pg_db_qry, i, 1));
	rowreq_ctx->data.activeTimeMonth = atoi(PQgetvalue(pg_db_qry, i, 2));
	rowreq_ctx->data.activeTimeDay = atoi(PQgetvalue(pg_db_qry, i, 3));
	rowreq_ctx->data.activeTimeHour = atoi(PQgetvalue(pg_db_qry, i, 4));
	rowreq_ctx->data.activeTimeMinutes = atoi(PQgetvalue(pg_db_qry, i, 5));
	rowreq_ctx->data.activeTimeSeconds = atoi(PQgetvalue(pg_db_qry, i, 6));
	rowreq_ctx->data.activeTimeDeciSeconds = atoi(PQgetvalue(pg_db_qry, i, 7));
	rowreq_ctx->data.activeTimeUtcOffsetHours = atoi(PQgetvalue(pg_db_qry, i, 8));
	rowreq_ctx->data.activeTimeUtcOffsetMinutes = atoi(PQgetvalue(pg_db_qry, i, 9));
	tmpInt = rowreq_ctx->data.activeTimeUtcOffsetHours * 60 + rowreq_ctx->data.activeTimeUtcOffsetMinutes;
	if (tmpInt == 0)
		rowreq_ctx->data.activeTimeUtcOffsetDirection = 0;
	else
		rowreq_ctx->data.activeTimeUtcOffsetDirection = (tmpInt > 0 ? 1 : -1);


        /*
         * insert into table container
         */
        CONTAINER_INSERT(container, rowreq_ctx);
        ++count;
    }

    DEBUGMSGT(("verbose:rdbmsRelTable:rdbmsRelTable_cache_load",
               "inserted %d records\n", count));

    PQclear(pg_db_qry);

    return errorCode;
} /* rdbmsRelTable_cache_load */

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
rdbmsRelTable_cache_free(netsnmp_container *container)
{
    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelTable_cache_free","called\n"));

    /*
     * TODO:380:M: Free rdbmsRelTable cache.
     */
} /* rdbmsRelTable_cache_free */

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
rdbmsRelTable_row_prep( rdbmsRelTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("verbose:rdbmsRelTable:rdbmsRelTable_row_prep","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
} /* rdbmsRelTable_row_prep */

/** @} */
