/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:56:29 by alouriga          #+#    #+#             */
/*   Updated: 2024/09/02 06:25:46 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <limits.h>

static int	cheak_the_string(char *s)
{
	int	j;

	j = 0;
		while (s[j] != '\0')
		{
			if ((s[j] == '-' || s[j] == '+') && j != 0)
				return (1);
			j++;
		}
	return (0);
}


int	sign(char *arr)
{
	int	j = 0;
	int	count_sing = 0;

		while (arr[j] != '\0')
		{
			if (arr[j] == '+' || arr[j] == '-')
				count_sing++;
			j++;
		}
		if (count_sing >= 2)
			return (1);
	return (0);
}

static int	check_ch(char *s)
{
	int	j;

	j = 0;
		while (s[j] != '\0')
		{
			if (!((s[j] >= '0' && s[j] <= '9')
			|| (s[j] == '+') || s[j] == '-'))
				return (1);
			j++;
		}
	return (0);
}



long long my_atoi(char *str, int *index)
{
    long long result = 0;
    int sign = 1;
    int i = 0;
    
    *index = 0; // Initialize index to 0
    
    // Handle optional sign
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9')
    {
        // Check for overflow
        if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && (str[i] - '0') > LLONG_MAX % 10))
        {
            *index = 1; // Overflow detected
            return (sign * LLONG_MAX);
        }
        
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}

// long long my_atoi(char *str, int *index)
// {
//     long result;
//     long f_result;
//     int sign;
//     int i;
    
//     i = 0;
//     sign = 1;
//     f_result = 0;
//     result = 0;
//     if (str[i] == '-' || str[i] == '+')
//     {
//         if (str[i] == '-')
//             sign *= -1;
//         i++;
//     }
//     while (str[i] != '\0')
//     {
//         result = f_result * 10 + (str[i] - '0');
//         if (result <= f_result)
//         {
//             *index = 1;
//         }
//         i++;
//     }
//     return(result * sign);
// }

void    ft_exit(char **av)
{
    int i;
    int j;
    int x;
    int index = 0;

    i = 0;
    j = 1;
    x = 0;
    while (av[i] != NULL)
    {
        index++;
        i++;
    }
    if (index == 1)
        exit(0);
    i = 0;
    if (check_ch(av[1]) == 1 || sign(av[1]) == 1 || cheak_the_string(av[1]) == 1)
    {
        printf("numeric argument required\n"); // to do
        exit(255);
    }
    i = 0;
    index = 0;
    while (av[i])
    {
        index++;
        i++;
    }
    if (index != 2)
    {
        printf("too many arguments\n"); //too do
    }
    else
    {
        my_atoi(av[1], &x);
        if (x == 1)
        {
            printf("numeric argument required \n"); // to do
            exit(255);
        }
        else
        {
            // printf ("%d\n", x);
            // printf ("%lld\n", my_atoi(av[1], &x));
            exit(my_atoi(av[1], &x) % 256);
        }
    }
}
