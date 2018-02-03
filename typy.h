#ifndef TYPY_H
#define TYPY_H

#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;

struct Type{
  string n;
  int nr;
  Type *nast;
};
void WczytajDoListyTypy(string typy, Type *&glowa_t);
void UsunListeTypy(Type *glowa);
#endif // TYPY_H
