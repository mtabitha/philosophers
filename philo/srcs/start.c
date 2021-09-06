#include "philosophers.h"

void	init_philo(t_philo *ph, pthread_mutex_t *mutex, int i)
{
	ph->id = i + 1;
	ph->eat_count = 0;
	pthread_mutex_init(&ph->m_die, NULL);
	pthread_mutex_init(&ph->m_eat, NULL);
	pthread_mutex_lock(&ph->m_eat);
	ph->left = &mutex[i];
	ph->right = &mutex[(i + 1) % g_rules.phs];
}

void	*die_check(void *arg)
{
	t_philo	*ph;
	int		i;

	ph = (t_philo *)arg;
	while (1)
	{
		i = -1;
		while (++i < g_rules.phs)
		{
			pthread_mutex_lock(&ph[i].m_die);
			if (get_time() > ph[i].dead_time)
			{
				pthread_mutex_lock(&g_rules.m_print);
				g_rules.end_flag = 1;
				printf("\033[1;31m%d %d %s\n",
					get_time() - g_rules.time, ph[i].id, "is die");
				pthread_mutex_unlock(&g_rules.m_end);
				return (NULL);
			}
			pthread_mutex_unlock(&ph[i].m_die);
			ft_usleep(1000);
		}
	}
}

void	*eat_check(void *arg)
{
	t_philo	*ph;
	int		i;
	int		eat_count;

	eat_count = -1;
	ph = (t_philo *) arg;
	while (++eat_count < g_rules.phme)
	{
		i = -1;
		while (++i < g_rules.phs)
			pthread_mutex_lock(&ph[i].m_eat);
	}
	pthread_mutex_lock(&g_rules.m_print);
	g_rules.end_flag = 1;
	printf("\033[1;32mEach eat %d times\n", eat_count);
	pthread_mutex_unlock(&g_rules.m_end);
	return (0);
}

int	create_check(t_philo *ph, pthread_mutex_t *mutex)
{
	pthread_t	thd;

	if (pthread_create(&thd, NULL, &die_check, (void *)ph))
		return (print_error("error: create thread", ph, mutex));
	pthread_detach(thd);
	if (g_rules.phme > 0)
	{
		if (pthread_create(&thd, NULL, &eat_check, (void *)ph))
			return (print_error("error: create thread", ph, mutex));
		pthread_detach(thd);
	}
	return (0);
}

int	start_philo(void)
{
	int				i;
	t_philo			*ph;
	pthread_mutex_t	*mutex;

	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * g_rules.phs);
	ph = (t_philo *)malloc(sizeof(t_philo) * g_rules.phs);
	if (!mutex || !ph)
		return (print_error("error: malloc\n", ph, mutex));
	i = -1;
	while (++i < g_rules.phs)
	{
		init_philo(&ph[i], mutex, i);
		if (pthread_mutex_init(&mutex[i], NULL))
			return (print_error("error: mutex init", ph, mutex));
	}
	start_life(-1, ph, mutex);
	if (create_check(ph, mutex))
	{
		ft_free(ph, mutex);
		return (1);
	}
	pthread_mutex_lock(&g_rules.m_end);
	ft_free(ph, mutex);
	return (0);
}
