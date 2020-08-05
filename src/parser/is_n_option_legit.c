/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_n_option_legit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:20:54 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 18:17:13 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	n_basic(char **cmd_line, int i, int bounds)
{
	if (ft_strlen(cmd_line[i]) != N_OPTION_LENGTH)
		exit_error("n option malformed", (char *)__func__);
	if (is_out_of_bounds(i + 1, bounds))
		exit_error("n arg is out of bounds", (char *)__func__);
}

void	is_n_option_legit(char **av, int bounds, int *n_count)
{
	int		i;
	int		p_nb[5];
	char	*next;

	i = 1;
	ft_bzero(p_nb, sizeof(int) * 5);
	while (av[i])
	{
		if (is_n_option(av[i]) && av[i + 1] && (next = av[i + 1]))
		{
			n_basic(av, i, bounds);
			if (!does_arg_exist(next))
				exit_error("n arg doesn't exist", (char *)__func__);
			else
			{
				is_n_option_legit2(i, p_nb, bounds, av);
				*n_count += 1;
			}
		}
		i++;
	}
	are_players_numbers_legit(*n_count, p_nb);
}
