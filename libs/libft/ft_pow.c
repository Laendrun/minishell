/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:58:00 by saeby             #+#    #+#             */
/*   Updated: 2023/01/28 10:07:44 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int nb, int power)
{
	if (power != 0 && power >= 0)
		return (nb * (ft_pow(nb, power - 1)));
	else if (power < 0)
		return (0);
	else
		return (1);
}
