#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <locale>
#include <bits/stdc++.h>

void zodziu_paieska( std::map<std::string, std::vector<int>> & zodziai, std::vector<std::string> & nuorodos);
void spausdinimas(std::map<std::string, std::vector<int>> & zodziai, int ilg_zod, std::vector<std::string> & nuorodos);
std::string i_mazas_raides(std::string & a);
std::string istinti_simbolius(std::string & a);
int ilgiausias_zodis(std::map<std::string, std::vector<int>> & zodziai);
bool ar_nuoroda(std::string a);

#endif