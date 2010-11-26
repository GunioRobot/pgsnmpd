/*-------------------------------------------------------------------------
 * rdbmsSrvInfoTable_interface.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvInfoTable_interface.c,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"
/* include our parent header */
#include "rdbmsSrvInfoTable.h"


#include <net-snmp/library/container.h>

#include "rdbmsSrvInfoTable_interface.h"

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
typedef struct rdbmsSrvInfoTable_interface_ctx_s {

   netsnmp_container              *container;
   netsnmp_cache                  *cache; /* optional cache */

   rdbmsSrvInfoTable_registration_ptr      user_ctx;
   
   netsnmp_table_registration_info  tbl_info;

   netsnmp_baby_steps_access_methods access_multiplexer;

} rdbmsSrvInfoTable_interface_ctx;

static rdbmsSrvInfoTable_interface_ctx rdbmsSrvInfoTable_if_ctx;

static void _rdbmsSrvInfoTable_container_init(
    rdbmsSrvInfoTable_interface_ctx *if_ctx);


static Netsnmp_Node_Handler _mfd_rdbmsSrvInfoTable_pre_request;
static Netsnmp_Node_Handler _mfd_rdbmsSrvInfoTable_post_request;
static Netsnmp_Node_Handler _mfd_rdbmsSrvInfoTable_object_lookup;
static Netsnmp_Node_Handler _mfd_rdbmsSrvInfoTable_get_values;
/**
 * @internal
 * Initialize the table rdbmsSrvInfoTable 
 *    (Define its contents and how it's structured)
 */
void
_rdbmsSrvInfoTable_initialize_interface(rdbmsSrvInfoTable_registration_ptr reg_ptr,  u_long flags)
{
    netsnmp_baby_steps_access_methods *access_multiplexer =
        &rdbmsSrvInfoTable_if_ctx.access_multiplexer;
    netsnmp_table_registration_info *tbl_info = &rdbmsSrvInfoTable_if_ctx.tbl_info;
    netsnmp_handler_registration *reginfo;
    netsnmp_mib_handler *handler;
    int    mfd_modes = 0;

    DEBUGMSGTL(("internal:rdbmsSrvInfoTable:_rdbmsSrvInfoTable_initialize_interface","called\n"));


    /*************************************************
     *
     * save interface context for rdbmsSrvInfoTable
     */
    /*
     * Setting up the table's definition
     */
    netsnmp_table_helper_add_indexes(tbl_info,
                                  ASN_INTEGER, /** index: applIndex */
                             0);

    /*  Define the minimum and maximum accessible columns.  This
        optimizes retrival. */
    tbl_info->min_column = RDBMSSRVINFOTABLE_MIN_COL;
    tbl_info->max_column = RDBMSSRVINFOTABLE_MAX_COL;

    /*
     * save users context
     */
    rdbmsSrvInfoTable_if_ctx.user_ctx = reg_ptr;

    /*
     * call data access initialization code
     */
    rdbmsSrvInfoTable_init_data(reg_ptr);

    /*
     * set up the container
     */
    _rdbmsSrvInfoTable_container_init(&rdbmsSrvInfoTable_if_ctx);
    if (NULL == rdbmsSrvInfoTable_if_ctx.container) {
        snmp_log(LOG_ERR,"could not initialize container for rdbmsSrvInfoTable\n");
        return;
    }
    
    /*
     * access_multiplexer: REQUIRED wrapper for get request handling
     */
    access_multiplexer->object_lookup = _mfd_rdbmsSrvInfoTable_object_lookup;
    access_multiplexer->get_values = _mfd_rdbmsSrvInfoTable_get_values;

    /*
     * no wrappers yet
     */
    access_multiplexer->pre_request = _mfd_rdbmsSrvInfoTable_pre_request;
    access_multiplexer->post_request = _mfd_rdbmsSrvInfoTable_post_request;


    /*************************************************
     *
     * Create a registration, save our reg data, register table.
     */
    DEBUGMSGTL(("rdbmsSrvInfoTable:init_rdbmsSrvInfoTable",
                "Registering rdbmsSrvInfoTable as a mibs-for-dummies table.\n"));		 
    handler = netsnmp_baby_steps_access_multiplexer_get(access_multiplexer);
    reginfo = netsnmp_handler_registration_create("rdbmsSrvInfoTable", handler,
                                                  rdbmsSrvInfoTable_oid,
                                                  rdbmsSrvInfoTable_oid_size,
                                                  HANDLER_CAN_BABY_STEP |
                                                  HANDLER_CAN_RONLY
                                                  );
    if(NULL == reginfo) {
        snmp_log(LOG_ERR,"error registering table rdbmsSrvInfoTable\n");
        return;
    }
    reginfo->my_reg_void = &rdbmsSrvInfoTable_if_ctx;

    /*************************************************
     *
     * set up baby steps handler, create it and inject it
     */
    if( access_multiplexer->object_lookup )
        mfd_modes |= BABY_STEP_OBJECT_LOOKUP;
    if( access_multiplexer->set_values )
        mfd_modes |= BABY_STEP_SET_VALUES;
    if( access_multiplexer->irreversible_commit )
        mfd_modes |= BABY_STEP_IRREVERSIBLE_COMMIT;
    if( access_multiplexer->object_syntax_checks )
        mfd_modes |= BABY_STEP_CHECK_OBJECT;

    if( access_multiplexer->pre_request )
        mfd_modes |= BABY_STEP_PRE_REQUEST;
    if( access_multiplexer->post_request )
        mfd_modes |= BABY_STEP_POST_REQUEST;
    
    if( access_multiplexer->undo_setup )
        mfd_modes |= BABY_STEP_UNDO_SETUP;
    if( access_multiplexer->undo_cleanup )
        mfd_modes |= BABY_STEP_UNDO_CLEANUP;
    if( access_multiplexer->undo_sets )
        mfd_modes |= BABY_STEP_UNDO_SETS;
    
    if( access_multiplexer->row_creation )
        mfd_modes |= BABY_STEP_ROW_CREATE;
    if( access_multiplexer->consistency_checks )
        mfd_modes |= BABY_STEP_CHECK_CONSISTENCY;
    if( access_multiplexer->commit )
        mfd_modes |= BABY_STEP_COMMIT;
    if( access_multiplexer->undo_commit )
        mfd_modes |= BABY_STEP_UNDO_COMMIT;
    
    handler = netsnmp_baby_steps_handler_get(mfd_modes);
    netsnmp_inject_handler(reginfo, handler);

    /*************************************************
     *
     * inject row_merge helper with prefix rootoid_len + 2 (entry.col)
     */
    handler = netsnmp_get_row_merge_handler(reginfo->rootoid_len + 2);
    netsnmp_inject_handler(reginfo, handler);

    /*************************************************
     *
     * inject container_table helper
     */
    handler =
        netsnmp_container_table_handler_get(tbl_info,
                                            rdbmsSrvInfoTable_if_ctx.container,
                                            TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    netsnmp_inject_handler( reginfo, handler );

    /*************************************************
     *
     * inject cache helper
     */
    if(NULL != rdbmsSrvInfoTable_if_ctx.cache) {
        handler = netsnmp_cache_handler_get(rdbmsSrvInfoTable_if_ctx.cache);
        netsnmp_inject_handler( reginfo, handler );
    }

    /*
     * register table
     */
    netsnmp_register_table(reginfo, tbl_info);
} /* _rdbmsSrvInfoTable_initialize_interface */

void
rdbmsSrvInfoTable_valid_columns_set(netsnmp_column_info *vc)
{
    rdbmsSrvInfoTable_if_ctx.tbl_info.valid_columns = vc;
} /* rdbmsSrvInfoTable_valid_columns_set */

/**
 * @internal
 * convert the index component stored in the context to an oid
 */
int
rdbmsSrvInfoTable_index_to_oid(netsnmp_index *oid_idx,
                         rdbmsSrvInfoTable_mib_index *mib_idx)
{
    int err = SNMP_ERR_NOERROR;
    
    /*
     * temp storage for parsing indexes
     */
    /*
     * applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
     */
    netsnmp_variable_list var_applIndex;

    /*
     * set up varbinds
     */
    memset( &var_applIndex, 0x00, sizeof(var_applIndex) );
    var_applIndex.type = ASN_INTEGER;

    /*
     * chain temp index varbinds together
     */
    var_applIndex.next_variable =  NULL;


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_index_to_oid","called\n"));

        /* applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    snmp_set_var_value(&var_applIndex, (u_char*)&mib_idx->applIndex,
                       sizeof(mib_idx->applIndex));


    err = build_oid_noalloc(oid_idx->oids, oid_idx->len, (size_t *)&oid_idx->len,
                           NULL, 0, &var_applIndex);
    if(err)
        snmp_log(LOG_ERR,"error %d converting index to oid\n", err);

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers( &var_applIndex );

    return err;
} /* rdbmsSrvInfoTable_index_to_oid */

/**
 * extract rdbmsSrvInfoTable indexes from a netsnmp_index
 *
 * @retval SNMP_ERR_NOERROR  : no error
 * @retval SNMP_ERR_GENERR   : error
 */
int
rdbmsSrvInfoTable_index_from_oid(netsnmp_index *oid_idx,
                         rdbmsSrvInfoTable_mib_index *mib_idx)
{
    int err = SNMP_ERR_NOERROR;
    
    /*
     * temp storage for parsing indexes
     */
    /*
     * applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
     */
    netsnmp_variable_list var_applIndex;

    /*
     * set up varbinds
     */
    memset( &var_applIndex, 0x00, sizeof(var_applIndex) );
    var_applIndex.type = ASN_INTEGER;

    /*
     * chain temp index varbinds together
     */
    var_applIndex.next_variable =  NULL;


    DEBUGMSGTL(("verbose:rdbmsSrvInfoTable:rdbmsSrvInfoTable_index_from_oid","called\n"));

    /*
     * parse the oid into the individual index components
     */
    err = parse_oid_indexes( oid_idx->oids, oid_idx->len,
                             &var_applIndex );
    if (err == SNMP_ERR_NOERROR) {
        /*
         * copy out values
         */
    mib_idx->applIndex = *((long *)var_applIndex.val.string);


    }

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers( &var_applIndex );

    return err;
} /* rdbmsSrvInfoTable_index_from_oid */


/* *********************************************************************
 * @internal
 * allocate resources for a rdbmsSrvInfoTable_rowreq_ctx
 */
rdbmsSrvInfoTable_rowreq_ctx *
rdbmsSrvInfoTable_allocate_rowreq_ctx(void)
{
    rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx =
                  SNMP_MALLOC_TYPEDEF(rdbmsSrvInfoTable_rowreq_ctx);

    DEBUGMSGTL(("internal:rdbmsSrvInfoTable:rdbmsSrvInfoTable_allocate_rowreq_ctx","called\n"));

    if(NULL == rowreq_ctx) {
        snmp_log(LOG_ERR,"Couldn't allocate memory for a "
                 "rdbmsSrvInfoTable_rowreq_ctx.\n");
    }

    rowreq_ctx->oid_idx.oids = rowreq_ctx->oid_tmp;

    rowreq_ctx->rdbmsSrvInfoTable_data_list = NULL;
    rowreq_ctx->rdbmsSrvInfoTable_reg = rdbmsSrvInfoTable_if_ctx.user_ctx;


    return rowreq_ctx;
} /* rdbmsSrvInfoTable_allocate_rowreq_ctx */

/*
 * @internal
 * release resources for a rdbmsSrvInfoTable_rowreq_ctx
 */
void
rdbmsSrvInfoTable_release_rowreq_ctx(rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("internal:rdbmsSrvInfoTable:rdbmsSrvInfoTable_release_rowreq_ctx","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);
    

    /*
     * free index oid pointer
     */
    if(rowreq_ctx->oid_idx.oids != rowreq_ctx->oid_tmp)
        free(rowreq_ctx->oid_idx.oids);

    SNMP_FREE(rowreq_ctx);
} /* rdbmsSrvInfoTable_release_rowreq_ctx */

/**
 * @internal
 * wrapper
 */
static int
_mfd_rdbmsSrvInfoTable_pre_request(netsnmp_mib_handler *handler,
                            netsnmp_handler_registration *reginfo,
                            netsnmp_agent_request_info *agtreq_info,
                            netsnmp_request_info *requests)
{
    int rc = rdbmsSrvInfoTable_pre_request(rdbmsSrvInfoTable_if_ctx.user_ctx);
    if (MFD_SUCCESS != rc) {
        /*
         * nothing we can do about it but log it
         */
        DEBUGMSGTL(("internal:rdbmsSrvInfoTable","error %d from "
                    "rdbmsSrvInfoTable_pre_request\n", rc));
        netsnmp_request_set_error_all(requests, SNMP_VALIDATE_ERR(rc));
    }
    
    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsSrvInfoTable_pre_request */

/**
 * @internal
 * wrapper
 */
static int
_mfd_rdbmsSrvInfoTable_post_request(netsnmp_mib_handler *handler,
                             netsnmp_handler_registration *reginfo,
                             netsnmp_agent_request_info *agtreq_info,
                             netsnmp_request_info *requests)
{
    rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx;
    int rc = rdbmsSrvInfoTable_post_request(rdbmsSrvInfoTable_if_ctx.user_ctx);
    if (MFD_SUCCESS != rc) {
        /*
         * nothing we can do about it but log it
         */
        DEBUGMSGTL(("internal:rdbmsSrvInfoTable","error %d from "
                    "rdbmsSrvInfoTable_post_request\n", rc));
    }
    
    /*
     * if there are no errors, check for and handle row creation/deletion
     */
    rc = netsnmp_check_requests_error(requests);
    if ((SNMP_ERR_NOERROR == rc) &&
        (NULL !=
         (rowreq_ctx = netsnmp_container_table_row_extract(requests)))) {
        if (rowreq_ctx->rowreq_flags & MFD_ROW_CREATED) {
            rowreq_ctx->rowreq_flags &= ~MFD_ROW_CREATED;
            CONTAINER_INSERT(rdbmsSrvInfoTable_if_ctx.container, rowreq_ctx);
        }
        else if (rowreq_ctx->rowreq_flags & MFD_ROW_DELETED) {
            CONTAINER_REMOVE(rdbmsSrvInfoTable_if_ctx.container, rowreq_ctx);
            rdbmsSrvInfoTable_release_rowreq_ctx(rowreq_ctx);
        }
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsSrvInfoTable_post_request */

/**
 * @internal
 * wrapper
 */
static int
_mfd_rdbmsSrvInfoTable_object_lookup(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    
    DEBUGMSGTL(("internal:rdbmsSrvInfoTable:_mfd_rdbmsSrvInfoTable_object_lookup","called\n"));

    /*
     * get our context from mfd
     * rdbmsSrvInfoTable_interface_ctx *if_ctx =
     *             (rdbmsSrvInfoTable_interface_ctx *)reginfo->my_reg_void;
     */

    if(NULL == rowreq_ctx) {
        netsnmp_request_set_error_all(requests, SNMP_ERR_NOCREATION);
    }
    else {
        rdbmsSrvInfoTable_row_prep(rowreq_ctx);
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsSrvInfoTable_object_lookup */

/***********************************************************************
 *
 * GET processing
 *
 ***********************************************************************/
/*
 * @internal
 * Retrieve the value for a particular column
 */
NETSNMP_STATIC_INLINE int
_rdbmsSrvInfoTable_get_column( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx,
                       netsnmp_variable_list *var, int column )
{
    int rc = SNMPERR_SUCCESS;
    
    DEBUGMSGTL(("internal:rdbmsSrvInfoTable:_mfd_rdbmsSrvInfoTable_get_column","called\n"));


    netsnmp_assert(NULL != rowreq_ctx);

    switch(column) {

    /* rdbmsSrvInfoStartupTime(1)/DateAndTime/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H */
    case COLUMN_RDBMSSRVINFOSTARTUPTIME:
    var->type = ASN_OCTET_STR;
rc = rdbmsSrvInfoStartupTime_get(rowreq_ctx, (char **)&var->val.string, &var->val_len );
        break;

    /* rdbmsSrvInfoFinishedTransactions(2)/GAUGE/ASN_GAUGE/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFOFINISHEDTRANSACTIONS:
    var->val_len = sizeof(u_long);
    var->type = ASN_GAUGE;
rc = rdbmsSrvInfoFinishedTransactions_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoDiskReads(3)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFODISKREADS:
    var->val_len = sizeof(u_long);
    var->type = ASN_COUNTER;
rc = rdbmsSrvInfoDiskReads_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoLogicalReads(4)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFOLOGICALREADS:
    var->val_len = sizeof(u_long);
    var->type = ASN_COUNTER;
rc = rdbmsSrvInfoLogicalReads_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoDiskWrites(5)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFODISKWRITES:
    var->val_len = sizeof(u_long);
    var->type = ASN_COUNTER;
rc = rdbmsSrvInfoDiskWrites_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoLogicalWrites(6)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFOLOGICALWRITES:
    var->val_len = sizeof(u_long);
    var->type = ASN_COUNTER;
rc = rdbmsSrvInfoLogicalWrites_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoPageReads(7)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFOPAGEREADS:
    var->val_len = sizeof(u_long);
    var->type = ASN_COUNTER;
rc = rdbmsSrvInfoPageReads_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoPageWrites(8)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFOPAGEWRITES:
    var->val_len = sizeof(u_long);
    var->type = ASN_COUNTER;
rc = rdbmsSrvInfoPageWrites_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoDiskOutOfSpaces(9)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFODISKOUTOFSPACES:
    var->val_len = sizeof(u_long);
    var->type = ASN_COUNTER;
rc = rdbmsSrvInfoDiskOutOfSpaces_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoHandledRequests(10)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFOHANDLEDREQUESTS:
    var->val_len = sizeof(u_long);
    var->type = ASN_COUNTER;
rc = rdbmsSrvInfoHandledRequests_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoRequestRecvs(11)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFOREQUESTRECVS:
    var->val_len = sizeof(u_long);
    var->type = ASN_COUNTER;
rc = rdbmsSrvInfoRequestRecvs_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoRequestSends(12)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFOREQUESTSENDS:
    var->val_len = sizeof(u_long);
    var->type = ASN_COUNTER;
rc = rdbmsSrvInfoRequestSends_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoHighwaterInboundAssociations(13)/GAUGE/ASN_GAUGE/u_long(u_long)//l/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVINFOHIGHWATERINBOUNDASSOCIATIONS:
    var->val_len = sizeof(u_long);
    var->type = ASN_GAUGE;
rc = rdbmsSrvInfoHighwaterInboundAssociations_get(rowreq_ctx, (u_long *)var->val.string );
        break;

    /* rdbmsSrvInfoMaxInboundAssociations(14)/GAUGE/ASN_GAUGE/u_long(u_long)//l/A/W/e/r/d/h */
    case COLUMN_RDBMSSRVINFOMAXINBOUNDASSOCIATIONS:
    var->val_len = sizeof(u_long);
    var->type = ASN_GAUGE;
rc = rdbmsSrvInfoMaxInboundAssociations_get(rowreq_ctx, (u_long *)var->val.string );
        break;

     default:
         snmp_log(LOG_ERR,"unknown column %d in _rdbmsSrvInfoTable_get_column\n", column);
         break;
    }

    return rc;
} /* _rdbmsSrvInfoTable_get_column */

int
_mfd_rdbmsSrvInfoTable_get_values(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    netsnmp_table_request_info * tri;
    u_char                     * old_string;
    void                      (*dataFreeHook)(void *);
    int                        rc;

    DEBUGMSGTL(("internal:rdbmsSrvInfoTable:_mfd_rdbmsSrvInfoTable_get_values","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);
    
    for(;requests; requests = requests->next) {
        /*
         * save old pointer, so we can free it if replaced
         */
        old_string = requests->requestvb->val.string;
        dataFreeHook = requests->requestvb->dataFreeHook;
        if(NULL == requests->requestvb->val.string) {
            requests->requestvb->val.string = requests->requestvb->buf;
            requests->requestvb->val_len = sizeof(requests->requestvb->buf);
        }
        else if(requests->requestvb->buf == requests->requestvb->val.string) {
            if(requests->requestvb->val_len != sizeof(requests->requestvb->buf))
                requests->requestvb->val_len = sizeof(requests->requestvb->buf);
        }

        /*
         * get column data
         */
        tri = netsnmp_extract_table_info(requests);
        if(NULL == tri)
            continue;
        
        rc = _rdbmsSrvInfoTable_get_column(rowreq_ctx, requests->requestvb, tri->colnum);
        if(rc) {
            if(MFD_SKIP == rc) {
                requests->requestvb->type = ASN_PRIV_RETRY;
                rc = SNMP_ERR_NOERROR;
            }
        }
        else if (NULL == requests->requestvb->val.string) {
            snmp_log(LOG_ERR,"NULL varbind data pointer!\n");
            rc = SNMP_ERR_GENERR;
        }
        if(rc)
            netsnmp_request_set_error(requests, SNMP_VALIDATE_ERR(rc));

        /*
         * if the buffer wasn't used previously for the old data (i.e. it
         * was allcoated memory)  and the get routine replaced the pointer,
         * we need to free the previous pointer.
         */
        if(old_string && (old_string != requests->requestvb->buf) &&
           (requests->requestvb->val.string != old_string)) {
            if(dataFreeHook)
                (*dataFreeHook)(old_string);
            else
                free(old_string);
        }
    } /* for results */

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsSrvInfoTable_get_values */

/***********************************************************************
 *
 * SET processing
 *
 ***********************************************************************/

/*
 * NOT APPLICABLE (per MIB or user setting)
 */
/***********************************************************************
 *
 * DATA ACCESS
 *
 ***********************************************************************/
/**
 * @internal
 */
static int
_cache_load(netsnmp_cache *cache, void *vmagic)
{
    DEBUGMSGTL(("internal:rdbmsSrvInfoTable:_cache_load","called\n"));

    if((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache for rdbmsSrvInfoTable_cache_load\n");
        return -1;
    }

    /** should only be called for an invalid or expired cache */
    netsnmp_assert((0 == cache->valid) || (1 == cache->expired));
    
    /*
     * call user code
     */
    return rdbmsSrvInfoTable_cache_load((netsnmp_container*)cache->magic);
} /* _cache_load */

/**
 * @internal
 */
static void
_cache_item_free(rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx, void *context)
{
    DEBUGMSGTL(("internal:rdbmsSrvInfoTable:_cache_item_free","called\n"));

    if(NULL == rowreq_ctx)
        return;

    rdbmsSrvInfoTable_release_rowreq_ctx(rowreq_ctx);
} /* _cache_item_free */

/**
 * @internal
 */
static void
_cache_free(netsnmp_cache *cache, void *magic)
{
    netsnmp_container *container;

    DEBUGMSGTL(("internal:rdbmsSrvInfoTable:_cache_free","called\n"));

    if((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache in rdbmsSrvInfoTable_cache_free\n");
        return;
    }

    container = (netsnmp_container*)cache->magic;

    /*
     * call user code
     */
    rdbmsSrvInfoTable_cache_free(container);
    
    /*
     * free all items. inefficient, but easy.
     */
    CONTAINER_CLEAR(container,
                    (netsnmp_container_obj_func *)_cache_item_free,
                    NULL);
} /* _cache_free */

/**
 * @internal
 * initialize the iterator container with functions or wrappers
 */
void
_rdbmsSrvInfoTable_container_init(rdbmsSrvInfoTable_interface_ctx *if_ctx)
{
    DEBUGMSGTL(("internal:rdbmsSrvInfoTable:_rdbmsSrvInfoTable_container_init","called\n"));
    
    /*
     * set up the cache
     */
    if_ctx->cache = netsnmp_cache_create(30, /* timeout in seconds */
                                         _cache_load, _cache_free,
                                         rdbmsSrvInfoTable_oid,
                                         rdbmsSrvInfoTable_oid_size);

    if(NULL == if_ctx->cache) {
        snmp_log(LOG_ERR, "error creating cache for rdbmsSrvInfoTable\n");
        return;
    }

    if_ctx->cache->flags = NETSNMP_CACHE_DONT_INVALIDATE_ON_SET;

    rdbmsSrvInfoTable_container_init(&if_ctx->container, if_ctx->cache);
    if(NULL == if_ctx->container)
        if_ctx->container = netsnmp_container_find("rdbmsSrvInfoTable:table_container");
    if(NULL == if_ctx->container) {
        snmp_log(LOG_ERR,"error creating container in "
                 "rdbmsSrvInfoTable_container_init\n");
        return;
    }
    if_ctx->cache->magic = (void*)if_ctx->container;
} /* _rdbmsSrvInfoTable_container_init */

