NAME			:= minishell
SRC_DIR			:= src
OBJ_DIR			:= obj
SRCS			:= builtin_exec.c builtins2.c builtins.c env.c escape.c exec.c export.c free.c heredoc.c init.c lst_exe.c lst_free.c lst_tok.c main.c parse_line.c prompt.c punct_handle.c running.c signal.c tokenizer.c tokenizing.c unset.c utils.c utilstab.c
#commande shell pour les src: ls src/. | tr "\n" " " > oui | cat; rm oui
SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3
#CFLAGS			:= -g3 -Iinclude
RM				:= rm -rf
DIR_DUP			= mkdir -p $(@D)
LIBFT			:= libft
PRINTF			:= printf

all		:	$(NAME)

$(NAME) :	$(OBJS)
	@make -C $(PRINTF) --no-print-directory
	@make -C $(LIBFT) --no-print-directory
	$(CC) $(OBJS) $(PRINTF)/libftprinterr.a $(LIBFT)/libft.a -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) -c $< $(CFLAGS) -o $@

clean	:
	$(RM) $(OBJ_DIR)
	make -C $(LIBFT) clean --no-print-directory
	make -C $(PRINTF) clean --no-print-directory

fclean	:	clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean --no-print-directory
	make -C $(PRINTF) fclean --no-print-directory

re		:	fclean all
	make -C $(LIBFT) re --no-print-directory
	make -C $(PRINTF) re --no-print-directory

.PHONY: all clean fclean re

-include $(DEP)