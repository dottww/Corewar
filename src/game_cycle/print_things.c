/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:17:13 by cseguier          #+#    #+#             */
/*   Updated: 2020/07/23 13:17:15 by cseguier         ###   ########.fr       */
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
