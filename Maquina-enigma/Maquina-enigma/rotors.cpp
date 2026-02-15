#include <iostream>
#include <fstream>
#include "rotors.h"

void movimentRotors(int& posicioEsquerra, int& posicioCentral, int& posicioDreta, char notchEsquerra, char notchCentral)
{
    bool giraCentral = (posicioEsquerra == notchEsquerra - 'A');
    bool giraDreta = (posicioCentral == notchCentral - 'A');

    posicioEsquerra = (posicioEsquerra + 1) % 26;

    if (giraCentral) {
        posicioCentral = (posicioCentral + 1) % 26;

        if (giraDreta) {
            posicioDreta = (posicioDreta + 1) % 26;
        }
    }
}

void editarRotors() {



    int numeroRotor;

    std::cout << "Quin rotor vols editar? (1, 2 o 3): ";

    std::cin >> numeroRotor;



    std::string nomFitxer;



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

    std::cout << "Introdueix la nova permutacio (26 lletres majuscules): ";

    std::cin >> permutacio;



    // ---- COMPROBACIÓN 1: longitud ----

    if (permutacio.length() != 26) {

        std::cout << "Error: ha de tenir exactament 26 lletres\n";

        return;

    }



    // ---- COMPROBACIÓN 2: solo A-Z ----

    for (int i = 0; i < 26; i++) {

        if (permutacio[i] < 'A' || permutacio[i] > 'Z') {

            std::cout << "Error: nomes es permeten lletres majuscules A-Z\n";

            return;

        }

    }



    // ---- COMPROBACIÓN 3: no repetidas ----

    for (int i = 0; i < 26; i++) {

        for (int j = i + 1; j < 26; j++) {

            if (permutacio[i] == permutacio[j]) {

                std::cout << "Error: hi ha lletres repetides\n";

                return;

            }

        }

    }



    char notch;

    std::cout << "Introdueix la lletra del notch (A-Z): ";

    std::cin >> notch;



    // ---- COMPROBACIÓN 4: notch válido ----

    if (notch < 'A' || notch > 'Z') {

        std::cout << "Error: notch no valid\n";

        return;

    }



    std::ofstream fitxer(nomFitxer);



    if (!fitxer.is_open()) {

        std::cout << "Error obrint el fitxer\n";

        return;

    }



    fitxer << permutacio << std::endl;

    fitxer << notch << std::endl;



    std::cout << "Rotor actualitzat correctament!\n";

}