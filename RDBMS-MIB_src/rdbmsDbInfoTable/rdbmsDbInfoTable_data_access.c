/*-------------------------------------------------------------------------
 * rdbmsDbInfoTable_data_access.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbInfoTable_data_access.c,v 1.9 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */
#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsDbInfoTable.h"
#include "rdbmsDbInfoTable_data_access.h"

const char *rdbmsDbInfoProductName = { "PostgreSQL" };

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
 *** Table rdbmsDbInfoTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbInfoTable is subid 2 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.2, length: 9
*/

/**
 * initialization for rdbmsDbInfoTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param rdbmsDbInfoTable_reg
 *        Pointer to rdbmsDbInfoTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
rdbmsDbInfoTable_init_data(rdbmsDbInfoTable_registration_ptr rdbmsDbInfoTable_reg)
{
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoTable_init_data","called\n"));

    /*
     * TODO:303:o: Initialize rdbmsDbInfoTable data.
     */

    return MFD_SUCCESS;
} /* rdbmsDbInfoTable_init_data */

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
rdbmsDbInfoTable_container_init(netsnmp_container **container_ptr_ptr,
                        netsnmp_cache *cache)
{
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoTable_container_init","called\n"));

    if((NULL == cache) || (NULL == container_ptr_ptr)) {
        snmp_log(LOG_ERR,"bad params to rdbmsDbInfoTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    /*
     * TODO:345:A: Set up rdbmsDbInfoTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper. To completely disable caching, set
     * cache->enabled to 0.
     */
    cache->timeout = RDBMSDBINFOTABLE_CACHE_TIMEOUT; /* seconds */
} /* rdbmsDbInfoTable_container_init */

/**
 * load cache data
 *
 * TODO:350:M: Implement rdbmsDbInfoTable cache load
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
 *  rdbmsDbInfoTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
rdbmsDbInfoTable_cache_load(netsnmp_container *container)
{
    rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx;
    size_t count = 0;
    int i, resultCount, errorCode = MFD_SUCCESS, tmpInt;
    PGresult *pg_db_qry, *pgsnmpd_tbl_qry;
    char *db_oid, *tmpString;

    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoTable_cache_load","called\n"));

    if (PQstatus(dbconn) == CONNECTION_OK)
	    if (PQserverVersion(dbconn) < 80100)
		    pg_db_qry = PQexec(dbconn, "SELECT oid, version(), 0 FROM pg_database");
            else
		    pg_db_qry = PQexec(dbconn, "SELECT oid, version(), pg_database_size(datname) FROM pg_database");
    else {
	    snmp_log(LOG_ERR, "Can't get connected to the database");
	    return MFD_RESOURCE_UNAVAILABLE;
    }
    if (PQresultStatus(pg_db_qry) != PGRES_TUPLES_OK) {
	    snmp_log(LOG_ERR, "Didn't get any results from the database");
	    PQclear(pg_db_qry);
	    /* It's probably an error if I didn't find *any* information */
	    return MFD_RESOURCE_UNAVAILABLE;
    }

    resultCount = PQntuples(pg_db_qry);


    /*
     * TODO:351:M: |-> Load/update data in the rdbmsDbInfoTable container.
     * loop over your rdbmsDbInfoTable data, allocate a rowreq context,
     * set the index(es) [and data, optionally] and insert into
     * the container.
     */
    for (i = 0; i < resultCount; i++) {

        /*
         * TODO:352:M: |   |-> set indexes in new rdbmsDbInfoTable rowreq context.
         */
        rowreq_ctx = rdbmsDbInfoTable_allocate_rowreq_ctx();
        if (NULL == rowreq_ctx) {
            snmp_log(LOG_ERR, "memory allocation failed\n");
            return MFD_RESOURCE_UNAVAILABLE;
        }
	db_oid = PQgetvalue(pg_db_qry, i, 0);
        if(MFD_SUCCESS != rdbmsDbInfoTable_indexes_set(rowreq_ctx
                               , atol(db_oid)
               )) {
            snmp_log(LOG_ERR,"error setting index while loading "
                     "rdbmsDbInfoTable cache.\n");
            rdbmsDbInfoTable_release_rowreq_ctx(rowreq_ctx);
            continue;
        }

        /*
         * TODO:352:r: |   |-> populate rdbmsDbInfoTable data context.
         * Populate data context here. (optionally, delay until row prep)
         */

	rowreq_ctx->data.rdbmsDbInfoProductName_len = 255;
	rowreq_ctx->data.rdbmsDbInfoVersion_len = 255;

	pgsnmpd_tbl_qry = NULL;
	tmpInt = sizeof("SELECT EXTRACT(YEAR FROM last_backup), EXTRACT(MONTH FROM last_backup), EXTRACT(DAY FROM last_backup), EXTRACT(HOUR FROM last_backup), EXTRACT(MINUTE FROM last_backup), EXTRACT(SECOND FROM last_backup), EXTRACT(MILLISECOND FROM last_backup), EXTRACT(TIMEZONE_HOUR FROM last_backup), EXTRACT(TIMEZONE_MINUTE FROM last_backup) FROM pgsnmpd_rdbmsDbTable WHERE database_oid = %s") + sizeof(*db_oid);
	tmpString = calloc(tmpInt, sizeof(char*));
	if (tmpString == NULL) snmp_log(LOG_ERR, "Couldn't allocate memory to query pgsnmpd-specific database table\n");
	else {
		snmp_log(LOG_INFO, "Gathering rdbmsDbTable information from pgsnmpd_rdbmsDbTable\n");
		snprintf(tmpString, sizeof(char*) * tmpInt, "SELECT EXTRACT(YEAR FROM last_backup), EXTRACT(MONTH FROM last_backup), EXTRACT(DAY FROM last_backup), EXTRACT(HOUR FROM last_backup), EXTRACT(MINUTE FROM last_backup), EXTRACT(SECOND FROM last_backup), EXTRACT(MILLISECOND FROM last_backup), EXTRACT(TIMEZONE_HOUR FROM last_backup), EXTRACT(TIMEZONE_MINUTE FROM last_backup) FROM pgsnmpd_rdbmsDbTable WHERE database_oid = %s", db_oid);
		pgsnmpd_tbl_qry = PQexec(dbconn, tmpString);
		/* Ignore errors so that pgsnmpd will run without this table being available. Note that this error is INFO level,
		 * instead of something higher, because we're designed to work without this table */

                if (PQresultStatus(pgsnmpd_tbl_qry) == PGRES_TUPLES_OK && PQntuples(pgsnmpd_tbl_qry) > 0) {
	            rowreq_ctx->data.lastBackupYear = atoi(PQgetvalue(pgsnmpd_tbl_qry, 0, 0));
	            rowreq_ctx->data.lastBackupMonth = atoi(PQgetvalue(pgsnmpd_tbl_qry, 0, 1));
	            rowreq_ctx->data.lastBackupDay = atoi(PQgetvalue(pgsnmpd_tbl_qry, 0, 2));
	            rowreq_ctx->data.lastBackupHour = atoi(PQgetvalue(pgsnmpd_tbl_qry, 0, 3));
	            rowreq_ctx->data.lastBackupMinutes = atoi(PQgetvalue(pgsnmpd_tbl_qry, 0, 4));
	            rowreq_ctx->data.lastBackupSeconds = atoi(PQgetvalue(pgsnmpd_tbl_qry, 0, 5));
	            rowreq_ctx->data.lastBackupDeciSeconds = atoi(PQgetvalue(pgsnmpd_tbl_qry, 0, 6));
	            rowreq_ctx->data.utc_offset_hours = abs(atoi(PQgetvalue(pgsnmpd_tbl_qry, 0, 7)));
	            rowreq_ctx->data.utc_offset_minutes = atoi(PQgetvalue(pgsnmpd_tbl_qry, 0, 8));
	            tmpInt = rowreq_ctx->data.utc_offset_hours * 60 + rowreq_ctx->data.utc_offset_minutes;
	            if (tmpInt == 0) rowreq_ctx->data.utc_offset_direction = 0;
	            else
	      	        rowreq_ctx->data.utc_offset_direction = (tmpInt > 0 ? 1 : -1);
		}
		else snmp_log(LOG_INFO, "Unable to find relevant data in pgsnmpd_rdbmsDbTable\n");
		free(tmpString);
	}

    /*
     * TRANSIENT or semi-TRANSIENT data:
     * copy data or save any info needed to do it in row_prep.
     */
    /*
     * setup/save data for rdbmsDbInfoProductName
     * rdbmsDbInfoProductName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
     */
    /*
     * TODO:246:r: |-> Define rdbmsDbInfoProductName mapping.
     * Map values between raw/native values and MIB values
     *
     * if(MFD_SUCCESS !=
     *    rdbmsDbInfoProductName_map(&rowreq_ctx->data.rdbmsDbInfoProductName, &rowreq_ctx->data.rdbmsDbInfoProductName_len,
     *                rdbmsDbInfoProductName, rdbmsDbInfoProductName_len, 0)) {
     *    return MFD_ERROR;
     * }
     */
    /*
     * make sure there is enough space for rdbmsDbInfoProductName data
     */
    if ((NULL == rowreq_ctx->data.rdbmsDbInfoProductName) ||
        (rowreq_ctx->data.rdbmsDbInfoProductName_len < (strlen(rdbmsDbInfoProductName) * sizeof(rowreq_ctx->data.rdbmsDbInfoProductName[0])))) {
        snmp_log(LOG_ERR,"not enough space for value\n");
        errorCode = MFD_ERROR;
	break;
    }
    rowreq_ctx->data.rdbmsDbInfoProductName_len = strlen(rdbmsDbInfoProductName) * sizeof(rowreq_ctx->data.rdbmsDbInfoProductName[0]);
    memcpy( rowreq_ctx->data.rdbmsDbInfoProductName, rdbmsDbInfoProductName, rowreq_ctx->data.rdbmsDbInfoProductName_len );

    /*
     * setup/save data for rdbmsDbInfoVersion
     * rdbmsDbInfoVersion(2)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H
     */
    /*
     * TODO:246:r: |-> Define rdbmsDbInfoVersion mapping.
     * Map values between raw/native values and MIB values
     *
     * if(MFD_SUCCESS !=
     *    rdbmsDbInfoVersion_map(&rowreq_ctx->data.rdbmsDbInfoVersion, &rowreq_ctx->data.rdbmsDbInfoVersion_len,
     *                rdbmsDbInfoVersion, rdbmsDbInfoVersion_len, 0)) {
     *    return MFD_ERROR;
     * }
     */
    /*
     * make sure there is enough space for rdbmsDbInfoVersion data
     */
    tmpString = PQgetvalue(pg_db_qry, i, 1);
    tmpInt = strlen(tmpString);
    if ((NULL == rowreq_ctx->data.rdbmsDbInfoVersion) ||
        (rowreq_ctx->data.rdbmsDbInfoVersion_len < (tmpInt * sizeof(rowreq_ctx->data.rdbmsDbInfoVersion[0])))) {
        snmp_log(LOG_ERR,"not enough space for value\n");
	errorCode = MFD_ERROR;
	break;
    }
    rowreq_ctx->data.rdbmsDbInfoVersion_len = tmpInt * sizeof(rowreq_ctx->data.rdbmsDbInfoVersion[0]);
    memcpy( rowreq_ctx->data.rdbmsDbInfoVersion, tmpString, rowreq_ctx->data.rdbmsDbInfoVersion_len );

    /*
     * setup/save data for rdbmsDbInfoSizeUnits
     * rdbmsDbInfoSizeUnits(3)/INTEGER/ASN_INTEGER/long(u_long)//l/A/w/E/r/d/h
     */
    /*
     * TODO:246:r: |-> Define rdbmsDbInfoSizeUnits mapping.
     * Map values between raw/native values and MIB values
     *
    * enums usually need mapping.
    */
    if(MFD_SUCCESS !=
       rdbmsDbInfoSizeUnits_map(&rowreq_ctx->data.rdbmsDbInfoSizeUnits, INTERNAL_RDBMSDBINFOSIZEUNITS_BYTES)) {
       errorCode = MFD_ERROR;
       break;
    }

    /*
     * setup/save data for rdbmsDbInfoSizeAllocated
     * rdbmsDbInfoSizeAllocated(4)/INTEGER/ASN_INTEGER/long(long)//l/A/W/e/R/d/h
     */
    /*
     * TODO:246:r: |-> Define rdbmsDbInfoSizeAllocated mapping.
     * Map values between raw/native values and MIB values
     *
     * Integer based value can usually just do a direct copy.
     */
    rowreq_ctx->data.rdbmsDbInfoSizeAllocated = strtoul(PQgetvalue(pg_db_qry, i, 2), NULL, 10);

    /*
     * setup/save data for rdbmsDbInfoSizeUsed
     * rdbmsDbInfoSizeUsed(5)/INTEGER/ASN_INTEGER/long(long)//l/A/w/e/R/d/h
     */
    /*
     * TODO:246:r: |-> Define rdbmsDbInfoSizeUsed mapping.
     * Map values between raw/native values and MIB values
     *
     * Integer based value can usually just do a direct copy.
     */
    rowreq_ctx->data.rdbmsDbInfoSizeUsed = strtoul(PQgetvalue(pg_db_qry, i, 2), NULL, 10);

        /*
         * insert into table container
         */
        CONTAINER_INSERT(container, rowreq_ctx);
        ++count;
	PQclear(pgsnmpd_tbl_qry);
    }

    DEBUGMSGT(("verbose:rdbmsDbInfoTable:rdbmsDbInfoTable_cache_load",
               "inserted %d records\n", count));

    PQclear(pg_db_qry);
    return errorCode;
} /* rdbmsDbInfoTable_cache_load */

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
rdbmsDbInfoTable_cache_free(netsnmp_container *container)
{
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoTable_cache_free","called\n"));

    /*
     * TODO:380:M: Free rdbmsDbInfoTable cache.
     */
} /* rdbmsDbInfoTable_cache_free */

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
rdbmsDbInfoTable_row_prep( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoTable_row_prep","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
} /* rdbmsDbInfoTable_row_prep */

/** @} */
