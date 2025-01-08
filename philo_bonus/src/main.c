/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:52:53 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/09 00:18:27 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo				*metadatas;
	int					vars[5];

	if (check_input(argc, argv, vars))
		return (1);
	metadatas = create_philo_metadatas(vars, &forks);
	if (!metadatas)
		return (2);

	return (0);
}
