/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:52:53 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/10 00:37:58 by jianwong         ###   ########.fr       */
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

static void	handle_death(t_philo *metadatas)
{
	sem_wait(metadatas->is_alive_sem);
	metadatas->is_dead = 1;
	usleep(100);
	printf("%lu %d died\n", get_current_time() - metadatas->start_time, metadatas->index);
	// sem_post(metadatas->is_alive_sem);
}

int	monitor_thread(t_philo *metadatas)
{
	size_t	time_since_last_meal;

	while (1)
	{
		if (metadatas->min_meals > -1 && (metadatas->meals_ate < metadatas->min_meals))
			break ;
		time_since_last_meal = get_current_time() - metadatas->last_ate;
		if (time_since_last_meal >= metadatas->time_die && \
		metadatas->meals_ate != metadatas->min_meals)
		{
			handle_death(metadatas);
			return (1);
		}
	}
	return (0);
}

int	create_child(int *vars, t_philo *metadatas)
{
	pthread_t	*philo;
	int	pid;
	int	i;

	i = 0;
	sem_wait(metadatas->is_alive_sem);
	while (i < vars[NUM_PHILOS])
	{
		printf("forking\n");
		pid = fork();
		if (pid == -1)
		{
			printf("Fork has failed\n");
			return (1);
		}
		if (pid == 0)
		{

			philo = create_thread(metadatas + i);
			if (monitor_thread(metadatas + i))
				exit(1);
			pthread_join(*philo, NULL);
			exit(0);
		}
		else
			i++;
	}
	sem_post(metadatas->is_alive_sem);
	return (0);
}

void	kill_child(void)
{
	pid_t	w;
	int	status;

	while (1)
	{
		w = waitpid(-1, &status, WNOHANG);
		if (w == -1)
			break ;
		// if (WIFEXITED(status))
		// 	if (WEXITSTATUS(status) == 1)
				// kill(-1, SIGKILL);
	}
}

int	main(int argc, char **argv)
{
	t_philo				*metadatas;
	int					vars[5];

	printf("check_input\n");
	if (check_input(argc, argv, vars))
		return (1);
	printf("craete meta\n");
	metadatas = create_philo_metadatas(vars);
	if (!metadatas)
		return (2);
	printf("craete child\n");
	if (create_child(vars, metadatas))
		return (3);
	printf("kill child\n");
	kill_child();
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_ISDEAD);
	return (0);
}
