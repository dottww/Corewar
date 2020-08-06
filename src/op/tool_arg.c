/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:59:18 by weilin            #+#    #+#             */
/*   Updated: 2020/08/06 13:42:19 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	int_to_mem(t_env *e, int val, int ptr)
{
	int			i;

	i = 0;
	ptr %= MEM_SIZE;
	ptr = (ptr >= 0 ? ptr : MEM_SIZE + ptr);
	while (i < 4)
	{
		e->arena[ptr % MEM_SIZE] = val;
		ptr = (ptr > 0 ? ptr - 1 : MEM_SIZE + (ptr - 1));
		val = val >> 8;
		i += 1;
	}
}

int		mem_to_val(t_env *e, int *ext_ptr, int size)
{
	int			i;
	u_int32_t	val;
	// u_int8_t	val8;
	int			ptr;

	ptr = (*ext_ptr) % MEM_SIZE;
	val = 0;
	i = 0;
	while (i < size)
	{
		ptr = (ptr >= 0 ? ptr : MEM_SIZE + ptr);
		// if (size < 3)
		// 	val8 |= e->arena[ptr % MEM_SIZE];
		val |= e->arena[ptr % MEM_SIZE];
		if (i < size - 1)
			val <<= 8;
		ptr++;
		i++;
	}

	*ext_ptr = ptr;
	return (val);
}

int		check_arg_value(t_env *e, t_process *prcs)
{
	int		i;
	int		nb_arg;
/*de*/ (0)?	ft_printf("init_args 4\n"):0;
	nb_arg = g_ops[prcs->op_code_to_exec].nb_arg;
	i = 0;
	while (i < nb_arg)
	{
		if (e->args[i][1] == T_REG &&
			(e->args[i][0] <= 0 || e->args[i][0] >= 17))
		{
		/*de*/ (0)?		ft_printf("init_args 5\n"):0;
		/*de*/ (0)?		ft_printf("T_REG_ERROR[%d], op/cd [%d/%d], cycle %d\n",e->args[i][0], prcs->op_code_to_exec, prcs->op_cooldown, e->game.cycle_cpt):0;
			pc_movement(e, prcs);
			// prcs->op_cooldown = 0;
			// prcs->op_code_to_exec = -2;
			return (false);
		}
		i++;
	}
	return (true);
}

// int		get_arg_value(t_env *e, t_process *prcs)
// {
// 	int		i;
// 	int		ptr;
// 	int		nb_arg;

// 	nb_arg = g_ops[prcs->op_code_to_exec].nb_arg;
// 	ptr = (prcs->registers[PC] + 1 + g_ops[prcs->op_code_to_exec].encoding)
// 																% MEM_SIZE;
// 	i = 0;
// 	while (i < nb_arg)
// 	{
// 		if (e->args[i][1] == T_REG)
// 			e->args[i][0] = mem_to_val(e, &ptr, T_REG);
// 		else if (e->args[i][1] == T_IND)
// 			e->args[i][0] = mem_to_val(e, &ptr, T_IND);
// 		else if (e->args[i][1] == T_DIR)
// 			e->args[i][0] = mem_to_val(e, &ptr
// 			, g_ops[prcs->op_code_to_exec].dirsize);

// /*de*/ (0)?		ft_printf("pc[%d],i=%d, e->args[%d][0]=%d\n",prcs->registers[PC],i,i,e->args[i][0]):0;
// 		i++;
// 	}
// /*de*/ (0)?		ft_printf("init_args 3\n"):0;
// 	return (check_arg_value(e, prcs));
// }
int		ft_convert_ram_to_args(t_env *e, int end, int *i_ptr, int j)
{
	int	start;

	start = *i_ptr;
/*de*/ (0)?		ft_printf("\nft_convert_ram_to_args, args[%d][0], %d to %d \n",j,start,end):0;
	while (start < end)
	{
		e->args[j][0] |= e->arena[start % MEM_SIZE];
		if (start < end - 1)
			e->args[j][0] <<= 8;
/*de*/ (0)?		ft_printf("i=%d,args[%d][0]=%d\n",start,j,e->args[j][0]):0;
		start += 1;
	}
	// ft_printf("e[%d],i=%d, e->args[%d][0]=%d\n",e->,prcs->registers[PC],i,i,e->args[i][0]);
	*i_ptr = start;
	return (true);
}

int		get_arg_value(t_env *e, t_process *prcs)
{
	int		i;
	int		ptr;
	int		nb_arg;

	nb_arg = g_ops[prcs->op_code_to_exec].nb_arg;
	ptr = (prcs->registers[PC] + 1 + g_ops[prcs->op_code_to_exec].encoding)
																% MEM_SIZE;
	i = 0;
	while (i < nb_arg)
	{
		if (e->args[i][1] == T_REG)
			ft_convert_ram_to_args(e, ptr + 1, &ptr, i);
		else if (e->args[i][1] == T_IND)
			ft_convert_ram_to_args(e, ptr + 2, &ptr, i);
			// e->args[i][0] = mem_to_val(e, &ptr, T_IND);
		else if (e->args[i][1] == T_DIR)
			ft_convert_ram_to_args(e, ptr +
			g_ops[prcs->op_code_to_exec].dirsize, &ptr, i);
			// e->args[i][0] = mem_to_val(e, &ptr
			// , g_ops[prcs->op_code_to_exec].dirsize);

/*de*/ (0)?		ft_printf("get_arg_value,pc[%d],i=%d, e->args[%d][0]=%d\n",prcs->registers[PC],i,i,e->args[i][0]):0;
		i++;
	}
/*de*/ (0)?		ft_printf("init_args 3\n"):0;
	return (check_arg_value(e, prcs));
}

int		get_arg_type(u_int8_t encoded, t_process *prcs, t_env *e, int i)
{
	u_int8_t	mask;
	
	mask = encoded & BIT_IND;
/*de*/ (0)?		ft_printf("init_args 1->get_arg_type, mask=%d\n", mask):0;
	if (mask == BIT_REG
				&& (g_ops[prcs->op_code_to_exec].arg_type[i] & T_REG) != 0)
		e->args[i][1] = T_REG;
	else if (mask == BIT_IND
				&& (g_ops[prcs->op_code_to_exec].arg_type[i] & T_IND) != 0)
		e->args[i][1] = T_IND;
	else if (mask == BIT_DIR
				&& (g_ops[prcs->op_code_to_exec].arg_type[i] & T_DIR) != 0)
		e->args[i][1] = T_DIR;
	else
		return (false);
	return (true);
}
// int		get_arg_type(u_int8_t encoded, t_process *prcs, t_env *e, int i)
// {
// 	u_int8_t	mask;
	
// 	mask = encoded & BIT_IND;
// 	int k=0;
// 	int h=0;
// {
// 	/*de*/ (0)?		ft_printf("init_args 1->get_arg_type, encoded[%d],mask=%d\n", encoded,mask):0;

// }
// 	// if (mask == BIT_REG
// 	// 			&& (g_ops[prcs->op_code_to_exec].arg_type[i] & T_REG) != 0)
// 	// 	e->args[i][1] = T_REG;
// 	// else if (mask == BIT_IND
// 	// 			&& (g_ops[prcs->op_code_to_exec].arg_type[i] & T_IND) != 0)
// 	// 	e->args[i][1] = T_IND;
// 	// else if (mask == BIT_DIR
// 	// 			&& (g_ops[prcs->op_code_to_exec].arg_type[i] & T_DIR) != 0)
// 	// 	e->args[i][1] = T_DIR;
// 	if ((k = (mask == BIT_REG))
// 				&& (h = (g_ops[prcs->op_code_to_exec].arg_type[i] & T_REG)) != 0)
// 		e->args[i][1] = T_REG;
// 	else if ((k = (mask == BIT_IND)) 
// 				&& (h = (g_ops[prcs->op_code_to_exec].arg_type[i] & T_IND)) != 0)
// 		e->args[i][1] = T_IND;
// 	else if ((k = (mask == BIT_DIR)) 
// 				&& (h = (g_ops[prcs->op_code_to_exec].arg_type[i] & T_DIR)) != 0)
// 		e->args[i][1] = T_DIR;
// 	else
// {/*de*/ (0)?		ft_printf("init_args 1->get_arg_type, false e->args[i][1]=%d\n", e->args[i][1]):0;
// 		return (false);}
// 		// return (false);
// 	return (true);
// }

