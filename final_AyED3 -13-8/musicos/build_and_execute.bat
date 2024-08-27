:: Compilo c+odigo objeto
g++ -Wall -std=c++11 -I.\include\ -c .\src\FichadeAtencion.cpp
g++ -Wall -std=c++11 -I.\include\ -c .\src\centrodeSalud.cpp
g++ -Wall -std=c++11 -I.\include\ -c .\src\mockMySQL.cpp
g++ -Wall -std=c++11 -I.\include\ -c .\src\mockPostgreSQL.cpp
g++ -Wall -std=c++11 -I.\include\ -c .\src\paciente.cpp
g++ -Wall -std=c++11 -I.\include\ -c  .\main.cpp


:: Compilo el Binario
g++ -Wall -std=c++11 FichaDeAtencion.o centrodeSalud.o mockMySQL.o mockPostgreSQL.o  paciente.o  main.o -o main.exe

:: Limpio los códigos objeto
DEL .\*.o

:: Ejecuto el binario:
main.exe