/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:36:40 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/15 18:19:18 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>



typedef struct s_cmd
{
	int				in_file;
	int				out_file;
	char			**full_cmd;
	struct s_cmd	*next;
}					t_cmd;

// lexer 2 function

enum e_type
{
	WORD = -1,			 // ok
	WHITE_SPACE = ' ', 	 // ok
	NEW_LINE = '\n',
	QUOTE = '\'', 		 // ok 
	DQUOTE = '\"', 	     // ok 
	ESCAPE = '\\',
	ENV = '$',
	EXIT_STATUS,
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL
};

typedef struct s_elem
{
	char			*content;
	enum e_type		type;
	enum e_state	state;
	struct s_elem	*next;
}					t_elem;

typedef struct s_lexer
{
	char	*input;
	int		len;
	int		position;
}			t_lexer;

typedef struct s_token
{
	char			*value;
	int				len;
	enum e_type		type;
	enum e_state	state;
}			t_token;

// DATA :

typedef struct s_data
{
	t_cmd			*head;
	char			*input;
	t_list			*cmd_lst;
	int				in;
	int				out;
	t_elem			*elem;
	int				error;
	int				file_error;
	int				expanded;
	char			*expnd;
	t_list			*save_error;
	struct s_env	*n_env;
}			t_data;

int		check_empty_line(t_data *input);
int 	is_empty(char c);
int 	parsline(char *line, t_data *input);
void	init_data(t_data *data, char *line);

// creat the token node
t_elem	*create_token(char *content, enum e_type type, enum e_state state);
void	append_token(t_elem **head, t_elem *new);

void	handle_quote(const char *input, int *i, t_elem **head);
int handle_redirections(const char *input, int i, t_elem **head);
int handle_word(const char *input, int i, t_elem **head);




#endif