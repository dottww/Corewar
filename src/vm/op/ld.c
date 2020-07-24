/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 23:54:29 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 06:16:24 by weilin           ###   ########.fr       */
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

void		op_ld(t_vm *vm, t_process *prcs)
{
	int		ptr;
	int		arg_1;
	int		arg_2;

	arg_1 = vm->args[0][0];
	arg_2 = vm->args[1][0];
	if (vm->args[0][1] == T_DIR)
		prcs->registers[arg_2] = arg_1;
	else if (vm->args[0][1] == T_IND)
	{
		arg_1 = (short)arg_1;
		ptr = (prcs->registers[PC] + (arg_1 % IDX_MOD)) % MEM_SIZE;
		prcs->registers[arg_2] = mem_to_val(vm, &ptr, 4);
	}
	vm->args[0][0] = prcs->registers[arg_2];
	arg_1 = prcs->registers[arg_2];
	prcs->carry = (arg_1 == 0 ? 1 : 0);
	(vm->options.verbose & 4) ? op_verbose_4(prcs, vm->args) : 0;
	pc_movement(vm, prcs);
}
