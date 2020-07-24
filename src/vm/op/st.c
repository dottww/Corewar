/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:34:03 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 08:15:24 by weilin           ###   ########.fr       */
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
		if (i == 0 && args[i][1] == T_REG)
			ft_printf("r");
		if (args[i][1] == T_IND)
			ft_printf("%d", args[i][0]);
		else
			ft_printf("%d", args[i][0]);
		if (i < g_ops[prcs->op_code].nb_arg - 1)
			ft_printf(" ");
		i += 1;
	}
	ft_printf("\n");
}

void		op_st(t_vm *vm, t_process *prcs)
{
	int		ptr;
	int		arg_1;
	short	arg_2;

	arg_1 = vm->args[0][0];
	arg_2 = vm->args[1][0];
	if (vm->args[1][1] == T_REG)
		prcs->registers[arg_2] = prcs->registers[arg_1];
	else if (vm->args[1][1] == T_IND)
	{
		ptr = (prcs->registers[PC] + (arg_2 % IDX_MOD)) % MEM_SIZE;
		int_to_mem(vm, prcs->registers[arg_1], ptr + 3);
	}
	(vm->options.verbose & 4) ? op_verbose_4(prcs, vm->args) : 0;
	pc_movement(vm, prcs);
}
