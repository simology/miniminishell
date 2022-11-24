#ifndef MINISHELL_H
#define MINISHELL_H
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"

/*
#include <stdio.h>
#include <string.h> 
#include <stddef.h>
#include <sys/types.h>
*/

typedef struct s_cmd
{
    char    *line;
    char    **cmd_line;
    char    **cmd_args;
    char    **cmd_value;
    char    *banner;
    char    **envp;

} t_cmd;

char *read_line(t_cmd *config);
void shell_loop(t_cmd *config);
int shell_exec(t_cmd *config);
void shell_init(t_cmd *config, char **envp);
void	ft_env_update(t_cmd *config);
int     ft_get_status();
char	*ft_strcat(char *dest, char *src);
char	*ft_strdup(const char *s1);
int	ft_atoi(const char *str);
// char	*ft_strjoin(char const *s1, char const *s2);
// size_t	ft_strlen(const char *s);
#endif