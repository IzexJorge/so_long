
#include "so_long.h"

void	draw_map(char **map)
{
	int		i;
	char	*row;
	int		j;

	i = -1;
	while (map[++i])
	{
		row = map[i];
		j = -1;
		while (row[++j])
			ft_putchar_fd(row[j], 1);
		ft_putchar_fd('\n', 1);
	}
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

int	main(int argc, char *argv[])
{
	int		fd;
	char	*container;
	char	**map;

	if (argc != 2 || !is_arg_valid(argv[1]))
		return (ft_printf_error("Only one \"file_name.ber\" argument required."));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_perror());
	container = read_file(fd);
	close(fd);
	if (!container)
		return (ft_perror());
	map = ft_split(container, '\n');
	if (!map)
	{
		free(container);
		return (ft_perror());
	}
	if (!is_map_valid(container, map))
		return ft_printf_error("Invalid map.");
	draw_map(map);
	return (0);
}
