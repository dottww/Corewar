/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 23:00:28 by weilin            #+#    #+#             */
/*   Updated: 2020/08/07 14:08:29 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		get_ind_value(t_env *e, int pc, short ind)
{
	int	val;
	int	ptr;
	int move;

	move = (ind % IDX_MOD);
	ptr = pc + move;
	if (ptr < 0)
		ptr = MEM_SIZE + (ptr % MEM_SIZE);
	else
		ptr = ptr % MEM_SIZE;
	val = mem_to_val(e, &ptr, 4);
	return (val);
}

int				mem_to_val(t_env *e, int *ext_ptr, int size)
{
	int			i;
	u_int32_t	val;
	int			ptr;

	ptr = (*ext_ptr) % MEM_SIZE;
	val = 0;
	i = 0;
	while (i < size)
	{
		ptr = (ptr >= 0 ? ptr : MEM_SIZE + ptr);
		val |= e->arena[ptr % MEM_SIZE];
		if (i < size - 1)
			val <<= 8;
		ptr++;
		i++;
	}
	*ext_ptr = ptr;
	return (val);
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

int				mem_to_ind(t_env *e, int pc, short indirect)
{
	int			param;
	long		pos;
	u_int8_t	tab[4];

	pos = (pc + (indirect % IDX_MOD)) % MEM_SIZE; ///////pending_move_pc
	tab[0] = e->arena[pos++ % MEM_SIZE];
	tab[1] = e->arena[pos++ % MEM_SIZE];
	tab[2] = e->arena[pos++ % MEM_SIZE];
	tab[3] = e->arena[pos % MEM_SIZE];
	param = char4_to_int(tab);
	return (param);
}

long			get_and_or_val(t_env *e, int pc
						, u_int32_t arg[2], t_process *prcs)
{
	if (arg[1] == T_IND)
		return (get_ind_value(e, pc, arg[0]));
		// return (mem_to_ind(e, pc, arg[0]));
	else if (arg[1] == T_REG)
		return (prcs->registers[arg[0]]);
	return (arg[0]);
}

int				get_sti_ldi_val(t_env *e, t_process *prcs, u_int32_t arg[2])
{
	int	val;

	val = arg[0];
	if (arg[1] == T_DIR)
		val = (short)arg[0];
	else if (arg[1] == T_REG)
		val = prcs->registers[val];
	else if (arg[1] == T_IND)
		val = get_ind_value(e, prcs->registers[PC], val);
		// val = mem_to_ind(e, prcs->registers[PC], val);
	return (val);
}
