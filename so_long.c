
#include "so_long.h"

int	is_arg_valid(char *arg)
{
	char	*extension;
	size_t	n;

	extension = ft_strrchr(arg, '.');
	if (!extension)
		return (0);
	//n = math.max(ft_strlen(extension), ft_strlen(".ber"))
	if (ft_strlen(extension) > ft_strlen(".ber"))
		n = ft_strlen(extension);
	else
		n = ft_strlen(".ber");
	if (ft_strncmp(extension, ".ber", n))
		return (0);
	else
		return (1);
}

char	*read_file(int fd)
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

char	*get_container(char **argv)
{
	int		fd;
	char	*container;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (0);
	container = read_file(fd);
	close(fd);
	return (container);
}

char	**get_map(char *container)
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
	//int		fd;
	char	*container;
	char	**map;
	char	**map_copy;

	if (argc != 2 || !is_arg_valid(argv[1]))
		return (ft_printf_error("Only one \"file_name.ber\" argument required."));

	// fd = open(argv[1], O_RDONLY);
	// if (fd == -1)
	// 	return (ft_perror());
	// container = read_file(fd);
	// close(fd);
	// if (!container)
	// 	return (ft_perror());
	container = get_container(argv);
	if (!container)
		return (ft_perror());

	// map = ft_split(container, '\n');
	// if (!map)
	// {
	// 	free(container);
	// 	return (ft_perror());
	// }
	map = get_map(container);
	if (!map)
		return (ft_perror());

	map_copy = get_map(container);
	if (!map_copy)
		return (ft_perror());

	free(container);

	//Comprobar también que el mapa no es demasiado grande para la pantalla. Tal vez en draw_map.
	if (!is_map_valid(map, map_copy))
		return (ft_printf_error("Invalid map."));

	if (!draw_map(map))
	{
		free(map);
		return (ft_perror());
	}
	free(map);
	return (0);

	//Versión liberando map en draw_map en todos los casos, no dependiendo de qué retorne.
	// if (!draw_map(map))
	// 	return (ft_perror());
	// return (0);
}
