/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:12:34 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/03 00:05:28 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		free_op(t_op *op)
{
	t_param		*param;
	t_param		*tmp;

	param = op->param;
	while (param)
	{
		free(param->label);
		tmp = param->next;
		free(param);
		param = tmp;
	}
}

static void		free_action(t_env *env)
{
	t_action	*action;
	t_action	*tmp;
	t_op		*op;
	t_op		*tmp2;

	action = env->action;
	while (action)
	{
		free(action->name);
		op = action->op;
		while (op)
		{
			free_op(op);
			tmp2 = op->next;
			free(op->op);
			free(op->des);
			free(op);
			op = tmp2;
		}
		tmp = action->next;
		free(action);
		action = tmp;
	}
}

void			tafreetatoucompris(t_env *env)
{
	if (!env)
		exit(1);
	if (env->champion)
	{
		free(env->champion->name);
		free(env->champion->comment);
		free(env->champion);
	}
	if (env->action)
	{
		free_action(env);
	}
	if (env->file_name)
		free(env->file_name);
	free(env);
}
