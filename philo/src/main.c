/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:38:18 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/06 17:38:38 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(int *vars, t_philo *metadatas, pthread_t **threads)
{
	int	i;

	i = -1;
	*threads = malloc(sizeof(pthread_t) * vars[NUM_PHILOS]);
	if (!*threads)
	{
		printf("Failed to allocate memory for threads\n");
		return (1);
	}
	while (++i < vars[NUM_PHILOS])
		if (pthread_create(threads[i], NULL, philo_routine, &metadatas[i]) != 0)
		{
			printf("Failed to make threads\n");
			return (2);
		}
	return (0);
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
	create_threads(vars, metadatas, &threads);
}
