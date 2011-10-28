/*-------------------------------------------------------------------------
 * rdbmsDbTable_interface.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable_interface.c,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsDbTable.h"
#include "rdbmsDbTable_interface.h"

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
typedef struct rdbmsDbTable_interface_ctx_s {

   netsnmp_container              *container;
   netsnmp_cache                  *cache; /* optional cache */

   rdbmsDbTable_registration_ptr      user_ctx;

   netsnmp_table_registration_info  tbl_info;

   netsnmp_baby_steps_access_methods access_multiplexer;

} rdbmsDbTable_interface_ctx;

static rdbmsDbTable_interface_ctx rdbmsDbTable_if_ctx;

static void _rdbmsDbTable_container_init(
    rdbmsDbTable_interface_ctx *if_ctx);


static Netsnmp_Node_Handler _mfd_rdbmsDbTable_pre_request;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_post_request;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_object_lookup;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_get_values;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_check_objects;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_undo_setup;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_set_values;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_undo_cleanup;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_undo_values;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_commit;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_undo_commit;
static Netsnmp_Node_Handler _mfd_rdbmsDbTable_check_dependencies;

NETSNMP_STATIC_INLINE int _rdbmsDbTable_undo_column( rdbmsDbTable_rowreq_ctx *rowreq_ctx,
                                                   netsnmp_variable_list *var, int column );

rdbmsDbTable_data *rdbmsDbTable_allocate_data(void);
void rdbmsDbTable_release_data(rdbmsDbTable_data *data);

/**
 * @internal
 * Initialize the table rdbmsDbTable
 *    (Define its contents and how it's structured)
 */
void
_rdbmsDbTable_initialize_interface(rdbmsDbTable_registration_ptr reg_ptr,  u_long flags)
{
    netsnmp_baby_steps_access_methods *access_multiplexer =
        &rdbmsDbTable_if_ctx.access_multiplexer;
    netsnmp_table_registration_info *tbl_info = &rdbmsDbTable_if_ctx.tbl_info;
    netsnmp_handler_registration *reginfo;
    netsnmp_mib_handler *handler;
    int    mfd_modes = 0;

    DEBUGMSGTL(("internal:rdbmsDbTable:_rdbmsDbTable_initialize_interface","called\n"));


    /*************************************************
     *
     * save interface context for rdbmsDbTable
     */
    /*
     * Setting up the table's definition
     */
    netsnmp_table_helper_add_indexes(tbl_info,
                                  ASN_INTEGER, /** index: rdbmsDbIndex */
                             0);

    /*  Define the minimum and maximum accessible columns.  This
        optimizes retrival. */
    tbl_info->min_column = RDBMSDBTABLE_MIN_COL;
    tbl_info->max_column = RDBMSDBTABLE_MAX_COL;

    /*
     * save users context
     */
    rdbmsDbTable_if_ctx.user_ctx = reg_ptr;

    /*
     * call data access initialization code
     */
    rdbmsDbTable_init_data(reg_ptr);

    /*
     * set up the container
     */
    _rdbmsDbTable_container_init(&rdbmsDbTable_if_ctx);
    if (NULL == rdbmsDbTable_if_ctx.container) {
        snmp_log(LOG_ERR,"could not initialize container for rdbmsDbTable\n");
        return;
    }

    /*
     * access_multiplexer: REQUIRED wrapper for get request handling
     */
    access_multiplexer->object_lookup = _mfd_rdbmsDbTable_object_lookup;
    access_multiplexer->get_values = _mfd_rdbmsDbTable_get_values;

    /*
     * no wrappers yet
     */
    access_multiplexer->pre_request = _mfd_rdbmsDbTable_pre_request;
    access_multiplexer->post_request = _mfd_rdbmsDbTable_post_request;


    /*
     * REQUIRED wrappers for set request handling
     */
    access_multiplexer->object_syntax_checks = _mfd_rdbmsDbTable_check_objects;
    access_multiplexer->undo_setup = _mfd_rdbmsDbTable_undo_setup;
    access_multiplexer->undo_cleanup = _mfd_rdbmsDbTable_undo_cleanup;
    access_multiplexer->set_values = _mfd_rdbmsDbTable_set_values;
    access_multiplexer->undo_sets = _mfd_rdbmsDbTable_undo_values;

    /*
     * no wrappers yet
     */
    access_multiplexer->commit = _mfd_rdbmsDbTable_commit;
    access_multiplexer->undo_commit = _mfd_rdbmsDbTable_undo_commit;

    /*
     * REQUIRED for tables with dependencies
     */
    access_multiplexer->consistency_checks = _mfd_rdbmsDbTable_check_dependencies;

    /*************************************************
     *
     * Create a registration, save our reg data, register table.
     */
    DEBUGMSGTL(("rdbmsDbTable:init_rdbmsDbTable",
                "Registering rdbmsDbTable as a mibs-for-dummies table.\n"));
    handler = netsnmp_baby_steps_access_multiplexer_get(access_multiplexer);
    reginfo = netsnmp_handler_registration_create("rdbmsDbTable", handler,
                                                  rdbmsDbTable_oid,
                                                  rdbmsDbTable_oid_size,
                                                  HANDLER_CAN_BABY_STEP |
                                                  HANDLER_CAN_RWRITE
                                                  );
    if(NULL == reginfo) {
        snmp_log(LOG_ERR,"error registering table rdbmsDbTable\n");
        return;
    }
    reginfo->my_reg_void = &rdbmsDbTable_if_ctx;

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
                                            rdbmsDbTable_if_ctx.container,
                                            TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    netsnmp_inject_handler( reginfo, handler );

    /*************************************************
     *
     * inject cache helper
     */
    if(NULL != rdbmsDbTable_if_ctx.cache) {
        handler = netsnmp_cache_handler_get(rdbmsDbTable_if_ctx.cache);
        netsnmp_inject_handler( reginfo, handler );
    }

    /*
     * register table
     */
    netsnmp_register_table(reginfo, tbl_info);
} /* _rdbmsDbTable_initialize_interface */

void
rdbmsDbTable_valid_columns_set(netsnmp_column_info *vc)
{
    rdbmsDbTable_if_ctx.tbl_info.valid_columns = vc;
} /* rdbmsDbTable_valid_columns_set */

/**
 * @internal
 * convert the index component stored in the context to an oid
 */
int
rdbmsDbTable_index_to_oid(netsnmp_index *oid_idx,
                         rdbmsDbTable_mib_index *mib_idx)
{
    int err = SNMP_ERR_NOERROR;

    /*
     * temp storage for parsing indexes
     */
    /*
     * rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
     */
    netsnmp_variable_list var_rdbmsDbIndex;

    /*
     * set up varbinds
     */
    memset( &var_rdbmsDbIndex, 0x00, sizeof(var_rdbmsDbIndex) );
    var_rdbmsDbIndex.type = ASN_INTEGER;

    /*
     * chain temp index varbinds together
     */
    var_rdbmsDbIndex.next_variable =  NULL;


    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_index_to_oid","called\n"));

        /* rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    snmp_set_var_value(&var_rdbmsDbIndex, (u_char*)&mib_idx->rdbmsDbIndex,
                       sizeof(mib_idx->rdbmsDbIndex));


    err = build_oid_noalloc(oid_idx->oids, oid_idx->len, (size_t *)&oid_idx->len,
                           NULL, 0, &var_rdbmsDbIndex);
    if(err)
        snmp_log(LOG_ERR,"error %d converting index to oid\n", err);

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers( &var_rdbmsDbIndex );

    return err;
} /* rdbmsDbTable_index_to_oid */

/**
 * extract rdbmsDbTable indexes from a netsnmp_index
 *
 * @retval SNMP_ERR_NOERROR  : no error
 * @retval SNMP_ERR_GENERR   : error
 */
int
rdbmsDbTable_index_from_oid(netsnmp_index *oid_idx,
                         rdbmsDbTable_mib_index *mib_idx)
{
    int err = SNMP_ERR_NOERROR;

    /*
     * temp storage for parsing indexes
     */
    /*
     * rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
     */
    netsnmp_variable_list var_rdbmsDbIndex;

    /*
     * set up varbinds
     */
    memset( &var_rdbmsDbIndex, 0x00, sizeof(var_rdbmsDbIndex) );
    var_rdbmsDbIndex.type = ASN_INTEGER;

    /*
     * chain temp index varbinds together
     */
    var_rdbmsDbIndex.next_variable =  NULL;


    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_index_from_oid","called\n"));

    /*
     * parse the oid into the individual index components
     */
    err = parse_oid_indexes( oid_idx->oids, oid_idx->len,
                             &var_rdbmsDbIndex );
    if (err == SNMP_ERR_NOERROR) {
        /*
         * copy out values
         */
    mib_idx->rdbmsDbIndex = *((long *)var_rdbmsDbIndex.val.string);


    }

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers( &var_rdbmsDbIndex );

    return err;
} /* rdbmsDbTable_index_from_oid */


/*
 * rdbmsDbTable_allocate_data
 *
 * Purpose: create new rdbmsDbTable_data.
 */
rdbmsDbTable_data *
rdbmsDbTable_allocate_data(void)
{
    rdbmsDbTable_data *rtn = SNMP_MALLOC_TYPEDEF(rdbmsDbTable_data);

    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_allocate_data","called\n"));

    if(NULL == rtn) {
        snmp_log(LOG_ERR, "unable to malloc memory for new "
                 "rdbmsDbTable_data.\n");
    }

    return rtn;
} /* rdbmsDbTable_allocate_data */

/*
 * rdbmsDbTable_release_data
 *
 * Purpose: release rdbmsDbTable data.
 */
void
rdbmsDbTable_release_data(rdbmsDbTable_data *data)
{
    DEBUGMSGTL(("verbose:rdbmsDbTable:rdbmsDbTable_release_data","called\n"));

    free(data);
} /* rdbmsDbTable_release_data */

/* *********************************************************************
 * @internal
 * allocate resources for a rdbmsDbTable_rowreq_ctx
 */
rdbmsDbTable_rowreq_ctx *
rdbmsDbTable_allocate_rowreq_ctx(void)
{
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  SNMP_MALLOC_TYPEDEF(rdbmsDbTable_rowreq_ctx);

    DEBUGMSGTL(("internal:rdbmsDbTable:rdbmsDbTable_allocate_rowreq_ctx","called\n"));

    if(NULL == rowreq_ctx) {
        snmp_log(LOG_ERR,"Couldn't allocate memory for a "
                 "rdbmsDbTable_rowreq_ctx.\n");
    }

    rowreq_ctx->oid_idx.oids = rowreq_ctx->oid_tmp;

    rowreq_ctx->rdbmsDbTable_data_list = NULL;
    rowreq_ctx->rdbmsDbTable_reg = rdbmsDbTable_if_ctx.user_ctx;


    return rowreq_ctx;
} /* rdbmsDbTable_allocate_rowreq_ctx */

/*
 * @internal
 * release resources for a rdbmsDbTable_rowreq_ctx
 */
void
rdbmsDbTable_release_rowreq_ctx(rdbmsDbTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("internal:rdbmsDbTable:rdbmsDbTable_release_rowreq_ctx","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);


    if(rowreq_ctx->undo)
        rdbmsDbTable_release_data(rowreq_ctx->undo);

    /*
     * free index oid pointer
     */
    if(rowreq_ctx->oid_idx.oids != rowreq_ctx->oid_tmp)
        free(rowreq_ctx->oid_idx.oids);

    SNMP_FREE(rowreq_ctx);
} /* rdbmsDbTable_release_rowreq_ctx */

/**
 * @internal
 * wrapper
 */
static int
_mfd_rdbmsDbTable_pre_request(netsnmp_mib_handler *handler,
                            netsnmp_handler_registration *reginfo,
                            netsnmp_agent_request_info *agtreq_info,
                            netsnmp_request_info *requests)
{
    int rc = rdbmsDbTable_pre_request(rdbmsDbTable_if_ctx.user_ctx);
    if (MFD_SUCCESS != rc) {
        /*
         * nothing we can do about it but log it
         */
        DEBUGMSGTL(("internal:rdbmsDbTable","error %d from "
                    "rdbmsDbTable_pre_request\n", rc));
        netsnmp_request_set_error_all(requests, SNMP_VALIDATE_ERR(rc));
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsDbTable_pre_request */

/**
 * @internal
 * wrapper
 */
static int
_mfd_rdbmsDbTable_post_request(netsnmp_mib_handler *handler,
                             netsnmp_handler_registration *reginfo,
                             netsnmp_agent_request_info *agtreq_info,
                             netsnmp_request_info *requests)
{
    rdbmsDbTable_rowreq_ctx *rowreq_ctx;
    int rc = rdbmsDbTable_post_request(rdbmsDbTable_if_ctx.user_ctx);
    if (MFD_SUCCESS != rc) {
        /*
         * nothing we can do about it but log it
         */
        DEBUGMSGTL(("internal:rdbmsDbTable","error %d from "
                    "rdbmsDbTable_post_request\n", rc));
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
            CONTAINER_INSERT(rdbmsDbTable_if_ctx.container, rowreq_ctx);
        }
        else if (rowreq_ctx->rowreq_flags & MFD_ROW_DELETED) {
            CONTAINER_REMOVE(rdbmsDbTable_if_ctx.container, rowreq_ctx);
            rdbmsDbTable_release_rowreq_ctx(rowreq_ctx);
        }
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsDbTable_post_request */

/**
 * @internal
 * wrapper
 */
static int
_mfd_rdbmsDbTable_object_lookup(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);

    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_object_lookup","called\n"));

    /*
     * get our context from mfd
     * rdbmsDbTable_interface_ctx *if_ctx =
     *             (rdbmsDbTable_interface_ctx *)reginfo->my_reg_void;
     */

    if(NULL == rowreq_ctx) {
        netsnmp_request_set_error_all(requests, SNMP_ERR_NOCREATION);
    }
    else {
        rdbmsDbTable_row_prep(rowreq_ctx);
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsDbTable_object_lookup */

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
_rdbmsDbTable_get_column( rdbmsDbTable_rowreq_ctx *rowreq_ctx,
                       netsnmp_variable_list *var, int column )
{
    int rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_get_column","called\n"));


    netsnmp_assert(NULL != rowreq_ctx);

    switch(column) {

    /* rdbmsDbPrivateMibOID(2)/OBJECTID/ASN_OBJECT_ID/oid(oid)//L/A/w/e/r/d/h */
    case COLUMN_RDBMSDBPRIVATEMIBOID:
    var->type = ASN_OBJECT_ID;
rc = rdbmsDbPrivateMibOID_get(rowreq_ctx, (oid **)&var->val.string, &var->val_len );
        break;

    /* rdbmsDbVendorName(3)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H */
    case COLUMN_RDBMSDBVENDORNAME:
    var->type = ASN_OCTET_STR;
rc = rdbmsDbVendorName_get(rowreq_ctx, (char **)&var->val.string, &var->val_len );
        break;

    /* rdbmsDbName(4)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H */
    case COLUMN_RDBMSDBNAME:
    var->type = ASN_OCTET_STR;
rc = rdbmsDbName_get(rowreq_ctx, (char **)&var->val.string, &var->val_len );
        break;

    /* rdbmsDbContact(5)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H */
    case COLUMN_RDBMSDBCONTACT:
    var->type = ASN_OCTET_STR;
rc = rdbmsDbContact_get(rowreq_ctx, (char **)&var->val.string, &var->val_len );
        break;

     default:
         snmp_log(LOG_ERR,"unknown column %d in _rdbmsDbTable_get_column\n", column);
         break;
    }

    return rc;
} /* _rdbmsDbTable_get_column */

int
_mfd_rdbmsDbTable_get_values(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    netsnmp_table_request_info * tri;
    u_char                     * old_string;
    void                      (*dataFreeHook)(void *);
    int                        rc;

    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_get_values","called\n"));

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

        rc = _rdbmsDbTable_get_column(rowreq_ctx, requests->requestvb, tri->colnum);
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
} /* _mfd_rdbmsDbTable_get_values */

/***********************************************************************
 *
 * SET processing
 *
 ***********************************************************************/

/*----------------------------------------------------------------------
 *
 * SET: Syntax checks
 *
 *---------------------------------------------------------------------*/
/*
 * @internal
 * Check the syntax for a particular column
 */
NETSNMP_STATIC_INLINE int
_rdbmsDbTable_check_column( rdbmsDbTable_rowreq_ctx *rowreq_ctx,
                         netsnmp_variable_list *var, int column )
{
    int rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:rdbmsDbTable:_rdbmsDbTable_check_column","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    switch(column) {

    /* rdbmsDbContact(5)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H */
    case COLUMN_RDBMSDBCONTACT:
    rc = netsnmp_check_vb_type( var, ASN_OCTET_STR );
    if(SNMPERR_SUCCESS == rc) {
    /* check that the value is in the defined range(s); inefficent
     * but keeps rc value knowledge in libarary where it belongs. */
    if( 1
       && ((rc = netsnmp_check_vb_size_range(var, 0,255)) != SNMP_ERR_NOERROR)
     ) {
        ; /* rc set in condition */
    }
   }
    if(SNMPERR_SUCCESS == rc) {
        rc = rdbmsDbContact_check_value( rowreq_ctx, (char *)var->val.string, var->val_len );
        if((MFD_SUCCESS != rc) && (MFD_NOT_VALID_EVER != rc) &&
           (MFD_NOT_VALID_NOW != rc)) {
            snmp_log(LOG_ERR, "bad rc %d from rdbmsDbContact_check_value\n", rc);
            rc = SNMP_ERR_GENERR;
        }
    }
        break;

        default: /** We shouldn't get here */
            rc = SNMP_ERR_GENERR;
            snmp_log(LOG_ERR, "unknown column %d in _rdbmsDbTable_check_column\n", column);
    }

    return rc;
} /* _rdbmsDbTable_check_column */

int
_mfd_rdbmsDbTable_check_objects(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    netsnmp_table_request_info * tri;
    int                          rc;

    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_check_objects","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    for(;requests; requests = requests->next) {

        /*
         * get column number from table request info, and check that column
         */
        tri = netsnmp_extract_table_info(requests);
        if(NULL == tri)
            continue;

        rc = _rdbmsDbTable_check_column(rowreq_ctx, requests->requestvb, tri->colnum);
        if(rc) {
            netsnmp_request_set_error(requests, SNMP_VALIDATE_ERR(rc));
            break;
        }

    } /* for results */

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsDbTable_check_objects */



/*----------------------------------------------------------------------
 *
 * SET: check dependencies
 *
 *---------------------------------------------------------------------*/
/*
 * @internal
 * Check dependencies wrapper
 */
static int
_mfd_rdbmsDbTable_check_dependencies(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    int                    rc;
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_check_dependencies","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    rc = rdbmsDbTable_check_dependencies(rowreq_ctx);
    if(rc){
        DEBUGMSGTL(("verbose:rdbmsDbTable:mfd","error %d from "
                    "rdbmsDbTable_check_dependencies\n", rc));
        netsnmp_request_set_error_all(requests, SNMP_VALIDATE_ERR(rc));
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsDbTable_check_dependencies */

/*----------------------------------------------------------------------
 *
 * SET: Undo setup
 *
 *---------------------------------------------------------------------*/
/*
 * @internal
 * Set the value for a particular column
 */
NETSNMP_STATIC_INLINE int
_rdbmsDbTable_undo_setup_column( rdbmsDbTable_rowreq_ctx *rowreq_ctx, int column )
{
    int rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:rdbmsDbTable:_rdbmsDbTable_undo_setup_column","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    switch(column) {

    /* rdbmsDbContact(5)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H */
    case COLUMN_RDBMSDBCONTACT:
        rowreq_ctx->column_set_flags |= FLAG_RDBMSDBCONTACT;
        rc = rdbmsDbContact_undo_setup(rowreq_ctx );
        break;

     default:
         snmp_log(LOG_ERR,"unknown column %d in _rdbmsDbTable_undo_setup_column\n", column);
         break;
    }

    return rc;
} /* _rdbmsDbTable_undo_setup_column */


/**
 * @internal
 * undo setup
 */
int
_mfd_rdbmsDbTable_undo_setup(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    int                    rc;
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);

    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_undo_setup","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * allocate undo context
     */
    rowreq_ctx->undo = rdbmsDbTable_allocate_data();
    if(NULL == rowreq_ctx->undo) {
        /** msg already logged */
        netsnmp_request_set_error_all(requests, SNMP_ERR_RESOURCEUNAVAILABLE);
        return SNMP_ERR_NOERROR;
    }

    /*
     * row undo setup
     */
    rowreq_ctx->column_set_flags = 0;
    rc = rdbmsDbTable_undo_setup(rowreq_ctx);
    if (MFD_SUCCESS != rc)  {
        DEBUGMSGTL(("verbose:rdbmsDbTable:mfd","error %d from "
                    "rdbmsDbTable_undo_setup\n", rc));
        netsnmp_request_set_error_all(requests, SNMP_VALIDATE_ERR(rc));
    }
    else {
        /*
         * column undo setup
         */
        netsnmp_table_request_info * tri;
        for(;requests; requests = requests->next) {
            /*
             * set column data
             */
            tri = netsnmp_extract_table_info(requests);
            if(NULL == tri)
                continue;

            rc = _rdbmsDbTable_undo_setup_column(rowreq_ctx, tri->colnum);
            if(MFD_SUCCESS != rc)  {
                DEBUGMSGTL(("verbose:rdbmsDbTable:mfd","error %d from "
                            "rdbmsDbTable_undo_setup_column\n", rc));
                netsnmp_set_request_error(agtreq_info, requests, SNMP_VALIDATE_ERR(rc));
            }
        } /* for results */
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsDbTable_undo_setup */

/**
 * @internal
 * undo setup
 */
int
_mfd_rdbmsDbTable_undo_cleanup(netsnmp_mib_handler *handler,
                             netsnmp_handler_registration *reginfo,
                             netsnmp_agent_request_info *agtreq_info,
                             netsnmp_request_info *requests)
{
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    int rc;

    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_undo_cleanup","called\n"));

    /*
     * failed row create in early stages has no rowreq_ctx
     */
    if (NULL == rowreq_ctx)
        return MFD_SUCCESS;

    /*
     * call user cleanup
     */
    rc = rdbmsDbTable_undo_cleanup(rowreq_ctx);
    if (MFD_SUCCESS != rc) {
        /*
         * nothing we can do about it but log it
         */
        DEBUGMSGTL(("verbose:rdbmsDbTable:mfd","error %d from "
                    "rdbmsDbTable_undo_cleanup\n", rc));
    }

    /*
     * release undo context, if needed
     */
    if(rowreq_ctx->undo) {
         rdbmsDbTable_release_data(rowreq_ctx->undo);
         rowreq_ctx->undo = NULL;
    }

    /*
     * clear set flags
     */
    rowreq_ctx->column_set_flags = 0;

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsDbTable_undo_cleanup */

/*----------------------------------------------------------------------
 *
 * SET: Set values
 *
 *---------------------------------------------------------------------*/
/*
 * @internal
 * Set the value for a particular column
 */
NETSNMP_STATIC_INLINE int
_rdbmsDbTable_set_column( rdbmsDbTable_rowreq_ctx *rowreq_ctx,
                       netsnmp_variable_list *var, int column )
{
    int rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:rdbmsDbTable:_rdbmsDbTable_set_column","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    switch(column) {

    /* rdbmsDbContact(5)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H */
    case COLUMN_RDBMSDBCONTACT:
        rowreq_ctx->column_set_flags |= FLAG_RDBMSDBCONTACT;
        rc = rdbmsDbContact_set(rowreq_ctx, (char *)var->val.string, var->val_len );
        break;

     default:
         snmp_log(LOG_ERR,"unknown column %d in _rdbmsDbTable_set_column\n", column);
         break;
    }

    return rc;
} /* _rdbmsDbTable_set_column */

int
_mfd_rdbmsDbTable_set_values(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    netsnmp_table_request_info * tri;
    int                          rc = SNMP_ERR_NOERROR;

    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_set_values","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    rowreq_ctx->column_set_flags = 0;
    for(;requests; requests = requests->next) {
        /*
         * set column data
         */
        tri = netsnmp_extract_table_info(requests);
        if(NULL == tri)
            continue;

        rc = _rdbmsDbTable_set_column(rowreq_ctx,
                                    requests->requestvb, tri->colnum);
        if(MFD_SUCCESS != rc)  {
            DEBUGMSGTL(("verbose:rdbmsDbTable:mfd","error %d from "
                        "rdbmsDbTable_set_column\n", rc));
            netsnmp_set_request_error(agtreq_info, requests, SNMP_VALIDATE_ERR(rc));
        }
    } /* for results */

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsDbTable_set_values */

/*----------------------------------------------------------------------
 *
 * SET: commit
 *
 *---------------------------------------------------------------------*/
/**
 * @internal
 * commit the values
 */
int
_mfd_rdbmsDbTable_commit(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    int                    rc;
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);

    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_commit","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    rc = rdbmsDbTable_commit(rowreq_ctx);
    if (MFD_SUCCESS != rc) {
        DEBUGMSGTL(("verbose:rdbmsDbTable:mfd","error %d from "
                    "rdbmsDbTable_commit\n", rc));
        netsnmp_request_set_error_all(requests, SNMP_VALIDATE_ERR(rc));
    }

    return SNMP_ERR_NOERROR;
}

int
_mfd_rdbmsDbTable_undo_commit(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    int                    rc;
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);

    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_undo_commit","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    rc = rdbmsDbTable_undo_commit(rowreq_ctx);
    if (MFD_SUCCESS != rc) {
        /*
         * nothing we can do about it but log it
         */
        DEBUGMSGTL(("verbose:rdbmsDbTable:mfd","error %d from "
                    "rdbmsDbTable_undo_commit\n", rc));
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsDbTable_commit */

/*----------------------------------------------------------------------
 *
 * SET: Undo
 *
 *---------------------------------------------------------------------*/
/**
 * @internal
 * undo the value for a particular column
 */
NETSNMP_STATIC_INLINE int
_rdbmsDbTable_undo_column( rdbmsDbTable_rowreq_ctx *rowreq_ctx,
                       netsnmp_variable_list *var, int column )
{
    int rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:rdbmsDbTable:_rdbmsDbTable_undo_column","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    switch(column) {

    /* rdbmsDbContact(5)/DisplayString/ASN_OCTET_STR/char(char)//L/A/W/e/R/d/H */
    case COLUMN_RDBMSDBCONTACT:
        rc = rdbmsDbContact_undo(rowreq_ctx);
        break;

     default:
         snmp_log(LOG_ERR,"unknown column %d in _rdbmsDbTable_undo_column\n", column);
         break;
    }

    return rc;
} /* _rdbmsDbTable_undo_column */

int
_mfd_rdbmsDbTable_undo_values(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    int                    rc;
    rdbmsDbTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    netsnmp_table_request_info * tri;

    DEBUGMSGTL(("internal:rdbmsDbTable:_mfd_rdbmsDbTable_undo_values","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    for(;requests; requests = requests->next) {
        /*
         * set column data
         */
        tri = netsnmp_extract_table_info(requests);
        if(NULL == tri)
            continue;

        rc = _rdbmsDbTable_undo_column(rowreq_ctx, requests->requestvb,
                                     tri->colnum);
        if (MFD_SUCCESS != rc) {
            /*
             * nothing we can do about it but log it
             */
            DEBUGMSGTL(("verbose:rdbmsDbTable:mfd","error %d from "
                        "rdbmsDbTable_undo_column\n", rc));
        }
    } /* for results */

    return SNMP_ERR_NOERROR;
} /* _mfd_rdbmsDbTable_undo_values */

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
    DEBUGMSGTL(("internal:rdbmsDbTable:_cache_load","called\n"));

    if((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache for rdbmsDbTable_cache_load\n");
        return -1;
    }

    /** should only be called for an invalid or expired cache */
    netsnmp_assert((0 == cache->valid) || (1 == cache->expired));

    /*
     * call user code
     */
    return rdbmsDbTable_cache_load((netsnmp_container*)cache->magic);
} /* _cache_load */

/**
 * @internal
 */
static void
_cache_item_free(rdbmsDbTable_rowreq_ctx *rowreq_ctx, void *context)
{
    DEBUGMSGTL(("internal:rdbmsDbTable:_cache_item_free","called\n"));

    if(NULL == rowreq_ctx)
        return;

    rdbmsDbTable_release_rowreq_ctx(rowreq_ctx);
} /* _cache_item_free */

/**
 * @internal
 */
static void
_cache_free(netsnmp_cache *cache, void *magic)
{
    netsnmp_container *container;

    DEBUGMSGTL(("internal:rdbmsDbTable:_cache_free","called\n"));

    if((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache in rdbmsDbTable_cache_free\n");
        return;
    }

    container = (netsnmp_container*)cache->magic;

    /*
     * call user code
     */
    rdbmsDbTable_cache_free(container);

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
_rdbmsDbTable_container_init(rdbmsDbTable_interface_ctx *if_ctx)
{
    DEBUGMSGTL(("internal:rdbmsDbTable:_rdbmsDbTable_container_init","called\n"));

    /*
     * set up the cache
     */
    if_ctx->cache = netsnmp_cache_create(30, /* timeout in seconds */
                                         _cache_load, _cache_free,
                                         rdbmsDbTable_oid,
                                         rdbmsDbTable_oid_size);

    if(NULL == if_ctx->cache) {
        snmp_log(LOG_ERR, "error creating cache for rdbmsDbTable\n");
        return;
    }

    if_ctx->cache->flags = NETSNMP_CACHE_DONT_INVALIDATE_ON_SET;

    rdbmsDbTable_container_init(&if_ctx->container, if_ctx->cache);
    if(NULL == if_ctx->container)
        if_ctx->container = netsnmp_container_find("rdbmsDbTable:table_container");
    if(NULL == if_ctx->container) {
        snmp_log(LOG_ERR,"error creating container in "
                 "rdbmsDbTable_container_init\n");
        return;
    }
    if_ctx->cache->magic = (void*)if_ctx->container;
} /* _rdbmsDbTable_container_init */

