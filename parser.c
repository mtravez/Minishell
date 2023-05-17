
#include "parser.h"

void	free_tree(t_tree_node *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}

void	print_tree(t_tree_node *root, int branches)
{
	int	i;

	if (!root)
		return ;
	branches += 5;
	print_tree(root->right, branches);
	i = 5;
	while (i < branches)
	{
		printf(" ");
		i++;
	}
	printf("%s\n", root->token->content);
	print_tree(root->left, branches);
}

t_token	*get_token_before(t_token *head, t_token *next_token)
{
	t_token	*temp;

	temp = head;
	if (head == next_token)
		return (NULL);
	while (temp->next_token != next_token)
		temp = temp->next_token;
	return (temp);
}

t_tree_node	*new_tree(t_token *token)
{
	t_tree_node	*node;

	node = malloc (sizeof(t_tree_node));
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree_node	*parse_to_tree(t_lexer *lexer, t_token *last)
{
	t_tree_node	*tree;
	t_token		*root;

	root = get_token_before(lexer->token, last);
	while (root && (root->t_type == WORD_TOK || \
	root->t_type == QUOTE_TOK))
		root = get_token_before(lexer->token, root);
	if (root)
	{
		tree = new_tree(root);
		tree->right = new_tree(root->next_token);
		tree->left = parse_to_tree(lexer, root);
	}
	else
		tree = new_tree(lexer->token);
	return (tree);
}
