/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:29:03 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/12 01:31:27 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	is_nega;

	is_nega = 0;
	result = 0;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			is_nega = 1;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		result *= 10;
		result += (*nptr) - '0';
		nptr++;
	}
	if (is_nega)
		result *= -1;
	return (result);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error getting time of day\n");
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
// void	ft_sleep(size_t time)
// {
// 	size_t	start;
//
// 	start = get_current_time();
// 	while (get_current_time() - start <= time);
// 	return ;
// }
