/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:03:16 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 15:03:40 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		printed;
	long	num;

	printed = 0;
	num = (long) n;
	if (num < 0)
	{
		printed += ft_putchar_fd('-', fd);
		num *= -1;
	}
	if (10 <= num)
		printed += ft_putnbr_fd(num / 10, fd);
	printed += ft_putchar_fd('0' + (num % 10), fd);
	return (printed);
}
