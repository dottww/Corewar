/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_verbose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:05:54 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 08:23:13 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		verbose_1(t_vm *vm, int pid)
{
	ft_printf("Player %d (%s) is said to be alive\n",
			pid, vm->players[pid - 1].header.prog_name);
}

void		verbose_2_cycle(t_vm *vm)
{
	ft_printf("It is now cycle %lu\n", vm->cycle + 1);
}

void		verbose_2_delta(t_vm *vm)
{
	ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
}

void		verbose_8(t_vm *vm, t_process *prcs)
{
	ft_printf("Process %d hasn't lived for %lu cycles (CTD %d)\n",
		prcs->pid, vm->cycle - prcs->last_live, vm->cycle_to_die);
}

void		verbose_16(t_vm *vm, t_process *prcs, int skip)
{
	int		i;
	int		pc;

	pc = prcs->registers[PC];
	ft_printf("ADV %d (%#.4x -> %#.4x) ", skip + 1, pc, pc + skip + 1);
	i = 0;
	while (i <= skip)
		ft_printf("%.2x ", vm->ram[(pc + i++) % MEM_SIZE]);
	ft_printf("\n");
}
