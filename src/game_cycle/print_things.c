/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:17:13 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/07 13:56:21 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_forks(t_fork_utils *f)
{
	t_qnode			*cpy;
	t_qfork_data	*tmp;

	if (!(f->qfork->head || f->qfork->tail))
	{
		ft_printf("No Forks In Wainting Queue\n");
		return ;
	}
	cpy = f->qfork->head;
	while (cpy)
	{
		tmp = (t_qfork_data*)cpy->pdata;
		ft_printf(" [%d/%d]", tmp->process_id, tmp->cooldown);
		cpy = cpy->next;
	}
	ft_printf("\n");
}

void	print_list(t_process_info info)
{
	t_process	*cpy;

	ft_printf("nb.[%d] | ", info.process_nb);
	if (!(info.head || info.tail || info.process_nb))
	{
		ft_printf("No Process Alive\n");
		return ;
	}
	ft_printf("head.[%d] tail.[%d]\n", \
		info.head->process_id, info.tail->process_id);
	cpy = info.head;
	while (cpy)
	{
		ft_printf("[%d / ", cpy->player->id);
		ft_printf("%d]", cpy->process_id);
		ft_printf(" player{%d ", cpy->player->initial_pos);
		ft_printf("is_alive %d ", cpy->player->is_alive);
		ft_printf("%s ", cpy->player->name);
		ft_printf("%s}\n", cpy->player->path);
		cpy = cpy->next;
	}
	ft_printf("\n");
}

void	print_prcs(t_env *e, t_process *prcs)
{
	ft_printf("-----> PROCESS %d <----- cycle %d <<<<< "
					, prcs->process_id + 1, e->game.cycle_cpt);
	ft_printf(" is at ");
	ft_printf(" %p", prcs);
	ft_printf(" PC [%d]", prcs->registers[PC]);
	ft_printf(" op/cd ( %d", prcs->op_code_to_exec);
	ft_printf(" / %d )\n", prcs->op_cooldown);
}
