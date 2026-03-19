*This project has been created as part of the 42 curriculum by kevlim*

# Philosophers

## Description

Philosophers is a project that introduces us to the concepts of **multi-threading**, **mutexes**, and **data races**.  
The objective of this program is to simulate "**The Dining Philosophers Problem**".  
The goal is to keep the philosophers alive:
- each philosopher is a thread, and each fork is a mutex
- they perform the following actions in order: eat - sleep - think (wait for the forks)
- to eat, they must have two forks, knowing that there is only one fork per philosopher
- if one dies, the simulation stops and the death must be displayed within a maximum of 10 milliseconds
- write each change in philosopher status

Arguments :
- `number_of_philosophers`: The number of philosophers and also the number
of forks.
- `time_to_die (in milliseconds)`: If a philosopher has not started eating within
time_to_die milliseconds since the start of their last meal or the start of the
simulation, they die.
- `time_to_eat (in milliseconds)`: The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- `time_to_sleep (in milliseconds)`: The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat (optional argument)`: If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

## Instruction

- `make`
- `./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`

## Ressources

- Medium : https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
- Gitbook : https://42-cursus.gitbook.io/guide/3-rank-03/philosophers
- AI : fixing data races and starvation problems
