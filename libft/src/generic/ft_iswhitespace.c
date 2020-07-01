/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:59:21 by weilin            #+#    #+#             */
/*   Updated: 2020/06/08 23:00:08 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iswhitespace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
