/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:21:29 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/16 11:03:48 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static void	init_vars(t_vars *vars, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 5))
			vars->paths = ft_split(envp[i], ':');
		i++;
	}
	vars->in_file = open(argv[1], O_RDONLY);
	vars->out_file = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	vars->command_1 = ft_split(argv[2], ' ');
	vars->command_2 = ft_split(argv[3], ' ');
	vars->prog_1 = find_path(vars->command_1[0], vars);
	vars->prog_2 = find_path(vars->command_2[0], vars);
}

static void	run_commands(t_vars *vars)
{
	int	pid_1;

	pid_1 = fork();
	if (pid_1 == 0)
		execute_p1(vars);
	else
	{
		waitpid(pid_1, NULL, 0);
		execute_p2(vars);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		pid_0;

	init_vars(&vars, argv, envp);
	test_args(argc, argv, &vars);
	pipe(vars.p_fd);
	pid_0 = fork();
	if (pid_0 == 0)
		run_commands(&vars);
	close(vars.p_fd[0]);
	close(vars.p_fd[1]);
	waitpid(pid_0, NULL, 0);
	clean_up(&vars, NULL);
	return (0);
}
