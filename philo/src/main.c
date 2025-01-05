/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:38:18 by jianwong          #+#    #+#             */
/*   Updated: 2025/01/05 18:35:18 by jianwong         ###   ########.fr       */
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
		if ('0' <= *input && *input <= '9')
	}
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

}

int	main(int argc, char **argv)
{
	int	vars[5];
	if (check_input(argc, argv, vars))
		return (1);

}
