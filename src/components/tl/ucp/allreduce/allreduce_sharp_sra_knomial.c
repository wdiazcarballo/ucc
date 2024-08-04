#include "allreduce_sharp_sra_knomial.h"
#include "tl_sharp.h"
#include "components/mc/ucc_mc.h"

// SHARP resources
static sharp_coll_context_t *sharp_ctx = NULL;
static sharp_coll_comm_t *sharp_comm = NULL;

ucc_status_t ucc_tl_sharp_allreduce_sra_knomial_init(ucc_base_coll_args_t *coll_args,
                                                     ucc_base_team_t *team,
                                                     ucc_coll_task_t **task_h) {
    ucc_tl_sharp_team_t *tl_team = ucc_derived_of(team, ucc_tl_sharp_team_t);
    ucc_tl_sharp_task_t *task;
    ucc_status_t status;

    // Initialize SHARP context and communicator if not already done
    if (sharp_ctx == NULL) {
        sharp_coll_init();
        sharp_ctx = sharp_coll_context_create(...);
        sharp_comm = sharp_coll_comm_create(sharp_ctx, ...);
    }

    // Initialize task
    task = ucc_tl_sharp_init_task(coll_args, team);
    *task_h = &task->super;

    // Additional initialization steps if needed
    status = UCC_OK;
    return status;
}

ucc_status_t ucc_tl_sharp_allreduce_sra_knomial_start(ucc_coll_task_t *coll_task) {
    ucc_tl_sharp_task_t *task = ucc_derived_of(coll_task, ucc_tl_sharp_task_t);
    ucc_coll_args_t *args = &TASK_ARGS(task);
    sharp_coll_reduce_spec_t reduce_spec = {0};

    reduce_spec.sbuf = args->src.info.buffer;
    reduce_spec.rbuf = args->dst.info.buffer;
    reduce_spec.count = args->dst.info.count;
    reduce_spec.dtype = SHARP_DTYPE_INT32; // Example: Update based on actual datatype
    reduce_spec.op = SHARP_OP_SUM; // Example: Update based on actual operation

    // Offload reduce-scatter to SHARP
    sharp_coll_do_reduce(sharp_comm, &reduce_spec);

    // Mark task as in-progress
    task->super.status = UCC_INPROGRESS;

    return UCC_OK;
}

ucc_status_t ucc_tl_sharp_allreduce_sra_knomial_progress(ucc_coll_task_t *coll_task) {
    ucc_tl_sharp_task_t *task = ucc_derived_of(coll_task, ucc_tl_sharp_task_t);
    ucc_coll_args_t *args = &TASK_ARGS(task);
    sharp_coll_allgather_spec_t allgather_spec = {0};

    allgather_spec.sbuf = args->dst.info.buffer;
    allgather_spec.rbuf = args->dst.info.buffer;
    allgather_spec.count = args->dst.info.count;
    allgather_spec.dtype = SHARP_DTYPE_INT32; // Example: Update based on actual datatype

    // Offload allgather to SHARP
    sharp_coll_do_allgather(sharp_comm, &allgather_spec);

    // Mark task as complete
    task->super.status = UCC_OK;

    return UCC_OK;
}

ucc_status_t ucc_tl_sharp_allreduce_sra_knomial_finalize(ucc_coll_task_t *coll_task) {
    // Finalize SHARP resources if necessary
    if (sharp_comm) {
        sharp_coll_comm_destroy(sharp_comm);
        sharp_comm = NULL;
    }
    if (sharp_ctx) {
        sharp_coll_context_destroy(sharp_ctx);
        sharp_ctx = NULL;
    }

    return UCC_OK;
}
