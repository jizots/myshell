/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/27 23:40:24 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef MEMCHECK
#  include <memory_leak_detector.h>
# endif // MEMCHECK

# include <libft.h>
# include "external_functions.h"

typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;

enum e_token_type
{
	regular,
	dquote,
	none,
	input,
	output,
	input_limit,
	output_append,
	pipe,
};

struct s_token
{
	char	*data;

};


#endif // MINISHELL_H