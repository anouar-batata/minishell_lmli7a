/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:54:38 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/26 05:06:56 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **convert_env_to_td_env(t_shell *env)
{
    int size = ft_lstsize(env);
    char *first_join;
    char *second_join;
    char **td_env = malloc((size + 1) * sizeof(char *));
    int i = 0;
    if (!td_env)
        return(NULL);
    while (env)
    {
        first_join = ft_strjoin(env->k, "=");
        second_join = ft_strjoin(first_join, env->v);
        td_env[i] = ft_strdup(second_join);
        env = env->next;
        i++;
    }
    td_env[i] = NULL;
    return(td_env);
}

void    add_list(char **p, t_commands **curr)
{
    int i = 0;
    t_commands *tmp;
    char **res;

    while (p[i] != NULL)
    {
        res = ft_split_2(p[i], ' ');
         tmp = ft_lstnew_2(res);
         ft_lstadd_back_2(curr, tmp);
         i++;
    }
}

void ft_error(int err_no)
{
    if (err_no == 1)
        printf("command not found\n");
    else
        return ;
}


void    execute_command(char **command, char **path)
{
    char *first_join;
    char *second_join;
    
    t_shell *env = env_control(GET_ENV, 0, 0);
    char **td_env = convert_env_to_td_env(env);
    int i;
    int j;
    
    i = 0;
    j = 0;
    if (!path)
    {
        
        write(2, " : command not found\n", 21);
        exit(127);
    }
    if (ft_strcmp(command[0], "\0") == 0)
    {
        write(2, " : command not found\n", 21);
        exit(127);
    }
	while (path[i])
	{
		first_join = ft_strjoin(path[i], "/");
		second_join = ft_strjoin(first_join, command[0]);
		if (!access(second_join, X_OK))
		{
			execve(second_join, command, td_env);
			exit (127);
                
		}
		i++;
	}
    write(2, command[0], ft_strlen(command[0]));
    write(2, " : command not found\n", 21);
    exit(127);
}

char *find_path(t_shell *env)
{
    while (env)
    {
        if (!ft_strcmp(env->k, "PATH"))
        {
            return (env->v);
        }
        env = env->next;
    }
    return (NULL);
}

int    execute_path(char **command)
{
    int pid;
    t_shell *env = env_control(GET_ENV, 0, 0);
    char **td_env = convert_env_to_td_env(env);
    if (access(command[0], X_OK) == 0)
    {
        pid = fork();
        if (!pid)
        {
            execve(command[0], command, td_env);
            perror(command[0]);
            exit(127);
        }
    }
    else
    {
       perror("access");
       exit_status(127, ADD);
       return (-1);
    }
    return (pid);
}

int execute_programme(char **commands, char **path)
{
    char *first_join;
    char *second_join;
    int pid;
    t_shell *env = env_control(GET_ENV, 0, 0);
    char **td_env = convert_env_to_td_env(env);
    int i = 0;

    pid = fork();

        if (!pid)
        {
            if (!access(commands[0], X_OK))
            {
                {
                    // execve(second_join, commands, NULL);
                    execve(commands[0], commands, td_env);
                    
                }
            }
            perror(commands[0]);
            exit(127);
        }
    return (pid);
}

// int check_the_file(char **commands)
// {
//     int pid;
//     t_shell *env = env_control(GET_ENV, 0, 0);
//     char **td_env = convert_env_to_td_env(env);

//     if (!access(commands[0], F_OK))
//     {
//         if(!access(commands[0], X_OK))
//         {
//             pid = fork();
//             if (pid == 0)
//             {
//                 execve(commands[0], commands[0], td_env);
//                 exit (127);
//             }            
//         }
        
//     }
// }

int    execution_commands(char **commands, t_commands *cmds)
{
    char **path;
    char *p;
    int pid;
    int bkp_0 = dup(0);
    int bkp_1 = dup(1);

	t_shell *env =  env_control(GET_ENV, 0, 0);
    p = find_path(env_control(GET_ENV, 0, 0));
    if (check_the_redirection(cmds) == -1)
    {
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
        return(-1);
    }
    if (commands[0][0] == '/')
    {
        pid = execute_path(commands);
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
        if (pid > 0)
            return (pid);
        else
            return (-2);
    }
    else if (commands[0][0] != '/' && ft_strchr_pro(commands[0], "/"))
    {
        path = ft_split_2(p, ':');
        return (execute_programme(commands,path));
    }
	else if(check_built_ins(commands, env) == 0)
    {
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
		return (255);
    }
    else if (exit_status(0, 0) == 1)
    {
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
        return(-1);
    }
    else
    {
        path = ft_split_2(p, ':');
        pid = fork();
        if (!pid)
        execute_command(commands, path);
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
        return(pid);
    }
}
