# OOP_5
5 užduotis

## Idiegimas (Unix kompiuteryje).

- `git clone https://github.com/vikuliukas/OOP_5.git`
- `cd OOP_5`
- `make`
- `./main`

## Instrukcijos

- Į failą "tekstas.txt" nukopijuokite norimą tekstą.
- Įsidekite programą:
```shell
Idiegimas (Unix kompiuteryje).
- `git clone https://github.com/vikuliukas/OOP_5.git`
- `cd OOP_5`
- `make`
- `./main`
```
- Atsidarykine rezultatų failą "rezultatas.txt"
- Jei rezulato failo nebereikia, galima panaudoti komandą -`make clean`

## Programos tikslai:
- Nuskaityti duomenis nuo duomenų failo.
- Suskaičiuoti kiek kartų skirtingi žodžiai pasikartoja tekste.
- Sukurkiti cross-reference tipo lentelę kurioje bus nurodyta, kurioje teksto vietoje kiekvienas iš daugiau negu vieną kartą pasikartojantis žodis buvo paminėtas.
- Surasti tekste esančius URL adresus.

## Versiju istorija

# [v1.0](https://github.com/vikuliukas/OOP_5/releases/tag/v1.0)

## Duomenų failo ištrauka
```shell
Skaitykite daugiau: https://www.delfi.lt/news/daily/lithuania/vilniuje-vyko-baltic-pride-eitynes-greiciausiai-bus-fiksuotas-eityniu-dalyviu-rekordas.d?id=81403345

Išsipuošė įdomiais kostiumais
Eitynių dalyviai į eitynes pradėjo rinktis dar 11 val. Vienų veidus puošė išpieštos vaivorykštės spalvų vėliavos, o netrūko ir tokių, kurie pasirūpino ir įdomesniais kostiumais ir juos gaminosi patys. Sutikta mergina pasakojo dailią karūną gaminusi pati, o suknelę nusipirkusi.
„Manau, kad heteroseksualūs žmonės, jie nesupranta, kiek teisių jie turi. Mes dėl to ir protestuojame, dėl to ir palaikome“, sakė viena dalyvė.
Dalyviai, paklausti, kodėl jie šiandien yra čia, pasakojo tiesiog norintys palaikyti seksualines mažumas.
```
## Rezultatų failo ištrauka
```shell
Nuorodos: 
https://www.delfi.lt/news/daily/lithuania/vilniuje-vyko-baltic-pride-eitynes-greiciausiai-bus-fiksuotas-eityniu-dalyviu-rekordas.d?id=81403345
www.delfi.lt

Žodis "apie" pasikartojo 2 kartus, eilutėse: 11 14 
Žodis "atėjo" pasikartojo 4 kartus, eilutėse: 11 13 13 15 
Žodis "aš" pasikartojo 2 kartus, eilutėse: 10 20 
Žodis "baltic" pasikartojo 2 kartus, eilutėse: 1 11 
Žodis "buvo" pasikartojo 3 kartus, eilutėse: 14 15 19 
Žodis "būti" pasikartojo 2 kartus, eilutėse: 12 22 
Žodis "dalyviai" pasikartojo 2 kartus, eilutėse: 6 8 
Žodis "dar" pasikartojo 2 kartus, eilutėse: 6 10 
```

# Programoje naudojamos 5 funkcijos:
## funkcija zodziu_paieska

```c++
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
```
- Šioje funkcijoje suvedami žodžiai į `std::map` ir suvedamos nuorodos į atskira konteinerį `std::vector`. Ši funkcija naudoja kitas funkcijas kaip `ar_nuoroda`, `i_mazas_raides` ir `istrinti_simbolius`.

## funkcija i_mazas_raides

```c++
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
```
- Šioje funkcijoje naudojama komanda `std::tolower`, kuri paverčia ACSII raides iš didžiūjų į mažąsias, tačiau tai neveikia su lietuviškomis raidėmis. Todėl į šią funkciją paduodamas žodis būna paverčiamas į utf-8 ir tada atrenkamos lietuviškos raidės `ĄČĘĖĮŠŲŪŽ` ir paverčiamos į mažąsias raides.

## funkcija istrinti_simbolius

```c++
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
```
- Šioje funkcijoje ištinami skirybos ženklai, tačiau kaip ir su lietuviškomis raidėmis, kai kuriuos skirybos ženklus teko ištrinti naudojant jų utf-8 numerius.

## funkcija ar_nuoroda

```c++
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
```
- Funkcija patikrina ar jai perduotas žodis atitinka nuorodos tipą.

## funkcija spausdinimas

```c++
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
```
- Į rezultatų failą išveda nuorodas (jei tokių yra) ir visus žodžius tekste, kurie pasikartoja daugiau nei 1 kartą.