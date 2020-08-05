/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ctd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 14:59:29 by weilin            #+#    #+#             */
/*   Updated: 2020/08/02 22:48:52 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	reset_alive_status(t_env *e)
{
	int			i;
	t_process	*current;

	i = 0;
	while (i < e->player_count)
	{
		e->player[i].is_alive = (e->player[i].is_alive == -1) ? -1 : 0;
		i++;
	}
	current = NULL;
	while (e->info.head && (current = scroll_process(current, &e->info)))
	{
		if (current->last_cycle_called_live
			<= (e->game.cycle_cpt - e->game.max_ctd))
		{
			current->executed_live_in_this_check = -1;
		}
	}
}

void	manage_cycle_to_die(t_env *e)
{
	if (e->game.ctd_cpt >= e->game.ctd_tmp_criteria || e->game.max_ctd <= 0)
	{
		reset_alive_status(e);
		delete_dead_process(e);
		if (e->game.live_cpt >= NBR_LIVE)
		{
			e->game.max_ctd -= CYCLE_DELTA;
			V_DEBUG ? verbose_2_delta(e->game.max_ctd) : 0;
			e->game.ctd_maxcheck_cpt = 0;
		}
		else
			e->game.ctd_maxcheck_cpt++;
		if (e->game.ctd_maxcheck_cpt >= MAX_CHECKS)
		{
			e->game.ctd_maxcheck_cpt = 0;
			e->game.max_ctd -= CYCLE_DELTA;
			V_DEBUG ? verbose_2_delta(e->game.max_ctd) : 0;
		}
		e->game.live_cpt = 0;
		e->game.ctd_cpt = 0;
		e->game.ctd_tmp_criteria = e->game.max_ctd;
	}
}
