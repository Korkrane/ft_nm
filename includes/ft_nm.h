/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:39:54 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/22 18:40:35 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include "../libft/libft.h"

typedef struct t_sym
{
    char *value;
    char *name;
    char symbol;
    char *firstLetterInName;
    struct t_sym *next;
    //struct t_sym *prev;
} t_sym;

t_sym *ft_symnew(void);
void ft_symadd_back(t_sym **asym, t_sym *new);
void symlist_display(t_sym *sym);

void sort_symlist(struct t_sym **head);
#endif