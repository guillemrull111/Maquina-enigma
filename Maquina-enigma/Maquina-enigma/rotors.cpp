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
