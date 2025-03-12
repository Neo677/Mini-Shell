/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:35:06 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 15:35:09 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest_ptr;
	const char	*src_ptr;
	size_t		i;

	dest_ptr = dst;
	src_ptr = src;
	if (dest_ptr < src_ptr)
	{
		i = 0;
		while (i < len)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	else if (dest_ptr > src_ptr)
	{
		i = len;
		while (i > 0)
		{
			dest_ptr[i - 1] = src_ptr[i - 1];
			i--;
		}
	}
	return (dst);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ELEMENT_COUNT 10

int	main(void) {

	// On crée une zone de mémoire de 10 entiers et contenant
	// que neuf valeurs. La dixième est non utilisée (0).
	int data[] = { 20, 30, 40, 50, 60, 70, 80, 90, 100, 0 };

	// On affiche le contenu de la collection
	for( int i=0; i<ELEMENT_COUNT; i++ ) {
		printf( "%d ", data[i] );
	}
	puts( "" );  // Un retour à la ligne

	// On décale les éléménts dans la collection ...
	void * source = (void *) data;
	void * destination = (void *) ( data + 1 );
	size_t size = ELEMENT_COUNT * sizeof( int );
	ft_memmove( destination, source, size );

	// ... pour y insérer une nouvelle valeur en tête

	// On affiche le contenu de la collection
	for( int i=0; i<ELEMENT_COUNT; i++ ) {
		printf( "%d ", data[i] );
	}
	puts( "" );  // Un retour à la ligne

	return (EXIT_SUCCESS);
}*/
