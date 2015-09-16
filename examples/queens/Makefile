CXX	= g++
# Define EXE as .exe for MS-DOS and derivatives.
PURE	=
EXE	=
#EXE	= .exe

MFLAG	=
ICFLAGS = -g
XCFLAGS =
CXXFLAGS =
DDDEBUG =

PERF_CFLAGS = -O3 -Wall

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS= $(ICFLAGS) $(MFLAG) $(XCFLAGS) $(CXXFLAGS)
else
	CFLAGS= $(PERF_CFLAGS)
endif

WHERE	= ../..

INCLUDE = $(WHERE)/include

LIBS	= $(WHERE)/obj/libobj.a $(WHERE)/cudd/libcudd.a $(WHERE)/mtr/libmtr.a \
	$(WHERE)/st/libst.a $(WHERE)/util/libutil.a $(WHERE)/epd/libepd.a

TARGET	= queens$(EXE)

SRC	= queens$(P).cc
OBJ	= $(SRC:.cc=.o)

#------------------------------------------------------

$(TARGET): $(SRC) $(HDR) $(LIBS) $(OBJ)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LIBS) -I$(INCLUDE) -lm

$(OBJ): $(SRC)
	$(CXX) -c $(SRC) -I$(INCLUDE) $(CFLAGS) $(DDDEBUG)

all: $(TARGET)

clean:
	rm -f *.o *.u mon.out gmon.out *.pixie *.Addrs *.Counts mnem.* \
	.pure core *.warnings

distclean: clean
	rm -f $(TARGET)
