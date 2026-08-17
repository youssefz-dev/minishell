/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:40 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 14:39:54 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipe(t_shell **help)
{
	t_shell	*new;

	new = new_lst();
	(*help)->next = new;
	new->prev = (*help);
	(*help) = new;
}

void	help_inred(char *file, t_shell *help, int *x, t_env **env)
{
	file = get_in_quote(file, env, x);
	close_fd(help->infile);
	help->infile = open(file, O_RDONLY);
	free(help->inname);
	help->inname = ft_strdup(file);
	if (help->infile == -1)
		help->infile = -1;
	if (help->infile == -1 && !access(file, F_OK))
		help->infile = -2;
	free(file);
}

void	help_infil3(char *file, t_env **env, int *x, t_shell *help)
{
	if (is_dquote(file) || is_sqoute(file))
	{
		file = get_in_quote(file, env, x);
	}
	close_fd(help->infile);
	help->infile = open(file, O_RDONLY);
	free(help->inname);
	help->inname = ft_strdup(file);
	if (help->infile == -1)
		help->infile = -1;
	if (help->infile == -1 && !access(file, F_OK))
		help->infile = -2;
}

void	help_inred_4(char *s, t_shell *help)
{
	close_fd(help->infile);
	help->infile = open(s, O_RDONLY);
	free(help->inname);
	help->inname = ft_strdup(s);
	if (help->infile == -1)
		help->infile = -1;
	if (help->infile == -1 && !access(s, F_OK))
		help->infile = -2;
	free(s);
}

int	help_appnd5(char *file2, int *x)
{
	printf("bash: %s: ambiguous redirect\n", file2);
	*x = 1;
	g_flag = 0;
	return (0);
}
