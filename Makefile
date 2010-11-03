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

	g++ p2.cpp \
		-o p2 \
		-I ~/boost/ \
#		~/boost/stage/lib/libboost_graph.a

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
