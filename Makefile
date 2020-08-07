# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weilin <weilin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 01:31:01 by cseguier          #+#    #+#              #
#    Updated: 2020/08/07 02:09:59 by weilin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
# .SILENT:

NAME = corewar

LIBFT = libft/libftprintf.a

FILE = vm.c swap_op.c \
	add.c aff.c and.c exec.c g_ops.c ld.c ldi.c live.c lld.c lldi.c \
	or.c st.c sti.c sub.c tool_arg.c tool_exec.c tool_game.c \
	tool_op.c tool_pc.c tool_verbose.c xor.c zjmp.c \
	game.c player_death.c print_things.c process_death.c \
	basics_process.c delete_process.c tool_process.c\
	are_options_legit.c arg_parse.c check_champs.c does_arg_exist.c \
	is_dump_option_legit.c is_enough_args.c is_helpers.c is_n_option_legit.c \
	player.c startup.c fork.c check_ctd.c is_helpers2.c\

PATH_ASM = asm_dir/

INC = -I libft
HDR = includes/corewar.h
SRC = $(FILE:%=%)
OBJ = $(FILE:%.c=objs/%.o)
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address,undefined #-g3 #-O3
CC = clang $(CFLAGS) $(INC)
RM = rm -rf

all: $(NAME)
	make -C asm_dir
	mv asm_dir/asm .

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) -o $@ $(OBJ) -L libft/ -lftprintf 

$(LIBFT) : FORCE
	make -C libft/ all

FORCE:

objs/%.o: src/%.c $(HDR)
	@mkdir -p objs
	$(CC) $(INC) -o $@ -c $<

objs/%.o: src/game_cycle/%.c $(HDR)
	@mkdir -p objs
	$(CC) $(INC) -o $@ -c $<

objs/%.o: src/op/%.c $(HDR)
	@mkdir -p objs
	$(CC) $(INC) -o $@ -c $<

objs/%.o: src/parser/%.c $(HDR)
	@mkdir -p objs
	$(CC) $(INC) -o $@ -c $<

objs/%.o: src/process/%.c $(HDR)
	@mkdir -p objs
	$(CC) $(INC) -o $@ -c $<

#objs/%.o: src/folder/%.c
#	mkdir -p objs
#	$(CC) $(INC) -o $@ -c $<

clean:
	$(RM) $(OBJ)
	rm -rf objs
	make -C libft/ clean
	make -C asm_dir clean

fclean: clean
	$(RM) $(NAME)
	$(RM) asm
	make -C libft/ fclean
	make -C asm_dir fclean

re: fclean
	$(MAKE)
