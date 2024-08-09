#ifndef ManipularCinema_hpp
#define ManipularCinema_hpp

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Cinema.hpp"
#include "Filme.hpp"

class ManipularCinema{


public:
    std::vector<Cinema*> Coordenadas;
    std::vector<Cinema*> Preco;
    std::vector<Cinema*> Id;
    std::vector<Cinema*> FilmesEmExposicao;
    std::vector<Cinema> cinemas;

 void atualizarCinema() {
        Coordenadas.clear();
        Preco.clear();
        Id.clear();
        FilmesEmExposicao.clear();

        for (auto& cinema : cinemas) {
           Coordenadas.push_back(&cinema);
            Preco.push_back(&cinema);
            Id.push_back(&cinema);
            FilmesEmExposicao.push_back(&cinema);
           
        }

        std::cout << "\nEntrou na função atualizarCinema";
    }










};
















#endif