/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:47:50 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/21 12:48:57 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "lib/libft.h"

typedef struct s_pipex
{
	char			*cmd;
	char			*here_doc;
	char			**envp;
	char			**args;
	int				input;
	int				output;
	int				ac;
	char			*outfile;
	char			*infile;
	int				pipefd[2];
	bool			is_first;
	bool			is_middle;
	bool			is_last;
	bool			is_here_doc;
	pid_t			pid;
	struct s_pipex	*prev;
	struct s_pipex	*next;

}					t_pipex;

typedef struct s_data
{
	t_pipex			*prev;
	char			*cmd;
	char			**envp;
	char			**av;
	int				ac;
	int				bonus;
}					t_data;

/* Initialisation de la struct */
t_pipex				*init_pipeline(t_data *data);
t_pipex				*create_node(t_data *data);
void				set_first_or_last(t_pipex *head);
t_pipex				*add_pipex_node(t_data *data);

/* Gestion des erreurs & free */
void				ft_free_pipeline(t_pipex *pipeline);
void				error_and_exit(t_pipex *node, char *msg);
void				cleanup(t_pipex *node);
void				cleanup_head(t_pipex *head);
void				cleanup_here_doc(t_pipex *node);
void				ft_perror(char *msg);

/* Verifs, secures & utils */
void				secure_close(int fd);
int					secure_open(char *filename, int flags);
void				secure_dup2(int old_fd, int new_fd);
pid_t				secure_fork(void);
int					file_is_executable(char *file);

/* Gestion des pipes & des forks */
void				do_pipe(t_pipex *node);
void				process_pipeline(t_pipex *head);
void				close_pipes(t_pipex *node);

/* Executeur */
void				exec(t_pipex *node);
void				exec_redirection(t_pipex *node);
void				here_doc_redirection(t_pipex *node);
void				last_node_redirection(t_pipex *node);
void				exec_redirection_first(t_pipex *node);

/* Here_doc*/
void				here_doc(t_pipex *node);
void				here_doc_put_in(t_pipex *node, int tmp_fd);

/* Gestion des PATHS */
char				*get_envp(char *name, t_pipex *node);
char				*get_path(t_pipex *node);
char				*search_in_path(t_pipex *node, char **all_path);
char				*check_current_directory(t_pipex *node);
char				*check_absolute_path(t_pipex *node);

#endif