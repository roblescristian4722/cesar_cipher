#include <iostream>
#include <stdexcept>
#include <string>
#include "cipher.h"

#if defined(_WIN64) || defined(_WIN32)
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

using namespace std;
int main (int argc, char *argv[])
{
    CLEAR;
    if (argc <= 4)
        cout << "Modo de uso: cipher [cipher/decipher] [archivo origen] [archivo destino] [contraseña]"
             << endl << endl
             << "Nota: si quiere una contraseña generada aleatoriamente deje el campo de contraseña vacío"
             << endl
             << "y en su lugar coloque la bandera: --auto"
             << endl;
    else{
        string comando = argv[1];
        const char* origen = argv[2];
        const char* destino = argv[3];
        string pass = argv[4];
        if (comando == "cifrar")
            cipher(origen, destino, pass);
        else if (comando == "descifrar")
            decipher(origen, destino, pass);
        else{
            string error = "El comando \"";
            error += comando;
            error += "\" no es válido, utilice un comando válido [cifrar/descifrar]";       
            throw range_error(error);
        }
    }
}