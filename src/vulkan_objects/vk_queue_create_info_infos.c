#include "vk_queue_create_info_infos.h"

#include <stdlib.h>

vk_queue_create_info_infos vk_queue_create_info_infos_create(const vk_queue_family_indices *q_fly_idx)
{
    vk_queue_create_info_infos queue_create_info_infos = {
        .info_infos = (info_info *)malloc(3 * sizeof(info_info)),
        .info_infos_count = 0};

    if (q_fly_idx->gfx == q_fly_idx->cmpt)
    {
        info_info i_i = {.q_fly_idx = q_fly_idx->gfx,
                         .q_count = 2 < q_fly_idx->gfx_max_q_count ? 2 : q_fly_idx->gfx_max_q_count};

        i_i.priorities = (float *)malloc(i_i.q_count * sizeof(float));

        for (uint32_t q_count_idx = 0; q_count_idx < i_i.q_count; ++q_count_idx)
        {
            i_i.priorities[q_count_idx] = 1.f;
        }

        queue_create_info_infos.info_infos[queue_create_info_infos.info_infos_count] = i_i;
        ++queue_create_info_infos.info_infos_count;
    }
    else
    {
        info_info i_i = {.q_fly_idx = q_fly_idx->gfx,
                         .q_count = 1};

        i_i.priorities = (float *)malloc(i_i.q_count * sizeof(float));

        for (uint32_t q_count_idx = 0; q_count_idx < i_i.q_count; ++q_count_idx)
        {
            i_i.priorities[q_count_idx] = 1.f;
        }

        queue_create_info_infos.info_infos[queue_create_info_infos.info_infos_count] = i_i;
        ++queue_create_info_infos.info_infos_count;

        info_info i_j = {.q_fly_idx = q_fly_idx->cmpt,
                         .q_count = 1};

        i_j.priorities = (float *)malloc(i_j.q_count * sizeof(float));

        for (uint32_t q_count_idx = 0; q_count_idx < i_j.q_count; ++q_count_idx)
        {
            i_j.priorities[q_count_idx] = 1.f;
        }

        queue_create_info_infos.info_infos[queue_create_info_infos.info_infos_count] = i_j;
        ++queue_create_info_infos.info_infos_count;
    }

    if (q_fly_idx->xfer == q_fly_idx->gfx)
    {
        for (uint32_t info_info_idx = 0; info_info_idx < queue_create_info_infos.info_infos_count; ++info_info_idx)
        {
            if (queue_create_info_infos.info_infos[info_info_idx].q_fly_idx == q_fly_idx->gfx)
            {
                queue_create_info_infos.info_infos[info_info_idx].q_count = queue_create_info_infos.info_infos[info_info_idx].q_count + 1 < q_fly_idx->gfx_max_q_count ? queue_create_info_infos.info_infos[info_info_idx].q_count + 1 : q_fly_idx->gfx_max_q_count;
            }
        }
    }
    else if (q_fly_idx->xfer == q_fly_idx->cmpt)
    {
        for (uint32_t info_info_idx = 0; info_info_idx < queue_create_info_infos.info_infos_count; ++info_info_idx)
        {
            if (queue_create_info_infos.info_infos[info_info_idx].q_fly_idx == q_fly_idx->cmpt)
            {
                queue_create_info_infos.info_infos[info_info_idx].q_count = queue_create_info_infos.info_infos[info_info_idx].q_count + 1 < q_fly_idx->cmpt_max_q_count ? queue_create_info_infos.info_infos[info_info_idx].q_count + 1 : q_fly_idx->cmpt_max_q_count;
            }
        }
    }
    else
    {
        info_info i_i = {.q_fly_idx = q_fly_idx->xfer,
                         .q_count = 1};

        i_i.priorities = (float *)malloc(i_i.q_count * sizeof(float));

        for (uint32_t q_count_idx = 0; q_count_idx < i_i.q_count; ++q_count_idx)
        {
            i_i.priorities[q_count_idx] = 1.f;
        }

        queue_create_info_infos.info_infos[queue_create_info_infos.info_infos_count] = i_i;
        ++queue_create_info_infos.info_infos_count;
    }

    return queue_create_info_infos;
}

void vk_queue_create_info_infos_destroy(vk_queue_create_info_infos q_create_info_infos)
{
    if (q_create_info_infos.info_infos != NULL)
    {
        for (uint32_t info_count_idx = 0; info_count_idx < q_create_info_infos.info_infos_count; ++info_count_idx)
        {
            if (q_create_info_infos.info_infos[info_count_idx].priorities != NULL)
            {
                free(q_create_info_infos.info_infos[info_count_idx].priorities);
            }
        }
    }

    free(q_create_info_infos.info_infos);
}