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
                bool yra = 0;
                for(size_t i = 0; i < nuorodos.size(); i++){
                    if( t == nuorodos[i]){
                        yra = 1;
                    }
                }
                if(yra == 0){
                    nuorodos.push_back(t);   
                }
            }
            else{
                t = i_mazas_raides(t);
                t = istinti_simbolius(t);
                if(!t.empty()){
                    if(eilutes(zodziai[t], i) == 1){
                        zodziai[t].push_back(0);
                    }
                    else{
                        zodziai[t].push_back(i);
                    }
                }
            }
        }
        i++;
    }
    df.close();
}

void spausdinimas(std::vector<std::pair<std::string, std::vector<int>>> & zod, std::vector<std::string> & nuorodos, int & ilg_zod, int & did_vect){
    std::ofstream rf("rezultatas.txt");
    if(!nuorodos.empty()){
        rf << "Nuorodos: \n";
        for(size_t i = 0; i < nuorodos.size(); i++){
            rf<<nuorodos[i]<<"\n";
        }
    }
    rf << "\n";

    size_t pst, ast; // pirmo ir antro stulpelio ilgiai;
    if(zod.size() % 2 == 0){
        pst = ast = zod.size()/2;
    }
    else{
        pst = ast = zod.size()/2;
        pst++; 
    }
    size_t i = 0;
    size_t j = zod.size() - 1;
    while(i < pst){
        std::stringstream ss;
        ss << "Žodis \"" << zod[i].first << "\" pasikartojo " << zod[i].second.size() <<" kartus, eilutėse: ";
        for(size_t h = 0; h < zod[i].second.size(); h++){
            if(zod[i].second[h] != 0){
                ss<<zod[i].second[h]<<" ";
            }
        }
        rf <<std::left<< std::setw(ilg_zod + did_vect + 40)<<ss.str();
        if(j != i){
            rf << " Žodis \"" << zod[j].first << "\" pasikartojo " << zod[j].second.size() <<" kartus, eilutėse: ";
            for(size_t h = 0; h < zod[j].second.size(); h++){
                if(zod[j].second[h] != 0){
                    rf<<zod[j].second[h]<<" ";
                }
            }
        }
        rf << "\n";
        i ++;
        j --;
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

int ilgiausias_zodis(std::map<std::string, std::vector<int>> & zodziai){
    unsigned int max = 6; // 5 nes max zodis negali buti trumpesnis nei pats zodis "zodis:"
    for (auto p = zodziai.begin(); p != zodziai.end(); p++){
        if(max < p->first.length()){
            max = p->first.length();
        }
    }
    return max;
}

int didziausias_vector(std::map<std::string, std::vector<int>> & zodziai){
    unsigned int max = 0;
    for (auto p = zodziai.begin(); p != zodziai.end(); p++){
        if(max < p->second.size()){
            max = p->second.size();
        }
    }
    return max;
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

bool pagal_kartus(std::pair<std::string, std::vector<int>> a, std::pair<std::string, std::vector<int>> b){
    if(a.second.size() != b.second.size()){
        return a.second.size() < b.second.size();
    }
    return a.first < b.first;
}

void rikiuoti_pagal_kartus(std::map<std::string, std::vector<int>> & zodziai, std::vector<std::pair<std::string, std::vector<int>>> & zod){
    for(auto i = zodziai.begin(); i != zodziai.end(); i++){
        std::pair<std::string, std::vector<int>> t;
        t.first = i->first;
        t.second = i->second;
        zod.push_back(t);
    }
    std::sort(zod.begin(), zod.end(), pagal_kartus);
}

bool eilutes (std::vector<int> & a, int b){
    bool t = 0;
    for(size_t i = 0; i < a.size(); i++){
        if(a[i] == b){
            t = 1;
        }
    }
    return t;
}