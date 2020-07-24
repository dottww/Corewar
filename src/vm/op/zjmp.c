/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:34:57 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 08:04:56 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	op_verbose_4(t_process *prcs, short val)
{
	ft_printf("P%5d | %s ", prcs->pid, g_ops[prcs->op_code].op_name);
	ft_printf("%hd", val);
	prcs->carry == 1 ? ft_printf(" OK\n") : ft_printf(" FAILED\n");
}

void		op_zjmp(t_vm *vm, t_process *prcs)
{
	short	val;

	val = vm->args[0][0];
	(vm->options.verbose & 4) ? op_verbose_4(prcs, val) : 0;
	if (prcs->carry == 1)
		move_pc(prcs, (val % IDX_MOD) % MEM_SIZE);
	else
		pc_movement(vm, prcs);
}
