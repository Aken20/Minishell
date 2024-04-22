/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:42:00 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/04/22 12:13:03 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char *pwd, t_input *input)
{
	char	*temp;
	char	*temp2;

	if (!pwd)
		return ;
	if (!ft_get_env(pwd, input->env))
	{
		temp = getcwd(NULL, 0);
		temp2 = ft_strjoin(pwd, temp);
		add_env(temp2, input);
		(free(temp), free(temp2));
	}
	else
	{
		temp = getcwd(NULL, 0);
		temp2 = ft_strjoin(pwd, temp);
		replace_env(temp2, input, ft_get_env_index(pwd, input->env));
		(free(temp), free(temp2));
	}
	return ;
}

int	cd(t_cmd *cmd, t_input *input)
{
	update_pwd("OLDPWD=", input);
	if (!cmd || !cmd->cmd[1])
	{
		if (chdir(ft_get_env("HOME", input->env)) == -1)
			printf("cd: HOME not set\n");
	}
	else if (chdir(cmd->cmd[1]) == -1)
		printf("cd: no such file or directory: %s\n", cmd->cmd[1]);
	update_pwd("PWD=", input);
	return (1);
}

int	pwd(void)
{
	char	*str;

	str = NULL;
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	if (str)
		free(str);
	return (1);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	if (!env || !env[0])
		return (1);
	while (env[i])
		printf("%s\n", env[i++]);
	return (1);
}

int	ft_exit(t_cmd **cmd, t_input *input, t_var *var)
{
	int	len;

	if (cmd && cmd[0])
	{
		len = env_len(cmd[0]->cmd);
		printf("exit\n");
		if (len > 2)
			return (printf("bash: exit: too many arguments\n"));
		if (str_is_digit(cmd[0]->cmd[1]) == 1)
			printf("bash: exit: %s: numeric argument required\n",
				cmd[0]->cmd[1]);
		if (cmd[0]->cmd[1])
			g_exit_num = ft_atoi(cmd[0]->cmd[1]);
	}
	free_env(input->env);
	free_all(cmd, input, var);
	clear_history();
	exit (g_exit_num);
}
