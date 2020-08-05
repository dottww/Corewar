/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:17:16 by weilin            #+#    #+#             */
/*   Updated: 2020/08/02 19:49:19 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

t_game_op	g_ops[17] =
{
	{NULL, "", 0, 0, 0, 0, {0}, {0}},
	{&op_live, "live", 10, 1, 0, 4, {T_DIR}, {0}},
	{&op_ld, "ld", 5, 2, 1, 4, {T_DIR | T_IND, T_REG}, {0}},
	{&op_st, "st", 5, 2, 1, 4, {T_REG, T_IND | T_REG}, {0}},
	{&op_add, "add", 10, 3, 1, 4, {T_REG, T_REG, T_REG}, {0}},
	{&op_sub, "sub", 10, 3, 1, 4, {T_REG, T_REG, T_REG}, {0}},
	{&op_and, "and", 6, 3, 1, 4,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, {0}},
	{&op_or, "or", 6, 3, 1, 4,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, {0}},
	{&op_xor, "xor", 6, 3, 1, 4,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, {0}},
	{&op_zjmp, "zjmp", 20, 1, 0, 2, {T_DIR}, {0}},
	{&op_ldi, "ldi", 25, 3, 1, 2,
		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, {0}},
	{&op_sti, "sti", 25, 3, 1, 2,
		{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, {0}},
	{&op_fork, "fork", 800, 1, 0, 2, {T_DIR}, {0}},
	{&op_lld, "lld", 10, 2, 1, 4, {T_DIR | T_IND, T_REG}, {0}},
	{&op_lldi, "lldi", 50, 3, 1, 2,
		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, {0}},
	{&op_lfork, "lfork", 1000, 1, 0, 2, {T_DIR}, {0}},
	{&op_aff, "aff", 2, 1, 1, 4, {T_REG}, {0}}
};
