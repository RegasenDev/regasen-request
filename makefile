
.PHONY: build clean

ifndef GXX
	GXX = g++
endif

COMPILE_FLAGS = -c -fPIC -m32 -O3 -w -Wall -I./SDK/amx/ -DLINUX
LIBRARIES = -lcurl

OUTFILE = regasen-request.so

build:
	mkdir -p bin
	$(GXX) $(COMPILE_FLAGS) ./SDK/*.cpp
	$(GXX) $(COMPILE_FLAGS) *.cpp
	$(GXX) -m32 -shared -o $(OUTFILE) *.o $(LIBRARIES) 
	
clean:
	rm -f *.o