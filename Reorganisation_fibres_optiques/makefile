all : Chaine.o ManipReseau.o ReseauLC.o ReseauHach.o ReseauAQ.o SVGwriter.o ChaineMain.o ReseauMain.o ReconstitueReseau.o MainComp.o
	gcc -ggdb Chaine.o SVGwriter.o ChaineMain.o -o ChaineMain -lm
	gcc -ggdb Chaine.o ManipReseau.o ReseauLC.o ReseauHach.o SVGwriter.o ReseauMain.o -o ReseauMain -lm
	gcc -ggdb Chaine.o ManipReseau.o ReseauLC.o ReseauHach.o ReseauAQ.o SVGwriter.o ReconstitueReseau.o -o ReconstitueReseau -lm
	gcc -ggdb Chaine.o ManipReseau.o ReseauLC.o ReseauHach.o ReseauAQ.o SVGwriter.o MainComp.o -o MainComp -lm

Chaine.o : Chaine.c Chaine.h SVGwriter.h
	gcc -ggdb -c Chaine.c -o  Chaine.o

SVGwriter.o : SVGwriter.c SVGwriter.h
	gcc -ggdb -c SVGwriter.c -o SVGwriter.o 

ManipReseau.o : ManipReseau.c Chaine.h Reseau.h SVGwriter.h
	gcc -ggdb -c ManipReseau.c -o ManipReseau.o 

ReseauLC.O :  ReseauLC.c Chaine.h Reseau.h 
	gcc -ggdb -c ReseauLC.c -o ReseauLC.o

ReseauHach.o : ReseauHach.c Chaine.h Reseau.h Hachage.h
	gcc -ggdb -c ReseauHach.c -o ReseauHach.o

ReseauAQ.o : ReseauAQ.c Chaine.h Reseau.h ArbreQuat.h
	gcc -ggdb -c ReseauAQ.c -o ReseauAQ.o

ChaineMain.o : ChaineMain.c Chaine.h Reseau.h SVGwriter.h
	gcc -ggdb -c ChaineMain.c -o ChaineMain.o

ReseauMain.o : ReseauMain.c Chaine.h Reseau.h SVGwriter.h
	gcc -ggdb -c ReseauMain.c -o ReseauMain.o

ReconstitueReseau.o : ReconstitueReseau.c Chaine.h Reseau.h Hachage.h
	gcc -ggdb -c ReconstitueReseau.c -o ReconstitueReseau.o

MainComp.o : MainComp.c Chaine.h Reseau.h Hachage.h ArbreQuat.h SVGwriter.h 
	gcc -ggdb -c MainComp.c -o MainComp.o



clean :
	rm -rf *.o
	rm -rf *.html
	rm -rf ChaineMain
	rm -rf ReseauMain
	rm -rf ReconstitueReseau
	