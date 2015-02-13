#
# Makefile für GALAPAGOS
#
# By Andreas Hiemer, 21.04.2014
#
# !!!!! Replace all </path/to/...> !!!!!!!

# Compiler deinition
CC = mpicc

# Compiler parameters
CFLAGS = -g -O3 -Wall -std=c99 \
 -mtune=native -I</path/to/cpl/wcslib> -I./ -I</path/to/cpl/include>


# Libraries
LIB = -L</path/to/wcslib/lib> -L</path/to/cpl/lib> -lcplui -lcplcore -lcext -lwcs -lcpldrs
# voerbose Linker : -Wl,-verbose

# Header files
HEADERS = astrolib_utils.h galapagos_utils.h gala_sextractor.h \
          sextractor_utils.h  string_ops.h


# Depending files (include, Makefile etc.)
DEPS = Makefile $(HEADERS) 

# Parts
#
PARTS  =  astrolib_utils.o galapagos_utils.o gala_sextractor.o \
          sextractor_utils.o  string_ops.o GALAPAGOS.o

# Executable
EXE = ./GALAPAGOS

# MAKE
all: $(EXE)
#
# Command block
./GALAPAGOS: $(PARTS) $(DEPS) 
	$(CC) $(CFLAGS) $(LIB) $(PARTS) -o $@
# Clean
clean:
	rm *.o $(EXE)
