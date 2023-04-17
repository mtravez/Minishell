/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 14:00:03 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/17 11:38:20 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

typedef struct	s_token	t_token;
typedef struct	s_lexer	t_lexer;

typedef struct	s_tree_node
{
	t_token				*token;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

t_tree_node	*parse_to_tree(t_lexer *lexer, t_token *last);
void		print_tree(t_tree_node *root, int branches);
void		free_tree(t_tree_node *root);

#endif