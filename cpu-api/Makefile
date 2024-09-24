CC = gcc
CFLAGS = -Wall -Wextra

# List of tasks
TASKS = task1 task2 task3 task4 task5 task6 task7 task8

all: $(TASKS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TASKS)

