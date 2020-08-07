/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:45 by weilin            #+#    #+#             */
/*   Updated: 2020/08/06 23:18:40 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	lldi_second_line(t_process *prcs, int args[3][2])
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
	ft_printf(" (with pc %d)\n", (prcs->registers[PC] +
	((int)args[0][0] + (int)args[1][0])) % MEM_SIZE);
}

static void	op_verbose_4(t_process *prcs, int args[3][2])
{
	int		i;

	ft_printf("P%5d | %s ", prcs->process_id + 1
	, g_ops[prcs->op_code_to_exec].op_name);
	i = 0;
	while (i < g_ops[prcs->op_code_to_exec].nb_arg)
	{
		if (i == 2)
			ft_printf("r");
		if (args[i][1] == T_DIR)
			ft_printf("%hd", (short)args[i][0]);
		else
			ft_printf("%d", args[i][0]);
		if (i < g_ops[prcs->op_code_to_exec].nb_arg - 1)
			ft_printf(" ");
		i += 1;
	}
	lldi_second_line(prcs, args);
}

void		op_lldi(t_env *e, t_process *prcs)
{
	int		arg_1;
	int		arg_2;
	int		arg_3;
	int		ind;

	arg_1 = get_sti_ldi_val(e, prcs, (uint32_t *)e->args[0]);
	arg_2 = get_sti_ldi_val(e, prcs, (uint32_t *)e->args[1]);
	arg_3 = e->args[2][0];
	e->args[0][0] = arg_1;
	e->args[1][0] = arg_2;
	ind = arg_1 + arg_2;
	ind = (prcs->registers[PC] + ind) % MEM_SIZE;
	prcs->registers[arg_3] = mem_to_val(e, &ind, 4);
	prcs->carry = (prcs->registers[arg_3] == 0 ? 1 : 0);
	V_DEBUG ? op_verbose_4(prcs, e->args) : 0;
	pc_movement(e, prcs);
}
