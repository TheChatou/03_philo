# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:50:30 by fcoullou          #+#    #+#              #
#    Updated: 2024/09/20 13:51:49 by fcoullou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##	PROGS NAMES	################################################################
NAME			= philo

################################################################################
##	PATHS		################################################################
SRC_PATH		= ./src/
INC_PATH		= ./include/
OBJ_PATH		= ./obj/

################################################################################
##	FILES		################################################################
SRC				= $(addprefix $(SRC_PATH), \
											main.c) \
				$(addprefix $(SRC_PATH)Init_And_Set/, \
											init_n_set_00.c \
											init_n_set_01.c) \
				$(addprefix $(SRC_PATH)Simulation/, \
											checker.c \
											dinner.c \
											printer.c) \
				$(addprefix $(SRC_PATH)Utils/, \
											utils_00_mtx_n_thr.c \
											utils_01_mutex.c \
											utils_02_classics.c \
											utils_03_free.c \
											utils_04_time.c \
											utils_05_is_it_checkers.c)
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
CFLAGS			= -Wall -Werror -Wextra -I./include -g3 -ftrapv
CPPFLAGS		= -MMD -c
#------------------------------------------------------------------------------#
AR				= ar
CC				= cc -pthread
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
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(GREEN)[CREATED]$(RESET) : $(NAME)\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(DIR_DUP)
	@printf "$(GREEN)[COMPILATION]$(RESET) : $<$(CLEAR_EOL)\r"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< 
#------------------------------------------------------------------------------#
bonus: $(BONUS)
	
$(BONUS): $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS)
	@printf "CREATED $@\n"
		
$(OBJ_PATH)%.o: $(BONUS_PATH)%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf "CREATED $@\n"
#------------------------------------------------------------------------------#
clean:
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
