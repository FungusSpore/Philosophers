/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:33:42 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/06 18:16:24 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_think(t_philo *metadata)
{
	printf("%lu %d is thinking\n", \
	get_current_time() - metadata->start_time, metadata->index);
	if (metadata->index % 2 == 1)
	{
		pthread_mutex_lock(&(metadata->left_fork));
		pthread_mutex_lock(&(metadata->right_fork));
	}
	else
	{
		pthread_mutex_lock(&(metadata->right_fork));
		pthread_mutex_lock(&(metadata->left_fork));
	}
}

void	philo_eat(t_philo *metadata)
{

}

void	*philo_routine(void *args)
{
	t_philo	*metadata = (t_philo *)args;

	metadata->last_ate = get_current_time();
	metadata->start_time = get_current_time();
	philo_think(metadata);
	philo_eat(metadata);
	philo_sleep(metadata);
}
