/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:59:14 by cseguier          #+#    #+#             */
/*   Updated: 2020/07/23 12:59:40 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_queue			*create_queue(void)
{
	t_queue	*q;

	if (!(q = (t_queue*)ft_memalloc(sizeof(t_queue))))
		return (NULL);
	q->head = NULL;
	q->tail = NULL;
	return (q);
}
