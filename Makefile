OBJECTS=openCommBase.o main.o

LIBS=OpenCL

main : $(OBJECTS)
	g++ -o main $(OBJECTS) -l$(LIBS)
.PHONEY : clean
clean:
	-rm main $(OBJECTS)
