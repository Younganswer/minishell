/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:49 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 19:47:23 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/lexer.h"
#include <stdlib.h>

t_bool			handle_quote(t_token *token, const char **line);
t_bool			is_quote(int c);
static t_bool	handle_single_quote(t_token *token, const char **line);
static t_bool	handle_double_quote(t_token *token, const char **line);

t_bool	handle_quote(t_token *token, const char **line)
{
	if (**line == '\'')
		return (handle_single_quote(token, line));
	return (handle_double_quote(token, line));
}

t_bool	is_quote(int c)
{
	return (c == '\'' || c == '\"');
}

static t_bool	handle_single_quote(t_token *token, const char **line)
{
	(*line)++;
	while (**line && **line != '\'')
		ft_strncat(&token->value, (*line)++, 1);
	return (**line == '\'');
}

static t_bool	handle_double_quote(t_token *token, const char **line)
{
	char	*exp;

	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '$')
		{
			exp = expand((char **) line);
			if (exp == NULL)
				return (FALSE);
			ft_strcat(&token->value, exp);
			free(exp);
		}
		else
			ft_strncat(&token->value, *line, 1);
		(*line)++;
	}
	return (**line == '\"');
}
