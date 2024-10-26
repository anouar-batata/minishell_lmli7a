/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:42:01 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/26 05:42:03 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int   check_the_redirection(t_commands *command)
// {
//     t_redir *curr;
//     int fd;
//     curr = command->redir_lst;
//     while (curr)
//     {
//         if (curr->redir_type == REDIR_OUT)
//         {
//            fd = open(curr->file, O_WRONLY | O_CREAT  | O_TRUNC, 0644);
//            if (!fd)
//                 printf("error\n"); // to do
//         }
//         else if (curr->redir_type == DREDIR_OUT)
//         {
//             fd = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//              if (!fd)
//                 printf("error\n"); // to do
//         }
//         else if (curr->redir_type == REDIR_IN)
//         {
//             fd = open(curr->file, O_RDONLY);
//             if (fd == -1)
//             {
//                return (-1); 
//                 printf("the file does not exict\n"); // to do
//             }
//         }
//         if (curr->next == NULL)
//         {
//             if (curr->redir_type == REDIR_OUT || curr->redir_type == DREDIR_OUT)
//                 dup2(fd, 1);
//             else
//                 dup2(fd, 0);
//             close(fd);
//             return (0);
//         }
//         close(fd);
//         curr = curr->next;
//     }
//     return (0);
// }


// int check_the_redirection(t_commands *command)
// {
//     t_redir *curr;
//     int fd;

//     curr = command->redir_lst;
//     while (curr)
//     {
//         if (curr->redir_type == REDIR_IN)
//         {
//             fd = open(curr->file, O_RDONLY);
//             if (fd == -1)
//             {
//                 perror("Error: file does not exist for input redirection"); // handle error
//                 return (-1);
//             }
// 			if (curr->to_close)
// 				unlink(ft_strjoin2("./", curr->file));
//         }
//         if (curr->next == NULL)
//         {
//             dup2(fd, STDIN_FILENO);  
//             close(fd);
//             return (0);
//         }
//         curr = curr->next;
//     }

//     curr = command->redir_lst;
//     while (curr)
//     {
//         if (curr->redir_type == REDIR_OUT)
//         {
//             fd = open(curr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (fd == -1)
//             {
//                 perror("Error opening file for output redirection"); // handle error
//                 return (-1); 
//             }
//         }
//         else if (curr->redir_type == DREDIR_OUT)
//         {
//             fd = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//             if (fd == -1)
//             {
//                 perror("Error opening file for append redirection"); // handle error
//                 return (-1);
//             }
//         }
//         if (curr->next == NULL)
//         {
//             dup2(fd, STDOUT_FILENO);
//             close(fd);
//             return (0);
//         }
//         curr = curr->next;
//     }    
//     return (0);
// }


int check_the_redirection(t_commands *command)
{
    t_redir *curr;
    int fd = -1;

    // Handle input redirections
    curr = command->redir_lst;
    while (curr)
    {
        if (curr->redir_type == REDIR_IN)
        {
            if (fd != -1) close(fd);  // Close previous fd if any
            fd = open(curr->file, O_RDONLY);
            if (fd == -1)
            {
                perror("Error: file does not exist for input redirection");
                return (-1);
            }
            if (curr->to_close)
            {
                char *temp = ft_strjoin2("./", curr->file);
                unlink(temp);
                free(temp);
            }
        }
        curr = curr->next;
    }
    if (fd != -1)  // Apply input redirection if any
    {
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    // Handle output redirections
    curr = command->redir_lst;
    fd = -1;
    while (curr)
    {
        if (curr->redir_type == REDIR_OUT || curr->redir_type == DREDIR_OUT)
        {
            if (fd != -1) close(fd);  // Close previous fd if any
            fd = open(curr->file, O_WRONLY | O_CREAT | (curr->redir_type == REDIR_OUT ? O_TRUNC : O_APPEND), 0644);
            if (fd == -1)
            {
                perror("Error opening file for output redirection");
                return (-1);
            }
        }
        curr = curr->next;
    }
    if (fd != -1)  // Apply output redirection if any
    {
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    return (0);
}