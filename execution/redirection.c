/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:42:01 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/07 18:53:26 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int   check_the_redirection(t_commands *command)
{
    t_redir *curr;
    int fd;
    curr = command->redir_lst;
    while (curr)
    {
        if (curr->redir_type == REDIR_OUT)
        {
           fd = open(curr->file, O_WRONLY | O_CREAT  | O_TRUNC, 0644);
           if (!fd)
                printf("error\n"); // to do
        }
        else if (curr->redir_type == DREDIR_OUT)
        {
            fd = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
             if (!fd)
                printf("error\n"); // to do
        }
        else if (curr->redir_type == REDIR_IN)
        {
            fd = open(curr->file, O_RDONLY);
            if (fd == -1)
            {
               return (-1); 
                printf("the file does not exict\n"); // to do
            }
        }
        if (curr->next == NULL)
        {
            if (curr->redir_type == REDIR_OUT || curr->redir_type == DREDIR_OUT)
                dup2(fd, 1);
            else
                dup2(fd, 0);
            close(fd);
            return (0);
        }
        close(fd);
        curr = curr->next;
    }
    return (0);
}
