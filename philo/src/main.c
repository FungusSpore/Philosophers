/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:54:30 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/08 18:14:43 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static pthread_t	*create_threads(int *vars, t_philo *metadatas)
{
	int				i;
	pthread_t		*threads;

	i = -1;
	threads = malloc(sizeof(pthread_t) * (vars[NUM_PHILOS] + 1));
	if (!threads)
		return (NULL);
	pthread_mutex_lock(metadatas->is_philo_ready_mutex);
	while (++i < vars[NUM_PHILOS])
	{
		if (pthread_create(threads + i, \
		NULL, philo_routine, metadatas + i) != 0)
		{
			printf("Failed to make threads\n");
			return (NULL);
		}
	}
	if (pthread_create(threads + i, NULL, monitor_routine, metadatas) != 0)
	{
		printf("Failed to make threads\n");
		return (NULL);
	}
	pthread_mutex_unlock(metadatas->is_philo_ready_mutex);
	return (threads);
}

static void	wait_threads(pthread_t *threads, int *vars)
{
	int	i;

	i = 0;
	while (i <= vars[NUM_PHILOS])
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Thread faild to join\n");
			return ;
		}
		i++;
	}
	free(threads);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t		*forks;
	pthread_t			*threads;
	t_philo				*metadatas;
	int					vars[5];

	if (check_input(argc, argv, vars))
		return (1);
	metadatas = create_philo_metadatas(vars, &forks);
	if (!metadatas)
		return (2);
	threads = create_threads(vars, metadatas);
	wait_threads(threads, vars);
	free_metadata(metadatas, forks);
	return (0);
}
