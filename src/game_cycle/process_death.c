/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 12:54:57 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 19:00:06 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	free_list(t_process_info *info)
{
	t_process	*cpy;
	t_process	*tmp;

	cpy = info->head;
	tmp = NULL;
	while (cpy)
	{
		tmp = cpy->next;
		ft_memdel((void*)&cpy);
		cpy = NULL;
		cpy = tmp;
	}
	info->process_nb = 0;
	info->head = NULL;
	info->tail = NULL;
}

void	delete_dead_process(t_env *e)
{
	t_process		*current;

	current = NULL;
	while (e->info.head && (current = scroll_process(current, &e->info)))
	{
		if (current->executed_live_in_this_check == -1)
		{
			V_DEBUG ? verbose_8(e->game, current) : 0;
			delete_process_direct(&current, &e->info, &e->forks);
		}
	}
}
