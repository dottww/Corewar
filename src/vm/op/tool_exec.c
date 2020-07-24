/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:31:58 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 08:08:45 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

uint8_t	encoded_typedef(uint8_t encoded)
{
	if (encoded == BIT_IND)
		return (T_IND);
	else if (encoded == BIT_DIR)
		return (T_DIR);
	else if (encoded == BIT_REG)
		return (T_REG);
	else
		return (false);
}

int		skip_wrong_encoded(t_vm *vm, t_process *prcs, int nb_arg)
{
	int		i;
	int		skip;
	uint8_t	encoded;
	uint8_t	arg_type;

	encoded = vm->ram[(prcs->registers[PC] + 1) % MEM_SIZE];
	i = 0;
	skip = 0;
	while (i < nb_arg)
	{
		arg_type = encoded_typedef(encoded & BIT_IND);
		if (arg_type == T_DIR)
			skip += g_ops[prcs->op_code].dirsize;
		else if (arg_type != 0)
			skip += arg_type;
		encoded <<= 2;
		i += 1;
	}
	(vm->options.verbose & 16) ? verbose_16(vm, prcs, skip + 1) : 0;
	move_pc(prcs, skip + 2);
	return (false);
}

int		check_arg_type(t_vm *vm, t_process *prcs)
{
	int		i;
	int		nb_arg;

	nb_arg = g_ops[prcs->op_code].nb_arg;
	i = 0;
	while (i < nb_arg)
	{
		if (!(vm->args[i][1] & g_ops[prcs->op_code].arg_type[i]))
			return (skip_wrong_encoded(vm, prcs, nb_arg));
		i++;
	}
	return (true);
}

int		arg_encoding(t_vm *vm, t_process *prcs)
{
	int		i;
	int		nb_arg;
	uint8_t	encoded;

	encoded = vm->ram[(prcs->registers[PC] + 1) % MEM_SIZE];
	nb_arg = g_ops[prcs->op_code].nb_arg;
	i = 0;
	while (i < nb_arg)
	{
		if (!get_arg_type(encoded, prcs, vm, i++))
			return (false);
		encoded = encoded << 2;
	}
	return (check_arg_type(vm, prcs));
}

int		init_args(t_vm *vm, t_process *prcs)
{
	if (g_ops[prcs->op_code].encoding)
	{
		if (!arg_encoding(vm, prcs))
			return (false);
	}
	else
		vm->args[0][1] = T_DIR;
	return (get_arg_value(vm, prcs));
}
