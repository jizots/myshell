/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:40 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/23 09:49:00 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "environment.h"

static char	**split_wrap(char **matrix, char token)
{
	size_t	i;
	char	*tmp;

	tmp = get_env("PATH", NULL);
	if (tmp == NULL)
	{
		print_error_msg("Error: 'PATH' not found", 1);
		return (NULL);
	}
	matrix = ft_split(tmp, token);
	if (matrix == NULL)
	{
		free(tmp);
		print_error(MALLOC_ERROR);
		return (NULL);
	}
	free(tmp);
	return (matrix);
}

static int	make_potential_path(t_exe *exe, char *envpath, char *cmd)
{
	char	*pre_path;

	pre_path = ft_strjoin(envpath, "/");
	if (pre_path == NULL)
		return (print_error(MALLOC_ERROR));
	exe->cmd_path = ft_strjoin(pre_path, cmd);
	if (exe->cmd_path == NULL)
	{
		free(pre_path);
		return (print_error(MALLOC_ERROR));
	}
	free(pre_path);
	return (0);
}

int	path_is_envp(char *cmd, t_exe *exe)
{
	size_t	i;

	if (*cmd == '\0')
		return (CMD_NOTFOUND);
	i = 0;
	exe->matrix_envpath = split_wrap(exe->matrix_envpath, ':');
	if (exe->matrix_envpath == NULL)
		return (1);
	while (exe->matrix_envpath[i] != NULL)
	{
		if (make_potential_path(exe, exe->matrix_envpath[i++], cmd) != 0)
			return (1);
		if (check_cmdpath(exe->cmd_path, ACCESS_FOK) == 0)
			return (0);
		free_null((void **)&(exe->cmd_path));
	}
	return (CMD_NOTFOUND);
}

int	directory_is(char *path)
{
	int		status;
	char	*cpy;

	cpy = ft_strdup(path);
	if (cpy == NULL)
		return (print_error(MALLOC_ERROR));
	path[ft_strlen(path) - 1] = '\0';
	if (check_cmdpath(path, ACCESS_FOK) == 1)
		status = printf_error_msg("minishell: %: %",
				(char *[2]){cpy, strerror(errno)}, CMD_NOTFOUND);
	else if (ft_stat_wrap(path, STAT_ISDIR) == true)
		status = printf_error_msg("minishell: %: %",
				(char *[2]){cpy, "Is a directory"}, CMD_CANT_EXEC);
	else if (ft_stat_wrap(path, STAT_ISREG) == true)
		status = printf_error_msg("minishell: %: %",
				(char *[2]){cpy, "Not a directory"}, CMD_CANT_EXEC);
	else if (ft_stat_wrap(path, 0) == 255)
		status = 255;
	free(cpy);
	return (status);
}
