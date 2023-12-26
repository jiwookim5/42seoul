/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:06:18 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/26 20:01:56 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
//main
int		main(int argc, char **argv);
void	end_philo(t_info *info);
void	destroy_info_mutex(t_info *info);
int		philo_collect_all_thread(t_info *info);

//monitor
int		monitor(t_info *info);
int		check_philo_dead(t_info *info, t_philo *run);

//philo_act
void	philo_eat(t_info *info, t_philo *run);
void	put_down_fork(t_info *info, t_philo *run);
void	philo_sleep(t_info *info, t_philo *run);
void	philo_think(t_info *info, t_philo *run);

//philo_check
int		day_running_check_die(int die, t_philo *run);
int		day_running_check_eat_all(int eat_all, t_philo *run);

//philo_init
int		philo_init(t_info *info);
int		init_info_argv(int argc, char *argv[], t_info *info);
int		setting_struct(t_info *info);
int		check_argv(t_info *info);
t_info	*make_info(int argc, char **argv);

//philo_run
void	grab_fork(t_info *info, t_philo *run);
void	philo_day_running(t_philo *run);

//philo_utils
size_t	ft_strlen(const char *str);
int		p_error(char *msg);
int		ft_atoi(const char *str);

//philo
void	*philo_run(void *arg);
int		philo_create_thread(t_info *info);
int		philo(t_info *info);

//time
int		time_gap(struct timeval start_time, struct timeval now_time);
void	custom_usleep_timer(struct timeval *start, int sleep_time);

//voice
int		check_voice(t_info *info);
void	voice(enum e_state state, t_info *info, t_philo *run);

#endif