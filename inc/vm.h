/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:05:27 by weilin            #+#    #+#             */
/*   Updated: 2020/07/24 07:59:13 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "op.h"
# include "libft.h"
# include <stdbool.h>

# define PC			0
# define NONE_OP	64

typedef struct			s_process
{
	int					exec_time;
	int					last_live;
	int					op_code;
	bool				loaded;
	int					pid;
	int					arr_cycle;
	bool				carry;
	int					registers[REG_NUMBER + 1];
	struct s_process	*prev;
	struct s_process	*next;
}						t_process;

typedef struct		s_player
{
	t_header		header;
}					t_player;

typedef struct		s_options
{
	int				dump;
	int				verbose;
}					t_option;

/*
**	[args0~2][0=value,1=type] args loaded from ram and stored as int array
**	vm->args[0] is arg 1
**	vm->args[0][0]; //value of r'x', or %'x', or 'x'
**	vm->args[0][1]; //arg_type T_REG T_DIR T_IND
*/

typedef struct		s_vm
{
	unsigned char	ram[MEM_SIZE];
	t_process		**prcs_lst;
	t_player		players[MAX_PLAYERS];
	t_option		options;
	t_process		*arr[1024];
	size_t			cycle;
	int				nb_player;
	int				args[3][2];
	int				cycle_to_die;
	int				die_count[2];
	int				nb_prcs;
	int				nb_max_prcs;
	int				last_prcs;
	int				last_alive;
	int				lives;
	int				no_decrease;
}					t_vm;

typedef struct		s_op
{
	void			(*op_ptr)(t_vm *vm, t_process *prcs);
	char			*op_name;
	size_t			exec_cycle;
	unsigned char	nb_arg;
	unsigned char	encoding;
	unsigned char	dirsize;
	int				arg_type[3];
	char			paddings[6];
}					t_op;

extern t_op			g_ops[16];

void				introduce_player(t_vm *vm);
void				exec_loop(t_vm *vm, t_process *arr[1024]);
void				exec_process(t_vm *vm, t_process *arr[1024], size_t cycle);
void				exec_ops(t_vm *vm, t_process *prcs);
int					init_args(t_vm *vm, t_process *prcs);
int					get_arg_type(uint8_t encoded
								, t_process *prcs, t_vm *vm, int i);
int					get_arg_value(t_vm *vm, t_process *prcs);
void				check_live(t_vm *vm, t_process *arr[1024]);

void				pc_movement(t_vm *vm, t_process *prcs);
void				move_pc(t_process *prcs, int interval);
bool				pc_at_illegal_ram(t_vm *vm, t_process *prcs);
void				verbose_1(t_vm *vm, int pid);
void				verbose_2_cycle(t_vm *vm);
void				verbose_2_delta(t_vm *vm);
void				verbose_8(t_vm *vm, t_process *prcs);
void				verbose_16(t_vm *vm, t_process *prcs, int skip_byte);
void				arr_add(t_vm *vm, t_process *prcs, size_t cycle);
void				arr_assign(t_vm *vm
							, t_process *prcs, size_t cycle, int size);
t_process			*prcs_cpy(t_process *prcs, int pc, int pid);
void				prcs_list_add(t_vm *vm, t_process *prcs);
void				read_ram(t_vm *vm, t_process *prcs, size_t cycle);
void				load_to_prcs(t_vm *vm, t_process *prcs, size_t cycle);
void				int_to_mem(t_vm *vm, int val, int ptr);
int					mem_to_val(t_vm *vm, int *ptr, int size);
int					get_sti_ldi_val(t_vm *vm, t_process *prcs, int arg[2]);
int					get_ind_value(t_vm *vm, int pc, int ind);
int					get_and_or_val(t_vm *vm, int pc
									, int arg[2], t_process *prcs);
void				prcs_lst_slide_up(t_process **prcs_lst, int i, int nb);
void				del_prcs_list(t_vm *vm, t_process *prcs);
void				del_prcs_arr(t_process *arr[1024], t_process *prcs);
void				del_process(t_vm *vm, t_process *arr[1024], t_process *prcs);

void				op_add(t_vm *vm, t_process *prcs);
void				op_aff(t_vm *vm, t_process *prcs);
void				op_and(t_vm *vm, t_process *prcs);
void				op_fork(t_vm *vm, t_process *prcs);
void				op_ld(t_vm *vm, t_process *prcs);
void				op_ldi(t_vm *vm, t_process *prcs);
void				op_lfork(t_vm *vm, t_process *prcs);
void				op_live(t_vm *vm, t_process *prcs);
void				op_lld(t_vm *vm, t_process *prcs);
void				op_lldi(t_vm *vm, t_process *prcs);
void				op_or(t_vm *vm, t_process *prcs);
void				op_st(t_vm *vm, t_process *prcs);
void				op_sti(t_vm *vm, t_process *prcs);
void				op_sub(t_vm *vm, t_process *prcs);
void				op_xor(t_vm *vm, t_process *prcs);
void				op_zjmp(t_vm *vm, t_process *prcs);

#endif
