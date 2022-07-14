/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 11:03:04 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/14 13:35:28 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_itoalen(int n, int len)
{
	if (n < 1)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*rstr;

	len = ft_itoalen(n, 0);
	rstr = (char *)malloc(sizeof(*rstr) * (len + 1));
	if (!rstr)
		return (NULL);
	if (n == 0)
		rstr[0] = '0';
	rstr[len] = '\0';
	if (n < 0)
	{
		rstr[0] = '-';
		n *= -1;
	}
	while (n && len >= 0)
	{
		rstr[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (rstr);
}
