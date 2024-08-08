#ifndef SortFilmes_hpp
#define SortFilmes_hpp

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Filme.hpp"

class SortFilmes {
public:
    std::vector<Filme*> tconstArrayPtr;
    std::vector<Filme*> titleTypeArrayPtr;
    std::vector<Filme*> primaryTitleArrayPtr;
    std::vector<Filme*> originalTitleArrayPtr;
    std::vector<Filme*> isAdultArrayPtr;
    std::vector<Filme*> startYearArrayPtr;
    std::vector<Filme*> endYearArrayPtr;
    std::vector<Filme*> runtimeMinutesArrayPtr;
    std::vector<Filme*> genresArrayPtr;
    std::vector<Filme> filmes;

    SortFilmes(std::vector<Filme>& filmes)
        : filmes(filmes) {}

    ~SortFilmes() {}

    void atualizar() {
        tconstArrayPtr.clear();
        titleTypeArrayPtr.clear();
        primaryTitleArrayPtr.clear();
        originalTitleArrayPtr.clear();
        isAdultArrayPtr.clear();
        startYearArrayPtr.clear();
        endYearArrayPtr.clear();
        runtimeMinutesArrayPtr.clear();
        genresArrayPtr.clear();

        for (auto& filme : filmes) {
            tconstArrayPtr.push_back(&filme);
            titleTypeArrayPtr.push_back(&filme);
            primaryTitleArrayPtr.push_back(&filme);
            originalTitleArrayPtr.push_back(&filme);
            isAdultArrayPtr.push_back(&filme);
            startYearArrayPtr.push_back(&filme);
            endYearArrayPtr.push_back(&filme);
            runtimeMinutesArrayPtr.push_back(&filme);
            genresArrayPtr.push_back(&filme);
        }

        std::cout << "\nEntrou na função atualizar";
    }

    std::vector<Filme*> merge_sort(std::vector<Filme*> array, bool (*compareFilme)(Filme*, Filme*)) {
        if (array.size() <= 1) {
            return array;
        }

        size_t mid = array.size() / 2;
        std::vector<Filme*> arrayOne(array.begin(), array.begin() + mid);
        std::vector<Filme*> arrayTwo(array.begin() + mid, array.end());

        std::vector<Filme*> sortedArrayOne = merge_sort(arrayOne, compareFilme);
        std::vector<Filme*> sortedArrayTwo = merge_sort(arrayTwo, compareFilme);

        return merge(sortedArrayOne, sortedArrayTwo, compareFilme);
    }

    std::vector<Filme*> merge(const std::vector<Filme*>& a, const std::vector<Filme*>& b, bool (*compareFilme)(Filme*, Filme*)) {
        std::vector<Filme*> c;
        size_t i = 0, j = 0;

        while (i < a.size() && j < b.size()) {
            if (compareFilme(a[i], b[j])) {
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

    template <typename T>
    Filme* buscaBinaria(const std::vector<Filme*>& array, T key, T (Filme::*getter)() const) {
        int low = 0;
        int high = array.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            T midVal = (array[mid]->*getter)();

            if (midVal < key) {
                low = mid + 1;
            } else if (midVal > key) {
                high = mid - 1;
            } else {
                return array[mid];
            }
        }

        return nullptr;
    }

    std::vector<Filme*> buscaPorGenero(const std::string& genero) {
        std::vector<Filme*> resultados;
        for (auto& filme : genresArrayPtr) {
            if (std::find(filme->getGenres().begin(), filme->getGenres().end(), genero) != filme->getGenres().end()) {
                resultados.push_back(filme);
            }
        }
        return resultados;
    }

    void imprimirFilmes() {
        for (auto& filme : originalTitleArrayPtr) {
            std::cout << "ID: " << filme->getTconst() << "\n"
            //           << "Título Original: " << filme->getOriginalTitle() << "\n"
            //           << "Gêneros: ";
            // for (const auto& genero : filme->getGenres()) {
            //     std::cout << genero << " "
                ;
            // }
            // std::cout << "\n\n";
        }
    }
};

#endif
