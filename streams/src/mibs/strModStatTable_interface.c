/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.67.2.1 $ of : mfd-interface.m2c,v $ 
 *
 * $Id:$
 */
/*
 * *********************************************************************
 * *********************************************************************
 * *********************************************************************
 * ***                                                               ***
 * ***  NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE  ***
 * ***                                                               ***
 * ***                                                               ***
 * ***       THIS FILE DOES NOT CONTAIN ANY USER EDITABLE CODE.      ***
 * ***                                                               ***
 * ***                                                               ***
 * ***       THE GENERATED CODE IS INTERNAL IMPLEMENTATION, AND      ***
 * ***                                                               ***
 * ***                                                               ***
 * ***    IS SUBJECT TO CHANGE WITHOUT WARNING IN FUTURE RELEASES.   ***
 * ***                                                               ***
 * ***                                                               ***
 * *********************************************************************
 * *********************************************************************
 * *********************************************************************
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "strModStatTable.h"

#include <net-snmp/agent/table_container.h>
#include <net-snmp/library/container.h>

#include "strModStatTable_interface.h"

#include <ctype.h>

/**********************************************************************
 **********************************************************************
 ***
 *** Table strModStatTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * OPENSS7-STREAMS-MIB::strModStatTable is subid 1 of strModStat.
 * Its status is Current.
 * OID: .1.3.6.1.4.1.29591.1.1.1.1.1.3.1, length: 14
*/
typedef struct strModStatTable_interface_ctx_s {

        netsnmp_container *container;
        netsnmp_cache *cache;

        strModStatTable_registration *user_ctx;

        netsnmp_table_registration_info tbl_info;

        netsnmp_baby_steps_access_methods access_multiplexer;

} strModStatTable_interface_ctx;

static strModStatTable_interface_ctx strModStatTable_if_ctx;

static void _strModStatTable_container_init(strModStatTable_interface_ctx * if_ctx);
static void _strModStatTable_container_shutdown(strModStatTable_interface_ctx * if_ctx);

netsnmp_container *
strModStatTable_container_get(void)
{
        return strModStatTable_if_ctx.container;
}

strModStatTable_registration *
strModStatTable_registration_get(void)
{
        return strModStatTable_if_ctx.user_ctx;
}

strModStatTable_registration *
strModStatTable_registration_set(strModStatTable_registration * newreg)
{
        strModStatTable_registration *old = strModStatTable_if_ctx.user_ctx;

        strModStatTable_if_ctx.user_ctx = newreg;
        return old;
}

int
strModStatTable_container_size(void)
{
        return CONTAINER_SIZE(strModStatTable_if_ctx.container);
}

/*
 * mfd multiplexer modes
 */
static Netsnmp_Node_Handler _mfd_strModStatTable_pre_request;
static Netsnmp_Node_Handler _mfd_strModStatTable_post_request;
static Netsnmp_Node_Handler _mfd_strModStatTable_object_lookup;
static Netsnmp_Node_Handler _mfd_strModStatTable_get_values;

/**
 * @internal
 * Initialize the table strModStatTable 
 *    (Define its contents and how it's structured)
 */
void
_strModStatTable_initialize_interface(strModStatTable_registration * reg_ptr, u_long flags)
{
        netsnmp_baby_steps_access_methods *access_multiplexer =
            &strModStatTable_if_ctx.access_multiplexer;
        netsnmp_table_registration_info *tbl_info = &strModStatTable_if_ctx.tbl_info;
        netsnmp_handler_registration *reginfo;
        netsnmp_mib_handler *handler;
        int mfd_modes = 0;

        DEBUGMSGTL(("internal:strModStatTable:_strModStatTable_initialize_interface", "called\n"));

    /*************************************************
     *
     * save interface context for strModStatTable
     */
        /*
         * Setting up the table's definition
         */
        netsnmp_table_helper_add_indexes(tbl_info, ASN_UNSIGNED,
                                                /** index: strModIdnum */
                                         ASN_UNSIGNED,
                                                /** index: strModStatIndex */
                                         0);

        /*  Define the minimum and maximum accessible columns.  This
           optimizes retrival. */
        tbl_info->min_column = STRMODSTATTABLE_MIN_COL;
        tbl_info->max_column = STRMODSTATTABLE_MAX_COL;

        /*
         * save users context
         */
        strModStatTable_if_ctx.user_ctx = reg_ptr;

        /*
         * call data access initialization code
         */
        strModStatTable_init_data(reg_ptr);

        /*
         * set up the container
         */
        _strModStatTable_container_init(&strModStatTable_if_ctx);
        if (NULL == strModStatTable_if_ctx.container) {
                snmp_log(LOG_ERR, "could not initialize container for strModStatTable\n");
                return;
        }

        /*
         * access_multiplexer: REQUIRED wrapper for get request handling
         */
        access_multiplexer->object_lookup = _mfd_strModStatTable_object_lookup;
        access_multiplexer->get_values = _mfd_strModStatTable_get_values;

        /*
         * no wrappers yet
         */
        access_multiplexer->pre_request = _mfd_strModStatTable_pre_request;
        access_multiplexer->post_request = _mfd_strModStatTable_post_request;

    /*************************************************
     *
     * Create a registration, save our reg data, register table.
     */
        DEBUGMSGTL(("strModStatTable:init_strModStatTable",
                    "Registering strModStatTable as a mibs-for-dummies table.\n"));
        handler = netsnmp_baby_steps_access_multiplexer_get(access_multiplexer);
        reginfo = netsnmp_handler_registration_create("strModStatTable", handler,
                                                      strModStatTable_oid,
                                                      strModStatTable_oid_size,
                                                      HANDLER_CAN_BABY_STEP | HANDLER_CAN_RONLY);
        if (NULL == reginfo) {
                snmp_log(LOG_ERR, "error registering table strModStatTable\n");
                return;
        }
        reginfo->my_reg_void = &strModStatTable_if_ctx;

    /*************************************************
     *
     * set up baby steps handler, create it and inject it
     */
        if (access_multiplexer->object_lookup)
                mfd_modes |= BABY_STEP_OBJECT_LOOKUP;
        if (access_multiplexer->set_values)
                mfd_modes |= BABY_STEP_SET_VALUES;
        if (access_multiplexer->irreversible_commit)
                mfd_modes |= BABY_STEP_IRREVERSIBLE_COMMIT;
        if (access_multiplexer->object_syntax_checks)
                mfd_modes |= BABY_STEP_CHECK_OBJECT;

        if (access_multiplexer->pre_request)
                mfd_modes |= BABY_STEP_PRE_REQUEST;
        if (access_multiplexer->post_request)
                mfd_modes |= BABY_STEP_POST_REQUEST;

        if (access_multiplexer->undo_setup)
                mfd_modes |= BABY_STEP_UNDO_SETUP;
        if (access_multiplexer->undo_cleanup)
                mfd_modes |= BABY_STEP_UNDO_CLEANUP;
        if (access_multiplexer->undo_sets)
                mfd_modes |= BABY_STEP_UNDO_SETS;

        if (access_multiplexer->row_creation)
                mfd_modes |= BABY_STEP_ROW_CREATE;
        if (access_multiplexer->consistency_checks)
                mfd_modes |= BABY_STEP_CHECK_CONSISTENCY;
        if (access_multiplexer->commit)
                mfd_modes |= BABY_STEP_COMMIT;
        if (access_multiplexer->undo_commit)
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
                                                strModStatTable_if_ctx.container,
                                                TABLE_CONTAINER_KEY_NETSNMP_INDEX);
        netsnmp_inject_handler(reginfo, handler);

    /*************************************************
     *
     * inject cache helper
     */
        if (NULL != strModStatTable_if_ctx.cache) {
                handler = netsnmp_cache_handler_get(strModStatTable_if_ctx.cache);
                netsnmp_inject_handler(reginfo, handler);
        }

        /*
         * register table
         */
        netsnmp_register_table(reginfo, tbl_info);

}                               /* _strModStatTable_initialize_interface */

/**
 * @internal
 * Shutdown the table strModStatTable
 */
void
_strModStatTable_shutdown_interface(strModStatTable_registration * reg_ptr)
{
        /*
         * shutdown the container
         */
        //_strModStatTable_container_shutdown(&strModStatTable_if_ctx);
}

void
strModStatTable_valid_columns_set(netsnmp_column_info *vc)
{
        strModStatTable_if_ctx.tbl_info.valid_columns = vc;
}                               /* strModStatTable_valid_columns_set */

/**
 * @internal
 * convert the index component stored in the context to an oid
 */
int
strModStatTable_index_to_oid(netsnmp_index * oid_idx, strModStatTable_mib_index * mib_idx)
{
        int err = SNMP_ERR_NOERROR;

        /*
         * temp storage for parsing indexes
         */
        /*
         * strModIdnum(1)/UNSIGNED32/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/h
         */
        netsnmp_variable_list var_strModIdnum;

        /*
         * strModStatIndex(1)/UNSIGNED32/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/h
         */
        netsnmp_variable_list var_strModStatIndex;

        /*
         * set up varbinds
         */
        memset(&var_strModIdnum, 0x00, sizeof(var_strModIdnum));
        var_strModIdnum.type = ASN_UNSIGNED;
        memset(&var_strModStatIndex, 0x00, sizeof(var_strModStatIndex));
        var_strModStatIndex.type = ASN_UNSIGNED;

        /*
         * chain temp index varbinds together
         */
        var_strModIdnum.next_variable = &var_strModStatIndex;
        var_strModStatIndex.next_variable = NULL;

        DEBUGMSGTL(("verbose:strModStatTable:strModStatTable_index_to_oid", "called\n"));

        /* strModIdnum(1)/UNSIGNED32/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/h */
        snmp_set_var_value(&var_strModIdnum, (u_char *) &mib_idx->strModIdnum,
                           sizeof(mib_idx->strModIdnum));

        /* strModStatIndex(1)/UNSIGNED32/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/h */
        snmp_set_var_value(&var_strModStatIndex, (u_char *) &mib_idx->strModStatIndex,
                           sizeof(mib_idx->strModStatIndex));

        err = build_oid_noalloc(oid_idx->oids, oid_idx->len, &oid_idx->len,
                                NULL, 0, &var_strModIdnum);
        if (err)
                snmp_log(LOG_ERR, "error %d converting index to oid\n", err);

        /*
         * parsing may have allocated memory. free it.
         */
        snmp_reset_var_buffers(&var_strModIdnum);

        return err;
}                               /* strModStatTable_index_to_oid */

/**
 * extract strModStatTable indexes from a netsnmp_index
 *
 * @retval SNMP_ERR_NOERROR  : no error
 * @retval SNMP_ERR_GENERR   : error
 */
int
strModStatTable_index_from_oid(netsnmp_index * oid_idx, strModStatTable_mib_index * mib_idx)
{
        int err = SNMP_ERR_NOERROR;

        /*
         * temp storage for parsing indexes
         */
        /*
         * strModIdnum(1)/UNSIGNED32/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/h
         */
        netsnmp_variable_list var_strModIdnum;

        /*
         * strModStatIndex(1)/UNSIGNED32/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/h
         */
        netsnmp_variable_list var_strModStatIndex;

        /*
         * set up varbinds
         */
        memset(&var_strModIdnum, 0x00, sizeof(var_strModIdnum));
        var_strModIdnum.type = ASN_UNSIGNED;
        memset(&var_strModStatIndex, 0x00, sizeof(var_strModStatIndex));
        var_strModStatIndex.type = ASN_UNSIGNED;

        /*
         * chain temp index varbinds together
         */
        var_strModIdnum.next_variable = &var_strModStatIndex;
        var_strModStatIndex.next_variable = NULL;

        DEBUGMSGTL(("verbose:strModStatTable:strModStatTable_index_from_oid", "called\n"));

        /*
         * parse the oid into the individual index components
         */
        err = parse_oid_indexes(oid_idx->oids, oid_idx->len, &var_strModIdnum);
        if (err == SNMP_ERR_NOERROR) {
                /*
                 * copy out values
                 */
                mib_idx->strModIdnum = *((u_long *) var_strModIdnum.val.string);
                mib_idx->strModStatIndex = *((u_long *) var_strModStatIndex.val.string);

        }

        /*
         * parsing may have allocated memory. free it.
         */
        snmp_reset_var_buffers(&var_strModIdnum);

        return err;
}                               /* strModStatTable_index_from_oid */

/* *********************************************************************
 * @internal
 * allocate resources for a strModStatTable_rowreq_ctx
 */
strModStatTable_rowreq_ctx *
strModStatTable_allocate_rowreq_ctx(void *user_init_ctx)
{
        strModStatTable_rowreq_ctx *rowreq_ctx = SNMP_MALLOC_TYPEDEF(strModStatTable_rowreq_ctx);

        DEBUGMSGTL(("internal:strModStatTable:strModStatTable_allocate_rowreq_ctx", "called\n"));

        if (NULL == rowreq_ctx) {
                snmp_log(LOG_ERR, "Couldn't allocate memory for a "
                         "strModStatTable_rowreq_ctx.\n");
        }

        rowreq_ctx->oid_idx.oids = rowreq_ctx->oid_tmp;

        rowreq_ctx->strModStatTable_data_list = NULL;

        /*
         * if we allocated data, call init routine
         */
        if (!(rowreq_ctx->rowreq_flags & MFD_ROW_DATA_FROM_USER)) {
                if (SNMPERR_SUCCESS != strModStatTable_rowreq_ctx_init(rowreq_ctx, user_init_ctx)) {
                        strModStatTable_release_rowreq_ctx(rowreq_ctx);
                        rowreq_ctx = NULL;
                }
        }

        return rowreq_ctx;
}                               /* strModStatTable_allocate_rowreq_ctx */

/*
 * @internal
 * release resources for a strModStatTable_rowreq_ctx
 */
void
strModStatTable_release_rowreq_ctx(strModStatTable_rowreq_ctx * rowreq_ctx)
{
        DEBUGMSGTL(("internal:strModStatTable:strModStatTable_release_rowreq_ctx", "called\n"));

        netsnmp_assert(NULL != rowreq_ctx);

        strModStatTable_rowreq_ctx_cleanup(rowreq_ctx);

        /*
         * free index oid pointer
         */
        if (rowreq_ctx->oid_idx.oids != rowreq_ctx->oid_tmp)
                free(rowreq_ctx->oid_idx.oids);

        SNMP_FREE(rowreq_ctx);
}                               /* strModStatTable_release_rowreq_ctx */

/**
 * @internal
 * wrapper
 */
static int
_mfd_strModStatTable_pre_request(netsnmp_mib_handler *handler,
                                 netsnmp_handler_registration *reginfo,
                                 netsnmp_agent_request_info *agtreq_info,
                                 netsnmp_request_info *requests)
{
        int rc;

        DEBUGMSGTL(("internal:strModStatTable:_mfd_strModStatTable_pre_request", "called\n"));

        if (1 != netsnmp_row_merge_status_first(reginfo, agtreq_info)) {
                DEBUGMSGTL(("internal:strModStatTable", "skipping additional pre_request\n"));
                return SNMP_ERR_NOERROR;
        }

        rc = strModStatTable_pre_request(strModStatTable_if_ctx.user_ctx);
        if (MFD_SUCCESS != rc) {
                /*
                 * nothing we can do about it but log it
                 */
                DEBUGMSGTL(("strModStatTable", "error %d from "
                            "strModStatTable_pre_request\n", rc));
                netsnmp_request_set_error_all(requests, SNMP_VALIDATE_ERR(rc));
        }

        return SNMP_ERR_NOERROR;
}                               /* _mfd_strModStatTable_pre_request */

/**
 * @internal
 * wrapper
 */
static int
_mfd_strModStatTable_post_request(netsnmp_mib_handler *handler,
                                  netsnmp_handler_registration *reginfo,
                                  netsnmp_agent_request_info *agtreq_info,
                                  netsnmp_request_info *requests)
{
        strModStatTable_rowreq_ctx *rowreq_ctx = netsnmp_container_table_row_extract(requests);
        int rc, packet_rc;

        DEBUGMSGTL(("internal:strModStatTable:_mfd_strModStatTable_post_request", "called\n"));

        /*
         * release row context, if deleted
         */
        if (rowreq_ctx && (rowreq_ctx->rowreq_flags & MFD_ROW_DELETED))
                strModStatTable_release_rowreq_ctx(rowreq_ctx);

        /*
         * wait for last call before calling user
         */
        if (1 != netsnmp_row_merge_status_last(reginfo, agtreq_info)) {
                DEBUGMSGTL(("internal:strModStatTable", "waiting for last post_request\n"));
                return SNMP_ERR_NOERROR;
        }

        packet_rc = netsnmp_check_all_requests_error(agtreq_info->asp, 0);
        rc = strModStatTable_post_request(strModStatTable_if_ctx.user_ctx, packet_rc);
        if (MFD_SUCCESS != rc) {
                /*
                 * nothing we can do about it but log it
                 */
                DEBUGMSGTL(("strModStatTable", "error %d from "
                            "strModStatTable_post_request\n", rc));
        }

        return SNMP_ERR_NOERROR;
}                               /* _mfd_strModStatTable_post_request */

/**
 * @internal
 * wrapper
 */
static int
_mfd_strModStatTable_object_lookup(netsnmp_mib_handler *handler,
                                   netsnmp_handler_registration *reginfo,
                                   netsnmp_agent_request_info *agtreq_info,
                                   netsnmp_request_info *requests)
{
        int rc = SNMP_ERR_NOERROR;
        strModStatTable_rowreq_ctx *rowreq_ctx = netsnmp_container_table_row_extract(requests);

        DEBUGMSGTL(("internal:strModStatTable:_mfd_strModStatTable_object_lookup", "called\n"));

        /*
         * get our context from mfd
         * strModStatTable_interface_ctx *if_ctx =
         *             (strModStatTable_interface_ctx *)reginfo->my_reg_void;
         */

        if (NULL == rowreq_ctx) {
                rc = SNMP_ERR_NOCREATION;
        }

        if (MFD_SUCCESS != rc)
                netsnmp_request_set_error_all(requests, rc);
        else
                strModStatTable_row_prep(rowreq_ctx);

        return SNMP_VALIDATE_ERR(rc);
}                               /* _mfd_strModStatTable_object_lookup */

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
_strModStatTable_get_column(strModStatTable_rowreq_ctx * rowreq_ctx,
                            netsnmp_variable_list * var, int column)
{
        int rc = SNMPERR_SUCCESS;

        DEBUGMSGTL(("internal:strModStatTable:_mfd_strModStatTable_get_column",
                    "called for %d\n", column));

        netsnmp_assert(NULL != rowreq_ctx);

        switch (column) {

                /* strModStatQueues(2)/StreamsModuleQueues/ASN_OCTET_STR/char(u_long)//L/A/w/E/r/d/h */
        case COLUMN_STRMODSTATQUEUES:
        {
                u_long tmp = 0xff << ((sizeof(u_long) - 1) * 8);

                var->type = ASN_OCTET_STR;
                rc = strModStatQueues_get(rowreq_ctx, (u_long *) var->val.string);
                /*
                 * check for length of bits string
                 */
                var->val_len = 0;
                while (0 != tmp) {
                        if (*((u_long *) var->val.string) & tmp)
                                ++var->val_len;
                        tmp = tmp >> 8;
                }
        }
                break;

                /* strModStatPCnt(3)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
        case COLUMN_STRMODSTATPCNT:
                var->val_len = sizeof(u_long);
                var->type = ASN_COUNTER;
                rc = strModStatPCnt_get(rowreq_ctx, (u_long *) var->val.string);
                break;

                /* strModStatScnt(4)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
        case COLUMN_STRMODSTATSCNT:
                var->val_len = sizeof(u_long);
                var->type = ASN_COUNTER;
                rc = strModStatScnt_get(rowreq_ctx, (u_long *) var->val.string);
                break;

                /* strModStatOcnt(5)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
        case COLUMN_STRMODSTATOCNT:
                var->val_len = sizeof(u_long);
                var->type = ASN_COUNTER;
                rc = strModStatOcnt_get(rowreq_ctx, (u_long *) var->val.string);
                break;

                /* strModStatCcnt(6)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
        case COLUMN_STRMODSTATCCNT:
                var->val_len = sizeof(u_long);
                var->type = ASN_COUNTER;
                rc = strModStatCcnt_get(rowreq_ctx, (u_long *) var->val.string);
                break;

                /* strModStatAcnt(7)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h */
        case COLUMN_STRMODSTATACNT:
                var->val_len = sizeof(u_long);
                var->type = ASN_COUNTER;
                rc = strModStatAcnt_get(rowreq_ctx, (u_long *) var->val.string);
                break;

                /* strModStatPrivate(8)/OCTETSTR/ASN_OCTET_STR/char(char)//L/A/w/e/r/d/h */
        case COLUMN_STRMODSTATPRIVATE:
                var->type = ASN_OCTET_STR;
                rc = strModStatPrivate_get(rowreq_ctx, (char **) &var->val.string, &var->val_len);
                break;

                /* strModStatFlags(9)/UNSIGNED32/ASN_UNSIGNED/u_long(u_long)//l/A/w/e/r/d/h */
        case COLUMN_STRMODSTATFLAGS:
                var->val_len = sizeof(u_long);
                var->type = ASN_UNSIGNED;
                rc = strModStatFlags_get(rowreq_ctx, (u_long *) var->val.string);
                break;

        default:
                snmp_log(LOG_ERR, "unknown column %d in _strModStatTable_get_column\n", column);
                break;
        }

        return rc;
}                               /* _strModStatTable_get_column */

int
_mfd_strModStatTable_get_values(netsnmp_mib_handler *handler,
                                netsnmp_handler_registration *reginfo,
                                netsnmp_agent_request_info *agtreq_info,
                                netsnmp_request_info *requests)
{
        strModStatTable_rowreq_ctx *rowreq_ctx = netsnmp_container_table_row_extract(requests);
        netsnmp_table_request_info *tri;
        u_char *old_string;
        void (*dataFreeHook) (void *);
        int rc;

        DEBUGMSGTL(("internal:strModStatTable:_mfd_strModStatTable_get_values", "called\n"));

        netsnmp_assert(NULL != rowreq_ctx);

        for (; requests; requests = requests->next) {
                /*
                 * save old pointer, so we can free it if replaced
                 */
                old_string = requests->requestvb->val.string;
                dataFreeHook = requests->requestvb->dataFreeHook;
                if (NULL == requests->requestvb->val.string) {
                        requests->requestvb->val.string = requests->requestvb->buf;
                        requests->requestvb->val_len = sizeof(requests->requestvb->buf);
                } else if (requests->requestvb->buf == requests->requestvb->val.string) {
                        if (requests->requestvb->val_len != sizeof(requests->requestvb->buf))
                                requests->requestvb->val_len = sizeof(requests->requestvb->buf);
                }

                /*
                 * get column data
                 */
                tri = netsnmp_extract_table_info(requests);
                if (NULL == tri)
                        continue;

                rc = _strModStatTable_get_column(rowreq_ctx, requests->requestvb, tri->colnum);
                if (rc) {
                        if (MFD_SKIP == rc) {
                                requests->requestvb->type = SNMP_NOSUCHINSTANCE;
                                rc = SNMP_ERR_NOERROR;
                        }
                } else if (NULL == requests->requestvb->val.string) {
                        snmp_log(LOG_ERR, "NULL varbind data pointer!\n");
                        rc = SNMP_ERR_GENERR;
                }
                if (rc)
                        netsnmp_request_set_error(requests, SNMP_VALIDATE_ERR(rc));

                /*
                 * if the buffer wasn't used previously for the old data (i.e. it
                 * was allcoated memory)  and the get routine replaced the pointer,
                 * we need to free the previous pointer.
                 */
                if (old_string && (old_string != requests->requestvb->buf) &&
                    (requests->requestvb->val.string != old_string)) {
                        if (dataFreeHook)
                                (*dataFreeHook) (old_string);
                        else
                                free(old_string);
                }
        }                       /* for results */

        return SNMP_ERR_NOERROR;
}                               /* _mfd_strModStatTable_get_values */

/***********************************************************************
 *
 * SET processing
 *
 ***********************************************************************/

/*
 * SET PROCESSING NOT APPLICABLE (per MIB or user setting)
 */
/***********************************************************************
 *
 * DATA ACCESS
 *
 ***********************************************************************/
/**
 * @internal
 * wrapper around clean up a loop reference
 */
static int
_strModStatTable_loop_cleanup_context(strModStatTable_interface_ctx * wrap_ctx,
                                      strModStatTable_ref_loop_ctx * ref)
{
        DEBUGMSGTL(("internal:strModStatTable:_strModStatTable_loop_cleanup_context", "called\n"));

        return strModStatTable_loop_cleanup_context(wrap_ctx->user_ctx, ref);
}                               /* _strModStatTable_loop_cleanup_context */

/**
 * @internal
 * wrapper around save position
 */
static int
_strModStatTable_loop_save_position(strModStatTable_interface_ctx * wrap_ctx,
                                    strModStatTable_ref_loop_ctx * ref,
                                    strModStatTable_ref_loop_ctx * ref_copy, int reuse)
{
        DEBUGMSGTL(("internal:strModStatTable:_strModStatTable_loop_save_position", "called\n"));

        return strModStatTable_loop_save_position(wrap_ctx->user_ctx, ref, ref_copy, reuse);
}                               /* _strModStatTable_loop_save_position */

/**
 * @internal
 * wrapper around user get_first to setup the index oid
 */
static int
_strModStatTable_loop_get_first_wrapper(strModStatTable_interface_ctx * wrap_ctx,
                                        strModStatTable_ref_loop_ctx * loop_ctx_ref,
                                        strModStatTable_ref_rowreq_ctx * rowreq_ctx_ref)
{
        int rc;

        DEBUGMSGTL(("internal:strModStatTable:_strModStatTable_loop_get_first_wrapper",
                    "called\n"));

        rc = strModStatTable_loop_get_first(wrap_ctx->user_ctx, loop_ctx_ref, rowreq_ctx_ref);
        /*
         * convert index to OID
         */
        if (SNMPERR_SUCCESS == rc) {
                netsnmp_assert((NULL != rowreq_ctx_ref) &&
                               (rowreq_ctx_ref->rowreq_ctx->oid_idx.oids ==
                                rowreq_ctx_ref->rowreq_ctx->oid_tmp));
                rowreq_ctx_ref->rowreq_ctx->oid_idx.len =
                    sizeof(rowreq_ctx_ref->rowreq_ctx->oid_tmp);
                rc = strModStatTable_index_to_oid(&rowreq_ctx_ref->rowreq_ctx->oid_idx,
                                                  &rowreq_ctx_ref->rowreq_ctx->tbl_idx);
                netsnmp_assert(rowreq_ctx_ref->rowreq_ctx->oid_idx.len !=
                               sizeof(rowreq_ctx_ref->rowreq_ctx->oid_tmp));
        }

        return rc;
}                               /* _strModStatTable_loop_get_first_wrapper */

/**
 * @internal
 * wrapper around user get_next to setup the index oid
 */
static int
_strModStatTable_loop_get_next_wrapper(strModStatTable_interface_ctx * wrap_ctx,
                                       strModStatTable_ref_loop_ctx * loop_ctx_ref,
                                       strModStatTable_ref_rowreq_ctx * rowreq_ctx_ref)
{
        int rc;

        DEBUGMSGTL(("internal:strModStatTable:_strModStatTable_loop_get_next_wrapper", "called\n"));

        rc = strModStatTable_loop_get_next(wrap_ctx->user_ctx, loop_ctx_ref, rowreq_ctx_ref);
        /*
         * convert index to OID
         */
        if (SNMPERR_SUCCESS == rc) {
                netsnmp_assert((NULL != rowreq_ctx_ref) &&
                               (rowreq_ctx_ref->rowreq_ctx->oid_idx.oids ==
                                rowreq_ctx_ref->rowreq_ctx->oid_tmp));
                rowreq_ctx_ref->rowreq_ctx->oid_idx.len =
                    sizeof(rowreq_ctx_ref->rowreq_ctx->oid_tmp);
                rc = strModStatTable_index_to_oid(&rowreq_ctx_ref->rowreq_ctx->oid_idx,
                                                  &rowreq_ctx_ref->rowreq_ctx->tbl_idx);
                netsnmp_assert(rowreq_ctx_ref->rowreq_ctx->oid_idx.len !=
                               sizeof(rowreq_ctx_ref->rowreq_ctx->oid_tmp));
        }

        return rc;
}                               /* _strModStatTable_loop_get_next_wrapper */

/**
 * @internal
 * get data wrapper to allocate context for the user
 */
static int
_strModStatTable_loop_get_data_wrapper(strModStatTable_interface_ctx * wrap_ctx,
                                       strModStatTable_ref_loop_ctx * loop_ctx_ref,
                                       strModStatTable_ref_rowreq_ctx * rowreq_ctx_ref)
{
//    strModStatTable_rowreq_ctx *orig_ctx = rowreq_ctx_ref->rowreq_ctx;

        DEBUGMSGTL(("internal:strModStatTable:_strModStatTable_loop_get_data_wrapper", "called\n"));

        return strModStatTable_loop_get_data(wrap_ctx->user_ctx, loop_ctx_ref, rowreq_ctx_ref);
}                               /* _strModStatTable_loop_get_data_wrapper */

/**
 * @internal
 * initialize the iterator container with functions or wrappers
 */
void
_strModStatTable_container_init(strModStatTable_interface_ctx * if_ctx)
{
        DEBUGMSGTL(("internal:strModStatTable:_strModStatTable_container_init", "called\n"));

        if_ctx->container = netsnmp_container_iterator_get(
                                                       /** registration */
                                                                  if_ctx,
        /** compare */
                                                                  NULL,
        /** get_first */
                                                                  (Netsnmp_Iterator_Loop_Key *)
                                                                  _strModStatTable_loop_get_first_wrapper,
        /** get_next */
                                                                  (Netsnmp_Iterator_Loop_Key *)
                                                                  _strModStatTable_loop_get_next_wrapper,
        /** get_data */
                                                                  (Netsnmp_Iterator_Loop_Data *)
                                                                  _strModStatTable_loop_get_data_wrapper,
        /** save_pos */
                                                                  (Netsnmp_Iterator_Ctx_Dup *)
                                                                  _strModStatTable_loop_save_position,
        /** init_context */
                                                                  (Netsnmp_Iterator_Ctx *) NULL,
        /** cleanup_context */
                                                                  (Netsnmp_Iterator_Ctx *)
                                                                  _strModStatTable_loop_cleanup_context,
        /** free_user_ctx */
                                                                  NULL,
        /** sorted */
                                                                  0);
}                               /* _strModStatTable_container_init */

strModStatTable_rowreq_ctx *
strModStatTable_row_find_by_mib_index(strModStatTable_mib_index * mib_idx)
{
        strModStatTable_rowreq_ctx *rowreq_ctx;
        oid oid_tmp[MAX_OID_LEN];
        netsnmp_index oid_idx;
        int rc;

        /*
         * set up storage for OID
         */
        oid_idx.oids = oid_tmp;
        oid_idx.len = sizeof(oid_tmp) / sizeof(oid);

        /*
         * convert
         */
        rc = strModStatTable_index_to_oid(&oid_idx, mib_idx);
        if (MFD_SUCCESS != rc)
                return NULL;

        rowreq_ctx = CONTAINER_FIND(strModStatTable_if_ctx.container, &oid_idx);

        return rowreq_ctx;
}