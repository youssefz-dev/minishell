# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 11:09:17 by yzoullik          #+#    #+#              #
#    Updated: 2025/07/03 18:02:07 by yzoullik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LFLAGS = -lreadline

HEADER = minishell.h

CFLAGS = -Wall -Wextra -Werror

SRC =	exec/minishell.c\
		exec/exec.c\
		exec/exec_utils.c\
		exec/exec_utils1.c\
		exec/exec_utils2.c\
		exec/exec_utils3.c\
		exec/builtins.c\
		exec/signal.c\
		exec/echo.c\
		exec/cd.c\
		exec/cd_utils.c\
		exec/pwd.c\
		exec/export.c\
		exec/export_utils.c\
		exec/export_utils1.c\
		exec/export_utils2.c\
		exec/unset.c\
		exec/env.c\
		exec/exit.c\
		exec/utils.c\
		exec/utils1.c\
		exec/split.c\
		exec/free.c\
		exec/free1.c\
		parss/minishell.c\
		parss/pro_mpt.c\
		parss/ft_strcmp.c\
		parss/utils.c\
		parss/handlle_sig.c\
		parss/utils2.c\
		parss/parss_er.c\
		parss/syntax_err.c\
		parss/herdoc_handle.c\
		parss/get_next_line.c\
		parss/get_next_line_utils.c\
		parss/ft_itoa.c\
		parss/ft_putstr_fd.c\
		parss/utils3.c\
		parss/ft_strtrim.c\
		parss/expa_nd.c\
		parss/utils4.c\
		parss/ft_isalnum.c\
		parss/ft_isalpha.c\
		parss/help_norm.c\
		parss/help2.c\
		parss/help_free.c\
		parss/ft_split.c\
		parss/norme1.c\
		parss/norm_2.c\
		parss/norm_3.c\
		parss/norm_h4.c\
		parss/handl_qs.c\
		parss/norme_4.c\
		parss/help_norm3.c\
		parss/help_norm_1.c\
		parss/help_norm_2.c\
		parss/help_norm_3.c\
		parss/help_parss1.c\
		parss/norm_prmpt1.c\
		parss/norm_prmpt2.c\
		parss/herdoc_norm.c\
		parss/help_expnorm.c\

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

%.o : %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean