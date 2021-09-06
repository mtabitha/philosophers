#include "philosophers.h"

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
	if (argc < 5 || argc > 6)
		print_error("error: bad args");
	if (check_args(argv))
		print_error("error: bad val");
	start_philo();
	return (0);
}
