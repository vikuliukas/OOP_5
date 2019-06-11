#include "header.h"

int main(){
    std::setlocale(LC_ALL, "Lithuanian");
    std::map <std::string, std::vector<int>> zodziai;
    std::vector<std::string> nuorodos;

    zodziu_paieska(zodziai, nuorodos);
    int ilg_zod = ilgiausias_zodis(zodziai);
    spausdinimas(zodziai, ilg_zod, nuorodos);

    return 0;
}
