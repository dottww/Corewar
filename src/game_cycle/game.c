/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 07:48:58 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/06 15:12:43 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		valid_op_cooldown_finished(t_process *current)
{
	/*de*/ (0)?	ft_printf("checkOP_CD\n"):0;
		/*de*/ (0)?	ft_printf(" op/cd ( %d", current->op_code_to_exec):0;
		/*de*/ (0)?	ft_printf(" / %d )\n", current->op_cooldown):0;
	if (current->op_code_to_exec > 0 && current->op_code_to_exec <= 16)
	{
		if (current->op_cooldown > 0)
		{current->op_cooldown--;
		/*de*/ (0)?	ft_printf("op_cooldown-- = %d\n", current->op_cooldown):0;
			}
		return (current->op_cooldown == 0);
	}
	else
		{/*de*/ (0)?	ft_printf("invalid_OP_CD\n"):0;
		return (0);}
		// return (0);
}

int		are_all_players_dead(t_player player[MAX_PLAYERS], int player_count)
{
	int	i;

	i = 0;
	while (i < player_count)
	{
		if (player[i].is_alive != -1)
			return (0);
		i++;
	}
	return (1);
}

int		is_game_finished(t_env *e)
{
	if ((e->info.process_nb <= 0) || (e->game.max_ctd <= 0))
		return (1);
	return (0);
}

void	claim_winner(t_game *game, t_player *player)
{
	ft_printf("Contestant %d, ", game->last_claimed_live);
	ft_printf("\"%s\", has won !\n"
				, player[game->last_claimed_live - 1].name);
	return ;
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

void		verbose_2_cycle2(int cycle_cpt)
{
	ft_printf(">>>>>>>>>>>>>>>>>>>>>>It is now cycle %lu\n", cycle_cpt);
}

void	game_loop(t_env *e)
{
	t_process *current;

	init_game(e);
	while (!(is_game_finished(e)))
	{
		e->game.cycle_cpt++;
		manage_cycle_to_die(e);
		e->game.ctd_cpt++;
		V_DEBUG ? verbose_2_cycle(e->game.cycle_cpt) : 0;
		/*de*/ (0)?	verbose_2_cycle2(e->game.cycle_cpt) : 0;
		// print_list(e->info);
		current = NULL;
		while (e->info.head && (current = scroll_process(current, &e->info)))
		{
			// if (current->process_id < 10 && current->process_id >5)
			{
			/*de*/ (0)?	ft_printf("-----> PROCESS %d <<<<< cycle %d<<<< ", current->process_id + 1, e->game.cycle_cpt):0;
			// /*de*/ (0)?	ft_printf(" is at ");
			// /*de*/ (0)?	ft_printf(" %p", current);
			/*de*/ (0)?	ft_printf(" PC [%d]", current->registers[PC]):0;
			/*de*/ (0)?	ft_printf(" op/cd ( %d", current->op_code_to_exec):0;
			/*de*/ (0)?	ft_printf(" / %d )\n", current->op_cooldown):0;
			}
			// if (is_not_waiting(current))
			if (current->op_code_to_exec == -1 || current->op_code_to_exec == -2)
				{
					/*de*/ (0)?	ft_printf("Load_CD_or_move1\n"):0;
					get_op_to_exec(e, current);
				}
			else if (valid_op_cooldown_finished(current))
				exec_ops(e, current);
		}
		if (e->dump != -1 && !(is_game_finished(e))
			&& e->dump == e->game.cycle_cpt)
		{
			hexdump(e->arena, 4);
			return ;
		}
	}
	claim_winner(&e->game, e->player);
}
