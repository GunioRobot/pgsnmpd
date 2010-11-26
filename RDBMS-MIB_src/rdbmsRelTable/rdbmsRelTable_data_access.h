/*-------------------------------------------------------------------------
 * rdbmsRelTable_data_access.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsRelTable_data_access.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSRELTABLE_DATA_ACCESS_H
#define RDBMSRELTABLE_DATA_ACCESS_H

#ifdef __cplusplus
extern "C" {
#endif


/* *********************************************************************
 * function declarations
 */

/* *********************************************************************
 * Table declarations
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


    int rdbmsRelTable_init_data(rdbmsRelTable_registration_ptr rdbmsRelTable_reg);


/*
 * TODO:180:o: Review rdbmsRelTable cache timeout.
 * The number of seconds before the cache times out
 */
#define RDBMSRELTABLE_CACHE_TIMEOUT   60

void rdbmsRelTable_container_init(netsnmp_container **container_ptr_ptr,
                             netsnmp_cache *cache);
int rdbmsRelTable_cache_load(netsnmp_container *container);
void rdbmsRelTable_cache_free(netsnmp_container *container);

    /*
    ***************************************************
    ***             START EXAMPLE CODE              ***
    ***---------------------------------------------***/
/* *********************************************************************
 * Since we have no idea how you really access your data, we'll go with
 * a worst case example: a flat text file.
 */
#define MAX_LINE_SIZE 256
    /*
    ***---------------------------------------------***
    ***              END  EXAMPLE CODE              ***
    ***************************************************/
    int rdbmsRelTable_row_prep( rdbmsRelTable_rowreq_ctx *rowreq_ctx);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSRELTABLE_DATA_ACCESS_H */
