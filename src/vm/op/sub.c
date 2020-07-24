/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:05:09 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 06:42:50 by weilin           ###   ########.fr       */
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
		ft_printf("%d", args[i][0]);
		if (i < g_ops[prcs->op_code].nb_arg - 1)
			ft_printf(" ");
		i += 1;
	}
	ft_printf("\n");
}

void		op_sub(t_vm *vm, t_process *prcs)
{
	int			sub;

	sub = prcs->registers[vm->args[0][0]];
	sub -= prcs->registers[vm->args[1][0]];
	prcs->registers[vm->args[2][0]] = sub;
	prcs->carry = (sub == 0 ? 1 : 0);
	(vm->options.verbose & 4) ? op_verbose_4(prcs, vm->args) : 0;
	pc_movement(vm, prcs);
}
