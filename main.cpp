#include "header.h"

int main(){
    std::setlocale(LC_ALL, "Lithuanian");
    std::map <std::string, std::vector<int>> zodziai;
    std::vector<std::string> nuorodos;
    std::vector<std::pair<std::string, std::vector<int>>> zod;

    zodziu_paieska(zodziai, nuorodos);
    int ilg_zod = ilgiausias_zodis(zodziai);
    int did_vect = didziausias_vector(zodziai);
    rikiuoti_pagal_kartus(zodziai, zod);
    spausdinimas(zod, nuorodos, ilg_zod, did_vect);

    return 0;
}
