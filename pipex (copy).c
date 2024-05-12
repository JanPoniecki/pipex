/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:21:29 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/11 20:51:12 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	test_args(int argc)
{
	if (argc != 5)
		exit_and_free(0, 2, "invalid number of arguments\n");
}

int	main(int argc, char **argv)
{
	char	**program_1;
	char	**program_2;
	char	*command;
	int		fd_0;
	int		fd_1;
	int		pp[2];
	int		pid;

	t_vars	vars;

	// test_args(argc);
	fd_0 = open(argv[1], O_RDONLY);
	fd_1 = open(argv[4], O_CREAT | O_WRONLY);
	dup2(fd_0, 0);
	program_1 = ft_split(argv[2], ' ');
	program_2 = ft_split(argv[3], ' ');
	command = ft_strjoin("/usr/bin/", program_1[0]);
	pipe(pp);
	pid = fork();
	if (pid == 0)
	{
		close(pp[0]);
		dup2(pp[1], 1);
		execve(command, program_1, NULL);
	}
	else
	{
		wait(0);
		close(pp[1]);
		dup2(pp[0], 0);
		dup2(fd_1, 1);
		close(fd_1);
		execve(ft_strjoin("/usr/bin/", program_2[0]), program_2, NULL);
	}
	return (0);
}
