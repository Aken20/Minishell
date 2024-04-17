/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:24:30 by suibrahi          #+#    #+#             */
/*   Updated: 2024/04/16 18:40:12 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum) 
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// there is problem in this function its not in the header
		// rl_replace_line("", 0);
		g_exit_num = 130;
		rl_redisplay();
	}
}
