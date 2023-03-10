/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-cho <min-cho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:57 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/05 14:53:08 by min-cho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"
#include "../../incs/structs.h"
#include "../../incs/lexer.h"

t_bool	create_cmd_list(void);
void	del_cmd(void *cmd);

t_bool	create_cmd_list(void)
{
	t_list	*cmd;
	t_list	*tmp;

	cmd = NULL;
	tmp = g_var->token_list;
	while (tmp)
	{
		if (((t_token *) tmp->content)->type == T_PIPE)
		{
			ft_lstadd_back(&g_var->cmd_list, ft_lstnew(cmd));
			cmd = NULL;
		}
		else
			ft_lstadd_back(&cmd, ft_lstnew(clone_token(tmp->content)));
		tmp = tmp->next;
	}
	if (cmd != NULL)
		ft_lstadd_back(&g_var->cmd_list, ft_lstnew(cmd));
	return (TRUE);
}

void	del_cmd(void *cmd)
{
	t_list	*t_cmd;

	t_cmd = (t_list *) cmd;
	ft_lstclear(&t_cmd, del_token);
}
