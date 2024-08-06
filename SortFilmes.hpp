#ifndef SortFilmes_hpp
#define SortFilmes_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Filme.hpp"

class SortFilmes
{
private:
   
public:
 std::vector<Filme*> tconstArrayPtr;
    std::vector<Filme*> titleTypeArrayPtr;
    std::vector<Filme*> primaryTitleArrayPtr;
    std::vector<Filme*> originalTitleArrayPtr;
    std::vector<Filme*> isAdultArrayPtr;
    std::vector<Filme*> startYearArrayPtr;
    std::vector<Filme*> endYearArrayPtr;
    std::vector<Filme*> runtimeMinutesArrayPtr;
    std::vector<Filme> filmes;

    SortFilmes(std::vector<Filme>& filmes)
        : filmes(filmes) {}

    ~SortFilmes() {
        // Não é necessário deletar ponteiros de membros do vector,
        // pois eles são gerenciados pelo próprio vector.
    }

    void atualizar() {
        titleTypeArrayPtr.clear();
        for (auto& filme : filmes) {
            titleTypeArrayPtr.push_back(&filme);
        }
    
        tconstArrayPtr.clear();
        for (auto& filme : filmes) {
            tconstArrayPtr.push_back(&filme);
        }
    
        primaryTitleArrayPtr.clear();
        for (auto& filme : filmes) {
            primaryTitleArrayPtr.push_back(&filme);
        }

        originalTitleArrayPtr.clear();
        for (auto& filme : filmes) {
            originalTitleArrayPtr.push_back(&filme);
        }
        isAdultArrayPtr.clear();
        for (auto& filme : filmes) {
            isAdultArrayPtr.push_back(&filme);
        }
        startYearArrayPtr.clear();
        for (auto& filme : filmes) {
            startYearArrayPtr.push_back(&filme);
        }
        endYearArrayPtr.clear();
        for (auto& filme : filmes) {
            endYearArrayPtr.push_back(&filme);
        }
        runtimeMinutesArrayPtr.clear();
        for (auto& filme : filmes) {
            runtimeMinutesArrayPtr.push_back(&filme);
        }
        std::cout << "\nEntrou na função atualizar";
    }


std::vector<Filme*> merge_sort(const std::vector<Filme*>& array, bool (*compareFilme)(Filme*, Filme*)) {
        // Base case: if the array has 1 or no elements, it's already sorted
        if (array.size() <= 1) {
            return array;
        }

        // Find the midpoint of the array
        size_t mid = array.size() / 2;

        // Split the array into two halves
        std::vector<Filme*> arrayOne(array.begin(), array.begin() + mid);
        std::vector<Filme*> arrayTwo(array.begin() + mid, array.end());

        // Recursively sort each half
        std::vector<Filme*> sortedArrayOne = merge_sort(arrayOne, compareFilme);
        std::vector<Filme*> sortedArrayTwo = merge_sort(arrayTwo, compareFilme);

        // Merge the sorted halves and return
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
    template <typename T>//nao conhecia essa funcionalidade, chatgpt me ensinou, T pode ser de qualquer tipo, mas ja fiz o merge sort sem, enntao nao vou atualizar
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

        return nullptr; // Retorna nullptr se não encontrar o filme
    }


    void imprimirFilmes() {
        std::cout << "\nEntrou na função imprimir";

        for (size_t i = 0; i < filmes.size(); ++i) {
           std::cout << "ID " << tconstArrayPtr[i] ->getTconst() << "\n"
                       << "Tipo: " << titleTypeArrayPtr[i]->getTitleType() << "\n"
                       << "Título Principal: " << primaryTitleArrayPtr[i]->getPrimaryTitle() << "\n"
                       << "Título Original: " << originalTitleArrayPtr[i]->getOriginalTitle() << "\n"
                       << "Adulto: " << (isAdultArrayPtr[i]->getIsAdult() ? "Sim" : "Não") << "\n"
                       << "Ano de Início: " << startYearArrayPtr[i]->getStartYear() << "\n"
                       << "Ano de Término: " << endYearArrayPtr[i]->getEndYear() << "\n"
                       << "Duração: " << runtimeMinutesArrayPtr[i]->getRuntimeMinutes() << " minutos\n\n";
        }
    }
};

#endif
    