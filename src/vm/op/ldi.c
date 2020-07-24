/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:05 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 08:23:13 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ldi_second_line(t_process *prcs, int args[3][2])
{
	ft_printf("\n       | -> load from ");
	if (args[0][1] == T_DIR)
		ft_printf("%hd + ", (short)args[0][0]);
	else
		ft_printf("%d + ", args[0][0]);
	if (args[1][1] == T_DIR)
		ft_printf("%hd = ", (short)args[1][0]);
	else
		ft_printf("%d = ", args[1][0]);
	ft_printf("%d", args[0][0] + args[1][0]);
	ft_printf(" (with pc and mod %d)\n", (prcs->registers[PC] +
	((args[0][0] + args[1][0]) % IDX_MOD)) % MEM_SIZE);
}

static void	op_verbose_4(t_process *prcs, int args[3][2])
{
	int		i;

	ft_printf("P%5d | %s ", prcs->pid, g_ops[prcs->op_code].op_name);
	i = 0;
	while (i < g_ops[prcs->op_code].nb_arg)
	{
		if (i == 2 && args[i][1] == T_REG)
			ft_printf("r");
		if (args[i][1] == T_DIR)
			ft_printf("%hd", (short)args[i][0]);
		else
			ft_printf("%d", args[i][0]);
		if (i < g_ops[prcs->op_code].nb_arg - 1)
			ft_printf(" ");
		i += 1;
	}
	ldi_second_line(prcs, args);
}

void		op_ldi(t_vm *vm, t_process *prcs)
{
	int		arg_1;
	int		arg_2;
	int		arg_3;
	long	ind;

	arg_1 = get_sti_ldi_val(vm, prcs, vm->args[0]);
	arg_2 = get_sti_ldi_val(vm, prcs, vm->args[1]);
	arg_3 = vm->args[2][0];
	vm->args[0][0] = arg_1;
	vm->args[1][0] = arg_2;
	ind = arg_1 + arg_2;
	prcs->registers[arg_3] = get_ind_value(vm, prcs->registers[PC], ind);
	(vm->options.verbose & 4) ? op_verbose_4(prcs, vm->args) : 0;
	pc_movement(vm, prcs);
}
