XFLAGS= -std=c++11 -pedantic -Wall -Wextra -O -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo

CXXFLAGS+= $(shell pkg-config --cflags gtkmm-3.0)
LDFLAGS+= $(shell pkg-config --libs gtkmm-3.0)

all: main

clockMain: clockMain.cc clock.o
	g++ $^ $(LDFLAGS) -o $@

clock.o: clock.cc clock.h

main: main.o exam_timer.o timer.o
	g++ $^ $(LDFLAGS) -o $@

start_button.o:  start_button.h start_button.cc

pause_button.o:  pause_button.h pause_button.cc

resume_button.o:  resume_button.h resume_button.cc

spin_button.o: spin_button.h spin_button.cc

stop_button.o:  stop_button.h stop_button.cc

timer.o: timer.h timer.cc

exam_timer.o: exam_timer.h exam_timer.cc

main.o: main.cc exam_timer.o

clean:
	rm -rf *.o main	
tar:
	tar cvzf cs120-assignment-8-jmarron7-hpaisle1-mhauser5.tar.gz main.cc timer.cc timer.h exam_timer.cc exam_timer.h Makefile README
