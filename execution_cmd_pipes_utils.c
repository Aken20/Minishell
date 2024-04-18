/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_pipes_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:40:08 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/17 22:03:08 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	child_dupping_fds(t_input *input, t_var *var)
{
	if (var->prev_fd != -1)
	{
		if (dup2(var->prev_fd, STDIN_FILENO) == -1)
			return (ft_putstr_fd("Dup2 Error", STDERR_FILENO), false);
		close(var->prev_fd);
	}
	if ((var->i + 1) != input->num_of_cmd)
		if (dup2(var->fd[1], STDOUT_FILENO) == -1)
			return (ft_putstr_fd("Dup2 Error", STDERR_FILENO), false);
	close_fd(var);
	return (true);
}

void	wait_process(t_input *input, t_var *var)
{
	var->c = -1;
	while (++var->c < input->num_of_cmd)
	{
		if (wait(&var->status))
		{
			if (WIFEXITED(var->status))
			{
				if (WEXITSTATUS(var->status) == EXIT_FAILURE)
					g_exit_num = 127;
			}
			else if (WIFSIGNALED(var->status))
			{
				if (WEXITSTATUS(var->status))
					g_exit_num = 130;
			}
		}
	}
}

bool	close_fd(t_var *var)
{
	if (close(var->fd[0]) == -1)
		return (ft_putstr_fd("closing fd Error\n", STDERR_FILENO), false);
	if (close(var->fd[1]) == -1)
		return (ft_putstr_fd("closing fd Error\n", STDERR_FILENO), false);
	return (true);
}

bool	close_prev_fd(t_var *var)
{
	if (var->prev_fd != -1)
	{
		if (close(var->prev_fd) == -1)
		{
			ft_putstr_fd("error closing p_fd\n", STDERR_FILENO);
			return (false);
		}
		else
			var->prev_fd = -1;
	}
	return (true);
}

void	init_all(t_var *var)
{
	var->splitted = NULL;
	var->temp = NULL;
	var->cmd_path = NULL;
}
