/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 23:00:28 by weilin            #+#    #+#             */
/*   Updated: 2020/08/06 14:22:28 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		get_ind_value(t_env *e, int pc, short ind)
{
	int	val;
	int	ptr;

	ptr = (pc + (ind % IDX_MOD)) % MEM_SIZE;
	val = mem_to_val(e, &ptr, 4);
	return (val);
}

// int		get_ind_value(t_env *e, int pc, short ind)
// {
// 	int	val;
// 	int	ptr;
// 	int move;
// 	// int move2;
	
// 	/*or*/ (0)?ft_printf("pc=%d \n", pc):0;
// 	/*or*/ (0)?ft_printf("ind=%d \n", ind):0;
	
// 	move = (ind % IDX_MOD);
// 	/*or*/ (0)?ft_printf("ind %% IDX_MOD(%d)=move=%d \n", move, IDX_MOD):0;

// 	ptr = pc + move;
// 	/*or*/ (0)?ft_printf("pc+move=%d \n", ptr):0;
// 	if (ptr < 0)
// 		ptr = MEM_SIZE + (move % MEM_SIZE);
// 	else
// 		ptr = ptr % MEM_SIZE;
// 	/*or*/ (0)?ft_printf("correct pc=%d \n", ptr):0;
// 	// ptr = (pc + (ind % IDX_MOD)) % MEM_SIZE;
// 	// 		/*or*/ (0)?ft_printf("e->args[0]/[1]=[%d]/[%d] ", e->args[0],e->args[1]):0;
// 	// 		/*or*/ (0)?ft_printf("arg1/2=%d/%d\n", arg_1,arg_2):0;
// 	val = mem_to_val(e, &ptr, 2);
// 	/*or*/ (0)?ft_printf("val=%d \n", val):0;
// 	return (val);
// }
uint32_t		ft_convert_to_int(unsigned char tab[4])
{
	uint32_t	result;
	int			index;

	result = 0;
	index = 0;
	while (index < 4)
	{
		result |= tab[index];
		if (index < 3)
			result <<= 8;
		index++;
	}
	return (result);
}
int				ft_value_from_address(t_env *e, int pc, short indirect)
{
	int			param;
	long		pos;
	uint8_t		tab[4];

	pos = (pc + (indirect % IDX_MOD)) % MEM_SIZE; ///////pending_move_pc
	tab[0] = e->arena[pos++ % MEM_SIZE];
	tab[1] = e->arena[pos++ % MEM_SIZE];
	tab[2] = e->arena[pos++ % MEM_SIZE];
	tab[3] = e->arena[pos % MEM_SIZE];
	param = ft_convert_to_int(tab);
	return (param);
}
// long ft_parameter_recover_value(t_vm *vm, size_t pc,	uint32_t tab[2], t_process *process)
long		get_and_or_val(t_env *e, int pc, uint32_t arg[2], t_process *prcs)
{
	if (arg[1] == T_IND)
		return (ft_value_from_address(e, pc, arg[0]));//ft_value_from_address
	else if (arg[1] == T_REG)
		return (prcs->registers[arg[0]]);
	return (arg[0]);
}

// int		get_and_or_val(t_env *e, int pc, int arg[2], t_process *prcs)
// {
// 	if (arg[1] == T_IND)
// 		return (get_ind_value(e, pc, arg[0]));
// 	else if (arg[1] == T_REG)
// 		return (prcs->registers[arg[0]]);
// 	return (arg[0]);
// }

int		get_sti_ldi_val(t_env *e, t_process *prcs, int arg[2])
{
	int	val;

	val = arg[0];
	if (arg[1] == T_DIR)
		val = (short)arg[0];
	else if (arg[1] == T_REG)
		val = prcs->registers[val];
	else if (arg[1] == T_IND)
		val = get_ind_value(e, prcs->registers[PC], val);
	return (val);
}
