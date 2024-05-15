/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:19:47 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/15 22:13:49 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "sys/wait.h"

typedef struct s_vars
{
	char	**command_1;
	char	**command_2;
	char	*prog_1;
	char	*prog_2;
	int		in_file;
	int		out_file;
	int		p_fd[2];
}	t_vars;

void	clean_up(t_vars *vars);
void	test_args(int argc, t_vars *vars);
char	*find_path(char *program);

#endif