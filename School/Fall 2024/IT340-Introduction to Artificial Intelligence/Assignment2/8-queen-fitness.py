# -*- coding: utf-8 -*-
"""
Created on Thu Jan 12 08:37:08 2017

@author: xfang13

"""
import numpy as np
import random
import matplotlib.pyplot as mpl

def fitness(Input):
    #Input should be a list
    # assert(type(Input)==list)

    #Step1: make the state out of the Input
    state = np.zeros((8,8))
    for j in range(8):
        state[Input[j]-1][j] = 1
            

    #Step2: find the fitness of the state
    attacks = 0
    k = -1
    for j in range(8):
        k += 1
        #direction 1: the east
        for l in range(k+1,8):
            attacks += state[state[:,j].argmax()][l]
    
        #direction 2: the northeast
        row = state[:,j].argmax()
        column = j
        while row > 0 and column < 7:
            row -= 1
            column += 1
            attacks += state[row][column]
            
        #direction 3: the southeast
        row = state[:,j].argmax()
        column = j
        while row < 7 and column < 7:
            row += 1
            column += 1
            attacks += state[row][column]
            
    return 28 - attacks

#generates first generation
def population(pop_size):
    base_population = []
    for number in range(pop_size):
        individual = []
        for num in range(8):
            individual.append(random.randint(1,8))
        base_population.append(individual)
    return base_population

#finds the minimum fitness
def min_fitness(population, fitness_fn):
    min = -1
    min_individual = []
    for individual in population:
        fitness = fitness_fn(individual)
        if min == -1 or fitness < min:
            min = fitness
            min_individual = individual
    return (min_individual,min)

#finds the maximum fitness
def max_fitness(population, fitness_fn):
    max = -1
    max_individual = []
    for individual in population:
        fitness = fitness_fn(individual)
        if fitness > max:
            max = fitness
            max_individual = individual
    return (max_individual,max)

#finds the average fitness
def avg_fitness(population, fitness_fn):
    sum = 0
    for individual in population:
        fitness = fitness_fn(individual)
        sum += fitness
    avg = sum/len(population)
    return avg

#randomly selects an individual from a population
def random_selection(population, fitness_fn):
    avg = avg_fitness(population, fitness_fn)
    flag = True
    while flag == True:
       individual = population[random.randint(0,len(population)-1)]  
       if fitness_fn(individual) >= avg - .1:
           flag = False
    return individual
            
#creates a child
def reproduce(x , y):
    split = random.randint(0,len(x)-1)
    child = []
    child =  x[split:] + y[:split]
    return child

#mutates a child
def mutate(child):
    child[random.randint(0,len(child)-1)] = random.randint(1,8)
    return child
            
#performs the genetic algorithm
def genetic_algorithm(population, fitness_fn):
    max_tuple = max_fitness(population, fitness_fn)
    min_tuple = min_fitness(population, fitness_fn)
    y_max = [max_tuple[1]]
    y_min = [min_tuple[1]]
    y_avg = [avg_fitness(population, fitness_fn)]
    flag = True
    if max_tuple[1] == 28.0:
        flag = False
    generation = 1
    gen_size = len(population)
    while flag == True:
        new_population = []
        #print(generation)
        #print(population)
        for num in range(gen_size):
            x = random_selection(population, fitness_fn)
            y = random_selection(population, fitness_fn)
            #print(x,y)
            child = reproduce(x,y)
            if random.random() <= .03:
                child = mutate(child)
            new_population.append(child)
            #print(child)
        generation += 1
        population = new_population
        max_tuple = max_fitness(population, fitness_fn)
        min_tuple = min_fitness(population, fitness_fn)
        y_max.append(max_tuple[1])
        y_min.append(min_tuple[1])
        y_avg.append(avg_fitness(population, fitness_fn))
        if max_tuple[1] == 28.0:
            flag = False    
        #print(generation)
        #print(max_tuple)
    mpl.plot(y_max, '^-')
    mpl.plot(y_min, 's-')
    mpl.plot(y_avg,'--k')
    mpl.xlabel("generation")
    mpl.ylabel("fitness")
    mpl.title("population size = " + str(gen_size))
    
    mpl.show()
    return max_tuple[0]           
                
            
if __name__=='__main__':
#    print fitness([2, 4, 7, 4, 8, 5, 1, 3]) 
    #print (fitness([5,6,7,4,5,6,7,6]))
    #seed for population size 50
    #random.seed(53)
    
    #seed for population size 100
    random.seed(4538.260687181694)
    
    #seed for population size 200
    #random.seed(1161.7566299140958)
    
    #seed for population size 500
    #random.seed(3941.36764623101)
    
    
    first_gen = population(100)
    print(genetic_algorithm(first_gen,fitness))
          