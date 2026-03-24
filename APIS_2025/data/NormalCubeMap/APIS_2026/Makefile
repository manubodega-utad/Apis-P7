FILES = $(wildcard *.cpp mapi/*.cpp)
OBJS = $(patsubst %.cpp,%.o, $(FILES))
INC = -I. -I./mapi
FLAGS = -g -std=c++2a 

all: $(OBJS)
	g++ $(FLAGS) $(OBJS) -o api.exe -lshaderc_combined -lvulkan -lglfw -lpugixml -lpthread

%.o: %.cpp
	g++ -c $(FLAGS) $(INC) $^ -o $@
	
clean:
	rm $(OBJS)
