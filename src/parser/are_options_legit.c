/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_options_legit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:22:46 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 17:05:40 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		illgal_file(char *s)
{
	int	len;

	if (!s)
		return (1);
	len = ft_strlen(s);
	if (len < 4)
		return (1);
	if (!ft_strcmp(&s[len - 4], ".cor"))
		return (0);
	else
		return (1);
}

void	are_options_legit(char **cmd_line)
{
	int			i;
	char		*current;

	i = 1;
	while (cmd_line[i])
	{
		current = cmd_line[i];
		if (current[0] == '-')
		{
			if (is_dump_option(current))
			{
				if (ft_strlen(current) != DUMP_OPTION_LENGTH)
					exit_error("dump option malformed", (char *)__func__);
			}
			else if (is_n_option(current))
			{
				if (ft_strlen(current) != N_OPTION_LENGTH)
					exit_error("n option malformed", (char *)__func__);
			}
			else
				exit_error("option must be n or dump", (char *)__func__);
		}
		i++;
	}
}
