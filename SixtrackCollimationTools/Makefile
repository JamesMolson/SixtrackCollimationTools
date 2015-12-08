CPP=g++

CCFLAGS= -Wall -Wextra -pedantic

SRC = Aperture.o OneMetre.o ReadTwiss.o AssignOneMetre.o Survey.o OneMetreAlign.o 

default: BeamLossPattern GetAperture CleanInelastic CountAbs

BeamLossPattern: BeamLossPattern.o ${SRC}
	${CPP} ${CCFLAGS} -o BeamLossPattern BeamLossPattern.o ${SRC}

GetAperture: GetAperture.o ${SRC}
	${CPP} ${CCFLAGS} -o GetAperture GetAperture.o ${SRC}

CleanInelastic:
	${CPP} ${CCFLAGS} CleanInelastic.cpp -o CleanInelastic

CountAbs: 
	${CPP} ${CCFLAGS} CountNabs.cpp -o CountAbs

clean:
	rm -f *.o BeamLossPattern GetAperture CleanInelastic CountAbs

%.o: %.cpp
	${CPP} ${CCFLAGS} -c $< -o $@
