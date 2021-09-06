#include "philosophers.h"

void	print_act(t_philo *ph, char *str)
{
	char	*color;

	color = "\033[1;35m";
	if (ph->id % 2)
		color = "\033[1;36m";
	printf("\033[0m%d \t\t%s%d %s\n",
		get_time() - g_rules.time, color, ph->id, str);
}

void	print_eat(void)
{
	int	i;

	i = -1;
	printf("\033[1;32mEach eat %d times\n", g_rules.phme);
	while (++i < g_rules.phs)
		kill(g_rules.pids[i], SIGKILL);
	free(g_rules.pids);
	exit(0);
}

void	print_die(t_philo *ph)
{
	printf("\033[1;31m%d %d %s\n",
		get_time() - g_rules.time, ph->id, "is die");
	free(g_rules.pids);
	exit(0);
}

void	print_action(t_philo *ph, char *str, int type)
{
	sem_wait(g_rules.s_print);
	if (type == ACT)
		print_act(ph, str);
	else if (type == EAT)
		print_eat();
	else
		print_die(ph);
	sem_post(g_rules.s_print);
}

void	print_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}
