/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 23:54:29 by weilin            #+#    #+#             */
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
		if (args[i][1] == T_REG)
			ft_printf("r");
		ft_printf("%d", args[i][0]);
		if (i < g_ops[prcs->op_code_to_exec].nb_arg - 1)
			ft_printf(" ");
		i += 1;
	}
	ft_printf("\n");
}

void		op_ld(t_env *e, t_process *prcs)
{
	int		ptr;
	int		arg_1;
	int		arg_2;

	arg_1 = e->args[0][0];
	arg_2 = e->args[1][0];
	if (e->args[0][1] == T_DIR)
		prcs->registers[arg_2] = arg_1;
	else if (e->args[0][1] == T_IND)
	{
		arg_1 = (short)arg_1;
		ptr = (prcs->registers[PC] + (arg_1 % IDX_MOD)) % MEM_SIZE;
		prcs->registers[arg_2] = mem_to_val(e, &ptr, 4);
	}
	e->args[0][0] = prcs->registers[arg_2];
	arg_1 = prcs->registers[arg_2];
	prcs->carry = (arg_1 == 0 ? 1 : 0);
	V_DEBUG ? op_verbose_4(prcs, e->args) : 0;
	pc_movement(e, prcs);
}
