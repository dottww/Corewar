/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 07:03:49 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 07:03:56 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	prcs_lst_slide_up(t_process **prcs_lst, int i, int nb)
{
	while (i < nb)
	{
		prcs_lst[i] = prcs_lst[i + 1];
		i += 1;
	}
}

void	del_prcs_list(t_vm *vm, t_process *prcs)
{
	int	i;

	i = 0;
	while (vm->prcs_lst[i] != prcs)
		i += 1;
	prcs_lst_slide_up(vm->prcs_lst, i, vm->nb_prcs);
}

void	del_prcs_arr(t_process *arr[1024], t_process *prcs)
{
	t_process	*tmp;

	tmp = arr[prcs->arr_cycle];
	if (tmp == prcs)
		arr[prcs->arr_cycle] = tmp->next;
	else
	{
		while (tmp->next != NULL && (tmp->next != prcs))
			tmp = tmp->next;
		tmp->next = prcs->next;
	}
	free(prcs);
	prcs = NULL;
}

void	del_process(t_vm *vm, t_process *arr[1024], t_process *prcs)
{
	del_prcs_list(vm, prcs);
	del_prcs_arr(arr, prcs);
	vm->nb_player -= 1;
}
