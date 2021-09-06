#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_rule
{
	int				phs;
	int				ttd;
	int				tte;
	int				tts;
	int				phme;
	int				end_flag;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_end;	
	unsigned int	time;
}					t_rule;

typedef struct s_philo
{	
	unsigned int	dead_time;
	int				eat_count;
	int				id;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	pthread_mutex_t	m_die;
	pthread_mutex_t	m_eat;
}				t_philo;

t_rule	g_rules;

size_t			ft_strlen(const char *s);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);
void			ft_usleep(unsigned int n);
unsigned int	get_time(void);
void			print_action(t_philo *ph, char *str);
int				print_error(char *str, t_philo *ph, pthread_mutex_t *mutex);
int				start_philo(void);
void			*life(void *arg);
int				start_life(int i, t_philo *ph, pthread_mutex_t *mutex);
void			ft_free(t_philo *ph, pthread_mutex_t *mutex);
#endif