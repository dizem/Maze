FLAGS = -Wall -Wfatal-errors -Wextra -Werror -std=c++11 -pedantic
CC = g++

oop_ass2: main.cpp binaryHeap.h mazeBuilder.h astarMazeSolver.o bfsMazeSolver.o \
			  dfsMazeSolver.o depthBuilder.o disjointSets.o kruskalBuilder.o \
			  maze.o mazeFactory.o mazeSolver.o options.o stringUtils.o
	${CC} ${FLAGS} -o oop_ass2 main.cpp astarMazeSolver.o bfsMazeSolver.o \
	dfsMazeSolver.o depthBuilder.o disjointSets.o kruskalBuilder.o \
	maze.o mazeFactory.o mazeSolver.o options.o stringUtils.o
	
astarMazeSolver.o: astarMazeSolver.cpp astarMazeSolver.h
	${CC} ${FLAGS} -c astarMazeSolver.cpp
	
bfsMazeSolver.o: bfsMazeSolver.cpp bfsMazeSolver.h
	${CC} ${FLAGS} -c bfsMazeSolver.cpp

dfsMazeSolver.o: dfsMazeSolver.cpp dfsMazeSolver.h
	${CC} ${FLAGS} -c dfsMazeSolver.cpp

depthBuilder.o: depthBuilder.cpp depthBuilder.h
	${CC} ${FLAGS} -c depthBuilder.cpp
	
disjointSets.o: disjointSets.cpp disjointSets.h
	${CC} ${FLAGS} -c disjointSets.cpp
	
kruskalBuilder.o: kruskalBuilder.cpp kruskalBuilder.h
	${CC} ${FLAGS} -c kruskalBuilder.cpp
	
maze.o: maze.cpp maze.h
	${CC} ${FLAGS} -c maze.cpp
	
mazeFactory.o: mazeFactory.cpp mazeFactory.h
	${CC} ${FLAGS} -c mazeFactory.cpp
	
mazeSolver.o: mazeSolver.cpp mazeSolver.h
	${CC} ${FLAGS} -c mazeSolver.cpp
	
options.o: options.cpp options.h
	${CC} ${FLAGS} -c options.cpp
	
stringUtils.o: stringUtils.cpp stringUtils.h
	${CC} ${FLAGS} -c stringUtils.cpp

clean:
	rm -f *.o oop_ass2