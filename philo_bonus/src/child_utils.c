/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:34:20 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/12 01:22:40 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static pthread_t	*create_thread(t_philo *metadatas)
{
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_t));
	if (!threads)
		return (NULL);
	if (pthread_create(threads, \
	NULL, philo_routine, metadatas) != 0)
	{
		printf("Failed to make threads\n");
		return (NULL);
	}
	return (threads);
}

void	child_path(t_philo *metadatas, int i)
{
	pthread_t	*philo;

	sem_wait(metadatas->is_ready_sem);
	sem_post(metadatas->is_ready_sem);
	metadatas[i].start_time = get_current_time();
	metadatas[i].last_ate = get_current_time();
	philo = create_thread(metadatas + i);
	if (monitor_thread(metadatas + i))
		exit(metadatas->index);
	pthread_join(*philo, NULL);
	exit(0);
}

int	create_child(int *vars, t_philo *metadatas, int **pids)
{
	int	i;

	i = 0;
	sem_wait(metadatas->is_ready_sem);
	*pids = malloc(sizeof(int) * vars[NUM_PHILOS]);
	if (!*pids)
		return (1);
	while (i < vars[NUM_PHILOS])
	{
		(*pids)[i] = fork();
		if ((*pids)[i] == -1)
		{
			printf("Fork has failed\n");
			return (1);
		}
		if ((*pids)[i] == 0)
			child_path(metadatas, i);
		else
			i++;
	}
	sem_post(metadatas->is_ready_sem);
	return (0);
}

void	kill_child(int *pids, int *vars)
{
	pid_t	w;
	int		status;
	int		i;

	i = 0;
	while (1)
	{
		w = waitpid(-1, &status, WNOHANG);
		if (w == -1)
			break ;
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) != 0)
				while (i < vars[NUM_PHILOS])
					kill(pids[i++], SIGTERM);
	}
}
