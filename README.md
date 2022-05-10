# philosophers
Start arguments: *number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]*

- philo
  - Each philosopher be a thread.
  - There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
- philo_bonus
  - Each philosopher be a process.
  - All the forks are put in the middle of the table
