#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct Nodo {
    char dato;
    Nodo* siguiente;
};

struct Pila {
    Nodo* tope;
    
    Pila() : tope(nullptr) {}
    
    void push(char d) {
        Nodo* nuevo = new Nodo;
        nuevo->dato = d;
        nuevo->siguiente = tope;
        tope = nuevo;
    }
    
    char pop() {
        if (tope == nullptr) return '\0';
        char dato = tope->dato;
        Nodo* temp = tope;
        tope = tope->siguiente;
        delete temp;
        return dato;
    }
    
    char top() {
        if (tope == nullptr) return '\0';
        return tope->dato;
    }
    
    bool empty() {
        return tope == nullptr;
    }
};


struct NodoInt {
    int dato;
    NodoInt* siguiente;
};

struct PilaInt {
    NodoInt* tope;
    
    PilaInt() : tope(nullptr) {}
    
    void push(int d) {
        NodoInt* nuevo = new NodoInt;
        nuevo->dato = d;
        nuevo->siguiente = tope;
        tope = nuevo;
    }
    
    int pop() {
        if (tope == nullptr) return 0;
        int dato = tope->dato;
        NodoInt* temp = tope;
        tope = tope->siguiente;
        delete temp;
        return dato;
    }
    
    int top() {
        if (tope == nullptr) return 0;
        return tope->dato;
    }
    
    bool empty() {
        return tope == nullptr;
    }
};


int prioridad(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}


bool es_operador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}


bool es_digito(char c) {
    return c >= '0' && c <= '9';
}


string infijo_a_postfijo(const string& expr) {
    Pila pila_ops;
    string salida;
    int parentesis_count = 0;

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (c == ' ' || c == '\t') continue;

        if (es_digito(c)) {
            while (i < expr.size() && es_digito(expr[i])) {
                salida += expr[i];
                i++;
            }
            salida += ' ';
            if (i > 0) i--;
        }
        else if (c == '(') {
            pila_ops.push(c);
            parentesis_count++;
        }
        else if (c == ')') {
            parentesis_count--;
            while (!pila_ops.empty() && pila_ops.top() != '(') {
                salida += pila_ops.pop();
                salida += ' ';
            }
            if (!pila_ops.empty() && pila_ops.top() == '(') pila_ops.pop();
        }
        else if (es_operador(c)) {
            while (!pila_ops.empty() && pila_ops.top() != '(' &&
                   ((prioridad(pila_ops.top()) > prioridad(c)) ||
                    (prioridad(pila_ops.top()) == prioridad(c) && c != '^' && pila_ops.top() != '^'))) {
                salida += pila_ops.pop();
                salida += ' ';
            }
            pila_ops.push(c);
        }
    }

    while (!pila_ops.empty()) {
        if (pila_ops.top() == '(' || pila_ops.top() == ')') {
            pila_ops.pop();
        } else {
            salida += pila_ops.pop();
            salida += ' ';
        }
    }

    if (!salida.empty() && salida.back() == ' ') {
        salida.pop_back();
    }

    return salida;
}


int eval_postfijo(const string& expr) {
    PilaInt pila_nums;
    string numero_actual;
    
    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];
        
        if (es_digito(c)) {
            numero_actual += c;
        }
        else if (c == ' ') {
            if (!numero_actual.empty()) {
                int num = 0;
                for (char dig : numero_actual) {
                    num = num * 10 + (dig - '0');
                }
                pila_nums.push(num);
                numero_actual = "";
            }
        }
        else if (es_operador(c)) {
            int b = pila_nums.pop();
            int a = pila_nums.pop();
            int resultado;
            
            if (c == '+') resultado = a + b;
            else if (c == '-') resultado = a - b;
            else if (c == '*') resultado = a * b;
            else if (c == '/') resultado = a / b;
            else if (c == '^') {
                resultado = 1;
                for (int j = 0; j < b; j++) resultado *= a;
            }
            
            pila_nums.push(resultado);
        }
    }
    
    return pila_nums.pop();
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " archivo_entrada.txt" << endl;
        return 1;
    }

    ifstream entrada(argv[1]);
    ofstream salida("exp_postfijas.txt");
    
    if (!entrada) {
        cout << "Error al abrir " << argv[1] << endl;
        return 1;
    }

    string linea;
    while (getline(entrada, linea, ';')) {
        string expr_limpia;
        for (char c : linea) {
            if (c != ' ' && c != '\t' && c != '\n') {
                expr_limpia += c;
            }
        }
        
        if (expr_limpia.empty()) continue;
        
        string postfija = infijo_a_postfijo(expr_limpia);
        int resultado = eval_postfijo(postfija);
        
        salida << "Expresión: " << postfija << "; Resultado: " << resultado << endl;
    }
    
    entrada.close();
    salida.close();
    cout << "Proceso completado. Ver exp_postfijas.txt" << endl;
    
    return 0;
}