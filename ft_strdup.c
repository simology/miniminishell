/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatifi <mlatifi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:11:41 by mlatifi           #+#    #+#             */
/*   Updated: 2022/01/21 19:20:29 by mlatifi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*string;
	int		string_size;
	int		i;

	i = 0;
	string_size = ft_strlen(s1) + 1;
	string = malloc(sizeof(char) * string_size);
	if (!string)
		return (0);
	while (i < string_size)
	{
		string[i] = ((char *)s1)[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}
