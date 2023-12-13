
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# define ERROR		0
# define PHIL_DIE	0
# define RET_ERROR	-1

enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
};

typedef struct s_philo
{
	struct s_info		*info;
	int					id;
	int					right_fork;
	int					left_fork;
	struct timeval		current_eat;
	pthread_mutex_t		m_current_eat;
	int					eat_count;
	pthread_mutex_t		m_eat_count;
	int					flag_eat_all;
	pthread_mutex_t		m_flag_eat_all;
}						t_philo;

typedef struct s_info
{
	int					num_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_must_eat;
	int					count_everyone_eat;
	pthread_mutex_t		m_everyone_eat;
	int					must_eat_all_flag;
	pthread_mutex_t		m_must_eat_all_flag;
	int					flag_die;
	pthread_mutex_t		m_flag_die;
	struct timeval		start_time;
	pthread_mutex_t		m_start_time;
	pthread_mutex_t		m_print;
	t_philo				*philos;
	pthread_t			*t_philo;
	int					*fork;
	pthread_mutex_t		*m_fork;
}						t_info;

#endif