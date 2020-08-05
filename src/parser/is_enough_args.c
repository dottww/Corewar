/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_enough_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:17:51 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 17:07:51 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	is_enough_args(int argc)
{
	if (argc < 2)
		exit_error(USAGE, (char *)__func__);
	if (argc > 15)
		exit_error("Too much arguments", (char *)__func__);
}

void	is_all_numeric(char *str, char *reason)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			exit_error(reason, (char *)__func__);
		i++;
	}
}

int		is_n_option(char *to_check)
{
	return ((ft_strcmp(to_check, N_OPTION) == 0));
}

void	are_players_numbers_legit(int n_count, int player_number[5])
{
	while (n_count > -1)
	{
		if (is_out_of_bounds(n_count + 1, 5))
			exit_error(PLN1, (char *)__func__);
		if (player_number[n_count] != n_count)
			exit_error(PLN2, (char *)__func__);
		n_count--;
	}
}

int		get_n_option(char **cmd_line, t_options *ops)
{
	int	i;
	int	player_id;
	int	set;

	i = 0;
	set = 0;
	while (cmd_line[i])
	{
		if (is_n_option(cmd_line[i]))
		{
			set = 1;
			player_id = ft_atoi(cmd_line[i + 1]);
			ops->players[player_id].path = cmd_line[i + 2];
			ops->players[player_id].id = player_id;
		}
		i++;
	}
	return (set);
}
