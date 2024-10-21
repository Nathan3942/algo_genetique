/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:45:20 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/18 16:08:59 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	set_info(char *input, t_algo *algo)
{
	int i = 0;
	while (input[i] != '\0')
		i++;
	algo->target = (char *)malloc ((i + 1) * sizeof(char));
	i = 0;
	while (input[i] != '\0')
	{
		algo->target[i] = input[i];
		i++;
	}
	
	algo->target[i] = '\0';
	algo->target_len = i;
}

char    random_char(void)
{
    int random = rand() % 27;
    if (random == 26)
        return (' ');
	int maj = rand() % 2;
	if (maj > 0)
		return ('a' + random); 
    return ('A' + random);
}

void    generate_individu(t_algo *algo, int index)
{
	int i = 0;
    while (i < algo->target_len)
        algo->population[index][i++] = random_char();
    algo->population[index][i] = '\0';
}

int	fitness(t_algo *algo, int index)
{
	int score = 0;
	for(int i = 0; i < algo->target_len; i++)
	{
		if (algo->population[index][i] == algo->target[i])
			score++;
	}
	return (score);
}

int select_parent(t_algo *algo, int index)
{
	int	best = 0;
	for (int i = 1; i < POP_SIZE; i++)
	{
		if (fitness(algo, i) > fitness(algo, best) && index != i)
			best = i;
	}
	return (best);
}

void	crossover(t_algo *algo, char *child)
{
	for (int i = 0; i < algo->target_len; i++)
		child[i] = (rand() % 2 == 0) ? algo->parent1[i] : algo->parent2[i];
	child[algo->target_len] = '\0';
}

void	mutate(char *individue, int target_len)
{
	for (int i = 0; i < target_len; i++)
	{
		if ((float)rand() / RAND_MAX < MUTATION_RATE)
			individue[i] = random_char();
	}
}

int main(void)
{
	srand(time(NULL));
	t_algo	*algo = (t_algo *)malloc (sizeof(t_algo));
	char	*input = NULL;

	do
	{
		if (input != NULL)
			free(input);
		input = readline("Entrer the search world : ");
		if (strcmp(input, "exit") == 0)
			break ;
		set_info(input, algo);

		algo->population = (char **)malloc(POP_SIZE * sizeof(char *));
		for(int i = 0; i < POP_SIZE; i++)
			algo->population[i] = malloc((algo->target_len + 1) * sizeof(char));

		for (int i = 0; i < POP_SIZE; i++)
			generate_individu(algo, i);

		for (int gen = 0; gen < MAX_GEN; gen++)
		{
			algo->index_parent1 = select_parent(algo, -1);
			algo->index_parent2 = select_parent(algo, algo->index_parent1);
			algo->parent1 = algo->population[algo->index_parent1];
			algo->parent2 = algo->population[algo->index_parent2];

			char	new_population[POP_SIZE][algo->target_len + 1];

			printf("Gen : %d\n\nPopulation :\n", gen);
			for (int z = 0; z < POP_SIZE; z++)
				printf("%s\n", algo->population[z]);

			printf("\nParent : %s, %s\n", algo->parent1, algo->parent2);

			int best = select_parent(algo, -1);
			printf("Gen : %d, best individue : %s (fitness : %d)\n\n", gen, algo->population[best], fitness(algo, best));

			if (fitness(algo, best) == algo->target_len)
			{
				printf("Result final in gen %d : %s\n", gen, algo->population[best]);
				break ;
			}

			for (int i = 0; i < POP_SIZE; i++)
			{
				crossover(algo, new_population[i]);
				mutate(new_population[i], algo->target_len);
			}
			for (int i = 0; i < POP_SIZE; i++)
				strcpy(algo->population[i], new_population[i]);
		}
		for (int i = 0; i < POP_SIZE; i++)
			free(algo->population[i]);
		free(algo->population);
		free(algo->target);
		
	} while (strcmp(input, "exit") != 0);

	free(input);
	free(algo);
	
    return (0);
}