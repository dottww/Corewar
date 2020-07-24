/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:38 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 06:19:55 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	op_verbose_4(t_process *prcs, int args[3][2])
{
	int		i;

	ft_printf("P%5d | %s ", prcs->pid, g_ops[prcs->op_code].op_name);
	i = 0;
	while (i < g_ops[prcs->op_code].nb_arg)
	{
		if (args[i][1] == T_REG)
			ft_printf("r");
		if (args[i][1] == T_IND)
			ft_printf("%d", prcs->registers[args[1][0]]);
		else
			ft_printf("%d", args[i][0]);
		if (i < g_ops[prcs->op_code].nb_arg - 1)
			ft_printf(" ");
		i += 1;
	}
	ft_printf("\n");
}

short		mem_to_short(unsigned char tab[2])
{
	short	result;
	int		index;

	result = 0;
	index = 0;
	while (index < 2)
	{
		result |= tab[index];
		if (index < 1)
			result <<= 8;
		index++;
	}
	return (result);
}

void		op_lld(t_vm *vm, t_process *prcs)
{
	int		arg_1;
	int		arg_2;

	arg_1 = vm->args[0][0];
	arg_2 = vm->args[1][0];
	if (vm->args[0][1] == T_DIR)
		prcs->registers[arg_2] = arg_1;
	else if (vm->args[0][1] == T_IND)
	{
		prcs->registers[arg_2] =
		mem_to_short(vm->ram + (prcs->registers[PC] + arg_1) % MEM_SIZE);
		arg_1 = prcs->registers[arg_2];
	}
	prcs->carry = (arg_1 == 0 ? 1 : 0);
	(vm->options.verbose & 4) ? op_verbose_4(prcs, vm->args) : 0;
	pc_movement(vm, prcs);
}
