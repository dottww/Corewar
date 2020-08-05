/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:17 by weilin            #+#    #+#             */
/*   Updated: 2020/08/02 22:18:43 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	sti_second_line(int args[3][2], int ptr)
{
	ft_printf("\n       | -> store to ");
	if (args[1][1] == T_DIR)
		ft_printf("%hd + ", (short)args[1][0]);
	else
		ft_printf("%d + ", args[1][0]);
	if (args[2][1] == T_DIR)
		ft_printf("%hd ", (short)args[2][0]);
	else
		ft_printf("%d ", args[2][0]);
	ft_printf("= %d (with pc and mod %d)\n", args[1][0] + args[2][0], ptr);
}

static void	op_verbose_4(t_process *prcs, int args[3][2], int ptr)
{
	int		i;

	ft_printf("P%5d | %s ", prcs->process_id + 1
	, g_ops[prcs->op_code_to_exec].op_name);
	i = 0;
	while (i < g_ops[prcs->op_code_to_exec].nb_arg)
	{
		if (i == 0 && args[i][1] == T_REG)
			ft_printf("r");
		if (args[i][1] == T_REG)
			ft_printf("%d", args[i][0]);
		else if (args[i][1] == T_DIR)
			ft_printf("%hd", (short)args[i][0]);
		else if (args[i][1] == T_IND)
			ft_printf("%d", args[i][0]);
		if (i < g_ops[prcs->op_code_to_exec].nb_arg - 1)
			ft_printf(" ");
		i += 1;
	}
	sti_second_line(args, ptr);
}

void		op_sti(t_env *e, t_process *prcs)
{
	int		ptr;
	int		arg_1;
	int		arg_2;
	int		arg_3;

	arg_1 = e->args[0][0];
	arg_2 = get_sti_ldi_val(e, prcs, e->args[1]);
	arg_3 = get_sti_ldi_val(e, prcs, e->args[2]);
	e->args[1][0] = arg_2;
	e->args[2][0] = arg_3;
	ptr = (prcs->registers[PC] + ((arg_2 + arg_3) % IDX_MOD)) % MEM_SIZE;
	V_DEBUG ? op_verbose_4(prcs, e->args, ptr) : 0;
	int_to_mem(e, prcs->registers[arg_1], (ptr + 3) % MEM_SIZE);
	pc_movement(e, prcs);
}
