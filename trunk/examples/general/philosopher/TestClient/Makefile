QEDO = /home/boehme
CIDL_GEN = ${QEDO}/bin/cidl_gen
ORB_IDL_INCLUDE = -I../IDL -I/home/boehme/include -I/home/boehme/include/mico 
CIDL_ORB_DEF = -DMICO_ORB -DMICO_CIDL_GEN

CIDL_FILES = ../IDL/philosophers.cidl
IDL_FILES = dinner_EQUIVALENT.idl

CPP_FILES = dinner_EQUIVALENT.cpp \
            main.cpp \
				ClientValuetypes.cpp
OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

IDL_FLAGS += -I${QEDO}/idl --relative-paths
CXXFLAGS += -I. -I${QEDO}/include ${NAMING_INCLUDES}

LDLIBS += -L${QEDO}/lib -lComponentIDL ${NAMING_LIBS} ${MICO_LIBS}
include ../MakeVars

all: ${OBJ_FILES} main 

main: ${OBJ_FILES}

${IDL_FILES} : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--target dinner $<
