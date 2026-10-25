SRCS != ls *.c

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS += -Wall -Wextra -Werror -pedantic
CFLAGS += -pthread
CFLAGS += -MMD -MP
CFLAGS += -fstack-protector-all
LDFLAGS += -pthread

# Debugging
CFLAGS += -g3
LDFLAGS += -g3
CFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address
CFLAGS += -fsanitize=undefined
LDFLAGS += -fsanitize=undefined
#CFLAGS += -fsanitize=thread
#LDFLAGS += -fsanitize=thread

CC ?= cc

NAME = philo

.PHONY: all clean fclean re lint compliance
all: $(NAME)
clean:
	rm -f $(OBJS) $(DEPS)
fclean: clean
	rm -f $(NAME)
re: fclean .WAIT all
lint:
	clang-tidy $(SRCS)
compliance: lint all
	norminette

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

-include $(DEPS)
