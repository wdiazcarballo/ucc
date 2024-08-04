ucc_base_coll_alg_info_t ucc_tl_ucp_allreduce_algs[UCC_TL_UCP_ALLREDUCE_ALG_LAST + 1] = {
    [UCC_TL_UCP_ALLREDUCE_ALG_KNOMIAL] =
        {.id   = UCC_TL_UCP_ALLREDUCE_ALG_KNOMIAL,
         .name = "knomial",
         .desc = "recursive knomial with arbitrary radix (optimized for latency)"},
    [UCC_TL_UCP_ALLREDUCE_ALG_SRA_KNOMIAL] =
        {.id   = UCC_TL_UCP_ALLREDUCE_ALG_SRA_KNOMIAL,
         .name = "sra_knomial",
         .desc = "recursive knomial scatter-reduce followed by knomial "
                 "allgather (optimized for BW)"},
    [UCC_TL_UCP_ALLREDUCE_ALG_DBT] =
        {.id   = UCC_TL_UCP_ALLREDUCE_ALG_DBT,
         .name = "dbt",
         .desc = "alreduce over double binary tree where a leaf in one tree "
                 "will be intermediate in other (optimized for BW)"},
    [UCC_TL_UCP_ALLREDUCE_ALG_SLIDING_WINDOW] =
        {.id   = UCC_TL_UCP_ALLREDUCE_ALG_SLIDING_WINDOW,
         .name = "sliding_window",
         .desc = "sliding window allreduce (optimized for running on DPU)"},
    [UCC_TL_UCP_ALLREDUCE_ALG_SHARP_SRA_KNOMIAL] =
        {.id   = UCC_TL_UCP_ALLREDUCE_ALG_SHARP_SRA_KNOMIAL,
         .name = "sharp_sra_knomial",
         .desc = "scatter-reduce-allgather knomial using SHARP (optimized for bandwidth)"},
    [UCC_TL_UCP_ALLREDUCE_ALG_LAST] = {.id = 0, .name = NULL, .desc = NULL}
};

ucc_status_t ucc_tl_ucp_allreduce_init(ucc_tl_ucp_task_t *task) {
    ucc_status_t status;
    ALLREDUCE_TASK_CHECK(TASK_ARGS(task), TASK_TEAM(task));
    status = ucc_tl_ucp_allreduce_knomial_init_common(task);
out:
    return status;
}

ucc_status_t ucc_tl_ucp_allreduce_sharp_sra_knomial_init(ucc_base_coll_args_t *coll_args,
                                                         ucc_base_team_t *team,
                                                         ucc_coll_task_t **task_h) {
    return ucc_tl_sharp_allreduce_sra_knomial_init(coll_args, team, task_h);
}
