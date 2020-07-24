/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 06:52:17 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 07:26:47 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	hexdump(const unsigned char ram[MEM_SIZE], int width)
{
	int		len;

	len = 0;
	width *= 16;
	while (len < MEM_SIZE)
	{
		if (len % width == 0)
			ft_printf("0x%.4x : ", len);
		if ((len + 1) % width == 0)
			ft_printf("%.2x \n", ram[len]);
		else
			ft_printf("%.2x ", ram[len]);
		len++;
	}
}

void	introduce_player(t_vm *vm)
{
	int			i;
	t_player	*curr;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < vm->nb_player)
	{
		curr = vm->players + i;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			i + 1,
			curr->header.prog_size,
			curr->header.prog_name,
			curr->header.comment);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	(void)argc;
	(void)argv;
	introduce_player(&vm);
	exec_loop(&vm, vm.arr);
	return (0);
}
