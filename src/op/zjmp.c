/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:34:57 by weilin            #+#    #+#             */
/*   Updated: 2020/08/02 22:18:43 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	op_verbose_4(t_process *prcs, short val)
{
	ft_printf("P%5d | %s ", prcs->process_id + 1
	, g_ops[prcs->op_code_to_exec].op_name);
	ft_printf("%hd", val);
	prcs->carry == 1 ? ft_printf(" OK\n") : ft_printf(" FAILED\n");
}

void		op_zjmp(t_env *e, t_process *prcs)
{
	short	val;

	val = e->args[0][0];
	V_DEBUG ? op_verbose_4(prcs, val) : 0;
	if (prcs->carry == 1)
	{
		move_pc(prcs, (val % IDX_MOD) % MEM_SIZE);
	}
	else
	{
		pc_movement(e, prcs);
	}
}
