/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_get_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:01:55 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/13 01:41:29 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*pft_get_string(va_list ap)
{
	char	*res;
	char	*tmp;

	tmp = va_arg(ap, char*);
	if (tmp == NULL)
		res = ft_strdup("(null)");
	else
		res = ft_strdup(tmp);
	return (res);
}

char	*pft_get_char(va_list ap)
{
	char	*res;

	if (!(res = ft_strnew(1)))
		return (0);
	res[0] = va_arg(ap, int);
	return (res);
}
