#
#
ORB_IDL_INCLUDE = -I..

IDL_FILES = MDE.idl \
        MDE_0.idl \
	MDE_1.idl \
	PrimitiveTypes.idl \
	Reflective.idl \
	CorbaIdlTypes.idl \
	RepositoryRoot.idl

CPP_FILES = MDE.cpp \
	MDE_0.cpp \
	MDE_1.cpp \
	Reflective.cpp \
	CorbaIdlTypes.cpp \
	PrimitiveTypes.cpp \
	RepositoryRoot.cpp

H_FILES = MDE.h \
	MDE_0.h \
	MDE_1.h \
	Reflective.h \
	CorbaIdlTypes.h \
	PrimitiveTypes.h \
	RepositoryRoot.h

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${CPP_FILES} ${H_FILES} ${OBJ_FILES} libDCI_ClientIDL.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libDCI_ClientIDL.a

libDCI_ClientIDL.a: ${OBJ_FILES}

MDE.cpp: MDE.idl
	$(MICO)/bin/idl ${IDL_FLAGS} -I. -I$(MICO)/include -I$(MICO)/include/coss -I$(MICO)/include/mico --codegen-c++ --gen-included-defs -DMICO_ORB --c++-suffix cpp $<

MDE_0.cpp: MDE_0.idl
	$(MICO)/bin/idl ${IDL_FLAGS} -I. -I$(MICO)/include -I$(MICO)/include/coss -I$(MICO)/include/mico --codegen-c++ --gen-included-defs -DMICO_ORB --c++-suffix cpp $<

MDE_1.cpp: MDE_1.idl
	$(MICO)/bin/idl ${IDL_FLAGS} -I. -I$(MICO)/include -I$(MICO)/include/coss -I$(MICO)/include/mico --codegen-c++ --gen-included-defs -DMICO_ORB --c++-suffix cpp $<

Reflective.cpp: Reflective.idl
	$(MICO)/bin/idl ${IDL_FLAGS} -I. -I$(MICO)/include -I$(MICO)/include/coss -I$(MICO)/include/mico --codegen-c++ --gen-included-defs -DMICO_ORB --c++-suffix cpp $<

RepositoryRoot.cpp: RepositoryRoot.idl
	$(MICO)/bin/idl ${IDL_FLAGS} -I. -I$(MICO)/include -I$(MICO)/include/coss -I$(MICO)/include/mico --codegen-c++ --gen-included-defs -DMICO_ORB --c++-suffix cpp $<

CorbaIdlTypes.cpp: CorbaIdlTypes.idl
	$(MICO)/bin/idl ${IDL_FLAGS} -I. -I$(MICO)/include -I$(MICO)/include/coss -I$(MICO)/include/mico --codegen-c++ --gen-included-defs -DMICO_ORB --c++-suffix cpp $<

PrimitiveTypes.cpp: PrimitiveTypes.idl
	$(MICO)/bin/idl ${IDL_FLAGS} -I. -I$(MICO)/include -I$(MICO)/include/coss -I$(MICO)/include/mico --codegen-c++ --gen-included-defs -DMICO_ORB --c++-suffix cpp $<
