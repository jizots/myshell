/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:32:49 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/02 14:23:59 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// int	ft_exec(char *path, char *prog, char **cmd_opts); not adopt. i think its increase process.
int	ft_exec(char *path, char *prog, char **cmd_opts)
{
	t_dexec	dexec;
	t_pid	pid;

	pid = fork();
	if (pid == 0)
	{
		
		ft_get_envpaths(envp, &dexec);
		ft_open_redirection(/*cmd_opts, &dexec*/);
		ft_get_cmdpath(cmd, &dexec);
		if (execve(dexec.cmd_path, cmd_opts, envp) == -1)
		{
			if (errno == EISDIR)
			cmd_cant_use(dexec.cmd_path, &dexec, CMD_SIMPLE);
			exit(ft_print_perror(dexec.cmd_path));
		}
	}
// //comment out start
// 	for (size_t i = 0; dexec.matrix_envpath[i] != NULL ; i++)
// 	ft_printf("PATH = %s\n", dexec.matrix_envpath[i]);
// 	ft_printf("PATH COMMAND = %s\n", dexec.cmd_path);
// //end

ft_free_exec(dexec.matrix_envpath, cmd_opts, dexec.cmd_path, 0);
return (0);
}

//comment out start
int main(int ac, char **av, char **envp)
{
	if (init_env(envp) != 0)
		return (1);
	if (ac == 2)
		ft_exec(av[1], NULL, envp);
	if (ac == 3)
		ft_exec(av[1], ft_split(av[2], ' '), envp);
	if (ac == 1)
		ft_printf("argument is no entry\n");
	clean_env();
	return (0);
}
//end