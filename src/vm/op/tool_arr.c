/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:39:33 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 06:49:31 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	arr_insert(t_process *arr, t_process *prcs)
{
	while (arr->next && (arr->next->pid > prcs->pid))
		arr = arr->next;
	prcs->next = arr->next;
	arr->next = prcs;
}

void	arr_add(t_vm *vm, t_process *prcs, size_t cycle)
{
	prcs->arr_cycle = cycle;
	if (vm->arr[cycle] == NULL || (vm->arr[cycle]->pid < prcs->pid))
	{
		prcs->prev = NULL;
		prcs->next = vm->arr[cycle];
		vm->arr[cycle] = prcs;
	}
	else
		arr_insert(vm->arr[cycle], prcs);
}

void	arr_assign(t_vm *vm, t_process *prcs, size_t cycle, int size)
{
	int	src;
	int	dst;

	src = cycle % 1024;
	dst = (cycle + size) % 1024;
	vm->arr[src] = vm->arr[src]->next;
	arr_add(vm, prcs, dst);
}
