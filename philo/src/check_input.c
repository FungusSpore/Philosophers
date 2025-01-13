/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:06:54 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/13 15:02:47 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	not_posi_digit(char *input)
{
	if (*input == '-')
		return (1);
	if (*input == '+')
		input++;
	while (*input)
	{
		if (!('0' <= *input && *input <= '9'))
			return (1);
		input++;
	}
	return (0);
}

int	check_values(int *vars)
{
	int	i;

	i = 0;
	if (vars[i] > MAX_PHILOS || vars[i] <= 0)
	{
		printf("Enter only 200 or less or more than zero philo\n");
		return (1);
	}
	i++;
	while (i < 4)
	{
		if (vars[i++] < 60)
		{
			printf("Time cannot be less than 60 ms\n");
			return (2);
		}
	}
	return (0);
}

int	check_input(int argc, char **argv, int *vars)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("./philo <4 - 5 args>\n");
		return (1);
	}
	while (++i < argc)
	{
		if (not_posi_digit(argv[i]))
		{
			printf("Please only enter positive numbers\n");
			return (2);
		}
		vars[i - 1] = ft_atoi(argv[i]);
	}
	if (argc == 5)
		vars[MIN_MEALS] = NOT_SET;
	if (check_values(vars))
		return (3);
	return (0);
}
