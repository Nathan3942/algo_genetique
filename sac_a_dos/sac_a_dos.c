/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sac_a_dos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:40:37 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/18 15:17:14 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


#define POP_SIZE 10
#define MAX_GEN 500
#define MUTATION 0.1
#define NUM_ITEMS 10
#define MAX_WEIGHT 37

int weights[NUM_ITEMS] = {2, 3, 4, 5, 9, 6, 12, 8, 5, 9};
int value[NUM_ITEMS] = {3, 4, 8, 8, 10, 9, 15, 10, 6, 9};

typedef struct s_individue
{
    int gen[NUM_ITEMS];
    int fitness;
}   t_individue;


int fitness(t_individue *individue)
{
	int i_weight = 0;
	int i_value = 0;
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		if (individue->gen[i] == 1)
		{
			i_weight += weights[i];
			i_value += value[i];
		}
	}
	if (i_weight > MAX_WEIGHT)
		return (0);
	return (i_value);
}

void    generate_individue(t_individue *individue)
{
    for (int i = 0; i < NUM_ITEMS; i++)
	    individue->gen[i] = rand() % 2;
    individue->fitness = fitness(individue);
}

t_individue	*select_parent(t_individue *population, t_individue *best_indiv)
{
	int	best = 0;
	int	sec = 0;
	for (int i = 1; i < POP_SIZE; i++)
	{
		if (population[i].fitness > population[best].fitness)
		{
			if (best_indiv == NULL)
			{
				best = i;
				continue ;
			}
			for (int z = 0; z < NUM_ITEMS; z++)
			{
				if (population[i].gen[z] == best_indiv->gen[z])
					sec++;
			}
			if (sec != NUM_ITEMS)
				best = i;
		}
	}
	return (&population[best]);
}

void	crossover(t_individue *parent, t_individue *individue, t_individue *child)
{
	for (int i = 0; i < NUM_ITEMS; i++)
		child->gen[i] = (rand() % 2) ? parent->gen[i] : individue->gen[i];
	child->fitness = fitness(child);
}

void	mutate(t_individue *individue)
{
	for(int i = 0; i < NUM_ITEMS; i++)
	{
		if ((float)rand() / RAND_MAX < MUTATION)
			individue->gen[i] = !individue->gen[i];
	}
	individue->fitness = fitness(individue);
}


int main (void)
{
    srand(time(NULL));
	int	best_value = 0;
    t_individue population[POP_SIZE];

    for (int i = 0; i < POP_SIZE; i++)
		generate_individue(&population[i]);
	printf("\nGeneration 0\n\n");
	for(int i = 0; i < POP_SIZE; i++)
	{
		printf("indiv %d : ", i);
		for (int z = 0; z < NUM_ITEMS; z ++)
			printf("%d ", population[i].gen[z]);
		printf(" Fitness : %d", population[i].fitness);
		printf("\n");
	}

	for (int gen = 1; gen < MAX_GEN; gen++)
	{
		// if (best->fitness == 23)
		// {	
		// 	printf("Optimal solus found in gen %d\n", gen);
		// 	break ;
		// }
		t_individue *parent1 = select_parent(population, NULL);
		t_individue *parent2 = select_parent(population, parent1);

		printf("Fitness parent 1 : %d, 2 : %d\n", parent1->fitness, parent2->fitness);
		
		t_individue	new_population[POP_SIZE];
		for (int i = 0; i < POP_SIZE; i++)
		{
			crossover(parent1, &population[i], &new_population[i]);
			mutate(&new_population[i]);
		}
		for (int i = 0; i < POP_SIZE; i++)
			population[i] = new_population[i];
		
		printf("\nGeneration %d\n\n", gen);
		for(int i = 0; i < POP_SIZE; i++)
		{
			printf("indiv %d : ", i);
			for (int z = 0; z < NUM_ITEMS; z ++)
				printf("%d ", population[i].gen[z]);
			printf(" Fitness : %d", population[i].fitness);
			printf("\n");
		}
		t_individue	*best = select_parent(population, NULL);
		if (best->fitness > best_value)
			best_value = best->fitness;
		printf("Gen : %d, best individue gen (fitness : %d) | best individue all (fitness : %d)\n", gen, best->fitness, best_value);

		for (int i = 0; i < NUM_ITEMS; i++)
			printf("%d ", best->gen[i]);
		printf("\n");
	}
	return (0);
}