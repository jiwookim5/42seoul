/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:31:39 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/17 20:08:51 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int					philo_name;
	int					fork_left;
	int					fork_right;
	long int			thread_time;
	long int			last_eat;
	int					eat;
	pthread_t			thread;
	pthread_mutex_t		eye;
	struct s_info		*info;
}	t_philo;

typedef struct s_info
{
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				finished_eat;
	int				death_flag;
	long int		start_time;
	pthread_mutex_t	count_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	death_m;
	pthread_mutex_t	*fork_m;
	pthread_mutex_t	eat_mutex;
	t_philo			*philo;
}t_info;

int			str_length(char *tmp);
int			init_mutex(t_info *info);
int			init(t_info *info, char **argv, int argc);
long		atoi_while(char *str);
long int	time_init(void);
void		print_error(char *tmp);
int			check_time(t_philo philo);
int			thread_check_death(t_philo philo);
int			must_eat_check(t_philo *philo);
void		ft_philo_check_finish(t_philo *philo);
int			check_death(t_philo *philo);
void		ft_pass_time(long int time_to_eat, t_info *info);
int			printf_time_number(t_philo *philo, char *msg);
void		free_philo(t_info *info);

#endif