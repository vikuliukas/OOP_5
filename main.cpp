#include "header.h"

int main(){
    std::setlocale(LC_ALL, "Lithuanian");
    std::map <std::string, std::vector<int>> zodziai;
    std::vector<std::string> nuorodos;

    zodziu_paieska(zodziai, nuorodos);
    spausdinimas(zodziai, nuorodos);

    return 0;
}
