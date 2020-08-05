/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:24 by weilin            #+#    #+#             */
/*   Updated: 2020/08/02 22:21:49 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void		op_verbose_4(t_process *prcs, short val, size_t pc)
{
	ft_printf("P%5d | %s ", prcs->process_id + 1
	, g_ops[prcs->op_code_to_exec].op_name);
	ft_printf("%hd (%lu)\n", val, pc);
}

static void		get_op_to_exec_for_forked_prcs(t_env *e, t_process *current)
{
	current->op_code_to_exec = e->arena[current->registers[PC] % MEM_SIZE];
	if (current->op_code_to_exec > 16 || current->op_code_to_exec < 1)
	{
		current->op_code_to_exec = -1;
		return ;
	}
	current->op_cooldown = g_ops[current->op_code_to_exec].exec_cycle;
}

static void		do_fork_op(t_env *e, t_process *curr_prcs, bool flag)
{
	int			pc;
	int			val;
	t_process	*new_prcs;

	val = (short)e->args[0][0];
	val = flag ? (val % IDX_MOD) : val;
	pc = (curr_prcs->registers[PC] + val) % MEM_SIZE;
	new_prcs = add_new_process(*curr_prcs, &(e->info));
	move_pc(new_prcs, val);
	V_DEBUG ? op_verbose_4(curr_prcs, e->args[0][0], pc) : 0;
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
