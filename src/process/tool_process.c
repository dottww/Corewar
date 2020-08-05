/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 19:35:24 by weilin            #+#    #+#             */
/*   Updated: 2020/08/02 19:49:32 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	create_process_data_from_start(int id, t_player *player
										, t_process *process)
{
	process->process_id = id;
	process->op_code_to_exec = -1;
	process->op_cooldown = 0;
	process->carry = 0;
	process->player = player;
	ft_bzero(process->registers, sizeof(int) * 17);
	process->registers[PC] = player->initial_pos;
	process->registers[1] = -player->id;
	process->prev = NULL;
	process->next = NULL;
}

void	clean(t_process *process)
{
	process->process_id = 0;
	process->op_code_to_exec = 0;
	process->op_cooldown = 0;
	process->carry = 0;
	process->player = NULL;
	process->executed_live_in_this_check = 0;
	process->last_cycle_called_live = 0;
	ft_bzero(process->registers, sizeof(int) * (REG_NUMBER + 1));
	process->prev = NULL;
	process->next = NULL;
}
