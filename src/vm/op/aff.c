/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:59 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 06:19:55 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_aff(t_vm *vm, t_process *prcs)
{
	if (vm->options.verbose & 4)
		ft_printf("Aff: %c\n", prcs->registers[vm->args[0][0]]);
	pc_movement(vm, prcs);
}
