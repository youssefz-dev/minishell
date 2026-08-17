/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:47:54 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/03 17:02:14 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_flag;

int	cmd_size(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void	handel_under(t_shell *shell)
{
	t_env	**env;
	t_env	*node;
	char	*val;
	int		len;

	len = cmd_size(shell->cmd);
	env = shell->env;
	if (!*env || !env)
		return ;
	if (!search_env(env, "_"))
		ft_lstadd_back1(env, env_init2(ft_strdup("_"), 1, 0));
	node = get_env2(env, "_");
	val = ft_strdup(shell->cmd[len - 1]);
	free(node->val);
	node->val = val;
}

void	mini_exec1(t_shell *shell, t_list *list)
{
	first_proc(shell, list);
	(dup2(list->fd[0], 0), close(list->fd[0]), close(list->fd[1]));
	while (1)
	{
		shell = shell->next;
		free_shell1(shell->prev);
		if (shell->next == 0)
			break ;
		md_proc(shell, list);
	}
	(last_proc(shell, list), free_shell1(shell));
}

int	execshell(t_shell *shell)
{
	t_list			*list;

	g_flag = 0;
	signal(SIGINT, sig_action);
	signal(SIGQUIT, sig_action);
	list = list_init(shell);
	if (!shell->next && shell->cmd)
		handel_under(shell);
	if (!shell->next && shell->cmd && is_builtins1(shell))
		return (g_flag = 0, run_built(shell, list));
	if (!shell->next)
		one_proc(shell, list);
	else
		mini_exec1(shell, list);
	(dup2(list->in, 0), close(list->in), dup2(list->out, 1), close(list->out));
	return (ft_wait(list));
}
