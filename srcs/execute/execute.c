/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:33 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/15 14:25:48 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute.h"
#include "../../incs/builtin.h"
#include "../../incs/subsystem.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int				execute(void);
t_bool			set_underscore_env(void);
static t_bool	child_process(t_list *cmd);
static t_bool	set_fd_in_pipe(t_list *cmd, int *fd, t_bool is_child);

int	execute(void)
{
	if (g_var->cmd_list == NULL)
		return (0);
	if (g_var->cmd_list->next == NULL && is_builtin(g_var->cmd_list->content))
		return (execute_builtin(g_var->cmd_list->content, FALSE));
	child_process(g_var->cmd_list);
	set_underscore_env();
	if (g_var->exit_status == 2 && g_var->exit_status < 256)
		ft_putendl_fd("", 1);
	if (g_var->exit_status == 3 && g_var->exit_status < 256)
		ft_putendl_fd("Quit: 3", 1);
	return (g_var->exit_status);
}

t_bool	set_underscore_env(void)
{
	t_token	*last_token;
	char	*arg;

	last_token = ft_lstlast(g_var->cmd_list->content)->content;
	arg = ft_strdup("_=");
	if (1 < ft_lstsize(g_var->cmd_list))
		ft_strcat(&arg, "");
	else
		ft_strcat(&arg, last_token->value);
	export(arg);
	free(arg);
	return (TRUE);
}

static t_bool	child_process(t_list *cmd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (FALSE);
	pid = fork();
	if (pid == -1)
		return (FALSE);
	unset_subsystem(pid);
	if (pid == 0)
	{
		set_fd_in_pipe(cmd, fd, TRUE);
		if (set_fd_in_redir((t_list **) &cmd->content) == FALSE)
			exit(g_var->exit_status >> 8);
		if (is_builtin(cmd->content) && 0 <= execute_builtin(cmd->content, TRUE))
			exit(g_var->exit_status >> 8);
		else
			execute_extern(cmd->content);
	}
	set_fd_in_pipe(cmd, fd, FALSE);
	if (cmd->next != NULL && child_process(cmd->next))
		waitpid(pid, NULL, 0);
	else
		waitpid(pid, &g_var->exit_status, 0);
	return (TRUE);
}

static t_bool	set_fd_in_pipe(t_list *cmd, int *fd, t_bool is_child)
{
	if (is_child)
	{
		close(fd[0]);
		if (cmd->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
		else
			dup2(g_var->old_fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (cmd->next != NULL)
			dup2(fd[0], STDIN_FILENO);
		else
			dup2(g_var->old_fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (TRUE);
}
