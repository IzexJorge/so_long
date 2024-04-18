/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:23:04 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/19 00:21:06 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_arg_valid(char *arg)
{
	char	*extension;
	size_t	n;

	extension = ft_strrchr(arg, '.');
	if (!extension)
		return (0);
	if (ft_strlen(extension) > ft_strlen(".ber"))
		n = ft_strlen(extension);
	else
		n = ft_strlen(".ber");
	if (ft_strncmp(extension, ".ber", n))
		return (0);
	else
		return (1);
}

static char	*read_file(int fd)
{
	char	*buffer;
	char	*container;
	ssize_t	bytes_read;

	buffer = ft_calloc(sizeof(char), 30);
	if (!buffer)
		return (0);
	container = ft_calloc(sizeof(char), 1);
	if (!container)
		return (0);
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, 29);
		if (bytes_read == -1)
		{
			free(buffer);
			free(container);
			return (0);
		}
		buffer[bytes_read] = 0;
		container = ft_strjoin_free(container, buffer);
	}
	free(buffer);
	return (container);
}

static char	*get_container(char **argv)
{
	int		fd;
	char	*container;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_perror();
	container = read_file(fd);
	close(fd);
	if (!container)
		ft_perror();
	return (container);
}

static char	**get_map(char *container)
{
	char	**map;

	map = ft_split(container, '\n');
	if (!map)
	{
		free(container);
		return (0);
	}
	return (map);
}

int	main(int argc, char *argv[])
{
	char	*container;
	char	**map;
	char	**map_copy;

	if (argc != 2 || !is_arg_valid(argv[1]))
		ft_printf_error("Only one \"file_name.ber\" argument required.");
	container = get_container(argv);
	map = get_map(container);
	if (!map)
		ft_perror();
	map_copy = get_map(container);
	if (!map_copy)
	{
		free_array(map);
		ft_perror();
	}
	free(container);
	is_map_valid(map, map_copy);
	run_map(map);
	free_array(map);
	ft_perror();
	return (0);
}
