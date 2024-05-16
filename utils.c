/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:56:44 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/16 11:02:12 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *program, t_vars *vars)
{
	int		i;
	char	*curr_path;
	char	*prog_path;

	prog_path = ft_strjoin("/", program);
	i = 0;
	while (vars->paths[i])
	{
		curr_path = ft_strjoin(vars->paths[i], prog_path);
		if (access(curr_path, F_OK) == 0)
		{
			free(prog_path);
			return (curr_path);
		}
		free(curr_path);
		i++;
	}
	free(prog_path);
	return (NULL);
}

void	test_args(int argc, char **argv, t_vars *vars)
{
	if (argc != 5)
	{
		ft_putstr_fd("invalid number of arguments\n", 2);
		clean_up(vars, argv[0]);
	}
	if (!vars->command_1)
		exit_and_free(0, 2, "allocation error\n");
}

void	clean_up(t_vars *vars, char *message)
{
	if (message)
		perror(message);
	if (vars->command_1)
		free_split(vars->command_1);
	if (vars->command_2)
		free_split(vars->command_2);
	if (vars->paths)
		free_split(vars->paths);
	if (vars->prog_1)
		free(vars->prog_1);
	if (vars->prog_2)
		free(vars->prog_2);
	if (message)
		exit (1);
}
