# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chatou <chatou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:50:30 by fcoullou          #+#    #+#              #
#    Updated: 2024/07/16 15:24:01 by chatou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##	PROGS NAMES	################################################################
NAME			= philosophers

################################################################################
##	PATHS		################################################################
SRC_PATH		= ./src/
INC_PATH		= ./include/
OBJ_PATH		= ./obj/
LIBFT			= ./libft_v2/

################################################################################
##	FILES		################################################################
SRC				= $(addprefix $(SRC_PATH), \
											main.c \
											minishell.c) \
				$(addprefix $(SRC_PATH)builtins/, \
											cd.c \
											exec_builtins.c \
											pwd.c \
											env.c \
											echo.c \
											export_0.c \
											export_1.c \
											export_2.c \
											unset.c \
											exit.c) \
				$(addprefix $(SRC_PATH)exec_utils/, \
											exec_parsing_0.c \
											exec_parsing_1.c \
											free_functions_0.c \
											free_functions_1.c \
											free_functions_2.c \
											exec_utils_0.c \
											exec_utils_1.c \
											exec_utils_2.c) \
				$(addprefix $(SRC_PATH)execution/, \
											display_prompt.c \
											forking.c \
											handle_process.c \
											path_error.c \
											path_0.c \
											path_1.c \
											signals.c \
											underscore.c \
											underscore1.c) \
				$(addprefix $(SRC_PATH)redirection/, \
											here_doc.c \
											open_files.c \
											pipe.c) \
				$(addprefix $(SRC_PATH)parsing/, \
											frees.c \
											input_n_syntax.c \
											parse_cmds_0.c \
											parse_cmds_1.c \
											parse_quotes.c \
											parse_token_0.c \
											parse_token_1.c \
											t_cmd.c \
											t_dir.c \
											t_quote.c \
											t_token.c) \
				$(addprefix $(SRC_PATH)parsing_utils/, \
											futils_0.c \
											futils_1.c \
											futils_2.c \
											futils_3.c \
											futils_4.c \
											futils_5.c \
											futils_6.c) \
				$(addprefix $(SRC_PATH)extras/, \
											extras.c \
											prints.c)

SRC_BONUS		= $(BONUS_PATH).c
#------------------------------------------------------------------------------#
OBJ				= $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
OBJ_BONUS		= $(SRC_BONUS:$(BONUS_PATH)%.c=$(OBJ_PATH)%.o)
#------------------------------------------------------------------------------#
DEP 			= $(OBJ:%.o=%.d)
#------------------------------------------------------------------------------#
OUTPUT_LEAKS 	= valgrind-out.txt

################################################################################
##	COMPILER	################################################################
CFLAGS			= -Wall -Werror -Wextra -I./include -I./libft_v2/include -g3 -ftrapv
CPPFLAGS		= -MMD -c
LFLAGS 			= -L./libft_v2 -lft -lreadline
#------------------------------------------------------------------------------#
AR				= ar
CC				= cc
RM				= rm -f
CD				= cd
DIR_DUP			= mkdir -p $(@D)

################################################################################
##	+++++		################################################################
GREEN=\033[0;32m
RED=\033[0;31m
RESET=\033[0m
CLEAR_EOL=\033[K
#------------------------------------------------------------------------------#
VALCHECK=--leak-check=full
VALSHOW=--show-leak-kinds=all
VALFD=--track-fds=yes
VALIGNORE=--suppressions=valgrind_readline_leaks_ignore.txt
VALCHILD=--trace-children=yes

################################################################################
##	RULES		################################################################
all: $(NAME)

$(NAME): $(OBJ)
	@make -s -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS) 
	@printf "$(GREEN)[CREATED]$(RESET) : $(NAME)\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(DIR_DUP)
	@printf "$(GREEN)[COMPILATION]$(RESET) : $<$(CLEAR_EOL)\r"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $< 
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< 
#------------------------------------------------------------------------------#
bonus: $(BONUS)
	
$(BONUS): $(OBJ_BONUS)
	@make -s -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS) $(LFLAGS)
	@printf "CREATED $@\n"
		
$(OBJ_PATH)%.o: $(BONUS_PATH)%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf "CREATED $@\n"
#------------------------------------------------------------------------------#
clean:
	@make -s -C $(LIBFT) fclean
	@printf " "
	@for file in $(OBJ); do \
		printf "$(RED)[DELETE FILES]$(RESET) : $(CLEAR_EOL)$$file "; \
		sleep 0.01; \
		printf "\r"; \
	done && \
	printf "$(CLEAR_EOL)$(RED)[ALL FILES DELETED]$(RESET)\n" && \
	$(RM) -rf $(OBJ_PATH)
	@$(RM) -rf $(LIBFT_OBJ)
#------------------------------------------------------------------------------#
fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS)
	@$(RM) -rf $(OBJ_PATH)
#------------------------------------------------------------------------------#
re: fclean all
#------------------------------------------------------------------------------#
test: all
	./$(NAME)
#------------------------------------------------------------------------------#
leaks: all
	valgrind $(VALIGNORE) $(VALSHOW) $(VALCHECK) ./$(NAME)
	@cat valgrind-out.txt
#------------------------------------------------------------------------------#
valgrind : all
	valgrind $(VALIGNORE) $(VALSHOW) $(VALCHECK) $(VALCHILD) $(VALFD) ./${NAME}
#------------------------------------------------------------------------------#
.PHONY: all bonus clean fclean re test leaks  
#------------------------------------------------------------------------------#

-include $(DEP)
