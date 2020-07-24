/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 23:00:28 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 08:23:13 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_ind_value(t_vm *vm, int pc, int ind)
{
	int	val;
	int	ptr;

	ptr = (pc + (ind % IDX_MOD)) % MEM_SIZE;
	val = mem_to_val(vm, &ptr, 4);
	return (val);
}

int		get_and_or_val(t_vm *vm, int pc, int arg[2], t_process *prcs)
{
	if (arg[1] == T_IND)
		return (get_ind_value(vm, pc, arg[0]));
	else if (arg[1] == T_REG)
		return (prcs->registers[arg[0]]);
	return (arg[0]);
}

int		get_sti_ldi_val(t_vm *vm, t_process *prcs, int arg[2])
{
	int	val;

	val = arg[0];
	if (arg[1] == T_DIR)
		val = (short)arg[0];
	else if (arg[1] == T_REG)
		val = prcs->registers[val];
	else if (arg[1] == T_IND)
		val = get_ind_value(vm, prcs->registers[PC], val);
	return (val);
}
