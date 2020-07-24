/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:59:18 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 06:54:41 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	int_to_mem(t_vm *vm, int val, int ptr)
{
	int			i;

	i = 0;
	ptr = (ptr >= 0 ? ptr : MEM_SIZE + ptr);
	while (i < 4)
	{
		vm->ram[ptr % MEM_SIZE] = val;
		ptr = (ptr > 0 ? ptr - 1 : MEM_SIZE + (ptr - 1));
		val = val >> 8;
		i += 1;
	}
}

int		mem_to_val(t_vm *vm, int *ptr, int size)
{
	int			start;
	int			dst;
	int			val;

	start = *ptr;
	dst = start + size;
	val = 0;
	while (start < dst)
	{
		val |= vm->ram[start % MEM_SIZE];
		if (start < dst - 1)
			val <<= 8;
		start++;
	}
	*ptr = start;
	return (val);
}

int		check_arg_value(t_vm *vm, t_process *prcs)
{
	int		i;
	int		nb_arg;

	nb_arg = g_ops[prcs->op_code].nb_arg;
	i = 0;
	while (i < nb_arg)
	{
		if (vm->args[i][1] == T_REG &&
			(vm->args[i][0] <= 0 || vm->args[i][0] >= 17))
		{
			pc_movement(vm, prcs);
			return (false);
		}
		i++;
	}
	return (true);
}

int		get_arg_value(t_vm *vm, t_process *prcs)
{
	int		i;
	int		ptr;
	int		nb_arg;

	nb_arg = g_ops[prcs->op_code].nb_arg;
	ptr = (prcs->registers[PC] + 1 + g_ops[prcs->op_code].encoding) % MEM_SIZE;
	i = 0;
	while (i < nb_arg)
	{
		if (vm->args[i][1] == T_REG)
			vm->args[i][0] = mem_to_val(vm, &ptr, T_REG);
		else if (vm->args[i][1] == T_IND)
			vm->args[i][0] = mem_to_val(vm, &ptr, T_IND);
		else if (vm->args[i][1] == T_DIR)
			vm->args[i][0] = mem_to_val(vm, &ptr, g_ops[prcs->op_code].dirsize);
		i++;
	}
	return (check_arg_value(vm, prcs));
}

int		get_arg_type(uint8_t encoded, t_process *prcs, t_vm *vm, int i)
{
	uint8_t	mask;

	mask = encoded & BIT_IND;
	if (mask == BIT_REG && (g_ops[prcs->op_code].arg_type[i] & T_REG) != 0)
		vm->args[i][1] = T_REG;
	else if (mask == BIT_IND && (g_ops[prcs->op_code].arg_type[i] & T_IND) != 0)
		vm->args[i][1] = T_IND;
	else if (mask == BIT_DIR && (g_ops[prcs->op_code].arg_type[i] & T_DIR) != 0)
		vm->args[i][1] = T_DIR;
	else
		return (false);
	return (true);
}
