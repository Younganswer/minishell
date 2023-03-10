/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:56:55 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 20:49:43 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libs/libft/incs/libft.h"
# include <termios.h>

typedef struct termios	t_termios;

typedef enum e_token_type
{
	T_NULL = 0,
	T_WORD = 1,
	T_PIPE = 2,
	T_REDIRECT = 3,
	T_ARGV = 6,
	T_CMD = 7
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef enum e_open_flag
{
	HERE_DOC = 0,
	FILE_IN = 1,
	FILE_OUT_TRUNC = 2,
	FILE_OUT_APPEND = 3,
}	t_open_flag;

typedef struct s_var
{
	t_termios	old_termios_stdout;
	t_termios	new_termios_stdout;
	t_termios	old_termios_stdin;
	t_termios	new_termios_stdin;
	t_list		*token_list;
	t_list		*env_list;
	t_list		*cmd_list;
	int			exit_status;
	int			old_fd[3];
}	t_var;

t_var					*g_var;

#endif