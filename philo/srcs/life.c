#include "philosophers.h"

int	eating(t_philo *ph)
{
	print_action(ph, "is eating");
	ft_usleep(g_rules.tte * 1000);
	pthread_mutex_lock(&ph->m_die);
	ph->dead_time = get_time() + g_rules.ttd;
	pthread_mutex_unlock(&ph->m_die);
	ph->eat_count++;
	pthread_mutex_unlock(&ph->m_eat);
	if (g_rules.end_flag)
		return (1);
	print_action(ph, "is sleeping");
	return (0);
}

void	*life(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	ph->dead_time = get_time() + g_rules.ttd;
	while (1)
	{
		print_action(ph, "is thinking");
		if (g_rules.end_flag)
			return (NULL);
		pthread_mutex_lock(ph->left);
		print_action(ph, "has taken a fork");
		pthread_mutex_lock(ph->right);
		print_action(ph, "has taken a fork");
		if (eating(ph))
			return (NULL);
		pthread_mutex_unlock(ph->right);
		pthread_mutex_unlock(ph->left);
		ft_usleep(g_rules.tts * 1000);
		if (g_rules.end_flag)
			return (NULL);
	}
}
