/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 09:06:54 by cseguier          #+#    #+#             */
/*   Updated: 2020/08/07 14:10:29 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/includes/ft_printf.h"
# include <stdbool.h>

# define V_DEBUG			false
# define USAGE	"Usage: ./corewar [-dump N -n pid] <champion.cor>"

# define N1		"when using -n option, you should assign it for each player"

# define F1		"open couldn't open the file"

# define CMP1 	"You must give at least one champ"
# define CMP2 	"you can't give more than 4 champs"

# define D1		"dump option must be called once"
# define D2		"dump option malformed"
# define D3		"if dump option is specified, it must be first"
# define D4		"dump arg is out of bounds"
# define D5		"dump arg doesn't exist"
# define D6		"dump arg is not a number"
# define D7		"dump arg is negative or out of integer range"

# define HDR1	"magic number invalid"
# define HDR2	"prog_size bigger than 682 bytes"
# define HDR3	"code size differ from what is header says"

# define PLN1	"for some obscure reasons, the number of n_count > 4"
# define PLN2	"You must not assign numbers superior to the number of players"

/*
** GENERAL SPECS
*/

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			4

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			4096
# define IDX_MOD			512
# define CHAMP_MAX_SIZE		682

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define T_REG				1
# define T_IND				2
# define T_DIR				4
# define T_LAB				8

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

# define OP_FORK			12
# define OP_LFORK			15
# define FORK				0
# define LFORK				1

# define PC					0

# define FROM_LAST			0
# define FROM_FIRST			1

# define DUMP_OPTION_LENGTH 5
# define DUMP_OPTION		"-dump"

# define N_OPTION_LENGTH	2
# define N_OPTION			"-n"

# define NONE_OP			64

# define BIT_REG			64
# define BIT_DIR			128
# define BIT_IND			192

# define PROG_NAME_LENGTH	128
# define COMMENT_LENGTH		2048
# define COREWAR_EXEC_MAGIC	0xea83f3

/*
** STRUCTS
*/

typedef struct	s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}				t_header;

typedef char	t_arg_type;

/*
** ctd_cpt  		: Counter that increases each cycle until it meets the value
**						of tmporary CTD criteria.
** ctd_tmp_criteria	: Temporary criteria for Cycle_To_Die counter.
** max_ctd			: Max Cycle_To_Die value for assigning ctd_tmp_criteria, it
**						decreases by CYCLE_DELTA when meets certain conditions.
** ctd_maxcheck_cpt	: Counter that increases when not enough op_live executed.
** live_cpt			: Counter for op_times execution for this check period.
** cycle_cpt		: Counter for game cycle, never decreases.
** last_claimed_live: The last player that was claimed alive successfully.
*/

typedef struct	s_game
{
	int		max_ctd;
	int		ctd_cpt;
	int		ctd_tmp_criteria;
	int		ctd_maxcheck_cpt;
	int		live_cpt;
	int		cycle_cpt;
	int		last_claimed_live;
}				t_game;

typedef struct	s_player
{
	t_header	hdr;
	int			id;
	int			initial_pos;
	int			is_alive;
	char		*path;
	char		*name;
}				t_player;

/*
** last_cycle_called_live		: Last cycle that the process executed op_live.
** executed_live_in_this_check	: Indicates whether the process executed op_live
**									during this check period.
*/

typedef struct	s_process
{
	t_player			*player;
	int					registers[REG_NUMBER + 1];
	struct s_process	*prev;
	struct s_process	*next;
	int					process_id;
	int					op_code_to_exec;
	int					op_cooldown;
	int					carry;
	int					last_cycle_called_live;
	int					executed_live_in_this_check;
}				t_process;

typedef struct	s_process_info
{
	t_process	*head;
	t_process	*tail;
	int			process_nb;
	int			process_id_cpt;
}				t_process_info;

typedef struct	s_qfork_data
{
	t_player	*player;
	int			cooldown;
	int			process_id;
	int			pc;
}				t_qfork_data;

typedef struct	s_fork_utils
{
	t_queue	*qfork;
	int		fork_nb;
}				t_fork_utils;

typedef struct	s_options
{
	t_player	players[7];
	int			players_count;
	int			cycle_to_stop;
	int			n_option;
}				t_options;

typedef struct	s_file_handler
{
	int			fd;
	int			size;
}				t_file_handler;

typedef struct	s_env
{
	t_player		player[MAX_PLAYERS];
	unsigned char	arena[MEM_SIZE];
	int				args[3][2];
	int				player_count;
	t_process_info	info;
	t_fork_utils	forks;
	t_game			game;
	int				dump;
	void			*void_arena;
}				t_env;

typedef struct	s_game_op
{
	void			(*op_ptr)(t_env *e, t_process *current);
	char			*op_name;
	size_t			exec_cycle;
	unsigned char	nb_arg;
	unsigned char	encoding;
	unsigned char	dirsize;
	int				arg_type[3];
	char			paddings[6];
}				t_game_op;

extern t_game_op	g_ops[17];

/*
** PROCESS LINKED LIST
*/

void			free_list(t_process_info *i);
t_process		*get_process_from(int f, int id, t_process_info i);
void			delete_process_direct(t_process **d, t_process_info *i,
								t_fork_utils *forks);
void			delete_process_from_id(int id, t_process_info *i,
								t_fork_utils *forks);
t_process		*add_new_process(t_process to_add, t_process_info *i);
t_process		create_process_data(t_qnode *f);
t_process		*scroll_process(t_process *c, t_process_info *i);
void			create_process_data_from_start(int id, t_player *player
										, t_process *process);
void			clean(t_process *process);
int				is_not_waiting(t_process *current);
void			init_processes(t_env *e);

/*
** FORK LOGISTIC
*/

void			add_fork_to_queue(t_fork_utils *f, t_process *c, int i);
void			print_forks(t_fork_utils *f);

/*
** GAME CYCLE
*/

void			init_game(t_env *e);
void			game_loop(t_env *e);
void			delete_dead_process(t_env *e);
void			delete_dead_player(int player_count, t_player *player,
					t_fork_utils *forks, t_process_info *info);
int				are_all_players_dead(t_player p[MAX_PLAYERS], int ps);
void			pc_movement(t_env *e, t_process *prcs);
void			move_pc(t_process *prcs, int interval);
void			exec_ops(t_env *e, t_process *prcs);
long			get_and_or_val(t_env *e, int pc, u_int32_t arg[2], t_process *prcs);
int				init_args(t_env *e, t_process *prcs);
int				mem_to_val(t_env *e, int *ptr, int size);
int				mem_to_ind(t_env *e, int pc, short indirect);
int				get_sti_ldi_val(t_env *e, t_process *prcs, u_int32_t arg[2]);
void			int_to_mem(t_env *e, int val, int ptr);
int				get_arg_value(t_env *e, t_process *prcs);
int				get_arg_type(u_int8_t encoded, t_process *prcs,
					t_env *e, int i);
void			hexdump(const unsigned char ram[MEM_SIZE], int width);
int				valid_int(const char *str, int *num);

/*
** PARSER AND STARTUP
*/

int				check_argv(char **argv, int argc);
void			parse_command_line(int argc, char **argv, t_options *ops);
int				is_champ_valid(t_header *header, int total_size);
int				open_champ(char *path);
int				get_file_size(int champ_fd);
void			handle_sys_ops(char *path, t_file_handler *file);
void			is_file_valid(char *path, t_file_handler *meta);
void			*create_player(int size, int champ_fd);
void			*handle_player(t_file_handler f, t_player *pl, int *c);
int				is_out_of_bounds(int to_check, int bound);
int				is_path_legit(char *path);
int				is_magic_number_valid(unsigned int magic);
int				is_program_size_valid(unsigned int prog_size);
void			is_file_size_valid(int file_size);
int				is_n_option(char *to_check);
void			are_players_numbers_legit(int n_count, int player_number[5]);
int				get_n_option(char **cmd_line, t_options *ops);
void			is_n_option_legit(char **cmd_line, int bounds, int *n_count);
void			is_n_option_legit2(int i, int p_nb[5], int bounds, char **av);
int				get_dump_option(char **cmd_line);
int				is_dump_option(char *to_check);
void			is_dump_option_legit(char **cmd_line, int bounds);
int				check_all_champs(char **cmd_line, int bounds, int n_count);
void			write_players(unsigned char *p, unsigned char *a, int x, int s);
void			create_arena(t_env *e);
void			is_enough_args(int argc);
int				does_arg_exist(char *arg);
void			does_all_args_exists(char **argv);
void			are_options_legit(char **cmd_line);
void			is_all_numeric(char *str, char *reason);
void			handle_champs(t_options *ops, t_env *e);
void			cpy_champs_infos(t_player *s, t_player d[MAX_PLAYERS], int p);
int				illgal_file(char *s);
void			get_op_to_exec(t_env *e, t_process *current);
void			manage_cycle_to_die(t_env *e);
void			reset_alive_status(t_env *e);
void			clean_players_name(t_player *players);
void			clean_op_player_name(t_player *players);
int				valid_op_cooldown_finished(t_process *current);
int				skip_arg(t_env *e, int skip
					, const int arg, const u_int8_t op_code);
u_int32_t		char4_to_int(unsigned char tab[4]);

/*
** G OPS
*/

void			op_add(t_env *e, t_process *prcs);
void			op_aff(t_env *e, t_process *prcs);
void			op_and(t_env *e, t_process *prcs);
void			op_fork(t_env *e, t_process *prcs);
void			op_ld(t_env *e, t_process *prcs);
void			op_ldi(t_env *e, t_process *prcs);
void			op_lfork(t_env *e, t_process *prcs);
void			op_live(t_env *e, t_process *prcs);
void			op_lld(t_env *e, t_process *prcs);
void			op_lldi(t_env *e, t_process *prcs);
void			op_or(t_env *e, t_process *prcs);
void			op_st(t_env *e, t_process *prcs);
void			op_sti(t_env *e, t_process *prcs);
void			op_sub(t_env *e, t_process *prcs);
void			op_xor(t_env *e, t_process *prcs);
void			op_zjmp(t_env *e, t_process *prcs);

void			verbose_1(t_env *e, int player_id);
void			verbose_2_cycle(int cycle_cpt);
void			verbose_2_delta(int cycle_max);
void			verbose_8(t_game game, t_process *prcs);
void			verbose_16(t_env *e, t_process *prcs, int skip_byte);

/*
** MISCELLANEOUS UTILS
*/

unsigned short	swap_ushort(unsigned short val);
short			swap_short(short val);
unsigned int	swap_uint(unsigned int val);
int				swap_int(int val);

#endif
