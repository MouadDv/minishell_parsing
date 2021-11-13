/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:38:33 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/12 17:21:11 by chicky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_global_export_norm1(char *s, int *i, t_node *node, char **ptr)
{
	int		flag;
	char	*value;
	int		ret;

	flag = 0;
	*s = '\0';
	value = ft_strjoin("=\"", (s + 1));
	value = ft_strjoin(value, "\"");
	ft_check(&node, ptr[*i], value, &flag);
	if (flag != 2)
	{
		ret = ft_check_valid_identifier(ptr[*i]);
		if (ret != 1)
			test_add(&node, ptr[*i], value);
		else
		{
			printf ("bash: export: « %s%s» : identifiant non valable\n",
				ptr[*i], value);
			g_data.statuscode = 1;
		}
	}
}

void	ft_global_export_norm2(int *i, t_node *node, char **ptr)
{
	int		flag;
	char	*value;
	int		ret;

	flag = 0;
	value = ft_strdup("");
	ft_check(&node, ptr[*i], value, &flag);
	if (flag != 2)
	{
		ret = ft_check_valid_identifier(ptr[*i]);
		if (ret != 1)
			test_add(&node, ptr[*i], value);
		else
		{
			printf ("bash: export: « %s » : identifiant non valable\n",
				ptr[*i]);
			g_data.statuscode = 1;
		}
	}
}

void	ft_global_export(char **ptr, t_node	*node)
{
	int		i;
	char	*s;

	i = 1;
	while (ptr[i])
	{
		if ((ft_strncmp(ptr[i], "=", 1)) != 0)
		{
			s = ft_strchr(ptr[i], '=');
			if (s)
				ft_global_export_norm1(s, &i, node, ptr);
			else
				ft_global_export_norm2(&i, node, ptr);
		}
		else
		{
			printf ("bash: export: « %s » : identifiant non valable\n",
				ptr[i]);
			g_data.statuscode = 1;
		}
		i++;
	}
}


void	ft_export(t_node *head)
{
	t_node	*temp;

	temp = head;
	while (temp != NULL)
	{
		write(1, "declare -x ", 11);
		write(1, temp->name, ft_strlen(temp->name));
		write(1, temp->val, ft_strlen(temp->val));
		write(1, "\n", 1);
		temp = temp->next;
	}
}
