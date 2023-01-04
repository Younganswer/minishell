/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsystem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:56:59 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 15:36:44 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSYSTEM_H
# define SUBSYSTEM_H

# include "../libs/libft/incs/libft.h"

// subsystem.c
t_bool	set_subsystem(void);
t_bool	unset_subsystem(int pid);

// signal.c
t_bool	set_signal(void);
t_bool	unset_signal(int sig);

// termios.c
t_bool	init_termios(void);
t_bool	set_termios(void);
t_bool	reset_termios(void);

#endif