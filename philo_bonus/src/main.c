/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:52:53 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/09 16:54:17 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	create_child(int *vars)
{
	int	pid;
	int	i;

	i = 0;
	while (i < vars[NUM_PHILOS])
	{
		pid = fork();
		if (pid == -1)
		{
			printf("Fork has failed\n");
			return (1);
		}
		if (pid == 0)
			philo_routine();
		else
			i++;
	}
	return (0);
}

int	kill_child()
{
	pid_t	w;

	while (1)
	{
		w = wait(NULL);
		if (w == -1)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_philo				*metadatas;
	int					vars[5];

	if (check_input(argc, argv, vars))
		return (1);
	metadatas = create_philo_metadatas(vars, &forks);
	if (!metadatas)
		return (2);
	if (create_child())
		return (3);
	if (kill_child())
		return (4);
	return (0);
}
