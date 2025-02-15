/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:19:57 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/12 01:27:09 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <fcntl.h>
# include <signal.h>
# include <wait.h>

// semaphore path
# define SEM_FORK "/semaphore"
# define SEM_ISDEAD "/isdead"
# define SEM_READY "/isready"
# define SEM_LASTMEAL "/lastmeal"

# define FORK 0
# define READY 1
# define ISDEAD 2
# define LASTMEAL 3

// maximum number of philos
# define MAX_PHILOS 200

// int array index
# define NUM_PHILOS 0
# define TIME_DIE 1
# define TIME_EAT 2
# define TIME_SLEEP 3
# define MIN_MEALS 4
# define NOT_SET -1

// each philo metadata
typedef struct s_philo
{
	int					index;
	int					total_philo;
	size_t				time_sleep;
	size_t				time_eat;
	size_t				time_die;
	int					meals_ate;
	int					min_meals;	
	size_t				start_time;
	size_t				last_ate;
	int					is_dead;
	sem_t				*forks_sem;
	sem_t				*is_ready_sem;
	sem_t				*is_alive_sem;
	sem_t				*last_ate_sem;
}					t_philo;

// philo_utils
int			ft_atoi(const char *nptr);
size_t		get_current_time(void);
void		ft_sleep(size_t time);

// checker
int			check_input(int argc, char **argv, int *vars);

// metadata
t_philo		*create_philo_metadatas(int *vars);
void		free_metadata(t_philo *metadatas, pthread_mutex_t *forks);

// routine
void		*philo_routine(void *args);
void		philo_grab_fork(sem_t *sem_fork, t_philo *metadata, size_t start);
int			is_philo_dead(t_philo *metadata);

// baby making
void		kill_child(int *pids, int *vars);
int			create_child(int *vars, t_philo *metadatas, int **pids);

// monitoring baby
int			monitor_thread(t_philo *metadatas);

#endif // !PHILO_H
