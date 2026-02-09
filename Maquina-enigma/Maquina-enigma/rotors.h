#pragma once

#include <string>

std::string rotorWiring[3];
std::string rotorInv[3];
char rotorNotch[3];
int rotorPos[3];

bool cargarRotors();
void setVentana(char a, char b, char c);
void stepRotors();
char pasarForward(char c);
char pasarBackward(char c);
void editarRotors();

