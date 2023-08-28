/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 15:01:48 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

#include "signals.h"
#include "environment.h"
#include "parser.h"

#ifdef MEMCHECK

__attribute__((destructor))
static void	destructor(void)
{
	char	*pid;
	char	*cmd;

	print_report();
	pid = ft_itoa(getpid());
	cmd = ft_strjoin("leaks -q ", pid);
	system((const char *)cmd);
	free(pid);
	free(cmd);
}

#endif // MEMCHECK

static int	execute_args(int argc, char *argv[]);
static int	execute_file(char *file_name);

int	main(int argc, char *argv[], char *envp[])
{
	int	ret_val;

	if (sig_interactive_mode() != 0)
		return (print_error(SIGACTION_ERROR));
	if (init_env(envp) != 0)
		return (print_error(MALLOC_ERROR));
	if (isatty(STDIN_FILENO) == 0)
		execute_file(NULL);
	else if (argc > 1)
	{
		ret_val = execute_args(argc, argv);
		clear_env();
		return (ret_val);
	}
	else
	{
		minishell_loop();
		printf("exit\n");
	}
	clear_env();
	return (0);
}

static int	execute_args(int argc, char *argv[])
{
	t_ast	*ast;
	int		ret_val;

	if (argv[1][0] == '-' && argv[1][1] != 'c')
		return (printf_error_msg("minishell: %: invalid option", argv + 1, 2));
	if (str_cmp(argv[1], "-c") == 0)
	{
		if (argc < 3)
			return (print_error_msg("minishell: -c: option requires an \
argument", 2));
		ast = parse_cmd(argv[2]);
		if (ast != NULL)
		{
			ret_val = execute_ast(ast);
			clean_ast(ast);
			return (ret_val);
		}
	}
	return (execute_file(argv[1]));
}

static int	execute_file(char *file_name)
{
	int		fd;
	char	*line;
	t_ast	*ast;

	if (file_name == NULL)
		fd = STDIN_FILENO;
	else
		fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (printf_error_msg("minishell: %: %",
				(char *[2]){file_name, strerror(errno)}, errno + 125));
	line = get_next_line(fd);
	while (line != NULL)
	{
		ast = parse_cmd(line);
		if (ast != NULL)
		{
			set_last_error(execute_ast(ast));
			clean_ast(ast);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (get_last_error());
}
