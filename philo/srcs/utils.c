#include "philosophers.h"

void	ft_free(t_philo *ph, pthread_mutex_t *mutex)
{
	if (ph)
		free(ph);
	if (mutex)
		free(mutex);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static int	ft_intcount(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	i;
	int		len;
	char	*ptr;

	i = n;
	len = ft_intcount(i);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[len--] = '\0';
	if (!i)
		ptr[0] = '0';
	if (i < 0)
	{
		ptr[0] = '-';
		i *= -1;
	}
	while (i > 0)
	{
		ptr[len--] = '0' + (i % 10);
		i /= 10;
	}
	return (ptr);
}

int	ft_atoi(const char *str)
{
	long long int	num;
	int				sign;

	sign = 1;
	num = 0;
	while (*str == '\t' || *str == '\n' || *str == '\r' || *str == '\v'
		|| *str == '\f' || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str++ - '0';
		if (num > 4096)
			return (num);
	}
	if (num < 0 && sign < 0)
		return (0);
	num = sign * num;
	return ((int)num);
}
