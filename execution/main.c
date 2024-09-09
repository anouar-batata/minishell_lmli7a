/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:54:38 by alouriga          #+#    #+#             */
/*   Updated: 2024/09/09 05:27:39 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


void    execute_command(char **command, char **path)
{
    char *first_join;
    char *second_join;
    int i;
    
    i = 0;
	t_shell *env =  env_control(GET_ENV, 0, 0);
	if (check_built_ins(command, env) == 0)
		exit(0);
	else
	{
		while (path[i])
		{
			first_join = ft_strjoin(path[i], "/");
			second_join = ft_strjoin(first_join, command[0]);
				// printf("path == %s]]\n%s]]%s]]\n\n", second_join, command[0], command[1]);
			if (!access(second_join, X_OK))
			{
				
				execve(second_join, command, NULL);
				exit (0);
			}
			i++;
		}
	}
    printf("command not found \n");
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
    if (access(command[0], X_OK) == 0)
    {
        pid = fork();
        if (!pid)
        {
            execve(command[0], command, NULL);
            perror("Error");
            exit(127);
        }
    }
    // else
    //     printf("command not found \n");
    return (pid);
}

int    execution_commands(char **commands)
{
    char **path;
    char *p;
    int pid;

    p = find_path(env_control(GET_ENV, 0, 0));
    if (commands[0][0] == '/')
    {
        return (execute_path(commands));
    }
    else
    {
           path = ft_split_2(p, ':');
           pid = fork();
           if (!pid)
            execute_command(commands, path);
        return(pid);
        
    }
}

// int main(int ac, char **av, char **env)
// {
//     t_shell *envi = NULL;
//     t_commands *commands  = NULL;
//     int i = 0;
//     char **p;
//     ac = 0;
//     av = NULL;
//     while (env[i] != NULL)
//     {
//         p = split_first_equal(env[i]);
//         add(p, &envi);
//         i++;
//     }
//     env_control(0, envi, NULL);
//     while (1)
//     {
//         char *r = readline("shell:");
//         if(!r)
//             return (0);
//         add_history(r);
//         p = ft_split_2(r, '|');
//         add_list(p, &commands);
//         execute_pipes(commands);
//         commands = NULL; //free
//         // execution_commands(p);
//         wait(NULL);
//     }
// }
// // ls -a | cat -e

// // char **cmd;
// // cmd[0] = "ls"
// // cmd[1] = "-a"ew9