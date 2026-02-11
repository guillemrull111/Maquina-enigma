#include <iostream>
#include <fstream>
#include <string>
#include "xifratge i desxifratge.h"
#include "rotors.h"

void xifratge() {

    std::string rotorEsquerra, rotorCentral, rotorDret;
    char notchEsquerra, notchCentral, notchDret;

    std::ifstream fitxerRotorEsquerra("Rotor1.txt");
    std::ifstream fitxerRotorCentral("Rotor2.txt");
    std::ifstream fitxerRotorDret("Rotor3.txt");

    if (!fitxerRotorEsquerra.is_open() || !fitxerRotorCentral.is_open() || !fitxerRotorDret.is_open()) {
        std::cout << "No es poden obrir els rotors\n";
        return;
    }

    fitxerRotorEsquerra >> rotorEsquerra;
    fitxerRotorEsquerra >> notchEsquerra;

    fitxerRotorCentral >> rotorCentral;
    fitxerRotorCentral >> notchCentral;

    fitxerRotorDret >> rotorDret;
    fitxerRotorDret >> notchDret;

    char inicialEsquerra, inicialCentral, inicialDreta;
    std::cout << "Posicio inicial (A B C): ";
    std::cin >> inicialEsquerra >> inicialCentral >> inicialDreta;

    int posicioEsquerra = inicialEsquerra - 'A';
    int posicioCentral = inicialCentral - 'A';
    int posicioDreta = inicialDreta - 'A';

    std::ifstream entrada("Missatge.txt");
    std::ofstream sortida("Xifrat.txt");

    char lletraActual;
    int contador = 0;

    while (entrada >> lletraActual) {

        if (lletraActual >= 'a' && lletraActual <= 'z')
            lletraActual -= 32;

        if (lletraActual < 'A' || lletraActual > 'Z')
            continue;

        movimentRotors(posicioEsquerra, posicioCentral, posicioDreta, notchEsquerra, notchCentral);

        lletraActual = rotorEsquerra[(lletraActual - 'A' + posicioEsquerra) % 26];

        lletraActual = rotorCentral[(lletraActual - 'A' + posicioCentral) % 26];

        lletraActual = rotorDret[(lletraActual - 'A' + posicioDreta) % 26];

        sortida << lletraActual;
        contador++;

        if (contador == 5) {
            sortida << ' ';
            contador = 0;
        }
    }

    std::cout << "Missatge xifrat\n";
}

void desxifratge() {

    std::string rotorEsquerra, rotorCentral, rotorDret;
    char notchEsquerra, notchCentral, notchDret;

    std::ifstream fitxerRotorEsquerra("Rotor1.txt");
    std::ifstream fitxerRotorCentral("Rotor2.txt");
    std::ifstream fitxerRotorDret("Rotor3.txt");

    if (!fitxerRotorEsquerra.is_open() || !fitxerRotorCentral.is_open() || !fitxerRotorDret.is_open()) {
        std::cout << "No es poden obrir els rotors\n";
        return;
    }

    fitxerRotorEsquerra >> rotorEsquerra; 
    fitxerRotorEsquerra >> notchEsquerra;

    fitxerRotorCentral >> rotorCentral;
    fitxerRotorCentral >> notchCentral;

    fitxerRotorDret >> rotorDret;
    fitxerRotorDret >> notchDret;

    char inicialEsquerra, inicialCentral, inicialDreta;
    std::cout << "Posicio inicial (A B C): ";
    std::cin >> inicialEsquerra >> inicialCentral >> inicialDreta;

    int posicioEsquerra = inicialEsquerra - 'A';
    int posicioCentral = inicialCentral - 'A';
    int posicioDreta = inicialDreta - 'A';

    std::ifstream entrada("Xifrat.txt");
    std::ofstream sortida("Desxifrat.txt");

    char lletraActual;

    while (entrada >> lletraActual) {

        if (lletraActual < 'A' || lletraActual > 'Z')
            continue;

        movimentRotors(posicioEsquerra, posicioCentral, posicioDreta, notchEsquerra, notchCentral);

        int posicioFinal;

        posicioFinal = rotorDret.find(lletraActual);
        lletraActual = 'A' + (posicioFinal - posicioDreta + 26) % 26;

        posicioFinal = rotorCentral.find(lletraActual);
        lletraActual = 'A' + (posicioFinal - posicioCentral + 26) % 26;

        posicioFinal = rotorEsquerra.find(lletraActual);
        lletraActual = 'A' + (posicioFinal - posicioEsquerra + 26) % 26;

        sortida << lletraActual;
    }

    std::cout << "[OK] Missatge desxifrat\n";
}
