/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_pc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:04:29 by weilin            #+#    #+#             */
/*   Updated: 2020/08/07 14:06:49 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	hexdump(const unsigned char ram[MEM_SIZE], int width)
{
	int		len;

	len = 0;
	width *= 16;
	while (len < MEM_SIZE)
	{
		if (len % width == 0)
			ft_printf("0x%.4x : ", len);
		if ((len + 1) % width == 0)
			ft_printf("%.2x \n", ram[len]);
		else
			ft_printf("%.2x ", ram[len]);
		len++;
	}
}

int		skip_arg(t_env *e, int skip
					, const int arg, const u_int8_t op_code)
{
	if (e->args[arg][1] == T_REG)
		skip += 1;
	else if (e->args[arg][1] == T_IND)
		skip += 2;
	else if (e->args[arg][1] == T_DIR)
		skip += g_ops[op_code].dirsize;
	return (skip);
}

void	move_pc(t_process *prcs, int move)
{
	int	new_pc;

	new_pc = prcs->registers[PC] + move;
	if (new_pc < 0)
		new_pc = MEM_SIZE + (new_pc % MEM_SIZE);
	else
		new_pc = new_pc % MEM_SIZE;
	prcs->registers[PC] = new_pc;
}

void	pc_movement(t_env *e, t_process *prcs)
{
	int		i;
	int		nb_arg;
	int		skip_byte;

	skip_byte = 0;
	if (g_ops[prcs->op_code_to_exec].encoding)
		skip_byte = 1;
	nb_arg = g_ops[prcs->op_code_to_exec].nb_arg;
	i = 0;
	while (i < nb_arg)
		skip_byte = skip_arg(e, skip_byte, i++, prcs->op_code_to_exec);
	V_DEBUG ? verbose_16(e, prcs, skip_byte) : 0;
	move_pc(prcs, skip_byte + 1);
}

bool	pc_at_illegal_arena(t_env *e, t_process *prcs)
{
	return (e->arena[prcs->registers[PC] % MEM_SIZE] == 0 ||
		e->arena[prcs->registers[PC] % MEM_SIZE] > 16);
}
