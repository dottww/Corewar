/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:38 by weilin            #+#    #+#             */
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
		if (args[i][1] == T_IND)
			ft_printf("%d", prcs->registers[args[1][0]]);
		else
			ft_printf("%d", args[i][0]);
		if (i < g_ops[prcs->op_code_to_exec].nb_arg - 1)
			ft_printf(" ");
		i += 1;
	}
	ft_printf("\n");
}

short		mem_to_short(unsigned char tab[2])
{
	short	result;
	int		index;

	result = 0;
	index = 0;
	while (index < 2)
	{
		result |= tab[index];
		if (index < 1)
			result <<= 8;
		index++;
	}
	return (result);
}

void		op_lld(t_env *e, t_process *prcs)
{
	int		arg_1;
	int		arg_2;

	arg_1 = e->args[0][0];
	arg_2 = e->args[1][0];
	if (e->args[0][1] == T_DIR)
		prcs->registers[arg_2] = arg_1;
	else if (e->args[0][1] == T_IND)
	{
		prcs->registers[arg_2] =
		mem_to_short(e->arena + (prcs->registers[PC] + arg_1) % MEM_SIZE);
	}
	prcs->carry = (prcs->registers[arg_2] == 0 ? 1 : 0);
	V_DEBUG ? op_verbose_4(prcs, e->args) : 0;
	pc_movement(e, prcs);
}
