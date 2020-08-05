/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:13:13 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 21:28:25 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void			get_champs2(char **cmd_line, t_options *ops)
{
	int i;
	int p;

	i = 1;
	p = 0;
	while (p < ops->players_count)
	{
		(is_dump_option(cmd_line[i])) ? i += 2 : 0;
		if (!cmd_line[i] || illgal_file(cmd_line[i]))
			exit_error(USAGE, (char *)__func__);
		else
		{
			ops->players[p + 1].path = cmd_line[i];
			ops->players[p + 1].id = i;
			p++;
		}
		i++;
	}
}

static void		get_champs(char **cmd_line, t_options *ops)
{
	int i;
	int is_dump;

	is_dump = (is_dump_option(cmd_line[1])) ? 2 : 0;
	i = 1 + is_dump;
	while (cmd_line[i])
	{
		ops->players[i - is_dump].path = cmd_line[i];
		ops->players[i - is_dump].id = i - is_dump;
		i++;
	}
}

void			parse_command_line(int argc, char **argv, t_options *ops)
{
	ops->players_count = check_argv(argv, argc);
	ops->cycle_to_stop = get_dump_option(argv);
	ops->n_option = get_n_option(argv, ops);
	if (ops->n_option)
		return ;
	get_champs(argv, ops);
}

void			handle_champs(t_options *ops, t_env *e)
{
	int				code_size;
	void			*player;
	int				i;
	t_file_handler	file;

	code_size = 0;
	player = NULL;
	i = 0;
	while (i < ops->players_count)
	{
		is_file_valid(ops->players[i + 1].path, &file);
		player = handle_player(file, ops->players + i + 1, &code_size);
		if (!player)
		{
			clean_op_player_name(ops->players);
			exit(0);
		}
		write_players(player, e->arena, code_size
					, i * (MEM_SIZE / ops->players_count));
		e->game.last_claimed_live = i + 1;
		free(player - sizeof(t_header));
		i++;
	}
}

void			cpy_champs_infos(t_player *src
							, t_player dest[MAX_PLAYERS], int player_count)
{
	int	i;

	i = 0;
	while (i < player_count)
	{
		dest[i] = src[i + 1];
		dest[i].initial_pos = i * (MEM_SIZE / player_count);
		i++;
	}
}
