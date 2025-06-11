/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:36:40 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/23 10:29:45 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"
#include "get_next_line.h"


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
	WORD = 1,
	WHITE_SPACE = ' ',
	QUOTE = '\'',
	DQUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	DREDIR_OUT,
	NEW_LINE = '\n',
	EXIT_STATUS,
	HERE_DOC,
	ESCAPE = '\\',
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


// hahoma structs li glt  lik dyal execution a 

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_export
{
	char			*name;
	char			sep;
	char			*value;
	struct s_export	*next;
}					t_exprt;

typedef struct s_exec
{
	int			i;
	int			j;
	int			size;
	int			n_p;
	int			fork;
	int			**pe;
	char		*check;
	char		cd_path[1024];
	char		last_path[1024];
	char		old_path[1024];
	int			pos_path;
	char		**n_env;
	t_cmd		*tmp;
	t_env		*env;
	t_exprt		*export;
}				t_exec;


void	init_data(t_data *data, char *line);
int 	check_empty_line(t_data *data);
int parse_input(t_elem *token);

t_elem *init_tokens(t_lexer *lexer);
int 	handle_space(const char *input, int *i, t_elem **head);
int 	handle_word(const char *input, int i, t_elem **head);
int 	handle_redirections(const char *input, int i, t_elem **head);
void	handle_quote(const char *input, int *i, t_elem **head);
t_elem *create_token(char *content, enum e_type type, enum e_state state);
void	append_token(t_elem **head, t_elem *new);
int 	handle_env(const char *input, int *i, t_elem **head);
t_lexer *init_lexer(char *input);
// helper function

char	*ft_strndup(const char *s, size_t n);
int 	check_syntax(t_elem *token);
void 	print_tokens(t_elem *head);


// syntax validation
int		is_redirection(enum e_type type);
int		is_quote(enum e_type type);
int		validate_pipe(t_elem *prev_significant);
t_elem	*skip_whitespace(t_elem *token);
int		validate_redirection_target(t_elem *next);
int		validate_redirection(t_elem *curr);
int		check_final_syntax(enum e_state state, t_elem *prev_significant);

char	*get_redirection_symbol(enum e_type type);
int		check_initial_syntax(t_elem *curr);
int		update_quote_state(enum e_type type, enum e_state *state);
int		process_token(t_elem *curr, enum e_state *state, t_elem **prev_significant);
int		check_syntax(t_elem *token);

// parser file functions 
int	parse_pipeline(t_data *data);
t_cmd	*parse_command(t_data *data, t_elem **current);
int		parse_arguments(t_data *data, t_elem **current, t_cmd *cmd);
int		handle_redirection_in(t_data *data, t_elem **current, t_cmd *cmd);
int		handle_redirection_out(t_data *data, t_elem **current, t_cmd *cmd);
int		handle_redirection_append(t_data *data, t_elem **current, t_cmd *cmd);
int		handle_heredoc(t_data *data, t_elem **current, t_cmd *cmd);
void	skip_whitespace_ptr(t_elem **current);
int		count_command_args(t_elem *start);
int		is_redirection_target(t_elem *elem, t_elem *start);
int		allocate_cmd_args(t_cmd *cmd, int arg_count);
int		process_word_token(t_data *data, t_elem **current, t_cmd *cmd, int *arg_index);
int		process_redirection(t_data *data, t_elem **current, t_cmd *cmd);



// t_elem	*create_token(char *content, enum e_type type, enum e_state state);
// void	append_token(t_elem **head, t_elem *new);
// t_elem *init_tokens(char *input);
// void	handle_quote(const char *input, int *i, t_elem **head);
// int handle_redirections(const char *input, int i, t_elem **head);
// int handle_word(const char *input, int i, t_elem **head);
// void print_tokens(t_elem *head);
// const char *get_type_str(enum e_type type);
// int handle_env(const char *input, int *i, t_elem **head);
// int check_syntax(t_elem *token);
// int is_redirection(enum e_type  type);
// int parse_input(char *input);

// // expanding

// void expand_tokens(t_elem *tokens, char **envp);
// char *expnade_variable(const char *input, char **env, int state);
// char *get_env_value(const char *var_name, char **env);




// // helper functions 
// char *ft_strndup(const char *s, size_t n);

#endif