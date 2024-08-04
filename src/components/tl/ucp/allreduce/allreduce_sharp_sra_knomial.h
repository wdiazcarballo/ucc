#ifndef ALLREDUCE_SHARP_SRA_KNOMIAL_H_
#define ALLREDUCE_SHARP_SRA_KNOMIAL_H_

#include "allreduce.h"
#include "sharp/api/sharp.h"

ucc_status_t ucc_tl_sharp_allreduce_sra_knomial_init(ucc_base_coll_args_t *coll_args,
                                                     ucc_base_team_t *team,
                                                     ucc_coll_task_t **task_h);

ucc_status_t ucc_tl_sharp_allreduce_sra_knomial_start(ucc_coll_task_t *coll_task);

ucc_status_t ucc_tl_sharp_allreduce_sra_knomial_progress(ucc_coll_task_t *coll_task);

ucc_status_t ucc_tl_sharp_allreduce_sra_knomial_finalize(ucc_coll_task_t *coll_task);

#endif // ALLREDUCE_SHARP_SRA_KNOMIAL_H_
