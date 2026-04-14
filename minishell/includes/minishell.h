/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:20:24 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/14 10:38:47 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ========================== 🔹 DÉFINITIONS GÉNÉRALES =========================

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define SUCCESS 0
# define FAIL 1
# define CODE_FAIL 1
# define CODE_SUCCESS 0
# define READ 0
# define WRITE 1
# define ERR_HDOC "minishell: warning: here-document delimited by end-of-file"
# define ERR_SYNT "minishell: syntax error near unexpected token"
# define PROMPT "\033[1;32mminishell$> \033[0m"

extern volatile sig_atomic_t	g_status;

// ======================== 🧠 STRUCTURES DE DONNÉES ===========================

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	HEREDOC,
	APPEND,
}								t_TokenType;

typedef struct s_token
{
	char						*value;
	int							quoted;
	t_TokenType					type;
	struct s_token				*next;
}								t_token;

typedef struct s_env
{
	char						*name;
	char						*content;
	struct s_env				*next;
	struct s_env				*prev;
}								t_env;

typedef struct s_redir
{
	char						*file;
	char						*limiter;
	int							fd;
	int							type;
	struct s_redir				*next;
}								t_redir;

typedef struct s_cmd
{
	char						**args;
	char						*path;
	t_redir						*infile;
	t_redir						*outfile;
	int							here_doc_mode;
	int							pipe_fd[2];
	int							saved_stdin;
	int							saved_stdout;
	pid_t						pid;
	bool						cmd_valid;
	struct s_cmd				*next;
	struct s_cmd				*prev;
}								t_cmd;

typedef struct s_data
{
	char						*input;
	t_env						*env;
	t_env						*export;
	char						**envp;
	t_token						*token;
	t_cmd						*cmd_list;
	int							last_status;
	int							token_count;
}								t_data;

// ======================== 🧠 INITIALISATION DES DONNÉES =====================

t_token							*new_token(char *value, t_TokenType type,
									int quoted);
t_env							*env_new(char *name, char *value);
t_cmd							*new_cmd_node(void);
// void							init_data(t_data *data);
t_env							*init_export_list(char **env);
t_env							*init_env_list(char **env);
void							init_exec_vars(t_cmd *cmd, char ***args,
									char **path, t_data *data);

// ============================ 🧪 PARSING ====================================

int								parse(t_data *data);
int								valid_parse(t_data *data);
t_cmd							*parse_tokens(t_data *data);
void							add_arg(t_cmd *cmd, char *value);
t_token							*redir_token(char *input, int *i);
t_token							*redir_double(char *input, int *i);
char							*extract_word_single(char *input, int *i);
char							*extract_word_double(t_data *data, int *i);
char							*change_env(t_data *data, int *i);
char							*ft_get_env(char *str, t_data *data);
int								loop_parse(t_token *token, t_cmd **curr,
									t_cmd **head, int *skip_next_word);
int								add_redir(t_redir **redir_list, char *filename,
									int type, int *skip_next_word);
int								redir_assigment(t_cmd *curr, t_token *token,
									int *skip_next_word);
int								create_parse(t_token *token, t_cmd **curr,
									int *skip_next_word);
char							*handle_env_value(t_data *data, int *i,
									char *value);
char							*append_remaining_segment(t_data *data,
									char *extract, int first, int i);
char							*append_env_variable(t_data *data,
									char *extract, int *i, int *first);

// ============================ 🧩 LEXING =====================================

t_token							*ft_lexer(t_data *data);
int								is_token_ok(t_token *token);
t_token							*get_next_token(t_data *data, int *i);
int								is_token_invalid(t_token *current,
									char *trimmed);
t_token							*fill_tokens(char **tab, t_token *new_tokens,
									t_token *last);
t_token							*check_token_number(t_token *current,
									char *trimmed);
void							add_token_to_list(t_token **head,
									t_token **last, t_token *new_token);
char							*handle_quotes_part(t_data *data, int *i,
									char *value);
t_token							*handle_pipe(int *i);
t_token							*handle_cmd_or_arg(t_data *data, int *i);
char							*handle_plain_text(t_data *data, int *i,
									char *value);
void							print_export_list(t_env *export);
void							ft_lstadd_back_env(t_env **lst, t_env *new);
t_token							*handle_dollar_quote(t_data *data, int *i);

// ============================ 🛣️ PATH =======================================

char							*try_paths(char **paths, char *cmd);
char							*find_cmd_path(char *cmd, t_data *data);
char							*get_cmd_path(t_data *data, char **cmd);
int								resolve_command_path(t_data *data, t_cmd *cmd);
void							is_not_path(t_data *data, char **args,
									char *path);
int								which_command(t_data *data, t_cmd *cmd,
									int prev_fd);

// ============================ 🛠️ EXECUTION ==================================

void							read_prompt(t_data *data);
int								ft_process(t_data *data, t_cmd *cmd,
									int prev_fd);
int								exec_line(t_data *data, t_cmd *cmd);
int								exec_shell(t_data *data, t_cmd *cmd,
									int prev_fd);
void							exec_child(t_data *data, t_cmd *cmd,
									int prev_fd);
int								exec_child_process(t_data *data, t_cmd *cmd,
									int prev_fd);
int								exec_direct(t_data *data, t_cmd *cmd,
									int prev_fd);
int								ft_executables(t_data *data, t_cmd *cmd,
									int input_fd, int output_fd);
int								handle_single_command(t_data *data, t_cmd *cmd,
									int prev_fd);
void							handle_useless_command(t_cmd *cmd,
									int *prev_fd);
int								handle_path_exec(t_data *data, t_cmd *cmd);
int								wait_for_children(t_data *data, pid_t last_pid,
									int prev_fd);
char							**ft_get_cmd(t_data *data);
int								handle_exec(t_data *data, t_cmd *cmd,
									char **args, char *path);
int								check_path_and_exec(t_data *data, char **args,
									char *path);

// ============================ 📦 BUILTINS ===================================

int								ft_cd(t_data *data);
int								ft_echo(t_data *data, t_cmd *cmd);
int								ft_env(t_data *data);
int								ft_export(t_data *data);
int								ft_pwd(void);
int								ft_unset(t_data *data);
int								ft_exit(t_data *data, t_cmd *cmd, int stdin,
									int stdout);

// ============================ 🔀 REDIRECTIONS ===============================

int								redirect_management(t_cmd *cmd, int prev_fd);
void							fds_redirection(t_cmd *cmd, int *prev_fd);
void							exec_redirection(t_data *data, t_cmd *cmd,
									int input_fd, int output_fd);

// ============================ 🐚 HERE-DOC ===================================

void							made_new_file(int *fd, char **name);
int								if_limiter(char *line, char *limiter);
void							free_path(char *path_cmd);
int								fill_here_doc_file(int fd, char *delimitor);
char							*get_here_doc(char *str);

// ============================ 📊 UTILITAIRES ================================

int								ft_isalldigit(char *str);
int								ft_is_valid(char *str);
int								update_pwd_env(t_data *data);
int								cd_to_home(t_data *data);
int								cd_to_path(t_data *data, char *path);
int								export_variable(t_data *data, t_cmd *cmd);
int								add_in_export(t_data *data, char *str);
int								check_name(char *str, t_env *node,
									char *content);
int								update_oldpwd_and_chdir(t_data *data,
									char *path);
char							*get_content(char *str, int i);
void							handle_existing_name(t_data *data, char *name,
									char *content);
void							exit_cmd_not_found(t_data *data, t_cmd *cmd,
									char *arg);
void							ft_replace_in_env(t_data *data, char *name,
									char *value);
void							remove_from_list(t_env **list, char *name);
int								is_skippable_char(char c);
void							skip_whitespace(const char *input, int *i);
int								is_token_char(char c);
void							print_tokens(t_data *data);
void							sort(char **tmp);

// =========================== 🔍 CHECKERS ====================================

bool							is_builtin(char *cmd);
int								run_builtin(t_data *data, t_cmd *cmd);
int								which_command(t_data *data, t_cmd *cmd,
									int prev_fd);
void							handle_invalid_args(t_data *data, t_cmd *cmd,
									int prev_fd);
int								empty_line(const char *str);
int								is_directory(char *path);
int								check_quotes(char *input);

// =========================== 📂 FICHIERS ====================================

int								manag_infile(t_cmd *cmd, int prev_fd);
int								open_infile(char *str);
int								last_infile(t_cmd *cmd);
int								manag_outfile(t_cmd *cmd, int *pipe_fd);
int								open_outfile(char *file, t_TokenType mode);
int								last_outfile(t_cmd *cmd);
void							safe_close(int fd);
void							close_all_fds(int prev_fd, int pipe_read,
									int pipe_write);

// ============================= ⚠️ ERREURS ===================================

void							print_cmd_error(char *cmd);
void							print_no_such_file(char *path, char **args);
void							command_not_found(char *cmd);
void							no_such_file_or_directory(char *cmd);
void							permission_denied(char *file);
void							error_message(char *str);
void							is_a_directory(char *str);
char							*append_error_code(t_data *data, char *extract,
									int *i, int *first);
void							handle_invalid_command(t_data *data, t_cmd *cmd,
									int prev_fd);
void							exit_failed_resolution(t_data *data, t_cmd *cmd,
									int prev_fd);
char							*handle_error_code(t_data *data, char *value,
									int *i);

// ======================= 🔧 SIGNALS & SHELL MGMT ============================

void							signal_handler_here_doc(int signum);
void							setup_signal_heredoc(void);
void							handle_sigint(int sig);
void							init_signal(void);
void							reset_signals_child(void);

// =========================== 🧹 FREE MEMORY & EXIT ==========================

void							free_env_list(t_env *new_list);
void							free_one_token(t_token *token);
void							free_split(char **tmp);
void							free_token(t_token *head);
void							free_data(t_data *data);
void							exit_clean(t_data *data);
void							exit_clean2(t_data *data, t_cmd *cmd);
void							exit_d(t_data *data);
void							free_redir_list(t_redir *redir);
void							free_cmd_list(t_data *data);
void							free_cmd_list2(t_cmd *cmd);
void							close_fds(t_cmd *cmd);
void							free_and_exit(t_data *data, char *path,
									int code);
void							ft_exit_exec(int code, t_data *data,
									t_cmd *cmd);

#endif