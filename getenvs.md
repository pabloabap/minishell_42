__1. src/expander/expansion_malloc.c__
```
int	ft_expander(t_lexem *lex_list, t_single_cmd *cmd_list, int *exit);
\_static int	ft_str_expander(t_lexem *lex_list, int *exit);
	\_int	ft_expansion_malloc(char **dst, t_lexem *src, int *buff, int *exit);
		\_static int	ft_exp_logic(char *str, int *i, int *chars, int *exit);
			\_static int	ft_exp_len(char *str, int *i, int *chars, int *exit);
				\_getenv
```
__2. src/expander/fill_expansion.c__
```
int	ft_expander(t_lexem *lex_list, t_single_cmd *cmd_list, int *exit);
\_static int	ft_str_expander(t_lexem *lex_list, int *exit);
	\_int	ft_fill_expansion(char *dst, t_lexem *src, int *buff, int *exit);
		\_static int	ft_exp_fill(char *dst, char *src, int *i, int *chars);
			\_static int	ft_fill_var(char *dst, char *src, int *i, int *chars);
				\_getenv
```

__3. src/executor/ft_path_finder.c__
```
int	ft_executor(t_single_cmd *head, t_env *env, int *err_n)
\_static int	ft_child_mng(t_single_cmd *cmd, int std_out, t_env *env, int *en)
	\_int	ft_path_finder(t_single_cmd *cmd, int *err_n)
		\_static int	ft_check_path_env(t_single_cmd *cmd, int *err_n)
			\_getenv

```

__4. src/executor/ft_hdoc.c__
```
int	ft_executor(t_single_cmd *head, t_env *env, int *err_n)
\_static int	ft_prepare_exec(t_single_cmd *head, int *std_out, int *err_n)
	\_int	ft_check_hdoc(t_single_cmd *cmd, int *err_n)
		\_static int	ft_heredoc_creation(t_lexem *redir, int *err_n)
			\_static int	ft_fill_hdoc(char *line, int *err_n, int fd_hdoc)
				\_static int	ft_write_env_var(char *line, int v_start, int *err_n, int hdoc)
					\_getenv
```
