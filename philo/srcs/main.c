#include "philosophers.h"

int	start_life(int i, t_philo *ph, pthread_mutex_t *mutex)
{
	pthread_t	thd;

	g_rules.time = get_time();
	while (++i < g_rules.phs)
	{
		if (pthread_create(&thd, NULL, &life, (void *)&ph[i]))
			return (print_error("error: create thread", ph, mutex));
		pthread_detach(thd);
		ft_usleep(100);
	}
	return (0);
}

int	check_args(char **argv)
{
	g_rules.phs = ft_atoi(argv[1]);
	g_rules.ttd = ft_atoi(argv[2]);
	g_rules.tte = ft_atoi(argv[3]);
	g_rules.tts = ft_atoi(argv[4]);
	if (argv[5])
		g_rules.phme = ft_atoi(argv[5]);
	else
		g_rules.phme = 0;
	if ((g_rules.ttd < 60 || g_rules.tte < 60 || g_rules.tts < 60)
		|| (g_rules.phs > 200 || g_rules.phs < 1) || g_rules.phme < 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	pthread_mutex_init(&g_rules.m_print, NULL);
	pthread_mutex_init(&g_rules.m_end, NULL);
	pthread_mutex_lock(&g_rules.m_end);
	if (argc < 5 || argc > 6)
		return (print_error("error: bad args", NULL, NULL));
	if (check_args(argv))
		return (print_error("error: bad val", NULL, NULL));
	if (start_philo())
		return (1);
	return (0);
}
