#include "header.h"

void zodziu_paieska( std::map<std::string, std::vector<int>> & zodziai, std::vector<std::string> & nuorodos){
    std::ifstream df("tekstas.txt");
    std::string eil, t; // t - tarpinis kintamasis.
    int i = 1; // i - eilutes numeris.
    while(!df.eof()){
        std::getline(df, eil);
        std::istringstream iss(eil);
        while(iss >> t){
            if(ar_nuoroda(t) == 1){
                nuorodos.push_back(t);
            }
            else{
                t = i_mazas_raides(t);
                t = istinti_simbolius(t);
                if(!t.empty()){
                zodziai[t].push_back(i);
                }
            }
        }
        i++;
    }
    df.close();
}

void spausdinimas(std::map<std::string, std::vector<int>> & zodziai, std::vector<std::string> & nuorodos){
    std::ofstream rf("rezultatas.txt");
    if(!nuorodos.empty()){
        rf << "Nuorodos: \n";
        for(size_t i = 0; i < nuorodos.size(); i++){
            rf<<nuorodos[i]<<"\n";
        }
    }
    rf << "\n";

    for (auto p = zodziai.begin(); p != zodziai.end(); p++){
        if(p->second.size()>1){
            rf<<"Žodis \""<<p->first<<"\" pasikartojo "<<p->second.size()<<" kartus, eilutėse: ";
            for(size_t i = 0; i < p->second.size(); i++){
                rf << p->second[i] <<" ";
            }
            rf << "\n"; 
        }
    }
    rf.close();
}

std::string i_mazas_raides(std::string & a){
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);

    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>,char32_t> converter;
    std::u32string zodis32 = converter.from_bytes(a);

     for(char32_t &raide : zodis32) {
        if((raide == 260)||(raide == 268)||(raide == 278)||(raide == 280)||
        (raide == 302)||(raide == 352)||(raide == 362)||(raide == 370)||(raide == 381)){
            raide ++;
        }
    }

    a = converter.to_bytes(zodis32);
    return a;
}

std::string istinti_simbolius(std::string & a){
    for(size_t i = 0; i < a.size(); i++){
        if(ispunct(a[i])){
            a.erase(i,1);
        }
    }

    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>,char32_t> converter;
    std::u32string zodis32 = converter.from_bytes(a);

     for(char32_t &raide : zodis32) {
        if((raide == 148)||(raide == 147)||(raide == 132)||(raide == 151)||(raide == 150)||(raide == 750)||(raide == 8211)||(raide >= 8220 && raide <=8223)){
            raide = 32;
        }
    }
    a = converter.to_bytes(zodis32);

    std::size_t found = a.find(" "); 
    if (found!=std::string::npos){
        a.erase(found,1);
    }

    return a;
}

bool ar_nuoroda(std::string a){
    bool t = 0;
    if (std::regex_match (a, std::regex("https?:\\/\\/(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)"))) {
        t = 1;
    }
    if (std::regex_match (a, std::regex("[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)"))){
        t = 1;
    }
    return t;
}