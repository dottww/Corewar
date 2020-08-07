/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 07:48:58 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/07 15:54:34 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		valid_op_cooldown_finished(t_process *current)
{
	if (current->op_code_to_exec > 0 && current->op_code_to_exec <= 16)
	{
		if (current->op_cooldown > 0)
			current->op_cooldown--;
		return (current->op_cooldown == 0);
	}
	else
		return (0);
}

void	get_op_to_exec(t_env *e, t_process *current)
{
	if (current->op_code_to_exec == -2 && current->op_cooldown)
	{
		current->op_cooldown--;
		return ;
	}
	current->op_code_to_exec = e->arena[current->registers[PC] % MEM_SIZE];
	if (current->op_code_to_exec > 16 || current->op_code_to_exec < 1)
	{
		current->op_code_to_exec = -1;
		move_pc(current, 1);
		return ;
	}
	current->op_cooldown = g_ops[current->op_code_to_exec].exec_cycle - 1;
}

int		is_not_waiting(t_process *current)
{
	return (current->op_code_to_exec == -1 || current->op_code_to_exec == -2);
}

void	claim_winner(t_game *game, t_player *player)
{
	ft_printf("Contestant %d, ", game->last_claimed_live);
	ft_printf("\"%s\", has won !\n"
				, player[game->last_claimed_live - 1].name);
	return ;
}

void	game_loop(t_env *e)
{
	t_process *current;

	init_game(e);
	while (!(e->info.process_nb <= 0))
	{
		e->game.cycle_cpt++;
		V_DEBUG ? verbose_2_cycle(e->game.cycle_cpt) : 0;
		current = NULL;
		while (e->info.head && (current = scroll_process(current, &e->info)))
		{
			if (is_not_waiting(current))
				get_op_to_exec(e, current);
			else if (valid_op_cooldown_finished(current))
				exec_ops(e, current);
		}
		e->game.ctd_cpt++;
		manage_cycle_to_die(e);
		if (e->dump != -1 && !(e->info.process_nb <= 0)
			&& e->dump == e->game.cycle_cpt)
		{
			hexdump(e->arena, 4);
			return ;
		}
	}
	claim_winner(&e->game, e->player);
}
