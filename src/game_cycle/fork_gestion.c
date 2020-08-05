/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:37:56 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 19:49:01 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static t_qfork_data	*set_data(t_process *current, int flag)
{
	t_qfork_data *data;

	if (!(data = ft_memalloc(sizeof(t_qfork_data))))
		return (NULL);
	ft_bzero(data, sizeof(t_qfork_data));
	data->cooldown = flag ? (1000 - 1) : (800 - 1);
	data->player = current->player;
	data->process_id = current->process_id;
	data->pc = current->registers[PC];
	return (data);
}

static t_qnode		*fork_priority(t_qnode *to_add, t_qnode *current)
{
	t_qfork_data *fdata_to_add;
	t_qfork_data *fdata_current;

	fdata_to_add = (t_qfork_data *)(to_add->pdata);
	fdata_current = (t_qfork_data *)(current->pdata);
	if ((fdata_to_add->cooldown == fdata_current->cooldown
		&& fdata_to_add->process_id > fdata_current->process_id)
		|| (fdata_to_add->cooldown < fdata_current->cooldown))
		return (current);
	return (NULL);
}

void				add_fork_to_queue(t_fork_utils *f
								, t_process *current, int flag)
{
	t_qfork_data *data;

	data = set_data(current, flag);
	en_queue_with_priority(f->qfork, data, fork_priority);
}
