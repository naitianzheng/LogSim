OPENGL_LIBS = -lglut -lGL -lGLU

#CXX = $(shell /homes/ahg13/wxWidgets-3.0.3/gtk-build/wx-config --version=3.0 --cxx)
CXX = g++ --std=c++11

SRC = logsim.cc names.cc scanner.cc network.cc parser.cc monitor.cc devices.cc userint.cc gui.cc guitest.cc

L_OBJECTS = logsim.o names.o scanner.o network.o parser.o monitor.o devices.o userint.o gui.o

G_OBJECTS = guitest.o names.o network.o monitor.o devices.o gui.o

# implementation

.SUFFIXES:	.o .cc

.cc.o :
	$(CXX) -c `/homes/ahg13/wxWidgets-3.0.3/gtk-build/wx-config --version=3.0 --cxxflags` -g -o $@ $<

all:    logsim guitest

logsim:	$(L_OBJECTS)
	$(CXX) -o logsim $(L_OBJECTS) `/homes/ahg13/wxWidgets-3.0.3/gtk-build/wx-config --version=3.0 --libs --gl_libs` $(OPENGL_LIBS)

guitest: $(G_OBJECTS)
	 $(CXX) -o guitest $(G_OBJECTS) `/homes/ahg13/wxWidgets-3.0.3/gtk-build/wx-config --version=3.0 --libs --gl_libs` $(OPENGL_LIBS)

clean: 
	rm -f *.o logsim guitest

depend:
	makedepend $(SRC)

# DO NOT DELETE

logsim.o: logsim.h names.h devices.h network.h monitor.h parser.h userint.h
logsim.o: gui.h 
names.o: names.h
network.o: network.h names.h
parser.o: parser.h names.h network.h devices.h monitor.h
monitor.o: monitor.h names.h network.h devices.h
devices.o: devices.h names.h network.h
userint.o: userint.h names.h network.h devices.h monitor.h
gui.o: gui.h names.h devices.h network.h monitor.h parser.h scanner.h
guitest.o: guitest.h names.h devices.h network.h monitor.h gui.h
