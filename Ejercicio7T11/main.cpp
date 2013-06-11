//
//  main.cpp
//  Ejercicio7T11
//
//  Created by Daniel on 10/06/13.
//  Copyright (c) 2013 Daniel. All rights reserved.
//

#include <iostream>
#include "DCola.h"

using namespace std;

typedef int Lado;

Lado BABOR = 0;
Lado ESTRIBOR = 1;
const Lado LADOS[2] = { BABOR, ESTRIBOR };

bool esValida(double metrosFerry, double metrosBabor, double metrosEstribor) {
    
    return (metrosFerry >= metrosBabor && metrosFerry >= metrosEstribor);
}

bool esSolucion(const DCola<double> &coches, double metrosFerry, double metrosBabor, double metrosEstribor) {
    
    bool correcto = false;
    
    correcto = (metrosFerry >= metrosBabor && metrosFerry >= metrosEstribor);
    
    return correcto && ((coches.primero() > metrosFerry-metrosBabor) && (coches.primero() > metrosFerry-metrosEstribor));
}

void ejer7T11(DCola<double> &coches, double metrosFerry, Lado solucion[], Lado mejorSolucion[], int &numCoches, int numCochesMetidos, int k, double mB, double mE) {
    
    int cochesMetidos = 0;
    double metrosBabor, metrosEstribor = 0;
    double cocheM = 0;
    
    for ( int lado = 0; lado < 2; lado++) {
        
        metrosBabor = mB;
        metrosEstribor = mE;
        cochesMetidos = numCochesMetidos;
        
        solucion[k] = LADOS[lado];
        
        cochesMetidos++;
        
        cocheM = coches.primero();
        
        if ( lado == BABOR ) metrosBabor += cocheM;
        else metrosEstribor += cocheM;
        
        coches.quitaPrim();
        
        if ( esValida(metrosFerry, metrosBabor, metrosEstribor)) {
            
            if ( esSolucion(coches, metrosFerry, metrosBabor, metrosEstribor) ) {
                if ( cochesMetidos > numCoches ) {
                    
                    for (int j=0; j < cochesMetidos; j++) {
                        mejorSolucion[j] = solucion[j];
                    }
                    
                    numCoches = cochesMetidos;
                    
                    cout << endl << "Tratando solución" << endl;
                    for (int j=0; j < cochesMetidos; j++) {
                        cout << solucion[j] << ", ";
                    }
                }
            }
            else {
                ejer7T11(coches, metrosFerry, solucion, mejorSolucion, numCoches, cochesMetidos, k + 1, metrosBabor, metrosEstribor);
            }
        }
        
        if ( lado == BABOR ) metrosBabor -= cocheM;
        else metrosEstribor -= cocheM;
        
        coches.ponDelante(cocheM);
    }
}

void ejet7T11() {
    
    DCola<double> coches;
    
    coches.ponDetras(2.5);
    coches.ponDetras(3);
    coches.ponDetras(1);
    coches.ponDetras(1);
    coches.ponDetras(1.5);
    coches.ponDetras(0.7);
    coches.ponDetras(0.8);
    
    int metros = 5;
    
    Lado solucion[coches.numElems()];
    Lado mejorSolucion[coches.numElems()];
    
    int numCoches = 0;
    
    ejer7T11(coches, metros, solucion, mejorSolucion, numCoches, 0, 0, 0, 0);
}

int main(int argc, const char * argv[])
{
    ejet7T11();
    
    return 0;
}

