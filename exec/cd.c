/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:18:28 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/02 15:17:20 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chhnge_dir(t_shell *shell)
{
	char	*pwd;
	char	*dir;
	int		i;

	i = chdir(shell->cmd[1]);
	if (ft_strnstr(shell->cmd[1], "..", ft_strlen("..")) && i == -1)
	{
		pwd = pwd1();
		if (!pwd)
			return (0);
		dir = ft_substr(pwd, 0, (size_t) ft_strrchr1(pwd, '/'));
		free(pwd);
		if (!dir)
			return (0);
		if (chdir(dir) == -1)
			return (dup2(2, 1), printf("bash: cd: %s: Permission denied\n", \
				shell->cmd[1]), 0);
		return (free(dir), 1);
	}
	if (i == -1)
		return (dup2(2, 1), \
		printf("bash: cd: %s: No such file or directory\n", shell->cmd[1]), 0);
	return (1);
}

int	cd_validate(t_shell *shell)
{
	DIR	*dir;

	dir = opendir(shell->cmd[1]);
	if (!dir && !(ft_strnstr(shell->cmd[1], "..", ft_strlen("..")) \
	&& ft_strlen(shell->cmd[1]) == ft_strlen("..")))
	{
		dup2(2, 1);
		if (errno == EACCES)
			return (printf("bash: cd: %s: Permission denied\n", \
			shell->cmd[1]), 0);
		if (errno == ENOTDIR)
			return (printf("bash: cd: %s: Not a directory\n", shell->cmd[1]), 0);
		else
			return (printf("bash: cd: %s: No such file or directory\n", \
				shell->cmd[1]), 0);
	}
	closedir(dir);
	change_oldpwd(shell);
	return (chhnge_dir(shell));
}

int	cd(t_shell *shell)
{
	if (shell->cmd[1])
	{
		if (shell->cmd[2])
		{
			dup2(2, 1);
			printf("bash: cd: too many arguments\n");
			return (1);
		}
	}
	if (!shell->cmd[1] || (shell->cmd[1][0] == '~' && shell->cmd[1][1] == '\0'))
		if (!cd_utils(shell, "HOME"))
			return (1);
	if (shell->cmd[1][0] == '-' && shell->cmd[1][1] == '\0')
		if (!cd_utils(shell, "OLDPWD"))
			return (1);
	if (!cd_validate(shell))
		return (1);
	change_pwd(shell);
	return (0);
}
