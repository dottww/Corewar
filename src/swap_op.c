/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:48:30 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/02 19:49:42 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Byte swap unsigned short
*/

unsigned short	swap_ushort(unsigned short val)
{
	return (val << 8) | (val >> 8);
}

/*
** Byte swap short
*/

short			swap_short(short val)
{
	return (val << 8) | ((val >> 8) & 0xFF);
}

/*
** Byte swap unsigned int
*/

unsigned int	swap_uint(unsigned int val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

/*
** Byte swap int
*/

int				swap_int(int val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | ((val >> 16) & 0xFFFF);
}
