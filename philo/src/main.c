/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:38:18 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/07 16:59:03 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_t	*create_threads(int *vars, t_philo *metadatas)
{
	int	i;
	pthread_t	*threads;

	i = -1;
	threads = malloc(sizeof(pthread_t) * (vars[NUM_PHILOS] + 1));
	if (!threads)
	{
		printf("Failed to allocate memory for threads\n");
		return (NULL);
	}
	while (++i < vars[NUM_PHILOS])
	{
		if (pthread_create(threads + i, NULL, philo_routine, metadatas + i) != 0)
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
	return (threads);
}

void	wait_threads(pthread_t *threads, int *vars)
{
	int	i;

	i = 0;
	while (i < vars[NUM_PHILOS])
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Thread faild to join\n");
			return ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	vars[5];
	t_philo	*metadatas;
	pthread_t	*threads;

	if (check_input(argc, argv, vars))
		return (1);
	metadatas = create_philo_metadatas(vars);
	if (!metadatas)
		return (2);
	threads = create_threads(vars, metadatas);
	create_monitoring_thread(vars, metadatas);
	wait_threads(threads, vars);
}
