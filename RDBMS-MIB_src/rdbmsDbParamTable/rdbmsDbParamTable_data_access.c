/*-------------------------------------------------------------------------
 * rdbmsDbParamTable_data_access.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbParamTable_data_access.c,v 1.6 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsDbParamTable.h"
#include "rdbmsDbParamTable_data_access.h"
#include "pg_array.h"

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
 *** Table rdbmsDbParamTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbParamTable is subid 3 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.3, length: 9
*/

/**
 * initialization for rdbmsDbParamTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param rdbmsDbParamTable_reg
 *        Pointer to rdbmsDbParamTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
rdbmsDbParamTable_init_data(rdbmsDbParamTable_registration_ptr rdbmsDbParamTable_reg)
{
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamTable_init_data","called\n"));

    /*
     * TODO:303:o: Initialize rdbmsDbParamTable data.
     */

    return MFD_SUCCESS;
} /* rdbmsDbParamTable_init_data */

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
rdbmsDbParamTable_container_init(netsnmp_container **container_ptr_ptr,
                        netsnmp_cache *cache)
{
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamTable_container_init","called\n"));
    
    if((NULL == cache) || (NULL == container_ptr_ptr)) {
        snmp_log(LOG_ERR,"bad params to rdbmsDbParamTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    /*
     * TODO:345:A: Set up rdbmsDbParamTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper. To completely disable caching, set
     * cache->enabled to 0.
     */
    cache->timeout = RDBMSDBPARAMTABLE_CACHE_TIMEOUT; /* seconds */
} /* rdbmsDbParamTable_container_init */

/**
 * load cache data
 *
 * TODO:350:M: Implement rdbmsDbParamTable cache load
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
 *  rdbmsDbParamTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
rdbmsDbParamTable_cache_load(netsnmp_container *container)
{
    rdbmsDbParamTable_rowreq_ctx *rowreq_ctx;
    size_t                 count = 0;
    int i, j, resultCount, errorCode = MFD_SUCCESS, elements;
    
   long   rdbmsDbParamSubIndex = 0;
   PGresult *qryRes;
   char **array;

   int rdbmsDbIndex;
   int rdbmsDbParamCurrValue_len, rdbmsDbParamComment_len = 0, rdbmsDbParamName_len;
   char rdbmsDbParamCurrValue[255], rdbmsDbParamComment[255] = { "" }, *tmp, rdbmsDbParamName[64];

    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamTable_cache_load","called\n"));

    /*
     * TODO:351:M: |-> Load/update data in the rdbmsDbParamTable container.
     * loop over your rdbmsDbParamTable data, allocate a rowreq context,
     * set the index(es) [and data, optionally] and insert into
     * the container.
     */

    if (PQstatus(dbconn) == CONNECTION_OK) 
	    qryRes = PQexec(dbconn, "SELECT oid, datname, datconfig FROM pg_database");
    else {
	    snmp_log(LOG_ERR, "Can't get connected to the database");
	    return MFD_RESOURCE_UNAVAILABLE;
    }
    if (PQresultStatus(qryRes) != PGRES_TUPLES_OK) {
	    snmp_log(LOG_ERR, "Didn't get any results from the database");
	    PQclear(qryRes);
	    /*PQfinish(dbconn);*/
	    /* It's probably an error if I didn't find *any* databases */
	    return MFD_RESOURCE_UNAVAILABLE;
    }

    resultCount = PQntuples(qryRes);
    for (i = 0; i < resultCount; i++) {
	    rdbmsDbIndex = atoi(PQgetvalue(qryRes, i, 0));
	    array = pg_text_array_parse(PQgetvalue(qryRes, i, 2), &elements);
	    if (!array) {
		    snmp_log(LOG_INFO, "No rdbmsDbParamTable values found for database %s\n", PQgetvalue(qryRes, i, 1));
		    continue;
	    }
	    for (j = 0; j < elements; j++)  {
		    tmp = strchr(array[j], '=');
		    if (!tmp) continue;
		    memset(rdbmsDbParamName, 0, 64);
		    strncpy(rdbmsDbParamName, array[j], ((tmp - array[j]) < 64 ? (tmp - array[j]) : 64));
		    strncpy(rdbmsDbParamCurrValue, tmp+1, 255);
		    rdbmsDbParamName_len = strlen(rdbmsDbParamName);
		    rdbmsDbParamCurrValue_len = strlen(rdbmsDbParamCurrValue);

		/*
		 * TODO:352:M: |   |-> set indexes in new rdbmsDbParamTable rowreq context.
		 */
		rowreq_ctx = rdbmsDbParamTable_allocate_rowreq_ctx();
		if (NULL == rowreq_ctx) {
		    snmp_log(LOG_ERR, "memory allocation failed\n");
		    errorCode = MFD_RESOURCE_UNAVAILABLE;
		    break;
		}
		if(MFD_SUCCESS != rdbmsDbParamTable_indexes_set(rowreq_ctx
				       , rdbmsDbIndex
				       , rdbmsDbParamName, rdbmsDbParamName_len
				       , rdbmsDbParamSubIndex
		       )) {
		    snmp_log(LOG_ERR,"error setting index while loading "
			     "rdbmsDbParamTable cache.\n");
		    rdbmsDbParamTable_release_rowreq_ctx(rowreq_ctx);
		    continue;
		}

		/*
		 * TODO:352:r: |   |-> populate rdbmsDbParamTable data context.
		 * Populate data context here. (optionally, delay until row prep)
		 */
		rowreq_ctx->data.rdbmsDbParamID_len = 128;
		rowreq_ctx->data.rdbmsDbParamCurrValue_len = 255;
		rowreq_ctx->data.rdbmsDbParamComment_len = 255;
	    /*
	     * TRANSIENT or semi-TRANSIENT data:
	     * copy data or save any info needed to do it in row_prep.
	     */
	    /*
	     * setup/save data for rdbmsDbParamID
	     * rdbmsDbParamID(3)/AutonomousType/ASN_OBJECT_ID/oid(oid)//L/A/w/e/r/d/h
	     */
	    /*
	     * TODO:246:r: |-> Define rdbmsDbParamID mapping.
	     * Map values between raw/native values and MIB values
	     *
	     * if(MFD_SUCCESS !=
	     *    rdbmsDbParamID_map(&rowreq_ctx->data.rdbmsDbParamID, &rowreq_ctx->data.rdbmsDbParamID_len,
	     *                rdbmsDbParamID, rdbmsDbParamID_len, 0)) {
	     *    return MFD_ERROR;
	     * }
	     */
	    /*
	     * make sure there is enough space for rdbmsDbParamID data
	     */
	    /* See comment in rdbmsDbParamID_get() -- we don't need this value 
	    if ((NULL == rowreq_ctx->data.rdbmsDbParamID) ||
		(rowreq_ctx->data.rdbmsDbParamID_len < (rdbmsDbParamID_len * sizeof(rowreq_ctx->data.rdbmsDbParamID[0])))) {
		snmp_log(LOG_ERR,"not enough space for value\n");
		errorCode = MFD_ERROR;
		break;
	    }
	    rowreq_ctx->data.rdbmsDbParamID_len = rdbmsDbParamID_len * sizeof(rowreq_ctx->data.rdbmsDbParamID[0]);
	    memcpy( rowreq_ctx->data.rdbmsDbParamID, rdbmsDbParamID, rowreq_ctx->data.rdbmsDbParamID_len );
	    */
	    
	    /*
	     * setup/save data for rdbmsDbParamCurrValue
	     * rdbmsDbParamCurrValue(4)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H
	     */
	    /*
	     * TODO:246:r: |-> Define rdbmsDbParamCurrValue mapping.
	     * Map values between raw/native values and MIB values
	     *
	     * if(MFD_SUCCESS !=
	     *    rdbmsDbParamCurrValue_map(&rowreq_ctx->data.rdbmsDbParamCurrValue, &rowreq_ctx->data.rdbmsDbParamCurrValue_len,
	     *                rdbmsDbParamCurrValue, rdbmsDbParamCurrValue_len, 0)) {
	     *    return MFD_ERROR;
	     * }
	     */
	    /*
	     * make sure there is enough space for rdbmsDbParamCurrValue data
	     */
	    if ((NULL == rowreq_ctx->data.rdbmsDbParamCurrValue) ||
		(rowreq_ctx->data.rdbmsDbParamCurrValue_len < (rdbmsDbParamCurrValue_len * sizeof(rowreq_ctx->data.rdbmsDbParamCurrValue[0])))) {
		snmp_log(LOG_ERR,"not enough space for value\n");
		errorCode = MFD_ERROR;
		break;
	    }
	    rowreq_ctx->data.rdbmsDbParamCurrValue_len = rdbmsDbParamCurrValue_len * sizeof(rowreq_ctx->data.rdbmsDbParamCurrValue[0]);
	    memcpy( rowreq_ctx->data.rdbmsDbParamCurrValue, rdbmsDbParamCurrValue, rowreq_ctx->data.rdbmsDbParamCurrValue_len );
	    
	    /*
	     * setup/save data for rdbmsDbParamComment
	     * rdbmsDbParamComment(5)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H
	     */
	    /*
	     * TODO:246:r: |-> Define rdbmsDbParamComment mapping.
	     * Map values between raw/native values and MIB values
	     *
	     * if(MFD_SUCCESS !=
	     *    rdbmsDbParamComment_map(&rowreq_ctx->data.rdbmsDbParamComment, &rowreq_ctx->data.rdbmsDbParamComment_len,
	     *                rdbmsDbParamComment, rdbmsDbParamComment_len, 0)) {
	     *    return MFD_ERROR;
	     * }
	     */
	    /*
	     * make sure there is enough space for rdbmsDbParamComment data
	     */
	    if ((NULL == rowreq_ctx->data.rdbmsDbParamComment) ||
		(rowreq_ctx->data.rdbmsDbParamComment_len < (rdbmsDbParamComment_len * sizeof(rowreq_ctx->data.rdbmsDbParamComment[0])))) {
		snmp_log(LOG_ERR,"not enough space for value\n");
		errorCode = MFD_ERROR;
		break;
	    }
	    rowreq_ctx->data.rdbmsDbParamComment_len = rdbmsDbParamComment_len * sizeof(rowreq_ctx->data.rdbmsDbParamComment[0]);
	    memcpy( rowreq_ctx->data.rdbmsDbParamComment, rdbmsDbParamComment, rowreq_ctx->data.rdbmsDbParamComment_len );
	    
		
		/*
		 * insert into table container
		 */
		CONTAINER_INSERT(container, rowreq_ctx);
		++count;
	    }
	    pg_text_array_free(array, elements);
    }

    DEBUGMSGT(("verbose:rdbmsDbParamTable:rdbmsDbParamTable_cache_load",
               "inserted %d records\n", count));

    PQclear(qryRes);
    return errorCode;
} /* rdbmsDbParamTable_cache_load */

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
rdbmsDbParamTable_cache_free(netsnmp_container *container)
{
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamTable_cache_free","called\n"));

    /*
     * TODO:380:M: Free rdbmsDbParamTable cache.
     */
} /* rdbmsDbParamTable_cache_free */

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
rdbmsDbParamTable_row_prep( rdbmsDbParamTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("verbose:rdbmsDbParamTable:rdbmsDbParamTable_row_prep","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
} /* rdbmsDbParamTable_row_prep */

/** @} */
