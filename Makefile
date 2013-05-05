XFLAGS= -std=c++11 -pedantic -Wall -Wextra -O -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo

CXXFLAGS+= $(shell pkg-config --cflags gtkmm-3.0)
LDFLAGS+= $(shell pkg-config --libs gtkmm-3.0)

all: main

clockMain: clockMain.cc clock.o
	g++ $^ $(LDFLAGS) -o $@

clock.o: clock.cc clock.h

main: main.o exam_timer.o timer.o
	g++ $^ $(LDFLAGS) -o $@

timer.o: timer.h timer.cc

exam_timer.o: exam_timer.h exam_timer.cc

main.o: main.cc exam_timer.o

clean:
	rm -rf *.o main	
tar:
	tar cvzf cs120-assignment-9-jmarron7-hpaisle1-mhauser5.tar.gz main.cc timer.cc timer.h exam_timer.cc exam_timer.h Makefile README clock.png
