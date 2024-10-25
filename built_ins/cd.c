/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:51:43 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/24 12:27:47 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_the_directory(void)
{
	char	*str;
	char	*old_pwd;
	t_shell	*env;
	t_shell	*tmp;

	str = getcwd(NULL, 0);
	env = env_control(GET_ENV, 0, 0);
	tmp = env;
	old_pwd = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->k, "PWD") == 0)
		{
			old_pwd = tmp->v;
			break ;
		}
		tmp = tmp->next;
	}
	env_control(EDIT_VALUE, "PWD", str);
	env_control(EDIT_VALUE, "OLDPWD", old_pwd);
}

char	*get_home(void)
{
	t_shell	*env;
	t_shell	*tmp;

	env = env_control(GET_ENV, 0, 0);
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->k, "HOME"))
			return (tmp->v);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_cd(char **av)
{
	char	*str;

	if (av[1] == NULL)
		str = get_home();
	else
		str = av[1];
	if (!chdir(str))
		change_the_directory();
	else
	{
		write(2, av[1], ft_strlen(av[1]));
		write(2, " : No such file or dirrectory\n", 30);
		return (2);
	}
	return (0);
}
