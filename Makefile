CC = g++

code:
	${CC} -lncurses rc_control.cpp -o rc

clean:
	rm ./rc

