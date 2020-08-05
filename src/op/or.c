/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:34:40 by weilin            #+#    #+#             */
/*   Updated: 2020/08/05 19:47:50 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	op_verbose_4(t_process *prcs, int args[3][2],
						int arg_1, int arg_2)
{
	int		i;

	ft_printf("P%5d | %s ", prcs->process_id + 1
	, g_ops[prcs->op_code_to_exec].op_name);
	i = 0;
	while (i < g_ops[prcs->op_code_to_exec].nb_arg - 1)
	{
		if (i == 0)
			ft_printf("%d ", arg_1);
		else if (i == 1)
			ft_printf("%d ", arg_2);
		i += 1;
	}
	ft_printf("r%d\n", args[2][0]);
}

void		op_or(t_env *e, t_process *prcs)
{
	int	arg_1;
	int	arg_2;

	arg_1 = get_and_or_val(e, prcs->registers[PC], (uint32_t*)e->args[0], prcs);
	arg_2 = get_and_or_val(e, prcs->registers[PC], (uint32_t*)e->args[1], prcs);
			/*or*/ (0)?ft_printf("pc=%d \n", prcs->registers[PC]):0;
			/*or*/ (0)?ft_printf("e->args[0]/[1]=[%d]/[%d] ", e->args[0],e->args[1]):0;
			/*or*/ (0)?ft_printf("arg1/2=%d/%d\n", arg_1,arg_2):0;
	prcs->registers[e->args[2][0]] = arg_1 | arg_2;
	prcs->carry = (prcs->registers[e->args[2][0]] == 0 ? 1 : 0);
	V_DEBUG ? op_verbose_4(prcs, e->args, arg_1, arg_2) : 0;
	pc_movement(e, prcs);
}
