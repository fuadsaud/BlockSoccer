run: compile
	./BlockSoccer
compile:
	g++ -Wall -framework OpenGL -framework GLUT -o BlockSoccer *.cpp
clean:
	rm BlockSoccer