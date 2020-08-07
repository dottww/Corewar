/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:01:27 by weilin            #+#    #+#             */
/*   Updated: 2020/08/07 15:42:05 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	op_verbose_4(t_process *prcs, int args)
{
	ft_printf("P%5d | %s ", prcs->process_id + 1
	, g_ops[prcs->op_code_to_exec].op_name);
	ft_printf("%d\n", args);
}

void		op_live(t_env *e, t_process *prcs)
{
	int		player_id;

	player_id = e->args[0][0] * (-1);
	V_DEBUG ? op_verbose_4(prcs, e->args[0][0]) : 0;
	prcs->last_cycle_called_live = e->game.cycle_cpt;
	e->game.live_cpt++;
	prcs->executed_live_in_this_check = 1;
	if (player_id <= MAX_PLAYERS
		&& player_id <= e->player_count && 0 < player_id)
	{
		e->player[player_id - 1].is_alive = 1;
		e->game.last_claimed_live = player_id;
		V_DEBUG ? verbose_1(e, player_id) : 0;
	}
	pc_movement(e, prcs);
}
