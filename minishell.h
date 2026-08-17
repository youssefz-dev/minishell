/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:09:22 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/02 15:17:03 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_her
{
	int				file;
	struct s_her	*next;
	struct s_her	*prev;
}					t_her;

typedef struct s_env
{
	char			*str;
	int				envflag;
	int				exportflag;
	char			*key;
	char			*val;
	int				index;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_herdoc_d
{
	int		*x;
	char	*del;
	t_env	**env;
}		t_herdoc_d;

typedef struct s_list
{
	int		in;
	int		out;
	int		fd[2];
	pid_t	pid;
}				t_list;

typedef struct s_shell
{
	char			**cmd;
	int				infile;
	int				flgexp;
	char			*inname;
	int				outfile;
	int				validexp;
	int				exp;
	int				errfile;
	char			*outname;
	t_env			**env;
	struct s_shell	*next;
	struct s_shell	*prev;
}				t_shell;

typedef struct s_expand
{
	char	*var;
	char	*bfr;
	char	*aft;
	char	*value;
	int		i;
	int		index;
}	t_expand;

typedef enum s_tokentyp
{
	PIPE,
	HRDC,
	APPND,
	IN_RED,
	OUT_RED,
	WORD,
}	t_tokentyp;

typedef struct s_tokens
{
	char			*token;
	t_tokentyp		type;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}		t_tokens;

extern int	g_flag;

void		sig_action(int sig);
void		sig_action1(int sig);
void		sig_action2(int sig);
void		sig_action10(int sig);
int			execshell(t_shell *shell);
int			one_proc(t_shell *shell, t_list *list);
void		first_proc(t_shell *shell, t_list *list);
void		md_proc(t_shell *shell, t_list *list);
void		last_proc(t_shell *shell, t_list *list);
int			ft_wait(t_list *list);
int			is_builtins(t_shell *shell, t_list *list);
int			run_built(t_shell *shell, t_list *list);
int			ft_isdigit(int c);
char		*pwd1(void);
void		free_env(t_env **env);
int			echo(t_shell *shell);
int			cd(t_shell *shell);
int			pwd(void);
int			export(t_shell *shell);
int			unset(t_shell *shell);
int			env(t_shell *shell);
int			exit1(t_shell *shell, t_list *list);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *s);
char		*ft_strdup(char *s1);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, char *src, size_t dstsize);
char		*ft_strnstr(char *haystack, char *needle, size_t len);
char		**ft_split(char *s, char c);
void		ft_free(char **ptr);
void		add_env(t_env **env);
int			is_builtins1(t_shell *shell);
int			ft_isdigit(int c);
void		print_export(t_env **env);
void		exec_error(t_shell *shell, t_list *list);
void		change_pwd(t_shell *shell);
int			is_key(char *ptr);
int			flag_pos(char *ptr);
int			is_env(char *ptr, t_env **env, int pos);
void		replace(char *ptr, t_env **env, int pos);
void		add_to(char *ptr, t_env **env, int pos);
char		*ft_strrchr(char *s, int c);
void		mini_exec(t_shell *shell, t_list *list);
void		free_shell(t_shell *shell);
void		free_list(t_list *list);
void		free_shell1(t_shell *shell);
t_list		*list_init(t_shell *shell);
t_shell		*ft_lstlast(t_shell *lst);
void		ft_lstadd_back1(t_env **lst, t_env *new);
t_env		*env_init(char *str, int envflag, int exportflag);
t_env		*env_init2(char *str, int envflag, int exportflag);
int			is_env1(char *ptr);
char		*get_line(char	*key, char *val);
t_env		*get_env2(t_env **env, char *key);
void		handel_sh(t_env **env);
int			search_env(t_env **env, char *key);
long		ft_atoi1(char *str);
char		*get_pwd(t_env *env);
void		change_oldpwd(t_shell *shell);
int			ft_strrchr1(char *s, int c);
void		handel_under(t_shell *shell);
void		file_error(t_shell *shell, t_list *list);
int			file_error1(t_shell *shell, t_list *list);
int			env_utils(t_shell *shell, t_env **env);
void		mini_utils(t_shell *shell, t_list *list);
int			cd_utils(t_shell *shell, char *str);
void		cmd_exec(t_shell *shell, t_list *list, char **env);
char		*get_path(char *cmd, char **env);
void		exec_file(t_shell *shell, char **env);
void		close_fd(int fd);
void		free_shell0(t_shell *shell);
void		free_shell_rev(t_shell *shell);
void		pro_mpte(t_env **env);
int			ft_strcmp(char *s1, char *s2);
t_tokens	*add_token(t_tokens *lst, char *str, int type);
void		handlle_int(int sig);
t_tokens	*tokeni_zation(char *token);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_strndup(char *s1, int n);
t_shell		*parse_token(t_tokens *lst, t_env **env, int *x, t_her **her);
int			checked_syntax(t_tokens *lst, int *x);
int			check_unclosed_quote(char *line, int *x);
t_shell		*new_lst(void);
int			create_file(char *del, t_env **env, int *x);
char		*ft_strjoin1(char *s1, char *s2);
char		*ft_itoa(int n);
void		ft_putstr_fd(char *s, int fd);
int			ft_strchr(char *s, int c);
char		**add_to_array(char **s, char *str);
int			hav_dolare(char *s);
char		*next_dolar_str(char *s);
char		*ft_strtrim77(char *s1, char *set);
int			hav_dolare(char *s);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*get_var(char *str, t_env **env, int *x);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			dollar_index(char *s);
int			is_sqoute(char *s);
char		*get_in_quote(char *s, t_env **env, int *x);
int			is_dquote(char *s);
void		free_array(char **s);
char		*get_prev_equale(char *s);
void		ft_putstr_fd(char *s, int fd);
char		*help_heroc(char *ptr, t_env **env, char *del, int *x);
int			count_hrdc(t_tokens *s);
void		free_tok(t_tokens *head);
int			is_status(char *s);
int			is_squote_end(char *s);
int			is_dquote_end(char *s);
void		fre_shel(t_shell *head);
void		free_token(t_tokens *lst);
char		**ft_split1337(char *s, char c);
int			is_quotes_in_del(char *del);
void		handle_pipe(t_shell **help);
void		handlle_int_herdoc(int sig);
char		*new_file(void);
void		print_mssg(void);
char		*get_af_equale(char *s);
int			dollar_count(char *s);
int			dollar_count(char *s);
int			is_dir(char *ptr);
int			is_space(char *s);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			is_min(char *s);
int			is_delemtre(char *ptr, char *del);
int			dq_count(char *s);
char		*handle_eve_dl(char *s);
int			is_ev_del(char *s);
char		*remove_quotes(char *s);
char		*quote_her(char *s);
t_tokens	*handll_inred(t_shell *help, t_tokens *tok, t_env **env, int *x);
t_tokens	*handlle_oured(t_shell *help, t_tokens *tok, t_env **env, int *x);
t_tokens	*handlle_appnd(t_shell *help, t_tokens *tok, t_env **env, int *x);
t_tokens	*handlle_herd(t_shell *help, t_tokens *tok, t_env **env, int *x);
void		handlle_sq(t_shell *help, t_tokens *tok, t_env **env, int *x);
char		*handle_eve_dl(char *s);
int			is_ev_del(char *s);
char		*handle_normal_part(char *s, int *i);
char		*quote_her(char *s);
int			is_quote(char c);
int			is_dollar_quote(char *s, int i);
char		*handle_dollar_quote(char *s, int *i);
char		*handle_classic_quote(char *s, int *i);
void		help_inred(char *file, t_shell *help, int *x, t_env **env);
void		help_outred1(char *file1, t_shell *help, int *x, t_env **env);
void		help_outred2(t_shell *help, t_tokens *tok, char *file1);
int			help_outred3(char *file1, t_shell *help, t_env **env, int *x);
void		help_inred_4(char *s, t_shell *help);
void		help_infil3(char *file, t_env **env, int *x, t_shell *help);
int			help_appnd5(char *file2, int *x);
void		help_appnd1(char *file2, t_env **env, int *x, t_shell *help);
void		help_appnd2(char *file2, int *x, t_shell *help, t_env **env);
void		help_appnd3(char *s, t_shell *help);
void		help_appnd4(char *file2, t_shell *help);
void		help_no_quotes1(char *s, t_shell *help, int *x, t_env **env);
void		handlle_val_dq(t_shell *help, t_tokens *tok, t_env **env, int *x);
void		handlle_inval_dq(t_shell *help, t_tokens *tok, t_env **env, int *x);
void		free_her(t_her **her);
void		hand_exit(char *s, int x, t_env **env);
void		ft_lstadd_back4(t_her **lst, t_her *new);
t_her		*her_init(int fd);
int			help_seg(char *input, t_tokens *tok, int *x);
void		help_inis(int *x, t_env **env);
char		*inpu_red(void);
int			handle_it(t_her **her, t_tokens *tok, t_env **env, int *x);
int			open_file(char *ptr, char *ptr1);
int			help_heredoc(char **ptr);
int			help_loop_norm(char *ptr, char *ptr1, char *quotes, t_herdoc_d *d);
void		handle_dollar_question(t_expand *ex, char *str, int *x);
void		handle_dollar_var(t_expand *ex, char *str, t_env **env);
void		free_her0(t_her **her);
int			fun1(char **s, char **s1);
void		fun2(char *file2, t_env **env, t_shell *help, int *x);

#endif