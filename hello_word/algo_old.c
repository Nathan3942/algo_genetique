/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:52:10 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/18 10:52:27 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:45:20 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/18 10:51:22 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <readline/readline.h>

#define POP_SIZE 10
#define MAX_GEN 1000
#define MUTATION_RATE 0.1
#define TARGET "HELLO WORLD"
#define TARGET_LEN 11

char    random_char(void)
{
    int random = rand() % 27;
    if (random == 26)
        return (' ');
    return ('A' + random);
}

void    generate_individu(char *individu)
{
    for (int i = 0; i < TARGET_LEN; i++)
        individu[i] = random_char();
    individu[TARGET_LEN] = '\0';
}

int	fitness(char *individue)
{
	int score = 0;
	for(int i = 0; i < TARGET_LEN; i++)
	{
		if (individue[i] == TARGET[i])
			score++;
	}
	return (score);
}

int select_parent(char population[POP_SIZE][TARGET_LEN + 1], int parent1)
{
	int	best = 0;
	for (int i = 1; i < POP_SIZE; i++)
	{
		if (fitness(population[i]) > fitness(population[best]) && parent1 != i)
			best = i;
	}
	return (best);
}

void	crossover(char *parent1, char *parent2, char *child)
{
	for (int i = 0; i < TARGET_LEN; i++)
		child[i] = (rand() % 2 == 0) ? parent1[i] : parent2[i];
	child[TARGET_LEN] = '\0';
}

void	mutate(char *individue)
{
	for (int i = 0; i < TARGET_LEN; i++)
	{
		if ((float)rand() / RAND_MAX < MUTATION_RATE)
			individue[i] = random_char();
	}
}

int main(void)
{
	srand(time(NULL));

	char    population[POP_SIZE][TARGET_LEN + 1];

	for (int i = 0; i < POP_SIZE; i++)
		generate_individu(population[i]);

	for (int gen = 0; gen < MAX_GEN; gen++)
	{
		int index_parent1 = select_parent(population, -1);
		int index_parent2 = select_parent(population, index_parent1);
		char	*parent1 = population[index_parent1];
		char	*parent2 = population[index_parent2];

		char	new_population[POP_SIZE][TARGET_LEN + 1];

		printf("Gen : %d\n\nPopulation :\n", gen);
		for (int z = 0; z < POP_SIZE; z++)
			printf("%s\n", population[z]);

		printf("\nParent : %s, %s\n", parent1, parent2);

		int best = select_parent(population, -1);
		printf("Gen : %d, best individue : %s (fitness : %d)\n\n", gen, population[best], fitness(population[best]));

		if (fitness(population[best]) == TARGET_LEN)
		{
			printf("Result final in gen %d : %s\n", gen, population[best]);
			break ;
		}

		for (int i = 0; i < POP_SIZE; i++)
		{
			crossover(parent1, parent2, new_population[i]);
			mutate(new_population[i]);
		}
		memcpy(population, new_population, sizeof(population));
	}
    return (0);
}