NAME			:= minishell
SRC_DIR			:= src
OBJ_DIR			:= obj
SRCS			:= builtin_exec.c builtins2.c builtins.c cd.c env.c escape.c exec.c exit_status.c export.c free.c heredoc.c init.c lst_exe.c lst_free.c lst_tok.c lst_utils.c main.c parse_line.c pipe_utils.c prompt.c punct_handle.c redirect.c running.c signal.c tokenizer.c tokenizing.c unset.c utils2.c utils.c utilsexec.c utilsexit.c utilsexport.c utilstab.c validation.c var_dquote.c
#commande shell pour les src: ls src/. | tr "\n" " " > oui | cat; rm oui
SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS			:= $(OBJS:.o=.d)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3
CPPFLAGS		:= -MMD -MP -I include
#CFLAGS			:= -g3 -Iinclude
RM				:= rm -rf
DIR_DUP			= mkdir -p $(@D)
LIBFT			:= libft

all		:	$(NAME)

$(NAME) :	$(OBJS)
	@make -C $(LIBFT) --no-print-directory
	$(CC) $(OBJS) $(LIBFT)/libft.a -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

-include $(DEPS)

clean	:
	$(RM) $(OBJ_DIR)
	make -C $(LIBFT) clean --no-print-directory

fclean	:	clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean --no-print-directory

re		:	fclean all
	make -C $(LIBFT) re --no-print-directory

.PHONY: all clean fclean re
