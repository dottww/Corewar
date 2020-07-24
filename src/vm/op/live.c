/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:01:27 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 06:19:55 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	op_verbose_4(t_process *prcs, int args)
{
	ft_printf("P%5d | %s ", prcs->pid, g_ops[prcs->op_code].op_name);
	ft_printf("%d\n", args);
}

void		op_live(t_vm *vm, t_process *prcs)
{
	int		pid;
	int		nb_players;

	nb_players = vm->nb_player;
	pid = vm->args[0][0] * (-1);
	(vm->options.verbose & 4) ? op_verbose_4(prcs, vm->args[0][0]) : 0;
	prcs->last_live = vm->cycle;
	vm->lives += 1;
	if (pid > 0 && pid <= nb_players)
	{
		vm->last_alive = pid;
		(vm->options.verbose & 1) ? verbose_1(vm, pid) : 0;
	}
	pc_movement(vm, prcs);
}
