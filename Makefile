NAME            := minishell
SRC_DIR			:= src
OBJ_DIR			:= obj
SRCS			:= main.c
SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC				:= cc
#CFLAGS			:= -Wall -Wextra -Werror -g3
CFLAGS			:= -g3
RM				:= rm -rf
DIR_DUP			= mkdir -p $(@D)
LIBFT			:= libft

all		:	$(NAME)

$(NAME) :	$(OBJS)
	@make -C $(LIBFT) --no-print-directory
	$(CC) $(OBJS) $(LIBFT)/libft.a -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) -c $< $(CFLAGS) -o $@

clean	:
	$(RM) $(OBJ_DIR)
	make -C $(LIBFT) clean --no-print-directory

fclean	:	clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean --no-print-directory

re		:	fclean all
	make -C $(LIBFT) re --no-print-directory

.PHONY: all clean fclean re

-include $(DEP)