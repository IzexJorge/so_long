
// 1. Comprobar que el borde es válido(que sea rectangular y sin huecos).
// 2. Escanear todo el mapa en busca de la entrada.
// 3. Aprovechar ese escaneo para comprobar que hay al menos un coleccionable,
// que hay sólo una entrada y una salida y que no hay ningún carácter desconocido.
// 4. Recorrer cada tile accesible, añadiendo los colleccionables a un array y
// la salida a un puntero(que originalmente tiene valor 0) según se van encontrando.
int	is_rectangle(char **map)
{
	int	i;
	int	last_col_index;

	last_col_index = ft_strlen(map[0]) - 1;
	i = -1;
	while (map[++i])
		if (last_col_index != ft_strlen(map[i]))
			return (0);
	return (last_col_index);
}

int	is_border_valid(char **map, int last_col_index)
{
	int	last_row_index;
	int	i;
	int	*row;
	int	j;

	last_row_index = ft_arraylen(map) - 1;
	i = -1;
	while (map[++i])
	{
		row = map[i];
		j = -1;
		if (i == 0 || i == last_row_index)
		{
			while (row[++j])
				if (row[j] != '1')
					return (0);
		}
		else
		{
			while (row[++j])
				if ((j == 0 || j == last_col_index) && row[j] != '1')
					return (0);
		}
	}
	return (1);
}

//La misma función que compruebe si hay un path desde la entrada hasta la salida se puede utilizar
//exactamente de la misma forma para comprobar si hay un path hasta cada uno de los coleccionables.

//función recursiva que obtenga las casillas no-muros adyacentes. Tal vez no recursiva.
int	adyacent_tiles(char **map, int *coord)
{
	if (map[coord[1]][coord[2]] == 'P')
	{

	}
	//Añadir las coordenadas a una tabla que recoja todas las coordenadas transitables para no pasar
	//dos veces por la misma.
}

int	is_map_valid(char *container, char **map)
{
	int		start_coord[2];
	int		last_col_index;

	if (!are_chars_valid(container, start_coord))
		return (0);
	last_col_index = is_rectangle(map);
	if (!last_col_index)
		return (0);
	if (!is_border_valid(map, last_col_index))
		return (0);
	


	return (1);
}