/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:56:51 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 19:36:00 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// lexer.c
t_bool	lexer(char **line);

// expand.c
char	*expand(char **line);
t_bool	is_expand(int c);

// ifs.c
t_bool	is_ifs(int c);

// meta.c
t_bool	handle_meta(const char **line);
t_bool	is_meta(int c);
t_token	*init_meta_token(const char **line);

// quote.c
t_bool	handle_quote(t_token *token, const char **line);
t_bool	is_quote(int c);

// token.c
t_token	*init_token(void);
t_token	*clone_token(t_token *token);
void	del_token(void *content);

// tokenizer.c
t_bool	tokenize(const char *line);
t_bool	is_not_word(int c);

#endif