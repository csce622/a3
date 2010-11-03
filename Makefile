all:
	make p1
#	make p2
	make p3

p1: p1.cpp

	g++ p1.cpp \
		-o p1 \
		-I ~/boost/

p2: p2.cpp 

	g++ p2.cpp \
		-o p2 \
		-I ~/boost/ \
		~/boost/stage/lib/libboost_graph.a

p3: p3.cpp

	g++ p3.cpp \
		-o p3 \
		-I ~/boost/
clean:
	rm p1
#	rm p2
	rm p3
