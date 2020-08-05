/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:38:36 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 21:29:27 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	write_players(unsigned char *player, unsigned char *arena
						, int prog_size, int start)
{
	int				i;
	unsigned char	*map;

	i = 0;
	map = arena + start;
	while (i < prog_size)
	{
		map[i] = player[i];
		i++;
	}
}

int		return_error(char *reason, char *camefrom)
{
	ft_printf("In function <%s> : %s ", camefrom, reason);
	return (0);
}

int		is_champ_valid(t_header *header, int total_size)
{
	if (!is_magic_number_valid(swap_uint(header->magic)))
		return (return_error(HDR1, (char*)__func__));
	if (!is_program_size_valid(swap_uint(header->prog_size)))
		return (return_error(HDR2, (char*)__func__));
	if (swap_uint(header->prog_size) + sizeof(t_header)
											!= (unsigned int)total_size)
		return (return_error(HDR3, (char*)__func__));
	return (1);
}

int		open_champ(char *path)
{
	return (open(path, O_RDONLY));
}

int		get_file_size(int champ_fd)
{
	return (lseek(champ_fd, 0, SEEK_END));
}
