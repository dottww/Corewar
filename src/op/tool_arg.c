/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:59:18 by weilin            #+#    #+#             */
/*   Updated: 2020/08/07 13:48:16 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	int_to_mem(t_env *e, int val, int ptr)
{
	int			i;

	i = 0;
	ptr %= MEM_SIZE;
	ptr = (ptr >= 0 ? ptr : MEM_SIZE + ptr);
	while (i < 4)
	{
		e->arena[ptr % MEM_SIZE] = val;
		ptr = (ptr > 0 ? ptr - 1 : MEM_SIZE + (ptr - 1));
		val = val >> 8;
		i += 1;
	}
}

int		check_arg_value(t_env *e, t_process *prcs)
{
	int		i;
	int		nb_arg;

	nb_arg = g_ops[prcs->op_code_to_exec].nb_arg;
	i = 0;
	while (i < nb_arg)
	{
		if (e->args[i][1] == T_REG &&
			(e->args[i][0] <= 0 || e->args[i][0] >= 17))
		{
			pc_movement(e, prcs);
			return (false);
		}
		i++;
	}
	return (true);
}

int		mem_to_arg(t_env *e, int *i_ptr, int end, int i)
{
	int	start;

	start = *i_ptr;
	while (start < end)
	{
		e->args[i][0] |= e->arena[start % MEM_SIZE];
		if (start < end - 1)
			e->args[i][0] <<= 8;
		start += 1;
	}
	*i_ptr = start;
	return (true);
}

int		get_arg_value(t_env *e, t_process *prcs)
{
	int		i;
	int		ptr;
	int		nb_arg;

	nb_arg = g_ops[prcs->op_code_to_exec].nb_arg;
	ptr = (prcs->registers[PC] + 1 + g_ops[prcs->op_code_to_exec].encoding)
																% MEM_SIZE;
	i = 0;
	while (i < nb_arg)
	{
		if (e->args[i][1] == T_REG)
			mem_to_arg(e, &ptr, ptr + 1, i);
		else if (e->args[i][1] == T_IND)
			mem_to_arg(e, &ptr, ptr + 2, i);
		else if (e->args[i][1] == T_DIR)
			mem_to_arg(e, &ptr, ptr + g_ops[prcs->op_code_to_exec].dirsize, i);
		i++;
	}
	return (check_arg_value(e, prcs));
}

int		get_arg_type(u_int8_t encoded, t_process *prcs, t_env *e, int i)
{
	u_int8_t	mask;

	mask = encoded & BIT_IND;
	if (mask == BIT_REG
				&& (g_ops[prcs->op_code_to_exec].arg_type[i] & T_REG) != 0)
		e->args[i][1] = T_REG;
	else if (mask == BIT_IND
				&& (g_ops[prcs->op_code_to_exec].arg_type[i] & T_IND) != 0)
		e->args[i][1] = T_IND;
	else if (mask == BIT_DIR
				&& (g_ops[prcs->op_code_to_exec].arg_type[i] & T_DIR) != 0)
		e->args[i][1] = T_DIR;
	else
		return (false);
	return (true);
}
