/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_pc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:04:29 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 08:23:13 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	skip_arg(t_vm *vm, int skip, const int arg, const uint8_t op_code)
{
	if (vm->args[arg][1] == T_REG)
		skip += 1;
	else if (vm->args[arg][1] == T_IND)
		skip += 2;
	else if (vm->args[arg][1] == T_DIR)
		skip += g_ops[op_code].dirsize;
	return (skip);
}

void		move_pc(t_process *prcs, int move)
{
	int	new_pc;

	new_pc = prcs->registers[PC] + move;
	if (new_pc < 0)
		new_pc = MEM_SIZE + (move % MEM_SIZE);
	else
		new_pc = new_pc % MEM_SIZE;
	prcs->registers[PC] = new_pc;
}

void		pc_movement(t_vm *vm, t_process *prcs)
{
	int		i;
	int		nb_arg;
	int		skip_byte;

	skip_byte = 0;
	if (g_ops[prcs->op_code].encoding)
		skip_byte = 1;
	nb_arg = g_ops[prcs->op_code].nb_arg;
	i = 0;
	while (i < nb_arg)
		skip_byte = skip_arg(vm, skip_byte, i++, prcs->op_code);
	(vm->options.verbose & 16) ? verbose_16(vm, prcs, skip_byte) : 0;
	move_pc(prcs, skip_byte + 1);
}

bool		pc_at_illegal_ram(t_vm *vm, t_process *prcs)
{
	return (vm->ram[prcs->registers[PC] % MEM_SIZE] == 0 ||
		vm->ram[prcs->registers[PC] % MEM_SIZE] > 16);
}
