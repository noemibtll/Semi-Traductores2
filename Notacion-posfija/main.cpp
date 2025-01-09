#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

int main()
{
    stack<string> pila; // Declaramos la pila de cadenas de caracteres
    string expresion;
    float operando1;
    float operando2;

    // Leemos expresion posfija
    cin >> expresion;

    /// Algoritmo de evaluacion de expresiones posfijas
    // 1. Leemos toda la expresion digitada, hasta el final
    for (int i = 0; i < expresion.length(); i++)
    {
        // 2. El caracter leido es un operando, simplemente insertarlo en la pila
        if (isdigit(expresion[i]))
        {
            pila.push(string(1, expresion[i]));
        }

        // 3. El caracter leido es un operador aritmetico, tomar dos operandos de la pila
        //    y realizar la operacion indicada por el operando
        if (expresion[i] == '+' || expresion[i] == '-' ||
                expresion[i] == '*' || expresion[i] == '/')
        {
            operando1 = stof(pila.top());// Tomamos tope de pila
            pila.pop(); // Eliminamos tope de pila

            operando2 = stof(pila.top());
            pila.pop();

            // Realizamos la operacion en el orden operando2, operando1, como indica el algoritmo
            // e insertamos el resultado en la pila
            switch (expresion[i])
            {
            case '+':
                pila.push(to_string(operando2 + operando1));
                break;

            case '-':
                pila.push(to_string(operando2 - operando1));
                break;

            case '*':
                pila.push(to_string(operando2 * operando1));
                break;

            case '/':
                pila.push(to_string(operando2 / operando1));
                break;

            default:
                cout << "Error de sintaxis.";
                break;
            }

        }

        // 4. El caracter leido es un operador trigonometrico, sacar un dato de la pila
        //    y realizar la operacion con el.
        if (expresion[i] == 'S' || expresion[i] == 'C' || expresion[i] == 'T')
        {
            operando1 = stof(pila.top()); // Obtenemos el tope de pila
            pila.pop(); // Eliminamos el tope de pila

            // Verificamos el tipo de funcion trigonometrica y realizamos la operacion
            if (expresion[i] == 'S')
            {
                pila.push(to_string(sin(operando1))); // Aplicamos la funcion seno e insertamos en la pila
            }

            else if (expresion[i] == 'C')
            {
                pila.push(to_string(cos(operando1))); // Aplicamos la funcion coseno e insertamos en la pila
            }

            else
            {
                pila.push(to_string(tan(operando1))); // Aplicamos la funcion tangente e insertamos en la pila
            }
        }


    }

    cout << pila.top();

}
