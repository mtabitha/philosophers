#include "philosophers.h"

void	init_philo(t_philo *ph, sem_t *sem, int i)
{
	ph->id = i + 1;
	sem_unlink("s_die");
	ph->s_die = sem_open("s_die", O_CREAT, 0660, 1);
	sem_unlink("s_eat");
	ph->s_eat = sem_open("s_eat", O_CREAT, 0660, 0);
	ph->sem = sem;
}

void	*eat_sem(void *null)
{
	int	i;

	(void)null;
	i = -1;
	while (++i < g_rules.phs)
		sem_wait(g_rules.s_eat);
	i = -1;
	print_action(NULL, NULL, 2);
	return (NULL);
}

void	start_life(t_philo *ph)
{
	int			i;
	pthread_t	thd;

	i = -1;
	g_rules.pids = (pid_t *)malloc(sizeof(pid_t) * g_rules.phs);
	while (++i < g_rules.phs && g_rules.pids)
	{
		g_rules.pids[i] = fork();
		if (g_rules.pids[i] < 0)
			print_error("error: fork");
		if (!g_rules.pids[i])
			life(ph + i);
		ft_usleep(100);
	}
	if (g_rules.phme > 0)
	{
		if (pthread_create(&thd, NULL, &eat_sem, (void *)0))
			print_error("error: create thread");
		pthread_detach(thd);
	}
	wait(0);
	i = -1;
	while (++i < g_rules.phs && g_rules.pids)
		kill(g_rules.pids[i], SIGKILL);
	free(g_rules.pids);
}

void	start_philo(void)
{
	int			i;
	t_philo		*ph;
	sem_t		*sem;

	i = -1;
	ph = (t_philo *)malloc(sizeof(t_philo) * g_rules.phs);
	if (!ph)
		print_error("error: malloc\n");
	sem_unlink("sem");
	sem = sem_open("sem", O_CREAT, 0660, g_rules.phs);
	sem_unlink("sem_print");
	g_rules.s_print = sem_open("sem_print", O_CREAT, 0660, 1);
	sem_unlink("sem_eat");
	g_rules.s_eat = sem_open("sem_eat", O_CREAT, 0660, 0);
	while (++i < g_rules.phs)
		init_philo(&ph[i], sem, i);
	i = 0;
	g_rules.time = get_time();
	start_life(ph);
	free(ph);
}
