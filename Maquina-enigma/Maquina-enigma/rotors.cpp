#include "rotors.h"
#include <fstream>
#include <iostream>

bool permValida(const std::string& s) {
    if (s.size() != 26) return false;
    bool vist[26];
    int i;
    for (i = 0; i < 26; i++) vist[i] = false;

    for (i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        if (c < 'A' || c > 'Z') return false;
        int idx = c - 'A';
        if (vist[idx]) return false;
        vist[idx] = true;
    }
    return true;
}

void construirInv(int r) {
    rotorInv[r].assign(26, 'A');
    int i;
    for (i = 0; i < 26; i++) {
        char c = rotorWiring[r][i];
        int outIdx = c - 'A';
        rotorInv[r][outIdx] = (char)('A' + i);
    }
}

bool cargarRotors() {
    const char* noms[3] = { "Rotor1.txt", "Rotor2.txt", "Rotor3.txt" };
    bool correcte = true;

    int r;
    for (r = 0; r < 3; r++) {

        std::ifstream fitxer(noms[r]);
        if (!fitxer) {
            std::cout << "[ERROR] No s'ha pogut obrir " << noms[r] << "\n";
            correcte = false;
            continue;
        }

        std::string linia;
        if (!std::getline(fitxer, linia)) {
            std::cout << "[ERROR] " << noms[r] << ": fitxer buit\n";
            correcte = false;
            continue;
        }

        std::string aux = "";
        int i;
        for (i = 0; i < (int)linia.size(); i++) {
            char c = linia[i];
            if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            }
            else {
                if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
                aux = aux + c;
            }
        }
        linia = aux;

        if (!permValida(linia)) {
            std::cout << "[ERROR] " << noms[r]
                << ": permutació incorrecta — calen 26 lletres úniques A–Z\n";
            correcte = false;
            continue;
        }

        rotorWiring[r] = linia;

        if (std::getline(fitxer, linia)) {
            aux = "";
            for (i = 0; i < (int)linia.size(); i++) {
                char c = linia[i];
                if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
                }
                else {
                    if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
                    aux = aux + c;
                }
            }
            linia = aux;
            if (linia.size() > 0 && linia[0] >= 'A' && linia[0] <= 'Z') {
                rotorNotch[r] = linia[0];
            }
            else {
                rotorNotch[r] = 'Z';
            }
        }
        else {
            rotorNotch[r] = 'Z';
        }

        construirInv(r);
        rotorPos[r] = 0;
    }

    return correcte;
}

void setVentana(char a, char b, char c) {
    if (a >= 'a' && a <= 'z') a = a - 'a' + 'A';
    if (b >= 'a' && b <= 'z') b = b - 'a' + 'A';
    if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';

    rotorPos[0] = a - 'A';
    rotorPos[1] = b - 'A';
    rotorPos[2] = c - 'A';
}

void stepRotors() {
    rotorPos[0] = (rotorPos[0] + 1) % 26;
    bool carry = (char)('A' + rotorPos[0]) == rotorNotch[0];

    if (carry) {
        rotorPos[1] = (rotorPos[1] + 1) % 26;
        carry = (char)('A' + rotorPos[1]) == rotorNotch[1];
        if (carry) {
            rotorPos[2] = (rotorPos[2] + 1) % 26;
        }
    }
}

char forwardRotor(char c, int r) {
    int idx = c - 'A';
    int shifted = (idx + rotorPos[r]) % 26;
    char wired = rotorWiring[r][shifted];
    int outIdx = (wired - 'A' - rotorPos[r] + 26) % 26;
    return (char)('A' + outIdx);
}

char backwardRotor(char c, int r) {
    int idx = c - 'A';
    int shifted = (idx + rotorPos[r]) % 26;
    char wired = rotorInv[r][shifted];
    int outIdx = (wired - 'A' - rotorPos[r] + 26) % 26;
    return (char)('A' + outIdx);
}

char pasarForward(char c) {
    if (c < 'A' || c > 'Z') return c;
    stepRotors();
    c = forwardRotor(c, 0);
    c = forwardRotor(c, 1);
    c = forwardRotor(c, 2);
    return c;
}

char pasarBackward(char c) {
    if (c < 'A' || c > 'Z') return c;
    stepRotors();
    c = backwardRotor(c, 2);
    c = backwardRotor(c, 1);
    c = backwardRotor(c, 0);
    return c;
}

void editarRotors() {

    int idx;
    std::cout << "Quin rotor vols editar? (1-3): ";
    std::cin >> idx;

    if (idx < 1 || idx > 3) {
        std::cout << "[ERROR] Index de rotor invalid\n";
        return;
    }

    std::string permutacio;
    std::cout << "Introdueix permutacio de 26 lletres majuscules A-Z (sense espais):\n";
    std::cin >> permutacio;

    int i;
    // passar a majuscules
    for (i = 0; i < (int)permutacio.size(); i++) {
        char c = permutacio[i];
        if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
        permutacio[i] = c;
    }

    if (!permValida(permutacio)) {
        std::cout << "[ERROR] Permutacio invalida — calen 26 lletres úniques A–Z\n";
        return;
    }

    std::string notchText;
    char notch = 'Z';

    std::cout << "Introdueix lletra notch (A–Z, o ENTER per defecte Z): ";
    std::getline(std::cin, notchText);   // netejar \n pendent
    if (notchText.size() == 0) {
        std::getline(std::cin, notchText);
    }

    if (notchText.size() > 0) {
        char c = notchText[0];
        if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
        if (c >= 'A' && c <= 'Z') {
            notch = c;
        }
    }

    const char* noms[3] = { "Rotor1.txt", "Rotor2.txt", "Rotor3.txt" };

    std::ofstream fitxer(noms[idx - 1]);
    if (!fitxer) {
        std::cout << "[ERROR] No s'ha pogut escriure " << noms[idx - 1] << "\n";
        return;
    }

    fitxer << permutacio << "\n" << notch << "\n";
    fitxer.close();

    std::cout << "[OK] Rotor" << idx << " guardat a \"" << noms[idx - 1] << "\"\n";
}