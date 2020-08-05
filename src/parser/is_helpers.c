/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:33:56 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 16:11:31 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		is_out_of_bounds(int to_check, int bound)
{
	return (to_check > bound);
}

int		is_path_legit(char *path)
{
	return (open(path, O_RDONLY | O_NOFOLLOW));
}

int		is_magic_number_valid(unsigned int magic)
{
	return (magic == COREWAR_EXEC_MAGIC);
}

int		is_program_size_valid(unsigned int prog_size)
{
	return (prog_size < CHAMP_MAX_SIZE);
}

void	is_file_size_valid(int file_size)
{
	if (file_size < (int)sizeof(t_header))
		exit_error("file can't be shorter than header", (char*)__func__);
}
