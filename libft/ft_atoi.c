/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:58:54 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/19 13:38:20 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *p)
{
	int	i;
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	i = 0;
	while (p[i] == ' ' || p[i] == '\f' || p[i] == '\n' || p[i] == '\r'
		|| p[i] == '\t' || p[i] == '\v')
		i++;
	if (p[i + 1] >= '0' && p[i + 1] <= '9' && (p[i] == '-' || p[i] == '+'))
	{
		if (p[i] == '-')
			sign = -1;
		i++;
	}
	else if ((p[i] == '-' || p[i] == '+') && !(p[i + 1] >= '0' && p[i] <= '9'))
		return (0);
	while (p[i] >= '0' && p[i] <= '9')
	{
		result = result * 10 + (p[i] - '0');
		i++;
	}
	return (result * sign);
}

//#include <stdio.h>
//int main (void)
//{
//	printf("%i", ft_atoi("9 58"));
//}