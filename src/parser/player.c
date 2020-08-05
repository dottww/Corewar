/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:37:18 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 21:30:02 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	handle_sys_ops(char *path, t_file_handler *file)
{
	int	champ_fd;
	int	file_size;

	champ_fd = open_champ(path);
	if (champ_fd == -1)
		exit_error("Failed on file opening", (char*)__func__);
	file_size = get_file_size(champ_fd);
	if (file_size <= 0)
		exit_error("Empty file", (char*)__func__);
	lseek(champ_fd, 0, SEEK_SET);
	file->fd = champ_fd;
	file->size = file_size;
}

void	is_file_valid(char *path, t_file_handler *meta)
{
	handle_sys_ops(path, meta);
	is_file_size_valid(meta->size);
}

void	*create_player(int size, int champ_fd)
{
	void		*player;

	if (!(player = ft_memalloc(size)))
		exit_error("Malloc Failed", (char*)__func__);
	if (player == NULL)
		exit_error("malloc failed", (char*)__func__);
	if (read(champ_fd, player, size) < 0)
		exit_error("something unexpected happened", (char*)__func__);
	close(champ_fd);
	return (player);
}

void	clean_op_player_name(t_player *players)
{
	int i;

	i = 1;
	while (i < 5)
	{
		if (players[i].name)
			free(players[i].name);
		i++;
	}
	exit(0);
}

void	*handle_player(t_file_handler file, t_player *pl, int *code_size)
{
	t_header	*header;
	void		*player;

	player = create_player(file.size, file.fd);
	header = player;
	if (!is_champ_valid(header, file.size))
	{
		ft_printf("in file %s.cor\n", header->prog_name);
		free(player);
		return (NULL);
	}
	if (ft_strlen(header->prog_name) > PROG_NAME_LENGTH)
		exit_error("Champ name too big", (char*)__func__);
	pl->name = ft_strdup(header->prog_name);
	*code_size = swap_uint(header->prog_size);
	ft_memcpy(pl->hdr.prog_name, header->prog_name, PROG_NAME_LENGTH + 1);
	pl->hdr.prog_size = *code_size;
	ft_memcpy(pl->hdr.comment, header->comment, COMMENT_LENGTH + 1);
	return (player + sizeof(t_header));
}
