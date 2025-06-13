/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:41:58 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/13 14:45:59 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>

char	*get_next_line(int fd);
size_t	ft_strlen_gnl(char *s);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_read(int fd, char *string);
char	*ft_line(char *string);
char	*ft_new_string(char *string);
char	*ft_free(char **str);
char	*ft_strdup_gnl(char *s);

#endif
