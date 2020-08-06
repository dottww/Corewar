/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:37:45 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 12:20:46 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static t_qnode	*new_node(void *pdata)
{
	t_qnode	*cpy;

	if (!(cpy = ft_memalloc(sizeof(t_qnode))))
		return (NULL);
	cpy->pdata = pdata;
	cpy->prev = NULL;
	cpy->next = NULL;
	return (cpy);
}

static void		set_node_in_place
	(t_qnode *place_found, t_qnode *to_enq, t_qnode *cpy, t_queue *q)
{
	if (!(place_found))
	{
		to_enq->prev = cpy;
		cpy->next = to_enq;
		q->tail = to_enq;
	}
	else
	{
		if (place_found == q->head)
			q->head = to_enq;
		else
			place_found->prev->next = to_enq;
		to_enq->prev = place_found->prev;
		place_found->prev = to_enq;
		to_enq->next = place_found;
	}
}

void			en_queue_with_priority
	(t_queue *q, void *pdata, t_qnode *(*priority)(t_qnode*, t_qnode*))
{
	t_qnode *cpy;
	t_qnode	*to_enq;
	t_qnode	*place_found;

	place_found = NULL;
	to_enq = new_node(pdata);
	if (q->head == NULL && q->tail == NULL)
	{
		q->head = to_enq;
		q->tail = to_enq;
		return ;
	}
	cpy = q->head;
	while ((!(place_found = priority(to_enq, cpy)) && (cpy != q->tail)))
		cpy = cpy->next;
	set_node_in_place(place_found, to_enq, cpy, q);
}

void			en_queue(t_queue *q, void *pdata)
{
	t_qnode	*cpy;

	cpy = new_node(pdata);
	if (q->tail == NULL)
	{
		q->head = cpy;
		q->tail = cpy;
		return ;
	}
	q->tail->next = cpy;
	cpy->prev = q->tail;
}

/*
** Dont forget to free q after the program
*/

void			de_queue(t_queue *q)
{
	t_qnode	*cpy;

	cpy = q->head;
	if (q->head == NULL)
		return ;
	if (q->head->next == NULL && q->tail->prev == NULL)
	{
		q->head = NULL;
		q->tail = NULL;
	}
	else if (q->head == NULL)
		q->tail = NULL;
	else
	{
		q->head = q->head->next;
		q->head->prev = NULL;
	}
	free(cpy);
}
