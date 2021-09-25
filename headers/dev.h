/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 22:44:44 by zed               #+#    #+#             */
/*   Updated: 2021/09/25 14:33:31 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEV_H
# define DEV_H
// TODO: DELETE THIS IN PROD
extern char *types[];
void	print_helper(t_list *tokens);
void	debug_leaks(void);
#endif