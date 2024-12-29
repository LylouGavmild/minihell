SRCS		=	srcs/main.c srcs/errors/malloc_error.c srcs/signals/signals.c srcs/libft_utils/utils.c srcs/libft_utils/utils1.c srcs/libft_utils/itoa.c \
				srcs/libft_utils/utils2.c srcs/libft_utils/utils3.c srcs/exec/cmd.c srcs/exec/check_if_dir.c srcs/exec/echo.c srcs/exec/fd_distri.c \
				srcs/exec/list.c srcs/exec/here_doc.c srcs/exec/utils.c srcs/exec/build.c srcs/exec/exit.c srcs/exec/utils2.c srcs/exec/utils3.c srcs/exec/family.c \
				srcs/exec/cd.c srcs/exec/cd_utils.c srcs/exec/exit_utils.c srcs/exec/export.c srcs/exec/export_print.c srcs/exec/export_utils.c srcs/exec/env.c srcs/exec/realloc.c \
				srcs/parser/btree.c srcs/parser/btree_utils.c srcs/parser/lexer.c srcs/parser/lexer_utils.c  srcs/parser/parser.c srcs/parser/parser_utils.c srcs/exec/pwd.c \
				srcs/parser/cmd_maker.c srcs/parser/cmd_maker_if.c srcs/parser/cmd_maker_redirect.c srcs/parser/cmd_maker_redirect_utils.c srcs/exec/expand.c srcs/exec/unset.c \
				srcs/exec/spesplit.c srcs/exec/spesplit_utils.c srcs/exec/spesplit_utils2.c srcs/exec/wpids.c srcs/exec/wildcard.c srcs/exec/wildcard_utils.c srcs/exec/wildcard_utils2.c \
				srcs/parser/securedi.c srcs/parser/securedi_utils.c srcs/parser/securedi_utils2.c srcs/parser/securedirect.c


OBJS		=	$(SRCS:.c=.o)

OBJS_BONUS	=	$(SRCS:.c=.o)

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

NAME		=	minishell

BONUS	=	minishell_bonus

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -lreadline -o $(NAME)

bonus: $(BONUS)

$(BONUS): $(OBJS_BONUS)
			$(CC) $(OBJS_BONUS) -lreadline -o $(BONUS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
