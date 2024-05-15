/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:56:44 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/15 22:19:12 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *program)
{
	int	match;

	if (access(program, F_OK) == 0)
		ft_printf("found it!");
	else
		ft_printf("nie ma");
	exit(0);
}

void	test_args(int argc, t_vars *vars)
{
	if (argc != 5)
		exit_and_free(0, 2, "invalid number of arguments\n");
	if (!vars->command_1)
		exit_and_free(0, 2, "allocation error\n");
}

void	clean_up(t_vars *vars)
{
	free_split(vars->command_1);
	free_split(vars->command_2);
	free(vars->prog_1);
	free(vars->prog_2);
}
