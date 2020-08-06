/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:32:33 by cseguier          #+#    #+#             */
/*   Updated: 2020/07/20 15:30:58 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_foreach(int *tab, size_t length, void (*f)(int))
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		f(tab[i]);
		i++;
	}
}
