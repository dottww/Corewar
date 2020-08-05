/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dump_option_legit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:18:56 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 17:04:01 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		get_dump_option(char **cmd_line)
{
	if (is_dump_option(cmd_line[1]))
		return (ft_atoi(cmd_line[2]));
	return (-1);
}

int		is_dump_option(char *to_check)
{
	return (ft_strcmp(to_check, DUMP_OPTION) == 0);
}

int		valid_int(const char *str, int *num)
{
	long	nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	if (!str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if ((nbr > 2147483647 && sign == 1) || sign == -1 ||
		(nbr > 2147483648 && sign == -1) || *str != '\0')
		return (0);
	num != NULL ? *num = (int)(nbr * sign) : 0;
	return (1);
}

void	dump_verify(char *next)
{
	if (!does_arg_exist(next))
		exit_error(D5, (char *)__func__);
	else
	{
		is_all_numeric(next, D6);
		if (!valid_int(next, NULL))
			exit_error(D7, (char *)__func__);
	}
}

void	is_dump_option_legit(char **cmd_line, int bounds)
{
	int		i;
	int		calls;
	char	*current;
	char	*next;

	i = 1;
	calls = 0;
	while (cmd_line[i])
	{
		current = cmd_line[i];
		if (is_dump_option(current) && cmd_line[i + 1])
		{
			next = cmd_line[i + 1];
			(calls > 1) ? exit_error(D1, (char *)__func__) : 0;
			(ft_strlen(current) != DUMP_OPTION_LENGTH)
							? exit_error(D2, (char *)__func__) : 0;
			(i != 1) ? exit_error(D3, (char *)__func__) : 0;
			(is_out_of_bounds(i + 1, bounds))
							? exit_error(D4, (char *)__func__) : 0;
			dump_verify(next);
			calls++;
		}
		i++;
	}
}
