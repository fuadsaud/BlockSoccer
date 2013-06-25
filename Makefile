all: run
run: link
	./BlockSoccer
link: compile
	g++ -framework OpenGL -framework GLUT *.o -o BlockSoccer
compile:
	g++ -Wall -c *.cpp
clean:
	rm BlockSoccer