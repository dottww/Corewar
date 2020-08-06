/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_verbose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:05:54 by weilin            #+#    #+#             */
/*   Updated: 2020/08/06 12:53:39 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		verbose_1(t_env *e, int player_id)
{
	ft_printf("Player %d (%s) is said to be alive\n",
			player_id, e->player[player_id - 1].hdr.prog_name);
}

void		verbose_2_cycle(int cycle_cpt)
{
	ft_printf("It is now cycle %lu\n", cycle_cpt);
}

void		verbose_2_delta(int max_ctd)
{
	ft_printf("Cycle to die is now %d\n", max_ctd);
}

void		verbose_8(t_game game, t_process *prcs)
{
	ft_printf("Process %d hasn't lived for %lu cycles (CTD %d)\n",
		prcs->process_id + 1, game.cycle_cpt - prcs->last_cycle_called_live
		, game.max_ctd);
}

void		verbose_16(t_env *e, t_process *prcs, int skip)
{
	int		i;
	int		pc;

	pc = prcs->registers[PC];
	// ft_printf("ADV %d (%#.4x -> %#.4x) ", skip + 1, pc, pc + skip + 1);
	/*or*/ (1)?	ft_printf("ADV %d (%#.4x -> %#.4x) , skip == %d,", skip + 1, pc, pc + skip + 1, skip):0;
	/*or*/ (1)?	0:ft_printf("ADV %d (%#.4x -> %#.4x) ", skip + 1, pc, pc + skip + 1);
	i = 0;
	while (i <= skip)
		ft_printf("%.2x ", e->arena[(pc + i++) % MEM_SIZE]);
	ft_printf("\n");
}
