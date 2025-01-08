/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:16:52 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/08 17:13:48 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	handle_death(int i, t_philo *metadatas)
{
	int	size;
	int	j;

	pthread_mutex_lock(metadatas->is_alive_mutex);
	size = metadatas->total_philo;
	j = 0;
	while (j < size)
		metadatas[j++].is_dead = 1;
	usleep(100);
	printf("%lu %d died\n", get_current_time() - metadatas->start_time, i + 1);
	pthread_mutex_unlock(metadatas->is_alive_mutex);
}

static int	all_finished_eating(t_philo *metadatas)
{
	int	i;

	i = 0;
	while (i < metadatas->total_philo)
	{
		if (metadatas[i].meals_ate < metadatas->min_meals)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *args)
{
	t_philo	*metadatas;
	size_t	time_since_last_meal;
	size_t	i;

	metadatas = (t_philo *)args;
	i = 0;
	while (1)
	{
		if (metadatas->min_meals > -1 && all_finished_eating(metadatas))
			break ;
		time_since_last_meal = \
		get_current_time() - metadatas[i % metadatas->total_philo].last_ate;
		if (time_since_last_meal >= metadatas->time_die && \
		metadatas[i % metadatas->total_philo].meals_ate != metadatas->min_meals)
		{
			handle_death(i % metadatas->total_philo, metadatas);
			break ;
		}
		i++;
	}
	return (NULL);
}
