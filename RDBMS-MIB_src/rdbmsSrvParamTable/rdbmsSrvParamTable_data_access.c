/*-------------------------------------------------------------------------
 * rdbmsSrvParamTable_data_access.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvParamTable_data_access.c,v 1.3 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsSrvParamTable.h"
#include "rdbmsSrvParamTable_data_access.h"

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
 *** Table rdbmsSrvParamTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvParamTable is subid 7 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.7, length: 9
*/

/**
 * initialization for rdbmsSrvParamTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param rdbmsSrvParamTable_reg
 *        Pointer to rdbmsSrvParamTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
rdbmsSrvParamTable_init_data(rdbmsSrvParamTable_registration_ptr rdbmsSrvParamTable_reg)
{
    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_init_data","called\n"));

    /*
     * TODO:303:o: Initialize rdbmsSrvParamTable data.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvParamTable_init_data */

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
rdbmsSrvParamTable_container_init(netsnmp_container **container_ptr_ptr,
                        netsnmp_cache *cache)
{
    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_container_init","called\n"));

    if((NULL == cache) || (NULL == container_ptr_ptr)) {
        snmp_log(LOG_ERR,"bad params to rdbmsSrvParamTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    /*
     * TODO:345:A: Set up rdbmsSrvParamTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper. To completely disable caching, set
     * cache->enabled to 0.
     */
    cache->timeout = RDBMSSRVPARAMTABLE_CACHE_TIMEOUT; /* seconds */
} /* rdbmsSrvParamTable_container_init */

/**
 * load cache data
 *
 * TODO:350:M: Implement rdbmsSrvParamTable cache load
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
 *  rdbmsSrvParamTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
rdbmsSrvParamTable_cache_load(netsnmp_container *container)
{
    rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx;
    size_t                 count = 0;
    char   rdbmsSrvParamName[64];
    size_t      rdbmsSrvParamName_len;
    int i, resultCount, errorCode = MFD_SUCCESS, tmpInt, rdbmsSrvParamID = 1;
    PGresult *pg_db_qry;
    char *tmpString;

    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_cache_load","called\n"));

    if (PQstatus(dbconn) == CONNECTION_OK)
	    pg_db_qry = PQexec(dbconn, "SELECT name, setting, SUBSTRING(short_desc FROM 1 FOR 63) FROM pg_settings");
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
    for (i = 0; i < resultCount; i++) {

        rowreq_ctx = rdbmsSrvParamTable_allocate_rowreq_ctx();
        if (NULL == rowreq_ctx) {
            snmp_log(LOG_ERR, "memory allocation failed\n");
            return MFD_RESOURCE_UNAVAILABLE;
        }
	strncpy(rdbmsSrvParamName, PQgetvalue(pg_db_qry, i, 0), 64);
	rdbmsSrvParamName[63] = '\0';
	rdbmsSrvParamName_len = strlen(rdbmsSrvParamName);
        if(MFD_SUCCESS != rdbmsSrvParamTable_indexes_set(rowreq_ctx
                               , 1
                               , rdbmsSrvParamName, rdbmsSrvParamName_len
                               , 1
               )) {
            snmp_log(LOG_ERR,"error setting index while loading "
                     "rdbmsSrvParamTable cache.\n");
            rdbmsSrvParamTable_release_rowreq_ctx(rowreq_ctx);
            continue;
        }
	rowreq_ctx->data.rdbmsSrvParamID_len = 128;
	rowreq_ctx->data.rdbmsSrvParamCurrValue_len = 255;
	rowreq_ctx->data.rdbmsSrvParamComment_len = 255;

    if ((NULL == rowreq_ctx->data.rdbmsSrvParamID) ||
        (rowreq_ctx->data.rdbmsSrvParamID_len < sizeof(rowreq_ctx->data.rdbmsSrvParamID[0]))) {
        snmp_log(LOG_ERR,"not enough space for value\n");
	errorCode = MFD_ERROR;
	break;
    }
    rowreq_ctx->data.rdbmsSrvParamID_len = sizeof(rowreq_ctx->data.rdbmsSrvParamID[0]);
    memcpy( rowreq_ctx->data.rdbmsSrvParamID, &rdbmsSrvParamID, rowreq_ctx->data.rdbmsSrvParamID_len );

    tmpString = PQgetvalue(pg_db_qry, i, 1);
    tmpInt = strlen(tmpString);
    if ((NULL == rowreq_ctx->data.rdbmsSrvParamCurrValue) ||
        (rowreq_ctx->data.rdbmsSrvParamCurrValue_len < (tmpInt * sizeof(rowreq_ctx->data.rdbmsSrvParamCurrValue[0])))) {
        snmp_log(LOG_ERR,"not enough space for value\n");
	errorCode = MFD_ERROR;
	break;
    }
    rowreq_ctx->data.rdbmsSrvParamCurrValue_len = tmpInt * sizeof(rowreq_ctx->data.rdbmsSrvParamCurrValue[0]);
    memcpy( rowreq_ctx->data.rdbmsSrvParamCurrValue, tmpString, rowreq_ctx->data.rdbmsSrvParamCurrValue_len );

    tmpString = PQgetvalue(pg_db_qry, i, 2);
    tmpInt = strlen(tmpString);
    if ((NULL == rowreq_ctx->data.rdbmsSrvParamComment) ||
        (rowreq_ctx->data.rdbmsSrvParamComment_len < (tmpInt * sizeof(rowreq_ctx->data.rdbmsSrvParamComment[0])))) {
        snmp_log(LOG_ERR,"not enough space for value\n");
	errorCode = MFD_ERROR;
	break;
    }
    rowreq_ctx->data.rdbmsSrvParamComment_len = tmpInt * sizeof(rowreq_ctx->data.rdbmsSrvParamComment[0]);
    memcpy( rowreq_ctx->data.rdbmsSrvParamComment, tmpString, rowreq_ctx->data.rdbmsSrvParamComment_len );


        /*
         * insert into table container
         */
        CONTAINER_INSERT(container, rowreq_ctx);
        ++count;
    }


    DEBUGMSGT(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_cache_load",
               "inserted %d records\n", count));
    PQclear(pg_db_qry);

    return MFD_SUCCESS;
} /* rdbmsSrvParamTable_cache_load */

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
rdbmsSrvParamTable_cache_free(netsnmp_container *container)
{
    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_cache_free","called\n"));

    /*
     * TODO:380:M: Free rdbmsSrvParamTable cache.
     */
} /* rdbmsSrvParamTable_cache_free */

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
rdbmsSrvParamTable_row_prep( rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_row_prep","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvParamTable_row_prep */

/** @} */
