#include <iostream>
#include "rotors.h"
#include "xifratge i desxifratge.h"

int main() {

	int InputUsuario;

	std::cout << "         ENIGMA:" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "   1. Xifrar missatge" << std::endl;
	std::cout << "   2. Desxifrar missatge" << std::endl;
	std::cout << "   3. Editar rotors" << std::endl;
	std::cout << "   4. Sortir" << std::endl;
	std::cout << "\nQue vols fer: ";
	std::cin >> InputUsuario;

	if (InputUsuario == 1) // Xifrar missatge
	{
		xifratge();
	}

	else if (InputUsuario == 2) // Desxifrar missatge
	{
		desxifratge();
	}

	else if (InputUsuario == 3) // Editar rotors
	{
		editarRotors();
	}

	else if (InputUsuario == 4) // Sortir
	{
		return 0;
	}
}