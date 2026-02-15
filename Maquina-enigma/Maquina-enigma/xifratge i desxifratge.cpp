#include <iostream>
#include <fstream>
#include <string>
#include "xifratge i desxifratge.h"
#include "rotors.h"

void xifratge() {

    //Declarem variables

    std::string rotorEsquerra, rotorCentral, rotorDret;
    char notchEsquerra, notchCentral, notchDret;

    // Obrim els fitxers dels tres rotors

    std::ifstream fitxerRotorEsquerra("Rotor1.txt");
    std::ifstream fitxerRotorCentral("Rotor2.txt");
    std::ifstream fitxerRotorDret("Rotor3.txt");

    //Si no es pot obrir algun fitxer, que surti el missatge:

    if (!fitxerRotorEsquerra.is_open() || !fitxerRotorCentral.is_open() || !fitxerRotorDret.is_open()) {
        std::cout << "No es poden obrir els rotors\n";
        return;
    }

    // Llegim la seqüència i el notch de cada rotor

    fitxerRotorEsquerra >> rotorEsquerra;
    fitxerRotorEsquerra >> notchEsquerra;

    fitxerRotorCentral >> rotorCentral;
    fitxerRotorCentral >> notchCentral;

    fitxerRotorDret >> rotorDret;
    fitxerRotorDret >> notchDret;

    // Demanem a l’usuari la posició inicial de cada rotor

    char inicialEsquerra, inicialCentral, inicialDreta;
    std::cout << "Posicio inicial (A B C): ";
    std::cin >> inicialEsquerra >> inicialCentral >> inicialDreta;

    // Convertim les lletres inicials en posicions numèriques (0–25)

    int posicioEsquerra = inicialEsquerra - 'A';
    int posicioCentral = inicialCentral - 'A';
    int posicioDreta = inicialDreta - 'A';

    // Obrim el fitxer d’entrada (missatge original) i el de sortida (missatge xifrat)

    std::ifstream entrada("Missatge.txt");
    std::ofstream sortida("Xifrat.txt");

    char lletraActual;
    int contador = 0;

    // Llegim cada lletra del missatge

    while (entrada >> lletraActual) {

        // Convertim minúscules a majúscules

        if (lletraActual >= 'a' && lletraActual <= 'z')
            lletraActual -= 32;

        // Si no és una lletra, la saltem

        if (lletraActual < 'A' || lletraActual > 'Z')
            continue;

        // Movem els rotors segons el seu notch i posició

        movimentRotors(posicioEsquerra, posicioCentral, posicioDreta, notchEsquerra, notchCentral);

        // Passem la lletra pels tres rotors (esquerra → central → dret)

        lletraActual = rotorEsquerra[(lletraActual - 'A' + posicioEsquerra) % 26];

        lletraActual = rotorCentral[(lletraActual - 'A' + posicioCentral) % 26];

        lletraActual = rotorDret[(lletraActual - 'A' + posicioDreta) % 26];

        // Escrivim la lletra xifrada al fitxer de sortida

        sortida << lletraActual;
        contador++;

        // Afegim un espai cada 5 lletres (format clàssic d’Enigma)

        if (contador == 5) {
            sortida << ' ';
            contador = 0;
        }
    }

    std::cout << "Missatge xifrat\n";
}

void desxifratge() {

    // Declarem les variables

    std::string rotorEsquerra, rotorCentral, rotorDret;
    char notchEsquerra, notchCentral, notchDret;

    // Obrim els fitxers dels rotors

    std::ifstream fitxerRotorEsquerra("Rotor1.txt");
    std::ifstream fitxerRotorCentral("Rotor2.txt");
    std::ifstream fitxerRotorDret("Rotor3.txt");

    // Comprovem si s’han pogut obrir correctament i sinó mostrem missatge

    if (!fitxerRotorEsquerra.is_open() || !fitxerRotorCentral.is_open() || !fitxerRotorDret.is_open()) {
        std::cout << "No es poden obrir els rotors\n";
        return;
    }

    // Llegim el contingut dels rotors i el notch

    fitxerRotorEsquerra >> rotorEsquerra; 
    fitxerRotorEsquerra >> notchEsquerra;

    fitxerRotorCentral >> rotorCentral;
    fitxerRotorCentral >> notchCentral;

    fitxerRotorDret >> rotorDret;
    fitxerRotorDret >> notchDret;

    // Demanem la mateixa posició inicial usada al xifrat

    char inicialEsquerra, inicialCentral, inicialDreta;
    std::cout << "Posicio inicial (A B C): ";
    std::cin >> inicialEsquerra >> inicialCentral >> inicialDreta;

    // Convertim lletres inicials a posicions numèriques

    int posicioEsquerra = inicialEsquerra - 'A';
    int posicioCentral = inicialCentral - 'A';
    int posicioDreta = inicialDreta - 'A';

    // Obrim el fitxer d’entrada (text xifrat) i el de sortida (text desxifrat)

    std::ifstream entrada("Xifrat.txt");
    std::ofstream sortida("Desxifrat.txt");

    char lletraActual;

    // Llegim cada lletra del text xifrat

    while (entrada >> lletraActual) {

        // Si no és una lletra, la saltem

        if (lletraActual < 'A' || lletraActual > 'Z')
            continue;

        // Movem els rotors tal com es fa al xifrat

        movimentRotors(posicioEsquerra, posicioCentral, posicioDreta, notchEsquerra, notchCentral);

        int posicioFinal;

        // Passem la lletra pels rotors en ordre invers (dret → central → esquerra)

        posicioFinal = rotorDret.find(lletraActual);
        lletraActual = 'A' + (posicioFinal - posicioDreta + 26) % 26;

        posicioFinal = rotorCentral.find(lletraActual);
        lletraActual = 'A' + (posicioFinal - posicioCentral + 26) % 26;

        posicioFinal = rotorEsquerra.find(lletraActual);
        lletraActual = 'A' + (posicioFinal - posicioEsquerra + 26) % 26;

        // Escrivim la lletra desxifrada al fitxer de sortida

        sortida << lletraActual;
    }

    std::cout << "[OK] Missatge desxifrat\n";
}
