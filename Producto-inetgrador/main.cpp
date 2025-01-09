#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

/// Definimos palabras reservadas del lenguaje, tipos de datos, caracteres, etc.
vector<string> dataType = {"float","int","signed","unsigned"};

vector<string> keywords = {"auto","break","case","char","const","continue","default",
                           "do","double","else","enum","extern","for","goto",
                           "if","signed","sizeof","static","struct","switch","typedef","union",
                           "void","volatile","while"
                          };

vector<string> operators = {"+","-","*","/",">","<",">=","<=","||","&&", "!=", "="};
vector<string> numbers = {"0","1","2","3","4","5","6","7","8","9"};
vector<string> parenthesis = {"(",")","()"};
vector<string> brackets = {"[","]"};
vector<string> brace = {"{","}"};
vector<string> specialChar = {";", ",", ".", "%", "#", "!"};

string line; /// Linea a leer, para analisis sintactico

/// Prototipo de funciones
void others(string, size_t);

/// Analizador lexico
void lexer(string myString)
{
    myString.erase(std::remove(myString.begin(), myString.end(), '\n'), myString.end()); /// Eliminamos posibles saltos de linea
    char chars[] = {'=', '+', '-', '*', '/', '(', ')', ';', ','};
    size_t position = myString.find_first_of(chars);

    if(find(keywords.begin(), keywords.end(), myString) != keywords.end())
        cout<<myString<<" \t Palabra reservada\n";

    if(find(dataType.begin(), dataType.end(), myString) != dataType.end())
        cout<<myString<<" \t Tipo de dato\n";

    else if((isalpha(myString[0]) || myString[0] == '_') && position == string::npos)  /// Verificamos si es una variable
    {
        for (int i = 0; i < myString.length(); i++)
        {
            if (!isalnum(myString[i]) && myString[i] != '_')
            {
                return;
            }
        }
        cout<<myString<<" \t Identificador\n";
    }

    else if(find(operators.begin(), operators.end(), myString) != operators.end())
        cout<<myString<<" \t Operador\n";
    else if(find(numbers.begin(), numbers.end(), myString) != numbers.end() || (myString.find('.') != string::npos && isdigit(myString[0])))
        cout<<myString<<" \t Constante\n";
    else if(find(parenthesis.begin(), parenthesis.end(), myString) != parenthesis.end())
        cout<<myString<<" \t Parentesis\n";
    else if(find(brackets.begin(), brackets.end(), myString) != brackets.end())
        cout<<myString<<" \t Corchete\n";
    else if(find(brace.begin(), brace.end(), myString) != brace.end())
        cout<<myString<<" \t Llave\n";
    else if(find(specialChar.begin(), specialChar.end(), myString) != specialChar.end())
        cout<<myString<<" \t Caracter especial\n";

    else   /// Existen cadenas no espaciadas correctamente, tratarlas (ej.: int=a+b)
    {
        /// Buscamos algun caracter que divida a ambas partes de la cadena
        /// =, +, -, *, /, (, ;, ,
        if (position != string::npos)
        {
            others(myString, position);
            return;
        }
    }

}

void others(string myString, size_t position)
{
    if (position == 1)   /// Si solo hay un caracter antes del signo o caracter (parte izq)
    {
        string newString = string(1, myString[0]);
        lexer(newString);
    }
    else /// Si hay mas de un caracter antes del signo o caracter (parte izq)
        lexer(myString.substr(0, position));

    string newString2 = string(1, myString[position]); /// Tomamos en cuenta el signo o caracter (mid)
    lexer(newString2);

    if (myString.length() > position + 1)
        lexer(myString.substr(position + 1)); /// Tomamos en cuenta el lado derecho del signo o caracter (der)
}

/// Analizador sintactico

// Función que verifica si una cadena contiene otra subcadena
bool contains(const std::string &str, const std::string &sub) {
    // Busca la subcadena en la cadena
    return str.find(sub) != std::string::npos;
}

int simboloAEntero(string palabra)
{
    /*  E M A S P i m a n + ; = } $ */
    // int main(){ c=a+b; }
    if (palabra == "E")
    {
        return 0;
    }
    else if (palabra == "M")
    {
        return 1;
    }
    else if (palabra == "A")
    {
        return 2;
    }
    else if (palabra == "S")
    {
        return 3;
    }
    else if (palabra == "P")
    {
        return 4;
    }
    else if (palabra == "int")
    {
        return 5;
    }
    else if (palabra == "main(){")
    {
        return 6;
    }
    else if (palabra == "c")
    {
        return 7;
    }
    else if (palabra == "a" || palabra == "b")
    {
        return 8;
    }
    else if (palabra == "=")
    {
        return 11;
    }
    else if (palabra == "+")
    {
        return 9;
    }
    else if (palabra == ";")
    {
        return 10;
    }
    else if (palabra == "}")
    {
        return 12;
    }
    else if (palabra == "$")
    {
        return 13;
    }
}

/// Funcion principal
int main()
{
    /// Gramatica que define la sintaxis de los programas de entrada
    // E' -> E
    // E -> int M
    // M -> main(){ A
    // A -> a=S
    // S -> n+n;P
    // P -> }

    /// Programa de entrada
    // int main(){ c=a+b; }

    /// Formato del programa de entrada:
    // 1. Se da en una sola linea.
    // 2. Los lexemas vienen separados por espacios, a excepcion de asignaciones, sumas y restas y puntos y comas.
    // Otras consideraciones:
    // 1. Por simplicidad, el automata toma PALABRAS COMPLETAS entre transiciones y no simbolos individuales.

    /// Definimos la pila de estados
    stack<int> pila;
    // Definimos estado inicial de la pila
    pila.push(0);

    /// Definimos tabla LR(0)
    int estados = 15; // Representa los estados
    int simbolos = 14; // Representa los terminales y no terminales para efectuar los shifts/reduces
    int simboloActual; // Simbolo de lectura actual

    int tablaLR[estados][simbolos] =
{
    //   E M A S P i m a n + ; = } $
    /* 1 */ { 1,0,0,0,0,2,4,6,9,0,0,0,14,0 },
    /* 2 */ { 0,0,0,0,0,0,0,0,0,0,0,0,0,500 },
    /* 3 */ { 0,3,0,0,0,0,4,0,0,0,0,0,0,0 },
    /* 4 */ { 0,0,0,0,0,-2,-2,-2,-2,-2,-2,-2,-2,-2 },
    /* 5 */ { 0,0,5,0,0,0,0,6,0,0,0,0,0,0 },
    /* 6 */ { 0,0,0,0,0,-3,-3,-3,-3,-3,-3,-3,-3,-3 },
    /* 7 */ { 0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
    /* 8 */ { 0,0,0,8,0,0,0,0,9,0,0,0,0,0 },
    /* 9 */ { 0,0,0,0,0,-4,-4,-4,-4,-4,-4,-4,-4,-4 },
    /* 10*/ { 0,0,0,0,0,0,0,0,0,10,0,0,0,0 },
    /* 11*/ { 0,0,0,0,0,0,0,0,11,0,0,0,0,0 },
    /* 12*/ { 0,0,0,0,0,0,0,0,0,0,12,0,0,0 },
    /* 13*/ { 0,0,0,0,13,0,0,0,0,0,0,0,14,0 },
    /* 14*/ { 0,0,0,0,0,-5,-5,-5,-5,-5,-5,-5,-5,-5 },
    /* 15*/ { 0,0,0,0,0,-6,-6,-6,-6,-6,-6,-6,-6,-6 }
};

    /// Leemos programa de entrada
    vector<string> palabras;
    string programa, palabra;
    getline(cin, programa);

    // Dividimos la cadena en palabras
    stringstream ss(programa); // Utilizamos stringstream para dividir la cadena en palabras

    while (ss >> palabra) { // Leemos palabra por palabra de la cadena
        palabras.push_back(palabra); // Almacenamos cada palabra en el vector
    }
    palabras.push_back("$"); // Almacenamos simbolo de fin

    // Imprimimos las palabras almacenadas en el vector
    //for (const string& palabra : palabras) {
    //    cout << palabra << endl;
    //}
    // Definimos el simbolo inicial de la entrada

    /// Validamos la cadena de entrada
    int i = 0;
    signed int accion;
    while (true)
    {
        // A partir del simbolo leido, vemos que valor tiene en base a la tabla LR
        simboloActual = simboloAEntero(palabras[i]); // Traducimos el simbolo actual a su posicion en la tabla LR.
        accion = tablaLR[pila.top()][simboloActual]; // Validamos la accion a realizar a partir del estado actual y el
                                                     // simbolo actual.

        if (accion == 0)
        {
            // int main(){ c = a + b ; }
            cout << "Error de sintaxis. El programa no es correcto."; break;
        }
        else if (accion == 500)
        {
            cout << "Cadena aceptada.\n"; break;
        }
        else if (accion >= 0) // Hacemos un shift
        {
            pila.push(accion); // Metemos el nuevo estado a la pila.
            i++; // Removemos el simbolo de entrada SOLO al hacer un shift.
        }
        else if (accion <= 0) // Hacemos una reduccion
        {
            // Verificamos cuantos simbolos tneemos que remover de la pila

            if (accion == -2) // E -> int M
            {
                // Eliminamos dos simbolos de la pila
                pila.pop(); pila.pop();
                // Evaluamos el nuevo tope de pila en el simbolo indicado en el lado izquierdo de la produccion (E)
                // que, convertido a entero es el valor 0, e insertamos el resultado en la pila
                pila.push(tablaLR[pila.top()][0]);

            }
            else if (accion == -3) // M -> main(){ A
            {
                pila.pop();pila.pop();
                pila.push(tablaLR[pila.top()][1]);
            }
            else if (accion == -4) // A -> a=S
            {
                pila.pop(); pila.pop(); pila.pop();
                pila.push(tablaLR[pila.top()][2]);
            }
            else if (accion == -5) // S -> n+n;P
            {
                pila.pop();pila.pop();pila.pop();pila.pop();pila.pop();
                pila.push(tablaLR[pila.top()][3]);
            }
            else if (accion == -6) // P -> }
            {
                pila.pop();
                pila.push(tablaLR[pila.top()][4]);
            }

        }
    }

    system("pause");
    return 0;
}


