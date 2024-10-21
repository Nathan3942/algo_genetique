/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:49:01 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/18 16:23:10 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
#define ALGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <readline/readline.h>

#define POP_SIZE 100
#define MAX_GEN 100000
#define MUTATION_RATE 0.05

typedef struct s_algo
{
    char    **population;
    char    *target;
    int     target_len;
    int     index_parent1;
    int     index_parent2;
    char    *parent1;
    char    *parent2;

}   t_algo;


#endif