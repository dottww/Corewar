/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:35:59 by weilin            #+#    #+#             */
/*   Updated: 2020/08/02 12:51:42 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	op_aff(t_env *e, t_process *prcs)
{
	V_DEBUG ? ft_printf("Aff: %c\n", prcs->registers[e->args[0][0]]) : 0;
	pc_movement(e, prcs);
}
