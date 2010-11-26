/*-------------------------------------------------------------------------
 * rdbmsSrvTable_data_access.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvTable_data_access.c,v 1.9 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsSrvTable.h"
#include "rdbmsSrvTable_data_access.h"

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
 *** Table rdbmsSrvTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvTable is subid 5 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.5, length: 9
*/

/**
 * initialization for rdbmsSrvTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param rdbmsSrvTable_reg
 *        Pointer to rdbmsSrvTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
rdbmsSrvTable_init_data(rdbmsSrvTable_registration_ptr rdbmsSrvTable_reg)
{
    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvTable_init_data","called\n"));

    /*
     * TODO:303:o: Initialize rdbmsSrvTable data.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvTable_init_data */

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
rdbmsSrvTable_container_init(netsnmp_container **container_ptr_ptr,
                        netsnmp_cache *cache)
{
    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvTable_container_init","called\n"));
    
    if((NULL == cache) || (NULL == container_ptr_ptr)) {
        snmp_log(LOG_ERR,"bad params to rdbmsSrvTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    /*
     * TODO:345:A: Set up rdbmsSrvTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper. To completely disable caching, set
     * cache->enabled to 0.
     */
    cache->timeout = RDBMSSRVTABLE_CACHE_TIMEOUT; /* seconds */
} /* rdbmsSrvTable_container_init */

/**
 * load cache data
 *
 * TODO:350:M: Implement rdbmsSrvTable cache load
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
 *  rdbmsSrvTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
rdbmsSrvTable_cache_load(netsnmp_container *container)
{
    rdbmsSrvTable_rowreq_ctx *rowreq_ctx;
    oid rdbmsSrvPrivateMibOID[128] = { 1,3,6,1,4,1,27645 };
    size_t                 count = 0;
    
        /*
         * applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
         */

	/* Eventually we'll probably want to make this actually pay attention to 
	 * APPLICATION-MIB. For now, I'm ignoring it. When we make that change, we'll need to
	 * modify the other files that use applIndex (the one I'm thinking of now is rdbmsRelTable */
   long   applIndex = 1;
   PGresult *pgsnmpd_tbl_qry;
   int vendor_len, contact_len, product_len;
   char *vendor_name, *contact_name, *product_name;

    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvTable_cache_load","called\n"));

    /*
     * TODO:351:M: |-> Load/update data in the rdbmsSrvTable container.
     * loop over your rdbmsSrvTable data, allocate a rowreq context,
     * set the index(es) [and data, optionally] and insert into
     * the container.
     */
    
    /* There's only one server, so we only need to create one row */
        /*
         * TODO:352:M: |   |-> set indexes in new rdbmsSrvTable rowreq context.
         */
        rowreq_ctx = rdbmsSrvTable_allocate_rowreq_ctx();
        if (NULL == rowreq_ctx) {
            snmp_log(LOG_ERR, "memory allocation failed\n");
            return MFD_RESOURCE_UNAVAILABLE;
        }
        if(MFD_SUCCESS != rdbmsSrvTable_indexes_set(rowreq_ctx
                               , applIndex
               )) {
            snmp_log(LOG_ERR,"error setting index while loading "
                     "rdbmsSrvTable cache.\n");
            rdbmsSrvTable_release_rowreq_ctx(rowreq_ctx);
	    return MFD_ERROR;
        }

	pgsnmpd_tbl_qry = PQexec(dbconn, "SELECT vendor_name, product_name, contact_name FROM pgsnmpd_rdbmsSrvTable");
	if (PQresultStatus(pgsnmpd_tbl_qry) == PGRES_TUPLES_OK && PQntuples(pgsnmpd_tbl_qry) > 0) {
		vendor_name  = PQgetvalue(pgsnmpd_tbl_qry, 0, 0);
		product_name = PQgetvalue(pgsnmpd_tbl_qry, 0, 1);
		contact_name = PQgetvalue(pgsnmpd_tbl_qry, 0, 2);
		vendor_len = strlen(vendor_name);
		product_len = strlen(product_name);
		contact_len = strlen(contact_name);
	}
	else {
		product_name = NULL;
		vendor_name = NULL;
		contact_name = NULL;
		product_len = 0;
		vendor_len = 0;
		contact_len = 0;
	}

	rowreq_ctx->data.rdbmsSrvVendorName_len = 255;
	rowreq_ctx->data.rdbmsSrvContact_len = 255;
	rowreq_ctx->data.rdbmsSrvProductName_len = 255;

    rowreq_ctx->data.rdbmsSrvPrivateMibOID_len = 8 * sizeof(rowreq_ctx->data.rdbmsSrvPrivateMibOID[0]);
    memcpy( rowreq_ctx->data.rdbmsSrvPrivateMibOID, rdbmsSrvPrivateMibOID, rowreq_ctx->data.rdbmsSrvPrivateMibOID_len );

    rowreq_ctx->data.rdbmsSrvVendorName_len = vendor_len * sizeof(rowreq_ctx->data.rdbmsSrvVendorName[0]);
    memcpy( rowreq_ctx->data.rdbmsSrvVendorName, vendor_name, rowreq_ctx->data.rdbmsSrvVendorName_len );
    
    rowreq_ctx->data.rdbmsSrvProductName_len = product_len * sizeof(rowreq_ctx->data.rdbmsSrvProductName[0]);
    memcpy( rowreq_ctx->data.rdbmsSrvProductName, product_name, rowreq_ctx->data.rdbmsSrvProductName_len );
    
    rowreq_ctx->data.rdbmsSrvContact_len = contact_len * sizeof(rowreq_ctx->data.rdbmsSrvContact[0]);
    memcpy( rowreq_ctx->data.rdbmsSrvContact, contact_name, rowreq_ctx->data.rdbmsSrvContact_len );

    PQclear(pgsnmpd_tbl_qry);
    
        
        /*
         * insert into table container
         */
        CONTAINER_INSERT(container, rowreq_ctx);
        ++count;


    DEBUGMSGT(("verbose:rdbmsSrvTable:rdbmsSrvTable_cache_load",
               "inserted %d records\n", count));

    return MFD_SUCCESS;
} /* rdbmsSrvTable_cache_load */

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
rdbmsSrvTable_cache_free(netsnmp_container *container)
{
    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvTable_cache_free","called\n"));

    /*
     * TODO:380:M: Free rdbmsSrvTable cache.
     */
} /* rdbmsSrvTable_cache_free */

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
rdbmsSrvTable_row_prep( rdbmsSrvTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("verbose:rdbmsSrvTable:rdbmsSrvTable_row_prep","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
} /* rdbmsSrvTable_row_prep */

/** @} */
