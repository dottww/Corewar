/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 19:37:39 by weilin            #+#    #+#             */
/*   Updated: 2020/08/07 14:03:17 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	init_game(t_env *e)
{
	int i;

	i = -1;
	while (++i < e->player_count)
		e->player[i].is_alive = 0;
	e->game.max_ctd = CYCLE_TO_DIE;
	e->game.ctd_tmp_criteria = e->game.max_ctd;
	e->game.ctd_cpt = 0;
	e->game.ctd_maxcheck_cpt = 0;
	e->game.live_cpt = 0;
	e->game.cycle_cpt = 0;
	e->forks.qfork = create_queue();
	init_processes(e);
}
