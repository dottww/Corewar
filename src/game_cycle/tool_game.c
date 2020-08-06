/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 19:37:39 by weilin            #+#    #+#             */
/*   Updated: 2020/08/06 13:41:52 by weilin           ###   ########.fr       */
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

int		is_not_waiting(t_process *current)
{
	return (current->op_code_to_exec == -1 && current->op_code_to_exec == -2);
}

void	get_op_to_exec(t_env *e, t_process *current)
{
	if (current->op_code_to_exec == -2 && current->op_cooldown)
	{
		current->op_cooldown--;
/*de*/ (0)?	ft_printf("wrong args CD == %d\n", current->op_cooldown):0;
		return ;
	}
	current->op_code_to_exec = e->arena[current->registers[PC] % MEM_SIZE];
/*de*/ (0)?	ft_printf("op_at_arena[%d]:%d\n", current->registers[PC],current->op_code_to_exec):0;
	if (current->op_code_to_exec > 16 || current->op_code_to_exec < 1)
	{
		current->op_code_to_exec = -1;
	/*de*/ (0)?	ft_printf("turn op to -1 %d\n", current->op_code_to_exec):0;
	/*de*/ (0)?	ft_printf("move PC [%d]", current->registers[PC]):0;
		move_pc(current, 1);
	/*de*/ (0)?	ft_printf(" to [%d]\n", current->registers[PC]):0;
		return ;
	}
	current->op_cooldown = g_ops[current->op_code_to_exec].exec_cycle - 1;
/*de*/ (0)?	ft_printf("op_cooldown = %d\n", current->op_cooldown):0;
}
