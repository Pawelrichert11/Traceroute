CC = g++
CFLAGS = -Wall -Wextra -std=c++11

SRCS = traceroute.cpp sender.cpp receiver.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = traceroute

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
