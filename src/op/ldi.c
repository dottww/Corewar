/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:05 by weilin            #+#    #+#             */
/*   Updated: 2020/08/06 23:20:40 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	ldi_second_line(t_process *prcs, int args[3][2])
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

static void	op_verbose_4(t_process *prcs, int args[3][2])
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

int				ft_ldi_value_from_address(t_env *e, int pc, long indirect)
{
	int			param;
	long		pos;
	uint8_t		tab[4];

	pos = (pc + (indirect % IDX_MOD)) % MEM_SIZE; ///////pending_move_pc
	tab[0] = e->arena[pos++ % MEM_SIZE];
	tab[1] = e->arena[pos++ % MEM_SIZE];
	tab[2] = e->arena[pos++ % MEM_SIZE];
	tab[3] = e->arena[pos % MEM_SIZE];
	param = char4_to_int(tab);
	return (param);
}

void		op_ldi(t_env *e, t_process *prcs)
{
	long	arg_1;
	long	arg_2;
	long	arg_3;
	long	ind;

	// ft_printf("e->args[0][0]=%d\n", e->args[0][0]);
	// ft_printf("e->args[1][0]=%d\n", e->args[1][0]);
	arg_1 = get_sti_ldi_val(e, prcs, (uint32_t *)e->args[0]);
	arg_2 = get_sti_ldi_val(e, prcs, (uint32_t *)e->args[1]);
	arg_3 = e->args[2][0];
	e->args[0][0] = arg_1;
	e->args[1][0] = arg_2;
	ind = arg_1 + arg_2;
	// ft_printf("arg_1=%d\n", arg_1);
	// ft_printf("arg_2=%d\n", arg_2);
	// ft_printf("arg_3=%d\n", arg_3);

	// ft_printf("r[arg_3]=mem_to_val((arg_1 + arg_2)%MOD + PC\n");
	// ft_printf("r[%d]=mem_to_val((%d + %d)%MOD + %d\n",arg_3, arg_1, arg_2, prcs->registers[PC]);

	prcs->registers[arg_3] = ft_ldi_value_from_address(e, prcs->registers[PC], ind);
	// ft_printf("r[%d]=%d\n",arg_3,prcs->registers[arg_3]);
	V_DEBUG ? op_verbose_4(prcs, e->args) : 0;
	pc_movement(e, prcs);
}
