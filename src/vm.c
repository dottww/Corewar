/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 08:54:08 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 19:49:45 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			introduce_player(t_env *e)
{
	int			i;
	t_player	*curr;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < e->player_count)
	{
		curr = e->player + i;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			i + 1,
			curr->hdr.prog_size,
			curr->hdr.prog_name,
			curr->hdr.comment);
		i++;
	}
}

void			clean_players_name(t_player *players)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].name)
			free(players[i].name);
		i++;
	}
}

static void		clean_forks(t_env *e)
{
	while (e->forks.qfork->head)
	{
		ft_memdel((void*)&e->forks.qfork->head->pdata);
		de_queue(e->forks.qfork);
	}
	ft_memdel((void*)&e->forks.qfork);
}

static void		clean_process(t_process_info *info)
{
	t_process	*cpy;
	t_process	*tmp;

	cpy = info->head;
	tmp = NULL;
	while (cpy)
	{
		tmp = cpy->next;
		ft_memdel((void*)&cpy);
		cpy = NULL;
		cpy = tmp;
	}
}

int				main(int argc, char **argv)
{
	t_env		e;
	t_options	ops;

	ft_bzero(e.arena, 4096);
	ft_bzero(e.args, sizeof(e.args));
	ft_bzero(e.player, sizeof(t_player) * 4);
	ft_bzero(&ops, sizeof(t_options));
	parse_command_line(argc, argv, &ops);
	handle_champs(&ops, &e);
	cpy_champs_infos(ops.players, e.player, ops.players_count);
	e.player_count = ops.players_count;
	e.dump = ops.cycle_to_stop;
	introduce_player(&e);
	game_loop(&e);
	clean_players_name(e.player);
	clean_forks(&e);
	clean_process(&e.info);
	return (0);
}
