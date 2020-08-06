/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:36:07 by cseguier          #+#    #+#             */
/*   Updated: 2020/07/20 14:22:25 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** #ifdef DEBUG
*/

void	exit_error(char *reason, char *camefrom)
{
	ft_printf("In function <%s> : %s\n", camefrom, reason);
	exit(0);
}

/*
** #else
**
** void	exit_error(char *reason, char *camefrom)
** {
** 	(void)reason;
** 	(void)camefrom;
** 	ft_printf("ERROR\n");
** 	exit(0);
** }
**
** #endif
*/
