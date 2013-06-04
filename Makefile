run: compile
	./soccer
compile:
	g++ -Wall -framework OpenGL -framework GLUT -o soccer *.cpp