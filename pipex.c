/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:21:29 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/12 22:56:10 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	test_args(int argc, t_vars *vars)
{
	if (argc != 5)
		exit_and_free(0, 2, "invalid number of arguments\n");
	if (!vars->command_1)
		exit_and_free(0, 2, "allocation error\n");
}

static void	execute_p1(t_vars *vars)
{
	close(vars->p_fd[0]);
	dup2(vars->in_file, 0);
	close(vars->in_file);
	dup2(vars->p_fd[1], 1);
	close(vars->p_fd[1]);
	execve(vars->prog_1, vars->command_1, NULL);
}

static void	execute_p2(t_vars *vars)
{
	close(vars->p_fd[1]);
	dup2(vars->p_fd[0], 0);
	close(vars->p_fd[0]);
	dup2(vars->out_file, 1);
	close(vars->out_file);
	execve(vars->prog_2, vars->command_2, NULL);
}

static void	init_vars(t_vars *vars, char **argv)
{
	vars->in_file = open(argv[1], O_RDONLY);
	vars->out_file = open(argv[4], O_CREAT | O_WRONLY);
	vars->command_1 = ft_split(argv[2], ' ');
	vars->command_2 = ft_split(argv[3], ' ');
	vars->prog_1 = ft_strjoin("/usr/bin/", vars->command_1[0]);
	vars->prog_2 = ft_strjoin("/usr/bin/", vars->command_2[0]);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		pid_0;
	int		pid_1;

	unlink(argv[4]);
	init_vars(&vars, argv);
	pipe(vars.p_fd);
	test_args(argc, &vars);
	pid_0 = fork();
	if (pid_0 == 0)
	{
		pid_1 = fork();
		if (pid_1 == 0)
			execute_p1(&vars);
		else
		{
			waitpid(pid_1, NULL, 0);
			// ft_printf("my pid is %d\n", getpid());
			execute_p2(&vars);
		}
	}
	else
	{
		ft_printf("%d\n", pid_0);
		// waitpid(pid_0, NULL, 0);
		free_split(vars.command_1);
		free_split(vars.command_2);
		free(vars.prog_1);
		free(vars.prog_2);
	}
	return (0);
}
