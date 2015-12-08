
CPP=g++

#CCFLAGS= -Wall -static 

SRC = Aperture.o OneMetre.o ReadTwiss.o AssignOneMetre.o Survey.o OneMetreAlign.o 

default: BeamLossPattern

BeamLossPattern: BeamLossPattern.o ${SRC}
	${CPP} ${CCFLAGS} -o BeamLossPattern BeamLossPattern.o ${SRC}

GetAperture: GetAperture.o ${SRC}
	${CPP} ${CCFLAGS} -o GetAperture GetAperture.o ${SRC}

clean:
	rm -f *.o BeamLossPattern GetAperture

%.o: %.cpp
	${CPP} ${CCFLAGS} -c $< -o $@
