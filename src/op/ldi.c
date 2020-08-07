/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:05 by weilin            #+#    #+#             */
/*   Updated: 2020/08/07 16:01:25 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void		ldi_second_line(t_process *prcs, int args[3][2])
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
	ft_printf(" (with pc and mod %d)\n", prcs->registers[PC] +
	((args[0][0] + args[1][0]) % IDX_MOD));
}

static void		op_verbose_4(t_process *prcs, int args[3][2])
{
	int		i;

	ft_printf("P%5d | %s ", prcs->process_id + 1
		, g_ops[prcs->op_code_to_exec].op_name);
	i = 0;
	while (i < g_ops[prcs->op_code_to_exec].nb_arg)
	{
		if (i == 2 && args[i][1] == T_REG)
			ft_printf("r");
		if (args[i][1] == T_DIR)
			ft_printf("%hd", (short)args[i][0]);
		else
			ft_printf("%d", args[i][0]);
		if (i < g_ops[prcs->op_code_to_exec].nb_arg - 1)
			ft_printf(" ");
		i += 1;
	}
	ldi_second_line(prcs, args);
}

u_int32_t		char4_to_int(unsigned char tab[4])
{
	u_int32_t	result;
	int			index;

	result = 0;
	index = 0;
	while (index < 4)
	{
		result |= tab[index];
		if (index < 3)
			result <<= 8;
		index++;
	}
	return (result);
}

int				ldi_mem_to_indirect(t_env *e, int pc, long indirect)
{
	int			val;
	long		ptr;
	long		move;
	u_int8_t	tab[4];

	move = (indirect % IDX_MOD);
	ptr = pc + move;
	if (ptr < 0)
		ptr = MEM_SIZE + (ptr % MEM_SIZE);
	else
		ptr = ptr % MEM_SIZE;
	tab[0] = e->arena[ptr++ % MEM_SIZE];
	tab[1] = e->arena[ptr++ % MEM_SIZE];
	tab[2] = e->arena[ptr++ % MEM_SIZE];
	tab[3] = e->arena[ptr % MEM_SIZE];
	val = char4_to_int(tab);
	return (val);
}

void			op_ldi(t_env *e, t_process *prcs)
{
	long	arg_1;
	long	arg_2;
	long	arg_3;
	long	ind;

	arg_1 = get_sti_ldi_val(e, prcs, (u_int32_t *)e->args[0]);
	arg_2 = get_sti_ldi_val(e, prcs, (u_int32_t *)e->args[1]);
	arg_3 = e->args[2][0];
	e->args[0][0] = arg_1;
	e->args[1][0] = arg_2;
	ind = arg_1 + arg_2;
	prcs->registers[arg_3] = ldi_mem_to_indirect(e, prcs->registers[PC], ind);
	V_DEBUG ? op_verbose_4(prcs, e->args) : 0;
	pc_movement(e, prcs);
}
