/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:10:16 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/07 15:10:21 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	if ((c == ' ') || (c == '\f') || (c == '\n')
		|| (c == '\r') || (c == '\t') || (c == '\v'))
		return (1);
	else
		return (0);
}

static int	ft_to_int(char *str)
{
	int				i;
	unsigned int	nbr;

	nbr = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr);
}

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		s;
	int		nbr;

	s = 1;
	str = (char *)nptr;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		s = -1;
		str++;
	}
	nbr = ft_to_int(str);
	nbr *= s;
	return (nbr);
}