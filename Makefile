NAME = philo

SRCS = ./srcs/

PHILO_INCLUDES = -Iincludes

CFILES = $(SRCS)philo.c $(SRCS)init_values.c $(SRCS)quit_program.c $(SRCS)manage_threads.c $(SRCS)utility_functions.c $(SRCS)commute_job_sleep_routine.c $(SRCS)commute_job_sleep_actions.c $(SRCS)init_philo_data.c $(SRCS)manage_mutexes.c $(SRCS)big_brother.c $(SRCS)arg_checking.c $(SRCS)fork_management.c $(SRCS)routine_utilities.c
OFILES = $(CFILES:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -g3 -pthread

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) -g -o $(NAME) $(OFILES) -pthread

$(SRCS)%.o: $(SRCS)%.c
	$(CC) $(FLAGS) -g -c -o $@ $< $(PHILO_INCLUDES)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
