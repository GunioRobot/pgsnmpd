/*-------------------------------------------------------------------------
 * rdbmsSrvParamTable_interface.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvParamTable_interface.c,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsSrvParamTable.h"


#include <net-snmp/library/container.h>

#include "rdbmsSrvParamTable_interface.h"

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
typedef struct rdbmsSrvParamTable_interface_ctx_s {

   netsnmp_container              *container;
   netsnmp_cache                  *cache; /* optional cache */

   rdbmsSrvParamTable_registration_ptr      user_ctx;
   
   netsnmp_table_registration_info  tbl_info;

   netsnmp_baby_steps_access_methods access_multiplexer;

} rdbmsSrvParamTable_interface_ctx;

static rdbmsSrvParamTable_interface_ctx rdbmsSrvParamTable_if_ctx;

static void _rdbmsSrvParamTable_container_init(
    rdbmsSrvParamTable_interface_ctx *if_ctx);


static Netsnmp_Node_Handler _mfd_rdbmsSrvParamTable_pre_request;
static Netsnmp_Node_Handler _mfd_rdbmsSrvParamTable_post_request;
static Netsnmp_Node_Handler _mfd_rdbmsSrvParamTable_object_lookup;
static Netsnmp_Node_Handler _mfd_rdbmsSrvParamTable_get_values;
/**
 * @internal
 * Initialize the table rdbmsSrvParamTable 
 *    (Define its contents and how it's structured)
 */
void
_rdbmsSrvParamTable_initialize_interface(rdbmsSrvParamTable_registration_ptr reg_ptr,  u_long flags)
{
    netsnmp_baby_steps_access_methods *access_multiplexer =
        &rdbmsSrvParamTable_if_ctx.access_multiplexer;
    netsnmp_table_registration_info *tbl_info = &rdbmsSrvParamTable_if_ctx.tbl_info;
    netsnmp_handler_registration *reginfo;
    netsnmp_mib_handler *handler;
    int    mfd_modes = 0;

    DEBUGMSGTL(("internal:rdbmsSrvParamTable:_rdbmsSrvParamTable_initialize_interface","called\n"));


    /*************************************************
     *
     * save interface context for rdbmsSrvParamTable
     */
    /*
     * Setting up the table's definition
     */
    netsnmp_table_helper_add_indexes(tbl_info,
                                  ASN_INTEGER, /** index: applIndex */
                                  ASN_OCTET_STR, /** index: rdbmsSrvParamName */
                                  ASN_INTEGER, /** index: rdbmsSrvParamSubIndex */
                             0);

    /*  Define the minimum and maximum accessible columns.  This
        optimizes retrival. */
    tbl_info->min_column = RDBMSSRVPARAMTABLE_MIN_COL;
    tbl_info->max_column = RDBMSSRVPARAMTABLE_MAX_COL;

    /*
     * save users context
     */
    rdbmsSrvParamTable_if_ctx.user_ctx = reg_ptr;

    /*
     * call data access initialization code
     */
    rdbmsSrvParamTable_init_data(reg_ptr);

    /*
     * set up the container
     */
    _rdbmsSrvParamTable_container_init(&rdbmsSrvParamTable_if_ctx);
    if (NULL == rdbmsSrvParamTable_if_ctx.container) {
        snmp_log(LOG_ERR,"could not initialize container for rdbmsSrvParamTable\n");
        return;
    }
    
    /*
     * access_multiplexer: REQUIRED wrapper for get request handling
     */
    access_multiplexer->object_lookup = _mfd_rdbmsSrvParamTable_object_lookup;
    access_multiplexer->get_values = _mfd_rdbmsSrvParamTable_get_values;

    /*
     * no wrappers yet
     */
    access_multiplexer->pre_request = _mfd_rdbmsSrvParamTable_pre_request;
    access_multiplexer->post_request = _mfd_rdbmsSrvParamTable_post_request;


    /*************************************************
     *
     * Create a registration, save our reg data, register table.
     */
    DEBUGMSGTL(("rdbmsSrvParamTable:init_rdbmsSrvParamTable",
                "Registering rdbmsSrvParamTable as a mibs-for-dummies table.\n"));		 
    handler = netsnmp_baby_steps_access_multiplexer_get(access_multiplexer);
    reginfo = netsnmp_handler_registration_create("rdbmsSrvParamTable", handler,
                                                  rdbmsSrvParamTable_oid,
                                                  rdbmsSrvParamTable_oid_size,
                                                  HANDLER_CAN_BABY_STEP |
                                                  HANDLER_CAN_RONLY
                                                  );
    if(NULL == reginfo) {
        snmp_log(LOG_ERR,"error registering table rdbmsSrvParamTable\n");
        return;
    }
    reginfo->my_reg_void = &rdbmsSrvParamTable_if_ctx;

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
                                            rdbmsSrvParamTable_if_ctx.container,
                                            TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    netsnmp_inject_handler( reginfo, handler );

    /*************************************************
     *
     * inject cache helper
     */
    if(NULL != rdbmsSrvParamTable_if_ctx.cache) {
        handler = netsnmp_cache_handler_get(rdbmsSrvParamTable_if_ctx.cache);
        netsnmp_inject_handler( reginfo, handler );
    }

    /*
     * register table
     */
    netsnmp_register_table(reginfo, tbl_info);
} /* _rdbmsSrvParamTable_initialize_interface */

void
rdbmsSrvParamTable_valid_columns_set(netsnmp_column_info *vc)
{
    rdbmsSrvParamTable_if_ctx.tbl_info.valid_columns = vc;
} /* rdbmsSrvParamTable_valid_columns_set */

/**
 * @internal
 * convert the index component stored in the context to an oid
 */
int
rdbmsSrvParamTable_index_to_oid(netsnmp_index *oid_idx,
                         rdbmsSrvParamTable_mib_index *mib_idx)
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
     * rdbmsSrvParamName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
     */
    netsnmp_variable_list var_rdbmsSrvParamName;
    /*
     * rdbmsSrvParamSubIndex(2)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
     */
    netsnmp_variable_list var_rdbmsSrvParamSubIndex;

    /*
     * set up varbinds
     */
    memset( &var_applIndex, 0x00, sizeof(var_applIndex) );
    var_applIndex.type = ASN_INTEGER;
    memset( &var_rdbmsSrvParamName, 0x00, sizeof(var_rdbmsSrvParamName) );
    var_rdbmsSrvParamName.type = ASN_OCTET_STR;
    memset( &var_rdbmsSrvParamSubIndex, 0x00, sizeof(var_rdbmsSrvParamSubIndex) );
    var_rdbmsSrvParamSubIndex.type = ASN_INTEGER;

    /*
     * chain temp index varbinds together
     */
    var_applIndex.next_variable =  &var_rdbmsSrvParamName; var_rdbmsSrvParamName.next_variable =  &var_rdbmsSrvParamSubIndex; var_rdbmsSrvParamSubIndex.next_variable =  NULL;


    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_index_to_oid","called\n"));

        /* applIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    snmp_set_var_value(&var_applIndex, (u_char*)&mib_idx->applIndex,
                       sizeof(mib_idx->applIndex));

        /* rdbmsSrvParamName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H */
    snmp_set_var_value(&var_rdbmsSrvParamName, (u_char*)&mib_idx->rdbmsSrvParamName,
                       mib_idx->rdbmsSrvParamName_len * sizeof(mib_idx->rdbmsSrvParamName[0]));

        /* rdbmsSrvParamSubIndex(2)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    snmp_set_var_value(&var_rdbmsSrvParamSubIndex, (u_char*)&mib_idx->rdbmsSrvParamSubIndex,
                       sizeof(mib_idx->rdbmsSrvParamSubIndex));


    err = build_oid_noalloc(oid_idx->oids, oid_idx->len, (size_t *) &oid_idx->len,
                           NULL, 0, &var_applIndex);
    if(err)
        snmp_log(LOG_ERR,"error %d converting index to oid\n", err);

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers( &var_applIndex );

    return err;
} /* rdbmsSrvParamTable_index_to_oid */

/**
 * extract rdbmsSrvParamTable indexes from a netsnmp_index
 *
 * @retval SNMP_ERR_NOERROR  : no error
 * @retval SNMP_ERR_GENERR   : error
 */
int
rdbmsSrvParamTable_index_from_oid(netsnmp_index *oid_idx,
                         rdbmsSrvParamTable_mib_index *mib_idx)
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
     * rdbmsSrvParamName(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
     */
    netsnmp_variable_list var_rdbmsSrvParamName;
    /*
     * rdbmsSrvParamSubIndex(2)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
     */
    netsnmp_variable_list var_rdbmsSrvParamSubIndex;

    /*
     * set up varbinds
     */
    memset( &var_applIndex, 0x00, sizeof(var_applIndex) );
    var_applIndex.type = ASN_INTEGER;
    memset( &var_rdbmsSrvParamName, 0x00, sizeof(var_rdbmsSrvParamName) );
    var_rdbmsSrvParamName.type = ASN_OCTET_STR;
    memset( &var_rdbmsSrvParamSubIndex, 0x00, sizeof(var_rdbmsSrvParamSubIndex) );
    var_rdbmsSrvParamSubIndex.type = ASN_INTEGER;

    /*
     * chain temp index varbinds together
     */
    var_applIndex.next_variable =  &var_rdbmsSrvParamName; var_rdbmsSrvParamName.next_variable =  &var_rdbmsSrvParamSubIndex; var_rdbmsSrvParamSubIndex.next_variable =  NULL;


    DEBUGMSGTL(("verbose:rdbmsSrvParamTable:rdbmsSrvParamTable_index_from_oid","called\n"));

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
    /*
     * NOTE: val_len is in bytes, rdbmsSrvParamName_len might not be
     */
         if(var_rdbmsSrvParamName.val_len > sizeof(mib_idx->rdbmsSrvParamName))
             err = SNMP_ERR_GENERR;
         else {
             memcpy(mib_idx->rdbmsSrvParamName, var_rdbmsSrvParamName.val.string, var_rdbmsSrvParamName.val_len);
             mib_idx->rdbmsSrvParamName_len = var_rdbmsSrvParamName.val_len / sizeof(mib_idx->rdbmsSrvParamName[0]);
         }
    mib_idx->rdbmsSrvParamSubIndex = *((long *)var_rdbmsSrvParamSubIndex.val.string);


    }

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers( &var_applIndex );

    return err;
} /* rdbmsSrvParamTable_index_from_oid */


/* *********************************************************************
 * @internal
 * allocate resources for a rdbmsSrvParamTable_rowreq_ctx
 */
rdbmsSrvParamTable_rowreq_ctx *
rdbmsSrvParamTable_allocate_rowreq_ctx(void)
{
    rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx =
                  SNMP_MALLOC_TYPEDEF(rdbmsSrvParamTable_rowreq_ctx);

    DEBUGMSGTL(("internal:rdbmsSrvParamTable:rdbmsSrvParamTable_allocate_rowreq_ctx","called\n"));

    if(NULL == rowreq_ctx) {
        snmp_log(LOG_ERR,"Couldn't allocate memory for a "
                 "rdbmsSrvParamTable_rowreq_ctx.\n");
    }

    rowreq_ctx->oid_idx.oids = rowreq_ctx->oid_tmp;

    rowreq_ctx->rdbmsSrvParamTable_data_list = NULL;
    rowreq_ctx->rdbmsSrvParamTable_reg = rdbmsSrvParamTable_if_ctx.user_ctx;


    return rowreq_ctx;
} /* rdbmsSrvParamTable_allocate_rowreq_ctx */

/*
 * @internal
 * release resources for a rdbmsSrvParamTable_rowreq_ctx
 */
void
rdbmsSrvParamTable_release_rowreq_ctx(rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("internal:rdbmsSrvParamTable:rdbmsSrvParamTable_release_rowreq_ctx","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);
    

    /*
     * free index oid pointer
     */
    if(rowreq_ctx->oid_idx.oids != rowreq_ctx->oid_tmp)
        free(rowreq_ctx->oid_idx.oids);

    SNMP_FREE(rowreq_ctx);
} /* rdbmsSrvParamTable_release_rowreq_ctx */

/**
 * @internal
 * wrapper
 */
static int
_mfd_rdbmsSrvParamTable_pre_request(netsnmp_mib_handler *handler,
                            netsnmp_handler_registration *reginfo,
                            netsnmp_agent_request_info *agtreq_info,
                            netsnmp_request_info *requests)
{
    int rc = rdbmsSrvParamTable_pre_request(rdbmsSrvParamTable_if_ctx.user_ctx);
    if (MFD_SUCCESS != rc) {
        /*
         * nothing we can do about it but log it
         */
        DEBUGMSGTL(("internal:rdbmsSrvParamTable","error %d from "
                    "rdbmsSrvParamTable_pre_request\n", rc));
        netsnmp_request_set_error_all(requests, SNMP_VALIDATE_ERR(rc));
    }
    
    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsSrvParamTable_pre_request */

/**
 * @internal
 * wrapper
 */
static int
_mfd_rdbmsSrvParamTable_post_request(netsnmp_mib_handler *handler,
                             netsnmp_handler_registration *reginfo,
                             netsnmp_agent_request_info *agtreq_info,
                             netsnmp_request_info *requests)
{
    rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx;
    int rc = rdbmsSrvParamTable_post_request(rdbmsSrvParamTable_if_ctx.user_ctx);
    if (MFD_SUCCESS != rc) {
        /*
         * nothing we can do about it but log it
         */
        DEBUGMSGTL(("internal:rdbmsSrvParamTable","error %d from "
                    "rdbmsSrvParamTable_post_request\n", rc));
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
            CONTAINER_INSERT(rdbmsSrvParamTable_if_ctx.container, rowreq_ctx);
        }
        else if (rowreq_ctx->rowreq_flags & MFD_ROW_DELETED) {
            CONTAINER_REMOVE(rdbmsSrvParamTable_if_ctx.container, rowreq_ctx);
            rdbmsSrvParamTable_release_rowreq_ctx(rowreq_ctx);
        }
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsSrvParamTable_post_request */

/**
 * @internal
 * wrapper
 */
static int
_mfd_rdbmsSrvParamTable_object_lookup(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    
    DEBUGMSGTL(("internal:rdbmsSrvParamTable:_mfd_rdbmsSrvParamTable_object_lookup","called\n"));

    /*
     * get our context from mfd
     * rdbmsSrvParamTable_interface_ctx *if_ctx =
     *             (rdbmsSrvParamTable_interface_ctx *)reginfo->my_reg_void;
     */

    if(NULL == rowreq_ctx) {
        netsnmp_request_set_error_all(requests, SNMP_ERR_NOCREATION);
    }
    else {
        rdbmsSrvParamTable_row_prep(rowreq_ctx);
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsSrvParamTable_object_lookup */

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
_rdbmsSrvParamTable_get_column( rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx,
                       netsnmp_variable_list *var, int column )
{
    int rc = SNMPERR_SUCCESS;
    
    DEBUGMSGTL(("internal:rdbmsSrvParamTable:_mfd_rdbmsSrvParamTable_get_column","called\n"));


    netsnmp_assert(NULL != rowreq_ctx);

    switch(column) {

    /* rdbmsSrvParamID(3)/AutonomousType/ASN_OBJECT_ID/oid(oid)//L/A/w/e/r/d/h */
    case COLUMN_RDBMSSRVPARAMID:
    var->type = ASN_OBJECT_ID;
rc = rdbmsSrvParamID_get(rowreq_ctx, (oid **)&var->val.string, &var->val_len );
        break;

    /* rdbmsSrvParamCurrValue(4)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H */
    case COLUMN_RDBMSSRVPARAMCURRVALUE:
    var->type = ASN_OCTET_STR;
rc = rdbmsSrvParamCurrValue_get(rowreq_ctx, (char **)&var->val.string, &var->val_len );
        break;

    /* rdbmsSrvParamComment(5)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H */
    case COLUMN_RDBMSSRVPARAMCOMMENT:
    var->type = ASN_OCTET_STR;
rc = rdbmsSrvParamComment_get(rowreq_ctx, (char **)&var->val.string, &var->val_len );
        break;

     default:
         snmp_log(LOG_ERR,"unknown column %d in _rdbmsSrvParamTable_get_column\n", column);
         break;
    }

    return rc;
} /* _rdbmsSrvParamTable_get_column */

int
_mfd_rdbmsSrvParamTable_get_values(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    netsnmp_table_request_info * tri;
    u_char                     * old_string;
    void                      (*dataFreeHook)(void *);
    int                        rc;

    DEBUGMSGTL(("internal:rdbmsSrvParamTable:_mfd_rdbmsSrvParamTable_get_values","called\n"));

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
        
        rc = _rdbmsSrvParamTable_get_column(rowreq_ctx, requests->requestvb, tri->colnum);
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
} /* _mfd_rdbmsSrvParamTable_get_values */

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
    DEBUGMSGTL(("internal:rdbmsSrvParamTable:_cache_load","called\n"));

    if((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache for rdbmsSrvParamTable_cache_load\n");
        return -1;
    }

    /** should only be called for an invalid or expired cache */
    netsnmp_assert((0 == cache->valid) || (1 == cache->expired));
    
    /*
     * call user code
     */
    return rdbmsSrvParamTable_cache_load((netsnmp_container*)cache->magic);
} /* _cache_load */

/**
 * @internal
 */
static void
_cache_item_free(rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx, void *context)
{
    DEBUGMSGTL(("internal:rdbmsSrvParamTable:_cache_item_free","called\n"));

    if(NULL == rowreq_ctx)
        return;

    rdbmsSrvParamTable_release_rowreq_ctx(rowreq_ctx);
} /* _cache_item_free */

/**
 * @internal
 */
static void
_cache_free(netsnmp_cache *cache, void *magic)
{
    netsnmp_container *container;

    DEBUGMSGTL(("internal:rdbmsSrvParamTable:_cache_free","called\n"));

    if((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache in rdbmsSrvParamTable_cache_free\n");
        return;
    }

    container = (netsnmp_container*)cache->magic;

    /*
     * call user code
     */
    rdbmsSrvParamTable_cache_free(container);
    
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
_rdbmsSrvParamTable_container_init(rdbmsSrvParamTable_interface_ctx *if_ctx)
{
    DEBUGMSGTL(("internal:rdbmsSrvParamTable:_rdbmsSrvParamTable_container_init","called\n"));
    
    /*
     * set up the cache
     */
    if_ctx->cache = netsnmp_cache_create(30, /* timeout in seconds */
                                         _cache_load, _cache_free,
                                         rdbmsSrvParamTable_oid,
                                         rdbmsSrvParamTable_oid_size);

    if(NULL == if_ctx->cache) {
        snmp_log(LOG_ERR, "error creating cache for rdbmsSrvParamTable\n");
        return;
    }

    if_ctx->cache->flags = NETSNMP_CACHE_DONT_INVALIDATE_ON_SET;

    rdbmsSrvParamTable_container_init(&if_ctx->container, if_ctx->cache);
    if(NULL == if_ctx->container)
        if_ctx->container = netsnmp_container_find("rdbmsSrvParamTable:table_container");
    if(NULL == if_ctx->container) {
        snmp_log(LOG_ERR,"error creating container in "
                 "rdbmsSrvParamTable_container_init\n");
        return;
    }
    if_ctx->cache->magic = (void*)if_ctx->container;
} /* _rdbmsSrvParamTable_container_init */

