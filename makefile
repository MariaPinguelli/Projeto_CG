make: main.c pipe.c
    gcc pipe.c main.c -o main -lglut -lGLU -lGL