# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weilin <weilin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/02 01:11:49 by weilin            #+#    #+#              #
#    Updated: 2020/07/24 07:36:05 by weilin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
VM = corewar

ASM_FILES = 

VM_FILES = vm/op/exec\
		vm/op/g_ops\
		vm/op/tool_arr\
		vm/op/tool_arg\
		vm/op/tool_check\
		vm/op/tool_del\
		vm/op/tool_exec\
		vm/op/tool_op\
		vm/op/tool_pc\
		vm/op/tool_process\
		vm/op/tool_verbose\
		vm/op/add	\
		vm/op/aff	\
		vm/op/and	\
		vm/op/fork	\
		vm/op/ld	\
		vm/op/ldi	\
		vm/op/live	\
		vm/op/lld	\
		vm/op/lldi	\
		vm/op/or	\
		vm/op/st	\
		vm/op/sti	\
		vm/op/sub	\
		vm/op/xor	\
		vm/op/zjmp	\
		vm/op/main_op	\

CCH_DIR = cache/
SRC_DIR = src/
INC_DIR = inc/
LINC_DIR = libft/inc/
LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a

HEADERS += $(INC_DIR)op.h
HEADERS += $(INC_DIR)vm.h
HEADERS += $(LINC_DIR)libft.h
HEADERS += $(LINC_DIR)ft_printf.h
HEADERS += $(LINC_DIR)get_next_line.h

INCS = -I$(INC_DIR) -I$(LINC_DIR)

CC = clang
FLAGS = -Wall -Wextra -Werror -g
LEAKS = -fsanitize=address
RM = rm -rf

ASM_SRC = $(addprefix $(SRC_DIR),$(addsuffix .c,$(ASM_FILES)))
ASM_OBJ = $(addprefix $(CCH_DIR),$(addsuffix .o,$(ASM_FILES)))
VM_SRC = $(addprefix $(SRC_DIR),$(addsuffix .c,$(VM_FILES)))
VM_OBJ = $(addprefix $(CCH_DIR),$(addsuffix .o,$(VM_FILES)))

vpath  %.h inc/
vpath  %.h libft/inc/

all: $(VM)

$(ASM): $(LIBFT) $(CCH_DIR) $(ASM_OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(INCS) $(ASM_OBJ) -L $(LIB_DIR) -lft -o $@

$(VM): $(LIBFT) $(CCH_DIR) $(VM_OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(INCS) $(VM_OBJ) -L $(LIB_DIR) -lft -o $@

$(LIBFT): force
	@make -C libft all

force:
	@true

$(CCH_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)| $(CCH_DIR)
	$(CC) $(FLAGS) -c $(INCS) $< -o $@

$(CCH_DIR):
	mkdir $@
	mkdir cache/vm/
	mkdir cache/vm/op

clean:
	$(RM) $(CCH_DIR)
	$(RM) $(ASM).dSYM
	$(RM) $(VM).dSYM
	$(RM) *.o
	$(RM) *.out*
	make -C libft clean
	
fclean: clean
	$(RM) $(ASM)
	$(RM) $(VM)
	make -C libft fclean

re: fclean
	$(MAKE) all

norm:
	norminette $(SRC_DIR) $(INC_DIR) | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm