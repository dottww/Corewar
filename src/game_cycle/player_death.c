/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 09:53:47 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 19:49:11 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void		delete_player_process(int player_id,
	t_fork_utils *forks, t_process_info *info)
{
	t_process		*current;

	current = NULL;
	while ((current = scroll_process(current, info)))
	{
		if (current->player->id == player_id)
			delete_process_direct(&current, info, forks);
	}
}

void			delete_dead_player(int player_count, t_player *player,
	t_fork_utils *forks, t_process_info *info)
{
	int	i;

	i = 0;
	while (i < player_count)
	{
		if (player[i].is_alive == 0)
		{
			delete_player_process(i, forks, info);
			player[i].is_alive = -1;
		}
		i++;
	}
}
