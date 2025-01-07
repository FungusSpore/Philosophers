/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:38:36 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/07 17:09:45 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

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
	int		index;
	int		total_philo;
	size_t		time_sleep;
	size_t		time_eat;
	size_t		time_die;
	int		meals_ate;
	int		min_meals;	
	size_t		start_time;
	size_t		last_ate;
	int		is_dead;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;


// philo_utils
int	ft_atoi(const char *nptr);
size_t	get_current_time(void);

// checker
int	check_input(int argc, char **argv, int *vars);

// metadata
t_philo	*create_philo_metadatas(int *vars);

// routine
void	*philo_routine(void *args);

// monitoring
void	*monitor_routine(void *args);

#endif // !PHILO_H
