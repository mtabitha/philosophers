#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>

# define ACT 0
# define EAT 2
# define DIE 3

typedef struct s_rule
{
	int				phs;
	int				ttd;
	int				tte;
	int				tts;
	int				phme;
	sem_t			*s_print;
	sem_t			*s_eat;		
	unsigned int	time;
	pid_t			*pids;
}					t_rule;

typedef struct s_philo
{	
	unsigned int	dead_time;
	int				id;
	sem_t			*s_die;
	sem_t			*s_eat;
	sem_t			*sem;
}				t_philo;

t_rule	g_rules;

size_t			ft_strlen(const char *s);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);
void			ft_usleep(unsigned int n);
unsigned int	get_time(void);
void			print_action(t_philo *ph, char *str, int type);
void			print_error(char *str);
void			start_philo(void);
void			*life(void *arg);

#endif
