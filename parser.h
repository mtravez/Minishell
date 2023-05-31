
#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_token	t_token;
typedef struct s_lexer	t_lexer;

typedef struct s_tree_node
{
	t_token				*token;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

t_tree_node	*parse_to_tree(t_lexer *lexer, t_token *last);
void		print_tree(t_tree_node *root, int branches);
void		free_tree(t_tree_node *root);

#endif