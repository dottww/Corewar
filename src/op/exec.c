/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:39:46 by weilin            #+#    #+#             */
/*   Updated: 2020/08/07 01:54:44 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void exec_ops(t_env *e, t_process *prcs)
{
/*de*/ (0)?ft_printf("EXECOPS\n") : 0;
	if (!init_args(e, prcs))
	{

/*de*/ (0)?	ft_printf("init_args failed,") : 0;
// pc_movement(e, prcs);
prcs->op_code_to_exec = -2;
prcs->op_cooldown = 0;
	}
	else
	{
/*de*/ (0)?	ft_printf("init_args success\n") : 0;
/*de*/ (0)?	ft_printf("START_EXECOPS\n") : 0;
/*de*/ (0)?		ft_printf(" op/cd ( %d", prcs->op_code_to_exec) : 0;
/*de*/ (0)?		ft_printf(" / %d )\n", prcs->op_cooldown) : 0;
		g_ops[prcs->op_code_to_exec].op_ptr(e, prcs);
	prcs->op_code_to_exec = -1;
	}
/*de*/ (0)?	ft_printf("END_EXECOPS\n") : 0;
/*de*/ (0)?		ft_printf("after EXEC op/cd ( %d", prcs->op_code_to_exec) : 0;
/*de*/ (0)?		ft_printf(" / %d )\n", prcs->op_cooldown) : 0;
	// if (init_args(e, prcs))
	// {
	// 	g_ops[prcs->op_code_to_exec].op_ptr(e, prcs);
	// 	prcs->op_code_to_exec = -1;
	// }
	ft_bzero(e->args, sizeof(e->args));
}
