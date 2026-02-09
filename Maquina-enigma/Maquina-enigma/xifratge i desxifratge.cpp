#include <iostream>
#include <fstream>
#include <string>
#include "rotors.h"
#include "xifratge i desxifratge.h"

void xifratge() {

    if (!cargarRotors()) {
        return;
    }

    char a, b, c;
    std::cout << "Introdueix finestra (3 lletres, ex: A C B): ";
    std::cin >> a >> b >> c;
    setVentana(a, b, c);

    std::cin.ignore(10000, '\n');
    std::cout << "Introdueix el missatge (acaba amb línia buida):\n";

    std::ofstream fitxerMissatge("Missatge.txt");
    if (!fitxerMissatge) {
        std::cout << "[ERROR] No s'ha pogut escriure Missatge.txt\n";
        return;
    }

    std::string total;
    std::string linia;

    while (true) {
        std::getline(std::cin, linia);
        if (linia.size() == 0) {
            break;
        }
        fitxerMissatge << linia << '\n';
        total = total + linia + '\n';
    }

    fitxerMissatge.close();

    std::string pla;
    int i = 0;
    while (i < (int)total.size()) {
        char ch = total[i];
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - 'a' + 'A';
        }
        if (ch >= 'A' && ch <= 'Z') {
            pla = pla + ch;
        }
        i = i + 1;
    }

    std::string xifrat;
    i = 0;
    while (i < (int)pla.size()) {
        char enc = pasarForward(pla[i]);
        xifrat = xifrat + enc;
        i = i + 1;
    }

    std::string grups;
    int comptador = 0;
    i = 0;
    while (i < (int)xifrat.size()) {
        if (comptador == 5) {
            grups = grups + ' ';
            comptador = 0;
        }
        grups = grups + xifrat[i];
        comptador = comptador + 1;
        i = i + 1;
    }

    std::ofstream fitxerXifrat("Xifrat.txt");
    if (!fitxerXifrat) {
        std::cout << "[ERROR] No s'ha pogut escriure Xifrat.txt\n";
        return;
    }

    fitxerXifrat << grups;
    fitxerXifrat.close();

    int grups5 = ((int)xifrat.size() + 4) / 5;
    std::cout << "[OK] Missatge xifrat a \"Xifrat.txt\" ("
        << xifrat.size() << " lletres, " << grups5 << " grups de 5)\n";
}

void desxifratge() {

    if (!cargarRotors()) {
        return;
    }

    char a, b, c;
    std::cout << "Introdueix finestra (3 lletres, ex: A C B): ";
    std::cin >> a >> b >> c;
    setVentana(a, b, c);

    std::ifstream fitxerXifrat("Xifrat.txt");
    if (!fitxerXifrat) {
        std::cout << "[ERROR] No s'ha trobat Xifrat.txt\n";
        return;
    }

    std::string total;
    std::string linia;
    while (std::getline(fitxerXifrat, linia)) {
        total = total + linia;
    }
    fitxerXifrat.close();

    std::string xifratNet;
    int i = 0;
    while (i < (int)total.size()) {
        char ch = total[i];
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - 'a' + 'A';
        }
        if (ch >= 'A' && ch <= 'Z') {
            xifratNet = xifratNet + ch;
        }
        i = i + 1;
    }

    std::string pla;
    i = 0;
    while (i < (int)xifratNet.size()) {
        char dec = pasarBackward(xifratNet[i]);
        pla = pla + dec;
        i = i + 1;
    }

    std::ofstream fitxerDesxifrat("desxifrat.txt");
    if (!fitxerDesxifrat) {
        std::cout << "[ERROR] No s'ha pogut escriure desxifrat.txt\n";
        return;
    }

    fitxerDesxifrat << pla;
    fitxerDesxifrat.close();

    std::cout << "[OK] Missatge desxifrat a \"desxifrat.txt\" ("
        << pla.size() << " lletres)\n";
}
