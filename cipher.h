#ifndef CIPHER_H
#define CIPHER_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#define AUTO_PASS_L 20
#define END_CHAR 78
#define BEG_CHAR 48
using namespace std;

void cipher(const char* orgFile, const char* dstFile, string pass);
void decipher(const char *orgFile, const char *dstFile, string pass);

void cipher(const char *orgFile, const char *dstFile, string pass)
{
    fstream org(orgFile, ios::in);
    fstream dst;
    string autoPass = "";
    char aux;
    char len;

    if (!org.is_open())
        throw range_error("El archivo origen no existe");
    // Si el usuario utilizó la bandera --auto entonces se le generará
    // una contraseña de 20 dígitos automáticamente y se escribirá
    // cifrada en el archivo de destino
    dst.open(dstFile, ios::out);
    if (pass == "--auto"){
        srand(time(NULL));
        for (int i = 0; i < AUTO_PASS_L; ++i){
            aux = char((rand() % END_CHAR) + BEG_CHAR);
            if ((aux > 57 && aux < 65) || (aux > 90 && aux < 97))
                aux = '_';
            autoPass += aux;
        }
        pass = autoPass;
        cout << "Su contraseña es: " << pass << endl;
    }
    len = pass.size() - 3;
    // Se escribe el largo de la contraseña de forma cifrada
    dst.write((char*)&len, sizeof(char));
    // Se escribe dicha contraseña
    // cifrada en el archivo destino
    for (long i = 0; i < pass.size(); ++i)
        dst << char(pass[i] - 3);
    while (!org.eof()){
        org.get(aux);
        if (org.eof())
            break;
        aux -= 3;
        dst << aux;
    }
    cout << "El archivo se ha cifrado de forma correcta" << endl;
    org.close();
    dst.close();
}

void decipher(const char *orgFile, const char *dstFile, string pass)
{
    fstream org(orgFile, ios::in);
    fstream dst(dstFile, ios::out);
    char aux;
    string tmp = "";
    char len;

    if (!org.is_open())
        throw range_error("El archivo origen no existe");
    org.read((char *)&len, sizeof(char));
    len += 3;
    for (long i = 0; i < len; ++i){
        org.get(aux);
        tmp += char(aux + 3);
    }
    cout << "tmp: " << tmp << endl
         << "pass: " << pass << endl;
    if (tmp != pass)
        throw range_error("Contraseña incorrecta");
    while (!org.eof()){
        org.get(aux);
        if (org.eof())
            break;
        aux += 3;
        dst << aux;
    }
    cout << "El archivo se ha descifrado de forma correcta" << endl;
    org.close();
    dst.close();
}

#endif // CIPHER_H