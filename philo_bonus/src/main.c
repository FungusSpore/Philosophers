/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:52:53 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/10 22:52:44 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo				*metadatas;
	int					*pids;
	int					vars[5];

	if (check_input(argc, argv, vars))
		return (1);
	metadatas = create_philo_metadatas(vars);
	if (!metadatas)
		return (2);
	if (create_child(vars, metadatas, &pids))
		return (3);
	kill_child(pids, vars);
	free(pids);
	free(metadatas);
	sem_close(metadatas->forks_sem);
	sem_close(metadatas->is_alive_sem);
	sem_close(metadatas->last_ate_sem);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_ISDEAD);
	sem_unlink(SEM_LASTMEAL);
	return (0);
}
