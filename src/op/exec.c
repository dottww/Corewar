/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:39:46 by weilin            #+#    #+#             */
/*   Updated: 2020/08/07 16:03:30 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	exec_ops(t_env *e, t_process *prcs)
{
	if (!init_args(e, prcs))
	{
		prcs->op_code_to_exec = -2;
		prcs->op_cooldown = 0;
	}
	else
	{
		g_ops[prcs->op_code_to_exec].op_ptr(e, prcs);
		prcs->op_code_to_exec = -1;
	}
	ft_bzero(e->args, sizeof(e->args));
}
