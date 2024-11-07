
#include "../include/cub3D.h"

static int	count_string(const char *s, char c)
{
	int	i;
	int	count_string;

	count_string = 0;
	i = 0;
	if (s[i] != c && s[i] != '\0')
		count_string = 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count_string++;
		i++;
	}
	return (count_string);
}

static char	*write_word(t_game * game, char *result, const char *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while(i < (int)game->longest)
	{
		while (s[i] == c && s[i])
			i++;
	
		if (!s[i])
		{
			result[i] = '\0';
			i++;
		}
		else if (s[i] && s[i] != c)
			result[j++] = s[i++];
	}
	result[j] = '\0';
	return (result);
}

static int	ft_free(char **result, int k)
{
	if (result[k] == NULL)
	{
		while (k >= 0)
		{
			free(result[k]);
			k--;
		}
		free(result);
		return (1);
	}
	else
		return (0);
}

static char	**write_result(t_game *game, char **result, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			result[k] = (char *)malloc((game->longest + 1) * sizeof(char));//longest
			if (ft_free(result, k) == 1)
				return (NULL);
			result[k] = write_word(game, result[k], s + i, c);
			i = i + j;
			k++;
		}
	}
	return (result);
}

char	**ft_3d_split(t_game * game, char const *s, char c)
{
	char	**result;
	int		i;

	i = count_string(s, c);
	result = (char **)malloc((i + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = write_result(game, result, s, c);
	if (result != NULL)
		result[i] = NULL;
	return (result);
}