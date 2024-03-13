/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:46:24 by aken              #+#    #+#             */
/*   Updated: 2024/03/13 10:42:19 by aken             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirections(t_red	*redirection)
{
	t_red	*tmp;

	if (!redirection)
		return ;
	tmp = redirection;
	while (tmp)
	{
		tmp = redirection->next_redricts;
		if (redirection->file_name)
			free(redirection->file_name);
		free(redirection);
	}
	redirection = NULL;
}

void	free_input(t_input *input)
{
	if (!input)
		return ;
	if (input->cmds)
		free (input->cmds);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd_name)
		free (cmd->cmd_name);
	if (cmd->redricts)
		free_redirections(cmd->redricts);
	if (cmd->cmd)
	{
		while (cmd->cmd[i])
			free(cmd->cmd[i++]);
		free(cmd->cmd);
	}
	free(cmd);
}

void	free_all(t_cmd **cmd, t_input *input)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
			free_cmd(cmd[i++]);
		free(cmd);
	}
	free_input(input);
}
