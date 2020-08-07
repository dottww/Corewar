/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:24 by weilin            #+#    #+#             */
/*   Updated: 2020/08/07 01:54:44 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void		op_verbose_4(t_process *prcs, short val, int pc)
{
	ft_printf("P%5d | %s ", prcs->process_id + 1
	, g_ops[prcs->op_code_to_exec].op_name);
	ft_printf("%hd (%d)\n", val, pc);
}

static void		get_op_to_exec_for_forked_prcs(t_env *e, t_process *current)
{
	current->op_code_to_exec = e->arena[current->registers[PC] % MEM_SIZE];
	if (current->op_code_to_exec > 16 || current->op_code_to_exec < 1)
	{
		current->op_code_to_exec = -1;
		// move_pc(current, 1);
		return ;
	}
	else
		current->op_cooldown = g_ops[current->op_code_to_exec].exec_cycle;
}

static void		do_fork_op(t_env *e, t_process *curr_prcs, bool flag)
{
	int			move;
	short		val;
	t_process	*new_prcs;

	(0)?ft_printf("e->args[0][0]=%d\n", e->args[0][0]):0;
	val = e->args[0][0];
	(0)?ft_printf("val=%hd\n", val):0;
	if (flag)
		move = ((val % IDX_MOD)) % MEM_SIZE;
	else
		move = (val) % MEM_SIZE;

	(0)?ft_printf("move=%d\n", move):0;
	(0)?ft_printf("oldpc=[%d]\n",  curr_prcs->registers[PC]):0;
	new_prcs = add_new_process(*curr_prcs, &(e->info));
	(0)?ft_printf("newpc move=[%d]\n",  new_prcs->registers[PC]):0;
	// new_prcs->registers[PC] = move;
	move_pc(new_prcs, move);
	V_DEBUG ? op_verbose_4(curr_prcs, e->args[0][0], curr_prcs->registers[PC] + (val % IDX_MOD)) : 0;
	(0)?ft_printf("newpc after move[%d]= %d\n", move, new_prcs->registers[PC]):0;
	get_op_to_exec_for_forked_prcs(e, new_prcs);
	pc_movement(e, curr_prcs);
}

void			op_fork(t_env *e, t_process *process)
{
	do_fork_op(e, process, 1);
}

void			op_lfork(t_env *e, t_process *process)
{
	do_fork_op(e, process, 0);
}
