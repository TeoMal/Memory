# Set the name of the output
EXEC := game

# paths
EXTRA := ./libs/libraylib.a
INCLUDE := ./include
SRC := ./src
BUILD := ./build

#Default compiler
CC := g++

#Exta libs
LIBS := -lraylib

################################### DO NOT EDIT BELOW THIS LINE UNLESS YOU KNOW WHAT YOU ARE DOING ###################################


#compiler options
FLAGS = -I$(INCLUDE) -lm -O3 -Wall

SRCS := $(shell find $(SRC) -name '*.cpp')
OBJS := $(SRCS:$(SRC)/%.cpp=$(SRC)/%.opp)
OBJPATH := $(addprefix $(BUILD)/,$(notdir $(OBJS)))
LDFLAGS := -lGL -lpthread -ldl -lrt -lX11

$(SRC)/%.opp: $(SRC)/%.cpp
	$(CC) $(FLAGS) -c $< -o $@ && mv $@ $(BUILD)

$(EXEC):$(OBJS)
	$(CC) $(OBJPATH) $(EXTRA) -o $(EXEC) $(LDFLAGS)

PHONY clean:
	rm -f $(BUILD)/*.o $(BUILD)/*.opp $(EXEC)
run: $(EXEC)
	./$(EXEC)