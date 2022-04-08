/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:19:07 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/08 18:17:34 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file meals_handler.c
 * \brief Contains functions for philosopher to meal.
*/

/** \headerfile philosopher.h */
#include "philosopher.h"

/**
 * \fn void *ft_eat_a_meal(void *global)
 * \brief The routine we call through 
 * the function pthread_create for the philosopher to eat.\n
 * This also here we lock and unlock the forks (the mutexes).
 * \param global : A structure containing 
 * both the philospher node and times Constants/Variables.
 */
void	*ft_routine(void *global)
{
	t_philo_list	*philo;

	t_global		*cast;
	t_timeval		*start_time;

	cast = (t_global *)(global);
	philo = *(cast->philo);
	start_time = (cast->start_time);
	while (1)
	{
		usleep(10);
		pthread_mutex_lock(philo->fork);
		ft_display_message(ft_timestamp(start_time), philo->id, 4);
		pthread_mutex_lock(philo->next->fork);
		ft_display_message(ft_timestamp(start_time), philo->id, 4);
		ft_display_message(ft_timestamp(start_time), philo->id, 0);
		philo->eat_counter++;
		cast->total_meals++;
		usleep(cast->time_to_eat * 1000);
		pthread_mutex_unlock(philo->next->fork);
		pthread_mutex_unlock(philo->fork);
		ft_display_message(ft_timestamp(start_time), philo->id, 1);
		usleep(cast->time_to_sleep * 1000);
		ft_display_message(ft_timestamp(start_time), philo->id, 2);
	}
	return (NULL);
}
