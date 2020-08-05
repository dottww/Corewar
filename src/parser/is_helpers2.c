/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_helpers2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:33:56 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 18:17:50 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void		path_err(void)
{
	exit_error("read error of the path after -n option", (char *)__func__);
}

static void		many_n_arg(void)
{
	exit_error("champ after n arg is out of bounds", (char *)__func__);
}

static void		pnbr_verify(int pnbr)
{
	if (pnbr < 1)
		exit_error("n arg can't be inferior to 1", (char *)__func__);
	if (pnbr > 4)
		exit_error("n arg can't be superior to 4", (char *)__func__);
}

static void		arg_not_exist(void)
{
	exit_error("champ after n arg doesn't exist", (char *)__func__);
}

void			is_n_option_legit2(int i, int p_nb[5]
								, int bounds, char **av)
{
	int			pnbr;
	char		*next;
	int			fd;

	fd = 0;
	next = av[i + 1];
	pnbr = 0;
	is_all_numeric(next, "n arg is not a number");
	if (!((ft_strlen(next) == 1) && (pnbr = ft_atoi(next))))
		exit_error("-n number should be between 1 and 4", (char *)__func__);
	pnbr_verify(pnbr);
	if (p_nb[pnbr] == pnbr)
		exit_error("player number already exists", (char *)__func__);
	p_nb[pnbr] = pnbr;
	(is_out_of_bounds(i + 2, bounds)) ? many_n_arg() : 0;
	(!does_arg_exist(av[i + 2])) ? arg_not_exist() : 0;
	((fd = is_path_legit(av[i + 2])) == -1) ? path_err() : 0;
	close(fd);
	fd = 0;
}
