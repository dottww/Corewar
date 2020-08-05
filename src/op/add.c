/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by weilin            #+#    #+#             */
/*   Updated: 2020/08/05 10:34:25 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	op_verbose_4(t_process *prcs, int args[3][2])
{
	int		i;

	ft_printf("P%5d | %s ", prcs->process_id + 1,
		g_ops[prcs->op_code_to_exec].op_name);
	i = 0;
	while (i < g_ops[prcs->op_code_to_exec].nb_arg)
	{
		if (args[i][1] == T_REG && i < g_ops[prcs->op_code_to_exec].nb_arg - 1)
			ft_printf("r%d ", args[i][0]);
		i++;
	}
	ft_printf("r%d\n", args[2][0]);
}

void		op_add(t_env *e, t_process *p)
{
	int		add;

	add = p->registers[e->args[0][0]];
	add += p->registers[e->args[1][0]];
	p->registers[e->args[2][0]] = add;
	p->carry = (p->registers[e->args[2][0]] == 0 ? 1 : 0);
	V_DEBUG ? op_verbose_4(p, e->args) : 0;
	pc_movement(e, p);
}
