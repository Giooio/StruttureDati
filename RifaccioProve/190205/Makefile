OBJ = compito.o tipo.o liste.o
CXXFLAGS = -g

Carte-list: $(OBJ)
	g++ -o Carte-list $(OBJ)

-include dependencies

.PHONY: clean cleanall
depend: 
	g++ -MM *.cc > dependencies
clean:
	rm -rf *.o
cleanall:
	rm -rf Carte-list *.o