![Philosophers – Dining Table Simulation](philo_image.png)

# Philosophers – Dining Philosophers Problem

A robust implementation of the classic **Dining Philosophers Problem** using POSIX threads (pthreads) and mutexes in C. This project demonstrates core concepts in concurrent programming including thread synchronization, deadlock prevention, and resource management.

---

## Project Overview

This implementation simulates philosophers sitting at a circular table, where each philosopher must acquire two forks (left and right) to eat. The simulation uses **pthread mutexes** to ensure thread-safe access to shared resources and prevent race conditions.

### Key Features

- **Multi-threaded Simulation**: Each philosopher runs as an independent thread
- **Mutex-based Synchronization**: Proper locking mechanisms to prevent deadlocks
- **Real-time State Monitoring**: Tracks philosopher actions (thinking, eating, sleeping, dying)
- **Death Detection**: Monitors philosophers for starvation and terminates simulation
- **Optional Meal Limits**: Set a target number of meals per philosopher
- **Precise Timing**: Accurate millisecond-level timing using `gettimeofday()`

---

## Compilation

Simply run:

```bash
make
```

This compiles all source files with the following flags:
- `-Wall -Werror -Wextra` : Strict error checking
- `-g` : Debug symbols
- `-pthread` : POSIX threads support

---

## Usage

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers (1-200) |
| `time_to_die` | Time in milliseconds before a philosopher dies of hunger |
| `time_to_eat` | Time in milliseconds a philosopher spends eating |
| `time_to_sleep` | Time in milliseconds a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional: target meals per philosopher |

### Example

```bash
./philo 5 800 200 200
./philo 4 410 200 200 10
```

---

## Implementation Details

### Core Components

- **`init.c`** : Initializes mutexes, philosopher structures, and program state
- **`create.c`** : Creates philosopher threads and monitoring thread using `pthread_create()`
- **`table_process.c`** : Main philosopher loop—fork acquisition, eating, sleeping, thinking
- **`monitoring.c`** : Background thread that checks for dead philosophers or meal completion
- **`destroy.c`** : Cleanup and state printing with thread-safe output
- **`utils.c`** : Helper functions for time management and sleeping
- **`philo.h`** : Header with data structures and function declarations

### Thread Synchronization

Three primary mutexes ensure thread safety:
1. **`write_lock`** : Protects console output
2. **`meal_lock`** : Protects eating counters and meal timestamps
3. **`dead_lock`** : Protects the global death flag

Fork access uses individual mutexes—one per fork—to prevent simultaneous pickup by neighbors.

### Algorithm Highlights

- Philosophers with even IDs sleep briefly at start to reduce contention
- Each philosopher acquires right fork first, then left fork (circular arrangement)
- Eating and last-meal timestamps are protected by mutex
- Monitor thread polls at 10ms intervals for death or meal completion
- Precise timing uses `gettimeofday()` with millisecond precision

---

## Compilation & Cleanup

| Command | Purpose |
|---------|---------|
| `make` | Compile the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and executable |
| `make re` | Clean and recompile |

---

## Author

Created as part of 42 School curriculum.

---

## Language Breakdown

- **C** — Core implementation
- **Makefile** — Build automation
