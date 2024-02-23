NAME            := minishell
SRC_DIR			:= src
OBJ_DIR			:= obj
SRCS			:= env.c  init.c  main.c  prompt.c  running.c  utilstab.c  signal.c utils.c parse_line.c punct_handle.c tokenizing.c tokenier.c lst_utils.c
SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC				:= cc
#CFLAGS			:= -Wall -Wextra -Werror -g3 -lreadline
CFLAGS			:= -g3 -Iinclude
RM				:= rm -rf
DIR_DUP			= mkdir -p $(@D)
LIBFT			:= libft

all		:	$(NAME)

$(NAME) :	$(OBJS)
	@make -C $(LIBFT) --no-print-directory
	$(CC) $(OBJS) $(LIBFT)/libft.a -lreadline -o $(NAME)

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