/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 07:01:46 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 07:43:06 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	alive(t_vm *vm, t_process *arr[1024])
{
	unsigned	i;

	i = vm->nb_prcs - 1;
	while (i >= 0)
	{
		if ((size_t)vm->prcs_lst[i]->last_live <= (vm->cycle - vm->cycle_to_die))
		{
			(vm->options.verbose & 8) ? verbose_8(vm, vm->prcs_lst[i]) : 0;
			del_process(vm, arr, vm->prcs_lst[i]);
		}
		i--;
	}
}

int		check_decrease(t_vm *vm)
{
	if (vm->lives >= NBR_LIVE)
	{
		vm->no_decrease = 0;
		vm->cycle_to_die -= CYCLE_DELTA;
		(vm->options.verbose & 2) ? verbose_2_delta(vm) : 0;
	}
	else
		vm->no_decrease += 1;
	return (vm->no_decrease);
}

void	check_live(t_vm *vm, t_process *arr[1024])
{
	alive(vm, arr);
	if (check_decrease(vm) == MAX_CHECKS)
	{
		vm->no_decrease = 0;
		vm->cycle_to_die -= CYCLE_DELTA;
		(vm->options.verbose & 2) ? verbose_2_delta(vm) : 0;
	}
	vm->lives = 0;
	vm->die_count[0] = 0;
	vm->die_count[1] = vm->cycle_to_die;
}
