#include "philosophers.h"

void	print_action(t_philo *ph, char *str)
{
	char	*color;

	color = "\033[1;35m";
	if (ph->id % 2)
		color = "\033[1;36m";
	pthread_mutex_lock(&g_rules.m_print);
	if (!g_rules.end_flag)
		printf("\033[0m%d \t\t%s%d %s\n",
			get_time() - g_rules.time, color, ph->id, str);
	pthread_mutex_unlock(&g_rules.m_print);
}

int 	print_error(char *str, t_philo *ph, pthread_mutex_t *mutex)
{
	ft_free(ph, mutex);
	printf("%s\n", str);
	return (1);
}
