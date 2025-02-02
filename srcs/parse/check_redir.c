/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:58:19 by bfiguet           #+#    #+#             */
/*   Updated: 2023/10/31 14:09:31 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in check_redir
static char	first_redir(char *str, t_data *data)
{
	char	redir;

	redir = str[data->i];
	data->i++;
	if (str[data->i] == '\0' || str[data->i] == '|')
	{
		if (str[data->i] == '|')
			print_error_redir("\0", '|');
		else
			print_error_redir("newline", '\0');
		return (-1);
	}
	if (str[data->i] == '<' || str[data->i] == '>')
	{
		if (str[data->i] != redir)
		{
			print_error_redir("\0", str[data->i]);
			return (-1);
		}
		redir = str[data->i];
		data->i++;
	}
	return (redir);
}

// check error with redirection's characteres
int	check_redir(t_data *data)
{
	char	redir;

	if (data->trimmed[data->i] == '<' || data->trimmed[data->i] == '>')
	{
		redir = first_redir(data->trimmed, data);
		if (redir == -1)
			return (-1);
		while (data->trimmed[data->i]
			&& ft_space(data->trimmed[data->i]) == 0)
			data->i++;
		if (data->trimmed[data->i] == '\0')
			return (print_error_redir("newline", '\0'));
		if (data->trimmed[data->i] == '|')
			return (print_error_redir("\0", '|'));
		if (data->trimmed[data->i] == '<' || data->trimmed[data->i] == '>')
			return (print_error_redir("\0", redir));
	}
	return (0);
}
