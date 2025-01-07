/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:16:52 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/07 17:24:30 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	handle_death(int i, t_philo *metadatas)
{
	int	size;
	int	j;

	size = metadatas->total_philo;
	j = 0;
	while (j < size)
		metadatas[j++].is_dead = 1;
	printf("%lu %d died\n", metadatas->start_time - get_current_time(), i);

}

void	*monitor_routine(void *args)
{
	t_philo	*metadatas;
	size_t	time_since_last_meal;
	int			i;
	
	metadatas = (t_philo *)args;
	i = 0;
	while (1)
	{
		time_since_last_meal = \
		metadatas[i % metadatas->total_philo].last_ate - get_current_time();
		if (time_since_last_meal >= metadatas->time_die && \
		metadatas[i % metadatas->total_philo].meals_ate != metadatas->min_meals)
			handle_death(i % metadatas->total_philo, metadatas);
		i++;
	}
}

