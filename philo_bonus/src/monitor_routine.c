/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 01:22:12 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/12 01:23:06 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	handle_death(t_philo *metadatas)
{
	sem_wait(metadatas->is_alive_sem);
	metadatas->is_dead = 1;
	usleep(100);
	printf("%lu %d died\n", \
	get_current_time() - metadatas->start_time, metadatas->index);
}

int	monitor_thread(t_philo *metadatas)
{
	size_t	time_since_last_meal;

	while (1)
	{
		if (metadatas->min_meals > -1 && \
		(metadatas->meals_ate >= metadatas->min_meals))
			break ;
		sem_wait(metadatas->last_ate_sem);
		time_since_last_meal = get_current_time() - metadatas->last_ate;
		if (time_since_last_meal >= metadatas->time_die && \
		metadatas->meals_ate != metadatas->min_meals)
		{
			handle_death(metadatas);
			return (1);
		}
		sem_post(metadatas->last_ate_sem);
	}
	return (0);
}
