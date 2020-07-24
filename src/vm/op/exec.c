/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:39:46 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 07:59:49 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_ops(t_vm *vm, t_process *prcs)
{
	if (init_args(vm, prcs))
		g_ops[prcs->op_code].op_ptr(vm, prcs);
	ft_bzero(vm->args, sizeof(vm->args));
}

void	load_to_process(t_vm *vm, t_process *prcs, size_t cycle)
{
	int	exec_cycle;

	prcs->op_code = vm->ram[prcs->registers[PC] % MEM_SIZE] - 1;
	exec_cycle = g_ops[prcs->op_code].exec_cycle;
	arr_assign(vm, prcs, cycle, exec_cycle);
}

void	read_ram(t_vm *vm, t_process *prcs, size_t cycle)
{
	if (pc_at_illegal_ram(vm, prcs))
	{
		prcs->op_code = NONE_OP;
		move_pc(prcs, 1);
		arr_assign(vm, prcs, cycle, 1);
	}
	else
	{
		prcs->loaded = true;
		load_to_process(vm, prcs, cycle);
	}
}

void	exec_process(t_vm *vm, t_process *arr[1024], size_t cycle)
{
	while (arr[cycle % 1024] != NULL)
	{
		if (arr[cycle % 1024]->loaded)
		{
			if(arr[cycle % 1024]->op_code != NONE_OP)
				exec_ops(vm, arr[cycle % 1024]);
			arr[cycle % 1024]->loaded = false;
			arr_assign(vm, arr[cycle % 1024], cycle, 1);
		}
		else
			read_ram(vm, arr[cycle % 1024], cycle);
	}
}

void	exec_loop(t_vm *vm, t_process *arr[1024])
{
	while (vm->nb_player > 0)
	{
		if (arr[vm->cycle % 1024] != NULL)
			exec_process(vm, arr, vm->cycle);
		if (vm->die_count[0] == vm->die_count[1] || vm->cycle_to_die <= 0)
			check_live(vm, arr);
		if (vm->nb_player == 0)
			break ;
		(vm->options.verbose & 2) ? verbose_2_cycle(vm) : 0;
		vm->cycle += 1;
		vm->die_count[0] += 1;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", vm->last_alive,
	vm->players[vm->last_alive - 1].header.prog_name);
}
