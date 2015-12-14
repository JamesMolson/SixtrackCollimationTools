CPP=g++

CCFLAGS= -Wall -Wextra -pedantic

SRC = Aperture.o OneMetre.o ReadTwiss.o AssignOneMetre.o Survey.o OneMetreAlign.o 

default: BeamLossPattern GetAperture CleanInelastic CountNAbs

BeamLossPattern: BeamLossPattern.o ${SRC}
	${CPP} ${CCFLAGS} -o BeamLossPattern BeamLossPattern.o ${SRC}

GetAperture: GetAperture.o ${SRC}
	${CPP} ${CCFLAGS} -o GetAperture GetAperture.o ${SRC}

CleanInelastic:
	${CPP} ${CCFLAGS} CleanInelastic.cpp -o CleanInelastic

CountNAbs:
	${CPP} ${CCFLAGS} CountNabs.cpp -o CountNAbs

clean:
	rm -f *.o BeamLossPattern GetAperture CleanInelastic CountNAbs

%.o: %.cpp
	${CPP} ${CCFLAGS} -c $< -o $@
