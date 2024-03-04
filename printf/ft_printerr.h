/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerr.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:19:45 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/04 13:08:47 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTERR_H
# define FT_PRINTERR_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printerr(const char *arg, ...);
int	print_char(char c);
int	print_lhex(unsigned int nbr);
int	print_nbr(int nb);
int	print_pointer(void *ptr);
int	print_str(char *str);
int	print_uhex(unsigned int nbr);
int	ft_tree(const char *str, int i, va_list lst);
int	is_from_set(char c);
int	print_unbr(unsigned int nb);

#endif