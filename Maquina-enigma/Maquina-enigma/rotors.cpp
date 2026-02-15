#include <iostream>
#include <fstream>
#include "rotors.h"

// Aquesta funció simula el moviment dels rotors com a la màquina Enigma

void movimentRotors(int& posicioEsquerra, int& posicioCentral, int& posicioDreta, char notchEsquerra, char notchCentral)
{
    // Comprovem si el rotor esquerre arriba al seu notch (punt de gir)

    bool giraCentral = (posicioEsquerra == notchEsquerra - 'A');

    // Comprovem si el rotor central arriba al seu notch

    bool giraDreta = (posicioCentral == notchCentral - 'A');

    // Girem sempre el rotor esquerre (cada lletra escrita)

    posicioEsquerra = (posicioEsquerra + 1) % 26;

    // Si el rotor esquerre ha arribat al seu notch, fem girar el central

    if (giraCentral) {
        posicioCentral = (posicioCentral + 1) % 26;

        // I si el central també està al seu notch, fem girar el dret

        if (giraDreta) {
            posicioDreta = (posicioDreta + 1) % 26;
        }
    }
}

void editarRotors() {

    int numeroRotor;

    // Demanem quin rotor vol editar l’usuari

    std::cout << "Quin rotor vols editar? (1, 2 o 3): ";

    std::cin >> numeroRotor;

    std::string nomFitxer;

    // Assignem el nom del fitxer segons el número seleccionat

    if (numeroRotor == 1)

        nomFitxer = "Rotor1.txt";

    else if (numeroRotor == 2)

        nomFitxer = "Rotor2.txt";

    else if (numeroRotor == 3)

        nomFitxer = "Rotor3.txt";

    else {

        std::cout << "Opcio incorrecta\n";

        return;

    }

    std::string permutacio;

    // L’usuari introdueix una nova seqüència de 26 lletres (la configuració del rotor)

    std::cout << "Introdueix la nova permutacio (26 lletres majuscules): ";

    std::cin >> permutacio;

    // ---- COMPROBACIÓ 1: longitud ----

    if (permutacio.length() != 26) {

        std::cout << "Error: ha de tenir exactament 26 lletres\n";

        return;

    }

    // ---- COMPROBACIÓ 2: nomes A-Z ----

    for (int i = 0; i < 26; i++) {

        if (permutacio[i] < 'A' || permutacio[i] > 'Z') {

            std::cout << "Error: nomes es permeten lletres majuscules A-Z\n";

            return;

        }
    }

    // ---- COMPROBACIÓ 3: no repetidas ----

    for (int i = 0; i < 26; i++) {

        for (int j = i + 1; j < 26; j++) {

            if (permutacio[i] == permutacio[j]) {

                std::cout << "Error: hi ha lletres repetides\n";

                return;

            }
        }
    }

    char notch;

    // L’usuari escriu la lletra del notch (on el rotor farà girar el següent)

    std::cout << "Introdueix la lletra del notch (A-Z): ";

    std::cin >> notch;

    // ---- COMPROBACIÓ 4: notch vàlid ----

    if (notch < 'A' || notch > 'Z') {

        std::cout << "Error: notch no valid\n";

        return;

    }

    // Obrim el fitxer corresponent per escriure-hi la nova configuració

    std::ofstream fitxer(nomFitxer);

    if (!fitxer.is_open()) {

        std::cout << "Error obrint el fitxer\n";

        return;

    }

    // Guardem la nova permutació i el notch al fitxer

    fitxer << permutacio << std::endl;

    fitxer << notch << std::endl;

    std::cout << "Rotor actualitzat correctament!\n";

}