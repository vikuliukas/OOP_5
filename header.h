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
#include <utility>

void zodziu_paieska( std::map<std::string, std::vector<int>> & zodziai, std::vector<std::string> & nuorodos);
void spausdinimas(std::vector<std::pair<std::string, std::vector<int>>> & zod, std::vector<std::string> & nuorodos, int & ilg_zod, int & did_vect);
std::string i_mazas_raides(std::string & a);
std::string istinti_simbolius(std::string & a);
int ilgiausias_zodis(std::map<std::string, std::vector<int>> & zodziai);
int didziausias_vector(std::map<std::string, std::vector<int>> & zodziai);
bool ar_nuoroda(std::string a);
bool pagal_kartus(std::pair<std::string, std::vector<int>> a, std::pair<std::string, std::vector<int>> b);
void rikiuoti_pagal_kartus(std::map<std::string, std::vector<int>> & zodziai, std::vector<std::pair<std::string, std::vector<int>>> & zod);
bool eilutes (std::vector<int> & a, int b);

#endif