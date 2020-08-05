/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   does_arg_exist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:15:00 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 23:25:11 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		does_arg_exist(char *arg)
{
	return (arg[0]);
}

void	does_all_args_exists(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (!does_arg_exist(argv[i]))
			exit_error("Arg doesnt exist", (char *)__func__);
		i++;
	}
}

int		check_argv(char **argv, int argc)
{
	int	n_count;

	n_count = 0;
	is_enough_args(argc);
	does_all_args_exists(argv);
	are_options_legit(argv);
	is_n_option_legit(argv, argc, &n_count);
	is_dump_option_legit(argv, argc);
	return (check_all_champs(argv, argc, n_count));
}
