#include "philosophers.h"

void	eating(t_philo *ph)
{
	print_action(ph, "is eating", 0);
	ft_usleep(g_rules.tte * 1000);
	sem_wait(ph->s_die);
	ph->dead_time = get_time() + g_rules.ttd;
	sem_post(ph->s_die);
	sem_post(ph->s_eat);
	print_action(ph, "is sleeping", 0);
}

void	*die_check(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		sem_wait(ph->s_die);
		if (get_time() > ph->dead_time)
			print_action(ph, NULL, 3);
		sem_post(ph->s_die);
		ft_usleep(1000);
	}
}

void	*eat_check(void *arg)
{
	t_philo	*ph;
	int		eat_count;

	eat_count = -1;
	ph = (t_philo *) arg;
	while (++eat_count < g_rules.phme)
		sem_wait(ph->s_eat);
	sem_post(g_rules.s_eat);
	return (0);
}

void	create_check(t_philo *ph)
{
	pthread_t	thd;

	if (pthread_create(&thd, NULL, &die_check, (void *)ph))
		print_error("error: create thread");
	pthread_detach(thd);
	if (g_rules.phme > 0)
	{
		if (pthread_create(&thd, NULL, &eat_check, (void *)ph))
			print_error("error: create thread");
		pthread_detach(thd);
	}
}

void	*life(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	ph->dead_time = get_time() + g_rules.ttd;
	create_check(ph);
	while (1)
	{
		print_action(ph, "is thinking", 0);
		sem_wait(ph->sem);
		print_action(ph, "has taken a fork", 0);
		sem_wait(ph->sem);
		print_action(ph, "has taken a fork", 0);
		eating(ph);
		sem_post(ph->sem);
		sem_post(ph->sem);
		ft_usleep(g_rules.tts * 1000);
	}
}
