#include "minishell.h"


char *read_line(t_cmd *config)
{
  char *line;
  line = readline(config->banner);
  if (!line[0])
  {
	while(!line[0])
	line = readline(config->banner);
  }
  else
	add_history(line);
    return (line);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ft_clean(t_cmd *config)
{
    char **cmd;
    cmd = malloc(sizeof(char *) * 4 );
    cmd[0] = strdup("rm");
    cmd[1] = strdup("-rf");
    cmd[2] = strdup(".status.txt .env.txt");
    cmd[3] = 0;
    pid_t pid;

    pid = fork();
    if (!pid)
    {
        execve("/bin/rm", cmd, config->envp);
        exit(0);
    }
    else
        wait(NULL);
}

void shell_loop(t_cmd *config)
{
    int status;

    status = 0;
    while(1) 
    {
            config->line = read_line(config); 
            if (!ft_strcmp(config->line, "echo $?")){
                printf("%d\n", status);
                status = 0;
            }
            else
            {
                status = shell_exec(config);
                ft_clean(config);
            }
            
    }
}
void ft_argv_print(char **argv, char *type)
{
  int i = 0;
  while (argv[i]){
    printf("%s argv print id %d : %s \n",type, i, argv[i]);
    i++;
  }
}


int shell_exec(t_cmd *config)
{
    char **cmd;
    int status;
    pid_t pid;
    cmd = malloc(sizeof(char *) * 4 );
    cmd[0] = strdup("bash");
    cmd[1] = strdup("-c");
    cmd[2] = ft_strjoin(config->line, "; echo $? > .status.txt ; env > .env.txt");
    cmd[3] = 0;

    pid = fork();
    if(!pid)
    {
        execve("/bin/bash",  cmd, config->envp);
        exit(127);
    }
    else
        waitpid(pid, &status, 0);
    ft_env_update(config);
    // ft_free_matrix(cmd);
    return(ft_get_status());
}

int ft_get_status()
{
    int fd;
    char buffer[5];
    
    fd = open(".status.txt", O_RDONLY);
    read(fd, buffer, 5);
    close(fd);
    return(ft_atoi(buffer));

}

void	ft_env_update(t_cmd *config)
{
    int righe;
    int fd;
	char *line;
    righe = 0;

	fd = open(".env.txt", O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return ;
    while(line)
    {
        righe++;
        line = get_next_line(fd);
    }
	fd = close(fd);
	fd = open(".env.txt", O_RDONLY);
	line = get_next_line(fd);
	config->envp = malloc(sizeof(char *) * (righe + 1));
    righe = 0;
	while (line)
	{
		config->envp[righe] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		righe++;
	}
    close(fd);
    config->envp[righe] = 0;
}


void shell_init(t_cmd *config, char **envp)
{
    config->envp = envp;
    config->banner = ft_strcat(getenv("USER"), "@minishell>");

}

int main(int argc, char **argv,char **envp)
{
    t_cmd config;
    shell_init(&config, envp);
	shell_loop(&config);
    return (1);
}

