#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	p_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (RET_ERROR);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		return (ERROR);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > 2147483647)
			return (ERROR);
		else
			res = res * 10 + (str[i] - '0');
		if (!res || !str[i])
			break ;
		i++;
	}
	if ((str[i] < '0' || str[i] > '9') && str[i] != 0)
		return (ERROR);
	return ((int) res);
}

////////////////////////////////////////////////////////////////
//init

int	init_info_argv(int argc, char *argv[], t_info *info)
{
	info->num_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_must_eat = ft_atoi(argv[5]);
	else
		info->num_must_eat = -1;
	if (info->num_philo <= 0 || info->time_to_die <= 0 || \
		info->time_to_eat <= 0 || info->time_to_sleep <= 0 || \
		((argc == 6) && info->num_must_eat <= 0))
	{
		p_error("ERROR : invalid input!\n");
		return (RET_ERROR);
	}
	return (1);
}

int	setting_struct(t_info *info)
{
	info->philos = malloc(sizeof(t_philo) * info->num_philo);
	info->t_philo = malloc(sizeof(pthread_t) * info->num_philo);
	info->fork = malloc(sizeof(int) * info->num_philo);
	info->m_fork = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->philos || !info->t_philo || !info->fork || !info->m_fork)
		return (RET_ERROR);
	if (pthread_mutex_init(&(info->m_everyone_eat), 0) || \
		pthread_mutex_init(&(info->m_flag_die), 0) || \
		pthread_mutex_init(&(info->m_start_time), 0) || \
		pthread_mutex_init(&(info->m_must_eat_all_flag), 0) || \
		pthread_mutex_init(&(info->m_print), 0))
		return (RET_ERROR);
	return (1);
}

// fork를 모두 1로 (사용가능상태)로 초기화하고 fork뮤텍스를 초기화해줌. 옵션은 0 
int	check_argv(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		info->fork[i] = 1;
		if (pthread_mutex_init(&info->m_fork[i], 0))
		{
			p_error("ERROR : mutex initialize error");
			return (RET_ERROR);
		}
		i++;
	}
	return (1);
}

t_info *make_info(int argc, char **argv)

{
	t_info	*info;

	if (!(argc == 5 || argc == 6))
		return (0);
	info = (t_info *)malloc(sizeof(t_info));
	memset(info, 0, sizeof(t_info));
	if (init_info_argv(argc, argv, info) == RET_ERROR || \
		setting_struct(info) == RET_ERROR || \
		check_argv(info) == RET_ERROR)
		return (0);
	return (info);
}

int philo_init(t_info *info)
{
	int i;

	i = 0;
	while (i < info->num_philo)
	{
		memset(&info->philos[i], 0, sizeof(t_philo));
		info->philos[i].info = info;
		info->philos[i].eat_count = 0;
		info->philos[i].id = i;
		info->philos[i].right_fork = i;
		info->philos[i].left_fork = (i + 1) % info->num_philo;
		i++;
	}
	return(1);
}

////////////////////////////////////////////////////////////////

// philo_run


// 초를 밀리초롤 바꿈 왜? -> 시간 차이를 더 세밀하게 표현하기 위해서
// ex) 0.5초는 초로만 계산되면 0초이지만 밀리초로 계산되면 500밀리초
// 1초는 1,000,000 마이크로초이며, 1,000 밀리초
// timeval에는 tv_sec (초) 와 tv_usec (밀리초) 가 있다.
int	time_gap(struct timeval start_time, struct timeval now_time)
{
	time_t	sec;
	time_t	micro;

	sec = (now_time.tv_sec) - (start_time.tv_sec);
	// 500 마이크로초는 0.5 밀리초로 변환되어야 합니다
	micro = (sec * 1000) + ((now_time.tv_usec - start_time.tv_usec) / 1000);
	return ((int)micro);
}

int	check_voice(t_info *info)
{
	int	die;
	int	eat_all;

	pthread_mutex_lock(&info->m_flag_die);
	die = info->flag_die;
	pthread_mutex_unlock(&info->m_flag_die);
	pthread_mutex_lock(&info->m_must_eat_all_flag);
	eat_all = info->must_eat_all_flag;
	pthread_mutex_unlock(&info->m_must_eat_all_flag);
	if (die || eat_all)
		return (1);
	return (0);
}

// 출력함수
void	voice(enum e_state state, t_info *info, t_philo *p)
{
	struct timeval	curr;
	int				gap;

	if (check_voice(info))
		return ;
	gettimeofday(&curr, NULL);
	gap = time_gap(info->start_time, curr);
	pthread_mutex_lock(&info->m_print);
	if (state == FORK)
		printf("[%d] philo %d has taken a fork\n", gap, p->id + 1);
	else if (state == EAT)
		printf("[%d] philo %d is eating\n", gap, p->id + 1);
	else if (state == SLEEP)
		printf("[%d] philo %d is sleeping\n", gap, p->id + 1);
	else if (state == THINK)
		printf("[%d] philo %d is thinking\n", gap, p->id + 1);
	else if (state == DEAD)
		printf("[%d] philo %d died\n", gap, p->id + 1);
	pthread_mutex_unlock(&info->m_print);
	return ;
}
////////////////////////////////////////////////////////////////
// 실행

void	grab_fork(t_info *info, t_philo *p)
{
	if (p->id % 2)
	{
		pthread_mutex_lock(&info->m_fork[p->left_fork]);
		info->fork[p->left_fork] = 0;
		voice(FORK, info, p);
		pthread_mutex_lock(&info->m_fork[p->right_fork]);
		info->fork[p->right_fork] = 0;
		voice(FORK, info, p);
	}
	else
	{
		pthread_mutex_lock(&info->m_fork[p->right_fork]);
		info->fork[p->right_fork] = 0;
		voice(FORK, info, p);
		pthread_mutex_lock(&info->m_fork[p->left_fork]);
		info->fork[p->left_fork] = 0;
		voice(FORK, info, p);
	}
}

void	custom_usleep_timer(struct timeval *start, int sleep_time)
{
	struct timeval	now;

	gettimeofday(&now, 0);
	while (time_gap(*start, now) < sleep_time)
	{
		usleep(300);
		gettimeofday(&now, 0);
	}
}

void	philo_eat(t_info *info, t_philo *p)
{
	struct timeval	time;
	int				eat_count;

	voice(EAT, info, p);
	gettimeofday(&time, NULL);
	// 현재시간 즉 먹은 시간
	p->current_eat = time;
	custom_usleep_timer(&time, info->time_to_eat);
	pthread_mutex_lock(&p->m_eat_count);
	// 동시에 많은 스레드가 이 작업을 할 수 있기 때문에 복사 후 증가시킴
	// 근데 없어도 될 듯
	p->eat_count++;
	eat_count = p->eat_count;
	pthread_mutex_unlock(&p->m_eat_count);
	if (eat_count == p->info->num_must_eat)
	{
		pthread_mutex_lock(&p->m_flag_eat_all);
		p->flag_eat_all = 1;
		pthread_mutex_unlock(&p->m_flag_eat_all);
	}
}

////////////////////////////////////////////////////////////////
// philo_day_running

int	day_running_check_die(int die, t_philo *p)
{
	pthread_mutex_lock(&p->info->m_flag_die);
	printf("flag = %d\n", p->info->flag_die);
	die = p->info->flag_die;
	pthread_mutex_unlock(&p->info->m_flag_die);
	return (die);
}

void	philo_day_running(t_philo *p)
{
	int	die;
	int	eat_all;

	die = 0;
	eat_all = 0;
	//철학자가 죽기 전까지 무한루프
	while (1)
	{
		// 철학자가 죽었는지에 대한 여부 체크
		die = day_running_check_die(die, p);
		//죽었다면 break;
		if (die)
			break ;
		grab_fork(p->info, p);
		philo_eat(p->info, p);
		put_down_fork(p->info, p);
		// 철학자가 모두 식사를 했는지 체크
		eat_all = day_running_check_eat_all(eat_all, p);
		if (eat_all)
			break ;
		philo_sleep(p->info, p);
		philo_think(p->info, p);
	}
	// 철학자가 모두 식사를 했고 죽지 않았을 때
	if (!die)
	{
		pthread_mutex_lock(&p->info->m_everyone_eat);
		// 식사를 다 했다는 플래그
		p->info->count_everyone_eat++;
		pthread_mutex_unlock(&p->info->m_everyone_eat);
	}
}

// 함수의 목적은 철학자가 생존하는 동안 수행할 행동을 결정하고 실행하는 것
void	*philo_run(void *arg)
{
	printf("dd\n");
	t_philo	*run;

	run = (t_philo *)arg;
	// 철학자가 한명일 때  포크를 집지 않고 쉬다가 죽는다.
	if (run->info->num_philo == 1)
	{
		pthread_mutex_lock(&run->info->m_fork[run->right_fork]);
		run->info->fork[run->right_fork] = 0;
		voice(FORK, run->info, run);
		usleep(run->info->time_to_die);
		pthread_mutex_unlock(&run->info->m_fork[run->right_fork]);
		return (NULL);
	}
	else if ((run->id) % 2 != 0)
		usleep(100);
	philo_day_running(run);
	return (NULL);
}

//스레드를 만드는 부분
int	philo_create_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		gettimeofday(&info->start_time, 0);
		//이 부분을 위해서 필로의 배열이 필요함
		// 첫 번째 인자는 스레드를 담을 주소
		// 두 번째 인자는 스레드 속성
		// 세 번째 인자 philo_run은 스레드가 실행 될 함수
		// 네 번째 인자는 세 번째 인자에서 불러온 함수 포인터에서 사용할 인자이다.
		if (pthread_create(&info->t_philo[i], 0, philo_run, &info->philos[i]))
			return (RET_ERROR);
		// 이 부분 이해를 못하겠어 philo_run에서 eat할 때 시간을 저장하는데 왜 또 나와서 저장해?
		gettimeofday(&info->philos[i].current_eat, 0);
		//printf("Current eat time: %ld seconds %d microseconds\n", info->philos[i].current_eat.tv_sec, info->philos[i].current_eat.tv_usec);
		i++;
	}
	return (1);
}

////////////////////////////////////////////////////////////////
// moniter

int	check_philo_dead(t_info *info, t_philo *p)
{
	struct timeval	curr;

	gettimeofday(&curr, 0);
	if (time_gap(p->current_eat, curr) > info->time_to_die)
	{
		printf("aaa = %d\n", time_gap(p->current_eat, curr) );
		pthread_mutex_lock(&info->m_flag_die);
		info->flag_die = 1;
		pthread_mutex_unlock(&info->m_flag_die);
		voice(DEAD, info, p);
		return (p->id);
	}
	return (-1);
}

int	monitor(t_info *info)
{
	int	i;
	int	count_everyone_eat;
	int	must_eat;

	i = 0;
	must_eat = 0;
	while (1)
	{
		if (check_philo_dead(info, &info->philos[i]) == info->philos[i].id)
			break ;
		pthread_mutex_lock(&(info->m_everyone_eat));
		count_everyone_eat = info->count_everyone_eat;
		pthread_mutex_unlock(&(info->m_everyone_eat));
		if (count_everyone_eat == info->num_philo)
		{
			pthread_mutex_lock(&(info->m_must_eat_all_flag));
			info->must_eat_all_flag = 1;
			must_eat = info->must_eat_all_flag;
			pthread_mutex_unlock(&(info->m_must_eat_all_flag));
		}
		if (must_eat == 1)
			return (-1);
		i = 0;
	}
	printf("00\n");
	return (info->philos[i].id + 1);
}
////////////////////////////////////////////////////////////////
//main

int	philo(t_info *info)
{
	// int				gap;
	// struct timeval	curr;
	int				ret_monitor;

	if (philo_init(info) == RET_ERROR)
		return (RET_ERROR);
	if (philo_create_thread(info) == RET_ERROR)
		return (RET_ERROR);
	ret_monitor = monitor(info);
	// gettimeofday(&curr, NULL);
	// gap = time_gap(info->start_time, curr);
	// if (ret_monitor == -1)
	// 	printf("== philo eat all. dinning end! ==\n");
	// else
	// 	printf("[%d] philo %d died\n", gap, ret_monitor);
	// if (philo_collect_all_thread(info) == RET_ERROR)
	// 	return (RET_ERROR);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = make_info(argc, argv);
	if (!info)
		return (RET_ERROR);
	if (philo(info) == RET_ERROR)
		return (RET_ERROR);
	// end_philo(info);
	return (0);
}