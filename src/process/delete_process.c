/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 09:15:43 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 19:51:56 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	info_null(t_process_info *info)
{
	info->head = NULL;
	info->tail = NULL;
}

void	to_delete_is_head(t_process_info *info, t_process *to_delete)
{
	to_delete->next->prev = NULL;
	info->head = to_delete->next;
}

void	to_delete_is_tail(t_process_info *info, t_process *to_delete)
{
	to_delete->prev->next = NULL;
	info->tail = to_delete->prev;
}

void	delete_process_direct(t_process **to_delete1
							, t_process_info *info, t_fork_utils *forks)
{
	t_process *to_delete;

	(void)forks;
	to_delete = *to_delete1;
	if (to_delete == info->head && to_delete == info->tail)
		info_null(info);
	else if (to_delete == info->head)
		to_delete_is_head(info, to_delete);
	else if (to_delete == info->tail)
		to_delete_is_tail(info, to_delete);
	else
	{
		to_delete->next->prev = to_delete->prev;
		to_delete->prev->next = to_delete->next;
	}
	ft_memdel((void *)to_delete1);
	info->process_nb--;
}
