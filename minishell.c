/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:11:39 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/30 19:06:41 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_handler(int sig)
{
	if (g_signal_status == 0)
	{
		exit_status(1, ADD);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_env(char **env, t_shell **envi)
{
	int		i;
	char	**p;

	i = 0;
	while (env[i])
	{
		p = split_first_equal(env[i]);
		add(p, envi);
		i++;
	}
	env_control(0, *envi, NULL);
}

void	parse_and_excute(t_data **lst, t_shell **envi, t_commands **command)
{
	expanding(*lst, *envi);
	check_if_to_expand_in_heredoc(*lst);
	join_word(lst);
	check_for_ambiguous(*lst);
	expanding_deleter(lst);
	split_word(lst);
	remove_spaces(lst);
	make_a_list_for_louriga_aviable(*lst, command, *envi);
	if (*command && !g_signal_status)
		execute_pipes(*command);
	g_signal_status = 0;
	smart_free(RL);
}

int	start_minishell(t_data **lst, t_shell **envi,
	t_commands **command, char *rl)
{
	if (!rl)
	{
		printf("exit\n");
		exit(exit_status(0, 0));
	}
	if (!ft_strlen2(rl))
	{
		free (rl);
		return (-1);
	}
	add_history(rl);
	fill_lst(rl, lst, 0);
	free(rl);
	change_it_to_word(*lst);
	if (parse_error(*lst))
	{
		smart_free(RL);
		exit_status(258, ADD);
		return (-1);
	}
	parse_and_excute(lst, envi, command);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data		*lst;
	char		*rl;
	t_shell		*envi;
	t_commands	*command;

	envi = NULL;
	if (!isatty(0))
		return (1);
	set_env(env, &envi);
	rl_catch_signals = 0;
	exit_status(0, ADD);
	while (1)
	{
		lst = NULL;
		command = NULL;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrl_c_handler);
		envi = env_control(GET_ENV, 0, 0);
		rl = readline("slawishell ~> ");
		if (start_minishell(&lst, &envi, &command, rl))
			continue ;
	}
}
