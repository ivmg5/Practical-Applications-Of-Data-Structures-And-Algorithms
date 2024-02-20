//Integrantes:
//Gabriel Álvarez Arzate
//Diego Ivan Morales Gallardo
//Karen Corona Espinoza
//Fernanda Díaz Gutiérrez

// Importar bibliotecas necesarias
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Clase Registro para saber que contiene cada línea del archivo
struct Registro {
    string month; // variable para el mes
    int day;    // variable para el dia
    string time; // variable para la hora
    string ip; // variable para la ip
    string razon; // variable para la razon
}; 

// Métodos para comparar los registros y ver que mes, día y hora es mayor (de 2 en 2)
bool compararRegistros(const Registro& a, const Registro& b) {
    string months= "JanFebMarAprMayJunJulAugSepOctNovDec"; // variable para los meses
    int monthA = months.find(a.month) / 3; // encontrar en el string el primer mes
    int monthB = months.find(b.month) / 3; // encontrar en el string el segundo mes
    if (monthA != monthB) return monthA < monthB; // si son diferentes, regresar T o F para saber cual es mayor
    if (a.day != b.day) return a.day < b.day; // lo mismo con los días
    return a.time < b.time; // hora (implícito con lo anterior)
}

void bubbleSort(vector<Registro>& registros) { // método de ordenamiento burbuja
    int n = registros.size(); // variable del tamaño de los registros 
    for (int i = 0; i < n - 1; i++) { // ciclo que compara los registros para el bubble sort
        for (int j = 0; j < n - i - 1; j++) { // " "
            if (compararRegistros(registros[j + 1], registros[j])) { // si el registro siguiente es mayor al actual, se hace el swap
                swap(registros[j], registros[j + 1]);
            }
        }
    }
}

bool enRango(const Registro& registro, const string& inicio, const string& fin) { // método para ver si el registro está en el rango de fechas
    string meses = "JanFebMarAprMayJunJulAugSepOctNovDec";
    istringstream issInicio(inicio), issFin(fin); // variables para el inicio y fin de las fechas, siguiendo el string de meses
    string mesInicio, mesFin; // rango de los meses (inicio y fin)
    int dayI, dayF; // fechas de inicio y final (día, entero)
    issInicio >> mesInicio >> dayI; // cin del inicio de la fecha
    issFin >> mesFin >> dayF; // cin del fin de la fecha
    int monthA = meses.find(registro.month) / 3; // buscar el mes en el registro
    int monthIndex = meses.find(mesInicio) / 3; // buscar qué fecha del mes (inicio)
    int monthFIndex = meses.find(mesFin) / 3; // buscar qué fecha del mes (fin)
    
    if (monthA < monthIndex || monthA > monthFIndex) return false; // si el mes de registro es menor que el mes de inicio o mayor que el de fin, false (no está en el rango).
    if (monthA == monthIndex && registro.day < dayI) return false; // si el mes de registro es igual al mes de inicio pero el día va antes, falso (no está en el rango).
    if (monthA == monthFIndex && registro.day> dayF) return false; // si el mes de registro es igual al mes de fin pero el día va después, falso (no está en el rango).
    
    return true;
}

int main() {
    vector<Registro> registros; // vector de registros
    
    ifstream archivo("bitacora.txt"); // leer archivo de bitácora
    string linea; // variable para cada línea del archivo
    while (getline(archivo, linea)) { // ciclo para leer c/línea del archivo
        istringstream iss(linea);
        Registro registro;
        iss >> registro.month >> registro.day >> registro.time >> registro.ip; // entrada de datos
        string resto; // variable para el resto de la línea (que no es mes, día, hora o ip)
        getline(iss, resto); // leer el resto de la línea
        registro.razon = resto.substr(1);
        registros.push_back(registro); // meterlo al vector de registros
    }
    
    bubbleSort(registros); // ordenar los registros con Bubble Sort
    
    string dateStart, dateEnd; // variables para las fechas de inicio y fin
    cout << "Ingrese la fecha de inicio (Ejemplo: Aug 4): "; // pedir la fecha de inicio del rango a buscar
    getline(cin, dateStart); // recibir el dato que introduzca el usuario
    cout << "Ingrese la fecha de fin (Ejemplo: Oct 9): "; // pedir la fecha de fin 
    getline(cin, dateEnd); // recibir el dato que introduzca el usuario
    
    cout << "Registros entre " << dateStart << " y " << dateEnd << ":\n"; // imprimir "los registros entre las fechas dadas..."
    for (const auto& registro : registros) { // ciclo para imprimir los registros entre las fechas dadas
        if (enRango(registro, dateStart, dateEnd)) { // si los datos están en el rango, desplegarlos
            cout << registro.month << " " << registro.day << " " << registro.time << " " << registro.ip << " " << registro.razon << endl;
        }
    }
    
    ofstream salida("resultados.txt"); // archivo de salida
    for (const auto& registro : registros) { // ciclo para imprimir registros en el archivo de salida ("Resultados.txt"); estamos escribiendo el nuevo archivo
        salida << registro.month << " " << registro.day << " " << registro.time << " " << registro.ip << " " << registro.razon << endl;
    }
    
    return 0;
}