/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:49:32 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 16:49:33 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	str_cpy(t_gnl_list *list, char *str)
{
	int	i;
	int	j;

	j = 0;
	if (!list)
		return ;
	while (list)
	{
		i = 0;
		while (list->buf_str[i])
		{
			if (list->buf_str[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->buf_str[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

int	found_nwl(t_gnl_list *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->buf_str[i] && i < BUFFER_SIZE)
		{
			if (list->buf_str[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	list_new(t_gnl_list **list, char *buf)
{
	t_gnl_list	*nw_node;
	t_gnl_list	*lt_node;

	nw_node = malloc(sizeof(t_gnl_list));
	if (!nw_node)
	{
		free(buf);
		return ;
	}
	lt_node = find_last_node(*list);
	if (!lt_node)
		*list = nw_node;
	else
		lt_node->next = nw_node;
	nw_node->buf_str = buf;
	nw_node->next = NULL;
}

int	len_to_newline(t_gnl_list *list)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (list)
	{
		i = 0;
		while (list->buf_str[i])
		{
			if (list->buf_str[i] == '\n')
				return (++len);
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

t_gnl_list	*find_last_node(t_gnl_list *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}
