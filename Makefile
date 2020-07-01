# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weilin <weilin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/02 01:11:49 by weilin            #+#    #+#              #
#    Updated: 2020/07/02 01:16:49 by weilin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
COREWAR = corewar

ASM_FILES = 

COREWAR_FILES = 


CCH_DIR = cache/
SRC_DIR = src/
INC_DIR = inc/
LINC_DIR = libft/inc/
LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a

INCS += $(INC_DIR)corewar.h 
INCS += $(LINC_DIR)libft.h 
INCS += $(LINC_DIR)ft_printf.h
INCS += $(LINC_DIR)get_next_line.h

CC = clang
FLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I$(LINC_DIR)
LEAKS = -fsanitize=address
RM = rm -rf

ASM_SRC = $(addprefix $(SRC_DIR),$(addsuffix .c,$(ASM_FILES)))
ASM_OBJ = $(addprefix $(CCH_DIR),$(addsuffix .o,$(ASM_FILES)))
COREWAR_SRC = $(addprefix $(SRC_DIR),$(addsuffix .c,$(COREWAR_FILES)))
COREWAR_OBJ = $(addprefix $(CCH_DIR),$(addsuffix .o,$(COREWAR_FILES)))

vpath  %.h inc/
vpath  %.h libft/inc/

all: $(ASM) $(COREWAR)

$(ASM): $(LIBFT) $(CCH_DIR) $(ASM_OBJ) $(INCS)
	$(CC) $(FLAGS) -o $@ $< $(ASM_OBJ) -L $(LIB_DIR) -lft

$(COREWAR): $(LIBFT) $(CCH_DIR) $(COREWAR_OBJ) $(INCS)
	$(CC) $(FLAGS) -o $@ $< $(COREWAR_OBJ) -L $(LIB_DIR) -lft

$(LIBFT): force
	@make -C libft all

force:
	@true

$(CCH_DIR)%.o: $(SRC_DIR)%.c $(INCS)| $(CCH_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(CCH_DIR):
	mkdir $@

clean:
	$(RM) $(CCH_DIR)
	$(RM) $(ASM).dSYM
	$(RM) $(COREWAR).dSYM
	$(RM) *.o
	$(RM) *.out*
	# make -C libft clean
	
fclean: clean
	$(RM) $(ASM)
	$(RM) $(COREWAR)
	# make -C libft fclean

re: fclean
	$(MAKE) all

norm:
	norminette $(SRC_DIR) $(INC_DIR) | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm