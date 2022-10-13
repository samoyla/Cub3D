#include "cub3d.h"

static int	ft_get_position(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_get_position(set, s1[i]))
		i++;
	len = strlen(s1) - 1;
	while (len > i && ft_get_position(set, s1[len]))
		len--;
	dest = malloc(sizeof(char) * (len - i) + 2);
	if (!dest)
		return (NULL);
	while (i <= len)
	{
		dest[j++] = s1[i++];
	}
	dest[j] = '\0';
	return (dest);
}
