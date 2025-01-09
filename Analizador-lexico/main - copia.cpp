#include <string>
#include <iostream>
using namespace std;

vector<string> keywords ={"auto","break","case","char","const","continue","default",
                            "do","double","else","enum","extern","float","for","goto",
                            "if","int","signed",
                            "sizeof","static","struct","switch","typedef","union",
                            "unsigned","void","volatile","while"};

vector<string> operators ={"+","-","*","/",">","<",">=","<=","||","&&", "!=", "="};

vector<string> numbers ={"0","1","2","3","4","5","6","7","8","9"};

vector<string> parenthesis = {"(",")","()"};

vector<string> brackets = {"[","]"};

vector<string> brace = {"{","}"};

vector<string> specialChar = {";", ",", ".", "%", "#", "!"};
void callprintout(string, size_t);

void printout(string q){
  q.erase(std::remove(q.begin(), q.end(), '\n'), q.end()); /// Eliminamos posibles saltos de linea
  char chars[] = {'=', '+', '-', '*', '/', '(', ';', ','};
  size_t position = q.find_first_of(chars);

  if(find(keywords.begin(), keywords.end(), q) != keywords.end())
    cout<<q<<" \t Palabra clave\n";

  else if((isalpha(q[0]) || q[0] == '_') && position == string::npos){ /// Verificamos si es una variable
    for (int i = 0; i < q.length(); i++) {
        if (!isalnum(q[i]) && q[i] != '_') {
            return;
        }
    }
    cout<<q<<" \t Identificador\n";
  }

  else if(find(operators.begin(), operators.end(), q) != operators.end())
    cout<<q<<" \t Operador\n";
  else if(find(numbers.begin(), numbers.end(), q) != numbers.end())
    cout<<q<<" \t Constante\n";
  else if(find(parenthesis.begin(), parenthesis.end(), q) != parenthesis.end())
    cout<<q<<" \t Parentesis\n";
  else if(find(brackets.begin(), brackets.end(), q) != brackets.end())
    cout<<q<<" \t Corchete\n";
  else if(find(brace.begin(), brace.end(), q) != brace.end())
    cout<<q<<" \t Llave\n";
  else if(find(specialChar.begin(), specialChar.end(), q) != specialChar.end())
    cout<<q<<" \t Caracter especial\n";

  else { /// Existen cadenas no espaciadas correctamente, tratarlas (ej.: int=a+b)
    /// Buscamos algun caracter que divida a ambas partes de la cadena
    /// =, +, -, *, /, (, ;, ,
    if (position != string::npos) {
        callprintout(q, position);
        return;
    }
  }

}

void callprintout(string q, size_t position) {
    if (position == 1) { /// Si solo hay un caracter antes del signo o caracter (parte izq)
        string newString = string(1, q[0]);
        printout(newString);
    }
    else /// Si hay mas de un caracter antes del signo o caracter (parte izq)
        printout(q.substr(0, position));

    string newString2 = string(1, q[position]); /// Tomamos en cuenta el signo o caracter (mid)
    printout(newString2);

    if (q.length() > position + 1)
        printout(q.substr(position + 1)); /// Tomamos en cuenta el lado derecho del signo o caracter (der)
}

int main() {

  string line;
  vector<string> sample;

  while(getline(cin, line, ' ')){
      sample.push_back(line);
  }
  for(auto q : sample){
    //cout<<q<<" \t \n";
    printout(q);
  }

  return 0;
}

