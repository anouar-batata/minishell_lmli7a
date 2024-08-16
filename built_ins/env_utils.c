/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:47:25 by alouriga          #+#    #+#             */
/*   Updated: 2024/08/15 05:02:26 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    remove_node(t_shell **env, char *str)
{
    t_shell *tmp = *env;
    t_shell *prev = NULL;

    if (tmp != NULL && ft_strcmp(tmp->k, str) == 0)
    {
        *env = tmp->next;
        free(tmp->k);
        free(tmp->v);
        free(tmp);
        return ;
    }
    while (tmp && ft_strcmp(tmp->k, str) != 0)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
     prev->next = tmp->next;
}
// void    add_node(t_shell **env, char *k, char *v)
// {
//     t_shell *tmp;
//     t_shell *new;
    
//     tmp = *env;
//     new = ft_lstnew(k, v);
//     while (tmp)
//         tmp = tmp->next;
//     tmp->next = new;
// }

void    edit_value(t_shell **env, char *k, char *v)
{
    t_shell *tmp;

    tmp = *env;
    while (tmp)
    {
        if (ft_strcmp(tmp->k, k) == 0)
        {
            tmp->v = v;
            break;
        }
        tmp = tmp->next;
    }
}

void add_node(t_shell **env, char *k, char *v)
{
    t_shell *tmp;
    t_shell *new;
    
    new = ft_lstnew(k, v);
    if (*env == NULL)
    {
        *env = new;
        return;
    }

    tmp = *env;
    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = new;
}

void    *env_control(int behaviour, void *key, char *value)
{
    static t_shell *env;

    if (behaviour == 0)
        env = (t_shell *)key;
    else
    {
        if (behaviour == REMOVE_NODE)
            remove_node(&env, key);
        else if (behaviour == ADD_NODE)
            add_node(&env, key, value);
        else if (behaviour == GET_ENV)
            return (env);
        else if (behaviour == EDIT_VALUE)
            edit_value(&env, key, value);
    }
    return (0);
}