all:
	make p1
	make p2
	make p3

p1: p1.cpp \
	path_count.hpp

	g++ p1.cpp \
		-o p1 \
		-I ~/boost/

p2: p2.cpp \
	path_count.hpp

	g++ -I ~/boost/ -c p2.cpp
	g++ p2.o -o p2 -L/Users/dalg24/boost/stage/lib/ -lboost_graph -lboost_regex

p3: p3.cpp \
	path_count.hpp

	g++ p3.cpp \
		-o p3 \
		-I ~/boost/

graph: randomgraph.dot

	dot randomgraph.dot -Tps -o randomgraph.ps

clean:
	rm p1
	rm p2
	rm p3
