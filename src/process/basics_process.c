/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 05:18:48 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 19:49:29 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

t_process	*scroll_process(t_process *current, t_process_info *info)
{
	if (!info->head)
		return (NULL);
	if (!(current) && info->head)
		current = info->head;
	else if (current->next == NULL)
		return (NULL);
	else
		current = current->next;
	return (current);
}

t_process	*get_process_from(int from, int process_id, t_process_info info)
{
	t_process	*cpy;

	from = FROM_FIRST;
	cpy = from ? info.head : info.tail;
	while (process_id != cpy->process_id && cpy->next != NULL)
		cpy = from ? cpy->next : cpy->prev;
	if (!cpy)
		exit_error("No Process : Empty Node", (char*)__func__);
	if (cpy->process_id != process_id)
		exit_error("Invalid [process_id] : Process Does Not Exist",
			(char*)__func__);
	return (cpy);
}

t_process	create_process_data(t_qnode *fork)
{
	t_process		new_process;
	t_qfork_data	*fdata;

	fdata = (t_qfork_data*)(fork->pdata);
	new_process.registers[PC] = fdata->pc;
	new_process.op_code_to_exec = -1;
	new_process.carry = 0;
	ft_bzero(new_process.registers, sizeof(int) * 17);
	new_process.player = fdata->player;
	new_process.process_id = -1;
	return (new_process);
}

t_process	*add_new_process(t_process to_add, t_process_info *info)
{
	t_process	*new_process;
	t_process	*cpy;

	cpy = info->head;
	if (!(new_process = (t_process*)malloc(sizeof(t_process))))
		exit_error("Malloc Failed", (char*)__func__);
	ft_memcpy(new_process, &to_add, sizeof(t_process));
	info->process_nb++;
	new_process->process_id = ++info->process_id_cpt;
	new_process->prev = NULL;
	if (!cpy)
	{
		new_process->next = NULL;
		info->head = new_process;
		info->tail = new_process;
		return (new_process);
	}
	new_process->next = cpy;
	cpy->prev = new_process;
	info->head = new_process;
	return (new_process);
}

void		init_processes(t_env *e)
{
	t_process process;

	clean(&process);
	e->info.head = NULL;
	e->info.tail = NULL;
	e->info.process_nb = 0;
	e->info.process_id_cpt = -1;
	while (e->info.process_nb < e->player_count)
	{
		create_process_data_from_start(e->info.process_id_cpt
						, &e->player[e->info.process_nb], &process);
		add_new_process(process, &e->info);
	}
}
