/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:34:40 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 08:23:13 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	op_verbose_4(t_process *prcs, int args[3][2],
						int arg_1, int arg_2)
{
	int		i;

	ft_printf("P%5d | %s ", prcs->pid, g_ops[prcs->op_code].op_name);
	i = 0;
	while (i < g_ops[prcs->op_code].nb_arg - 1)
	{
		if (i == 0)
			ft_printf("%d ", arg_1);
		else if (i == 1)
			ft_printf("%d ", arg_2);
		i += 1;
	}
	ft_printf("r%d\n", args[2][0]);
}

void		op_or(t_vm *vm, t_process *prcs)
{
	int		arg_1;
	int		arg_2;
	int		arg_3;

	arg_1 = get_and_or_val(vm, prcs->registers[PC], vm->args[0], prcs);
	arg_2 = get_and_or_val(vm, prcs->registers[PC], vm->args[1], prcs);
	arg_3 = vm->args[2][0];
	prcs->registers[vm->args[2][0]] = arg_1 | arg_2;
	prcs->carry = (prcs->registers[vm->args[2][0]] == 0 ? 1 : 0);
	(vm->options.verbose & 4) ? op_verbose_4(prcs, vm->args, arg_1, arg_2) : 0;
	pc_movement(vm, prcs);
}
