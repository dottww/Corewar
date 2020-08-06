/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:31:58 by weilin            #+#    #+#             */
/*   Updated: 2020/08/06 12:53:39 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

u_int8_t		encoded_typedef(u_int8_t encoded)
{
	if (encoded == BIT_IND)
		return (T_IND);
	else if (encoded == BIT_DIR)
		return (T_DIR);
	else if (encoded == BIT_REG)
		return (T_REG);
	else
		return (false);
}
//ft_skip_bad_ocp_parsing
int				skip_wrong_encoded(t_env *e, t_process *prcs, int nb_arg)
{
	int			i;
	int			skip;
	u_int8_t	encoded;
	u_int8_t	arg_type;

	encoded = e->arena[(prcs->registers[PC] + 1) % MEM_SIZE];
	i = 0;
	skip = 0;
	while (i < nb_arg)
	{
		arg_type = encoded_typedef(encoded & BIT_IND);
		if (arg_type == T_DIR)
			skip += g_ops[prcs->op_code_to_exec].dirsize;
		else if (arg_type != 0)
			skip += arg_type;
		encoded <<= 2;
		i += 1;
	}
	/*de*/ (1)?	ft_printf("skip_wrong_encoded\n"):0;
	V_DEBUG ? verbose_16(e, prcs, skip + 1) : 0;
	move_pc(prcs, skip + 2);
	prcs->op_cooldown = g_ops[prcs->op_code_to_exec].exec_cycle - 1;
	return (false);
}

int				check_arg_type(t_env *e, t_process *prcs)
{
	int			i;
	int			nb_arg;

	nb_arg = g_ops[prcs->op_code_to_exec].nb_arg;
	i = 0;
	while (i < nb_arg)
	{
		if (!(e->args[i][1] & g_ops[prcs->op_code_to_exec].arg_type[i]))
			return (skip_wrong_encoded(e, prcs, nb_arg));
		i++;
	}
	return (true);
}

int				arg_encoding(t_env *e, t_process *prcs)
{
	int			i;
	int			nb_arg;
	u_int8_t	encoded;

	encoded = e->arena[(prcs->registers[PC] + 1) % MEM_SIZE];
	nb_arg = g_ops[prcs->op_code_to_exec].nb_arg;
	i = 0;
	while (i < nb_arg)
	{
		if (!get_arg_type(encoded, prcs, e, i))
			return (false);
		encoded = encoded << 2;
		i++;
	}
	return (check_arg_type(e, prcs));
}

int				init_args(t_env *e, t_process *prcs)
{
	if (g_ops[prcs->op_code_to_exec].encoding)
	{
	/*de*/ (1)?		ft_printf("init_args 1\n"):0;
		if (!arg_encoding(e, prcs))
		{
		/*de*/ (1)?		ft_printf("init_args 2\n"):0;
			return (false);
		}
	}
	else
		e->args[0][1] = T_DIR;
	return (get_arg_value(e, prcs));
}
