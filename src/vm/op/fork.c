/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:24 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 08:23:13 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		op_verbose_4(t_process *prcs, short val, size_t pc)
{
	ft_printf("P%5d | %s ", prcs->pid, g_ops[prcs->op_code].op_name);
	ft_printf("%hd (%lu)\n", val, pc);
}

static void		legal_op(t_vm *vm, t_process *new_prcs)
{
	new_prcs->op_code = vm->ram[new_prcs->registers[PC]] - 1;
	arr_add(vm, new_prcs, (vm->cycle +
	g_ops[new_prcs->op_code].exec_cycle) % 1024);
}

static void		illegal_op(t_vm *vm, t_process *new_prcs)
{
	new_prcs->op_code = NONE_OP;
	arr_add(vm, new_prcs, (vm->cycle + 1) % 1024);
	move_pc(new_prcs, 1);
}

void			op_fork(t_vm *vm, t_process *prcs)
{
	int			pc;
	int			pid;
	short		val;
	t_process	*new_prcs;

	vm->last_prcs += 1;
	val = vm->args[0][0];
	pid = vm->last_prcs + 1;
	pc = (prcs->registers[PC] + (val % IDX_MOD)) % MEM_SIZE;
	if (!(new_prcs = prcs_cpy(prcs, pc, pid)))
		exit(0); //pending free malloc first
	(vm->options.verbose & 4) ? op_verbose_4(prcs, val, pc) : 0;
	if (pc_at_illegal_ram(vm, new_prcs))
		illegal_op(vm, new_prcs);
	else
		legal_op(vm, new_prcs);
	new_prcs->last_live = prcs->last_live;
	prcs_list_add(vm, new_prcs);
	pc_movement(vm, prcs);
}

void			op_lfork(t_vm *vm, t_process *prcs)
{
	int			pc;
	int			pid;
	short		val;
	t_process	*new_prcs;

	vm->last_prcs += 1;
	val = vm->args[0][0];
	pid = vm->last_prcs + 1;
	pc = (prcs->registers[PC] + val) % MEM_SIZE;
	if (!(new_prcs = prcs_cpy(prcs, pc, pid)))
		exit(0); //pending free malloc first
	(vm->options.verbose & 4) ? op_verbose_4(prcs, val, pc) : 0;
	if (pc_at_illegal_ram(vm, new_prcs))
		illegal_op(vm, new_prcs);
	else
		legal_op(vm, new_prcs);
	new_prcs->last_live = prcs->last_live;
	prcs_list_add(vm, new_prcs);
	pc_movement(vm, prcs);
}
