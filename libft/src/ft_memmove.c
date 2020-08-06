/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:30:00 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:40:43 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	char const	*s;
	char		*d;

	s = src;
	d = dest;
	if (d > s)
	{
		while (1 + (--n))
			d[n] = s[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
