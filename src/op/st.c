/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:34:03 by weilin            #+#    #+#             */
/*   Updated: 2020/08/02 22:18:43 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	op_verbose_4(t_process *prcs, int args[3][2])
{
	int		i;

	ft_printf("P%5d | %s ", prcs->process_id + 1
	, g_ops[prcs->op_code_to_exec].op_name);
	i = 0;
	while (i < g_ops[prcs->op_code_to_exec].nb_arg)
	{
		if (i == 0 && args[i][1] == T_REG)
			ft_printf("r");
		if (args[i][1] == T_IND)
			ft_printf("%hd", (short)args[i][0]);
		else
			ft_printf("%d", args[i][0]);
		if (i < g_ops[prcs->op_code_to_exec].nb_arg - 1)
			ft_printf(" ");
		i += 1;
	}
	ft_printf("\n");
}

void		op_st(t_env *e, t_process *prcs)
{
	int		ptr;
	int		arg_1;
	short	arg_2;

	arg_1 = e->args[0][0];
	arg_2 = e->args[1][0];
	if (e->args[1][1] == T_REG)
		prcs->registers[arg_2] = prcs->registers[arg_1];
	else if (e->args[1][1] == T_IND)
	{
		ptr = (prcs->registers[PC] + (arg_2 % IDX_MOD)) % MEM_SIZE;
		int_to_mem(e, prcs->registers[arg_1], (ptr + 3) % MEM_SIZE);
	}
	V_DEBUG ? op_verbose_4(prcs, e->args) : 0;
	pc_movement(e, prcs);
}
