#ifndef ManipularCinema_hpp
#define ManipularCinema_hpp

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Cinema.hpp"
#include "Filme.hpp"

class ManipularCinema{

    private:

        std::vector<Filme*>filmesEmCartaz;

    public:
        std::vector<Cinema*> Coordenadas;
        std::vector<Cinema*> Preco;
        std::vector<Cinema*> Id;
        std::vector<Cinema> cinemas;
        

        // Getter para filmesEmCartaz
        std::vector<Filme*> getFilmesEmCartaz() const {
            return filmesEmCartaz;
        }
          // Setter para filmesEmCartaz
        void setFilmesEmCartaz(const std::vector<Filme*>& novosFilmesEmCartaz) {
            filmesEmCartaz = novosFilmesEmCartaz;
        }


 void atualizarCinema( std::string nomeArquivo) {


    std::vector<Filme> filmes = lerArquivoFilmes(nomeArquivo);
    SortFilmes sort(filmes);
     sort.atualizar();

    sort.atualizar();
        Coordenadas.clear();
        Preco.clear();
        Id.clear();
        filmesEmCartaz.clear();

        for (auto& cinema : cinemas) {
           Coordenadas.push_back(&cinema);
            Preco.push_back(&cinema);
            Id.push_back(&cinema);
          for (const auto& filme : cinema.getFilmesEmExibicao()) {
        std::vector<Filme*> filmesEncontrados = sort.buscaBinariaMultiplosResultados(sort.tconstArrayPtr, filme, &Filme::getTconst);
        setFilmesEmCartaz(filmesEncontrados);
    }      
        }

        // std::cout << "\nEntrou na função atualizarCinema";
    }

    std::vector<Cinema*> merge_sort(std::vector<Cinema*> array, bool (*compareCinema)(Cinema*, Cinema*)) {
    if (array.size() <= 1) {
        return array;
    }

    size_t mid = array.size() / 2;
    std::vector<Cinema*> arrayOne(array.begin(), array.begin() + mid);
    std::vector<Cinema*> arrayTwo(array.begin() + mid, array.end());

    std::vector<Cinema*> sortedArrayOne = merge_sort(arrayOne, compareCinema);
    std::vector<Cinema*> sortedArrayTwo = merge_sort(arrayTwo, compareCinema);

    return merge(sortedArrayOne, sortedArrayTwo, compareCinema);
}

std::vector<Cinema*> merge(const std::vector<Cinema*>& a, const std::vector<Cinema*>& b, bool (*compareCinema)(Cinema*, Cinema*)) {
    std::vector<Cinema*> c;
    size_t i = 0, j = 0;

    while (i < a.size() && j < b.size()) {
        if (compareCinema(a[i], b[j])) {
            c.push_back(a[i]);
            ++i;
        } else {
            c.push_back(b[j]);
            ++j;
        }
    }

    while (i < a.size()) {
        c.push_back(a[i]);
        ++i;
    }

    while (j < b.size()) {
        c.push_back(b[j]);
        ++j;
    }

    return c;
}




};







#endif