/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 06:16:30 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 07:45:24 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_process		*prcs_create(const int pid, const int pc)
{
	t_process	*prcs;

	if (!(prcs = (t_process *)ft_memalloc(sizeof(t_process))))
		return (NULL);
	prcs->pid = pid;
	prcs->registers[PC] = pc % MEM_SIZE;
	return (prcs);
}

void			nullfill_process_lst(t_vm *vm)
{
	int		end;
	int		i;

	end = vm->nb_max_prcs * 2;
	i = vm->nb_max_prcs;
	while (i < end)
		vm->prcs_lst[i++] = NULL;
}

void			prcs_list_add(t_vm *vm, t_process *prcs)
{
	vm->nb_prcs += 1;
	if (vm->nb_prcs >= vm->nb_max_prcs)
	{
		if (!(vm->prcs_lst = realloc(vm->prcs_lst,
		vm->nb_max_prcs * 2 * sizeof(t_process *))))
			return ;
		nullfill_process_lst(vm);
		vm->nb_max_prcs *= 2;
	}
	vm->prcs_lst[vm->nb_prcs - 1] = prcs;
}

t_process		*prcs_cpy(t_process *prcs, int pc, int pid)
{
	t_process	*new_prcs;

	if (!(new_prcs = prcs_create(pid, pc)))
		return (NULL);
	ft_memcpy(&(new_prcs->registers), &(prcs->registers),
	17 * sizeof(int32_t));
	new_prcs->carry = prcs->carry;
	return (new_prcs);
}
