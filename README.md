_This project has been created as part of the 42 curriculum by pkongkha_

# Description

Philosopher _is_ deadly.

The project's goal was to introduce you to MUTal EXclusions, Data Races
, solving Deadlock, MT-Safe functions.

## Breif overview

The [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
is a example in concurrent programming to synchronization issue and technique
for resolving them.

It was originally formulated in 1965 by Edsger Dijkstra as a student
exam exercise, presented in terms of computers competing for access
to tape drive peripherals and then formulated in terms of diners,
dubbed the "dining quintet". Soon after, Tony Hoare gave the problem
its present name.

Five philosophers dine together at the same table. Each philosopher has
their own plate at the table. There is a fork between each pair of
adjacent plates. The dish served is a kind of spaghetti that must be
eaten with two forks. Each philosopher can only alternately think and
eat. Moreover, a philosopher can only eat their spaghetti when they
have both a left and a right fork. Thus, two forks will only be
available when their two nearest neighbors are thinking,
not eating. After an individual philosopher finishes eating, they will
put down both forks. The problem is how to design a regimen
(a concurrent algorithm) such that any philosopher will not starve;
i.e., each can forever continue to alternate between eating and thinking,
assuming that no philosopher can know when others may want to eat or
think (an issue of incomplete information).

# Instructions

## Mandatory part
```sh
cd philo/
```

To compile
```c
make all
```

To run
```
./philo <philo_cnt> <time_die> <time_eat> <time_sleep> [times_must_eat]
```

Each argument represents
- philo_cnt: total count of philosophers and forks
- time_die: time (in ms) before philosopher dies from starving
- time_eat: time (in ms) philosopher use for eating
- time_sleep: time (in ms) philosopher use for sleep
- times_must_eat: how much times each philosopher need to eat before
simulation ends, unspecifies this means infinity

# Resources
- [WikiPedia | Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [OpenBSD | pthread_mutex_init.3 manpage](https://man.openbsd.org/pthread_mutex_init.3)
- [Linux man-pages 6.19 | printf.3 manpage](https://linux.die.net/man/3/printf)
- [FreeBSD | pthread_create.3 manpage](https://man.freebsd.org/cgi/man.cgi?query=pthread_create&apropos=0&sektion=0&manpath=FreeBSD+15.1-STABLE&format=html)
- [Stack Overflow | Difference between pthread_exit, pthread_join and pthread_detach](https://stackoverflow.com/questions/22427007/difference-between-pthread-exit-pthread-join-and-pthread-detach)

## AI USAGE

AI IS USED FOR THE BUG FIXING.

IN MOST WAY I WILL NEVER BE ABLE TO SUBMIT THIS PROJECT WITHOUT
ASSISTANCE OF AI, BECAUSE THERE IS A LOT OF LOGIC ERRORS GOING ON IN THIS
PROJECT AND NO ONE IS GONNA NOTICE IT ALL.

THE PROJECT DESIGN IS SO COMPLICATED YET TO BE COMPLIANT TO THE SUBJECT
EVERY TIMING AND MUTEXES IS DESIGNED TO PROTECT AGAINST DATA RACES
AND STDOUT ORDERING PROBLEM.
