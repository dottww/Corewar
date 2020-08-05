/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_champs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:31:52 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 19:49:23 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void		exit_error2(char *reason, char *camefrom, char *filepath)
{
	ft_printf("In function <%s> : %s: %s\n", camefrom, reason, filepath);
	exit(0);
}

void			while_cmdline(char **cmd_line, int *cpt, int *champs, int fd)
{
	int i;

	i = *cpt;
	while (cmd_line[i])
	{
		i += (is_n_option(cmd_line[i])) ? 2 : 0;
		(illgal_file(cmd_line[i])) ? exit_error(USAGE, (char *)__func__) : 0;
		if ((fd = is_path_legit(cmd_line[i])) == -1)
			exit_error2(F1, (char *)__func__, cmd_line[i]);
		else
		{
			(*champs)++;
			close(fd);
			fd = 0;
		}
		i++;
	}
	*cpt = i;
}

int				check_all_champs(char **cmd_line, int bounds, int n_count)
{
	int i;
	int fd;
	int champs;

	i = 1;
	fd = 0;
	champs = 0;
	if (is_dump_option(cmd_line[i]))
	{
		i += 2;
		(is_out_of_bounds(i, bounds)) ? exit_error(CMP1, (char *)__func__) : 0;
	}
	while_cmdline(cmd_line, &i, &champs, fd);
	(n_count && n_count != champs) ? exit_error(N1, (char *)__func__) : 0;
	(champs > 4) ? exit_error(CMP2, (char *)__func__) : 0;
	return (champs);
}
