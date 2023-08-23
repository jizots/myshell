/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:23:23 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/23 09:48:46 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

//-------include-------
# include "minishell.h"
# include "error.h"
# include "exec.h"
# include "environment.h"

//-------define-------
# define BUILTIN_ECHO 1
# define BUILTIN_CD 2
# define BUILTIN_PWD 3
# define BUILTIN_EXPORT 4
# define BUILTIN_UNSET 5
# define BUILTIN_ENV 6
# define BUILTIN_EXIT 7

//-------prototype-------
int		built_in_echo(t_exe *exe);
int		built_in_cd(t_exe *exe);
int		built_in_pwd(t_exe *exe);
int		built_in_export(int argc, char *argv[]);
int		built_in_unset(int argc, char *argv[]);
int		built_in_env(int argc, char *argv[]);
int		built_in_exit(t_exe *exe, t_ast *node);
int		is_builtin(t_exe *exe, t_ast *node);

#endif