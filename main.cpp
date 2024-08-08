#include <iostream>
#include <vector>
#include "Filme.hpp"
#include "SortFilmes.hpp"

// Funções de comparação
// bool compareByOriginalTitle(Filme* a, Filme* b) {
//     return a->getOriginalTitle() < b->getOriginalTitle();
// }

bool compareByTconst(Filme* a, Filme* b) {
    return a->getTconst() < b->getTconst();
}


bool compareByTitleType(Filme* a, Filme* b) {
    return a->getTitleType() < b->getTitleType();
}


bool compareByPrimaryTitle(Filme* a, Filme* b) {
    return a->getPrimaryTitle() < b->getPrimaryTitle();
}

bool compareByOriginalTitle(Filme* a, Filme* b) {
    return a->getOriginalTitle() < b->getOriginalTitle();
}


bool compareByIsadult(Filme* a, Filme* b) {
    return a->getIsAdult() < b->getIsAdult();
}


bool compareByStartYear(Filme* a, Filme* b) {
    return a->getStartYear() < b->getStartYear();
}

// bool compareByStartYear(Filme* a, Filme* b) {
//     return a->getStartYear() < b->getStartYear();
// }
bool compareByEndYear(Filme* a, Filme* b) {
    return a->getEndYear() < b->getEndYear();
}


bool compareByRuntime(Filme* a, Filme* b) {
    return a->getRuntimeMinutes() < b->getRuntimeMinutes();
}





int main() {
    std::string nomeArquivo = "filmesCrop1.txt";
    std::vector<Filme> filmes = lerArquivoFilmes(nomeArquivo);

    SortFilmes sort(filmes);
    sort.atualizar();

    std::cout << "Antes da ordenação:\n";
    sort.imprimirFilmes();

    // Ordenar filmes por título original
    sort.originalTitleArrayPtr = sort.merge_sort(sort.startYearArrayPtr, compareByStartYear);

    std::cout << "Após a ordenação por título original:\n";
    sort.imprimirFilmes();

    // // Buscar filmes por gênero
    // std::string generoParaBuscar = "Action"; // Gênero que você quer buscar
    // std::vector<Filme*> filmesEncontrados = sort.buscaPorGenero(generoParaBuscar);

    // std::cout << "Filmes encontrados com o gênero '" << generoParaBuscar << "':\n";
    // if (filmesEncontrados.empty()) {
    //     std::cout << "Nenhum filme encontrado com o gênero '" << generoParaBuscar << "'.\n";
    // } else {
    //     for (auto& filme : filmesEncontrados) {
    //         std::cout << "ID: " << filme->getTconst() << "\n"
    //                   << "Título Original: " << filme->getOriginalTitle() << "\n"
    //                   << "Gêneros: ";
    //         for (const auto& genero : filme->getGenres()) {
    //             std::cout << genero << " ";
    //         }
    //         std::cout << "\n\n";
    //     }
    // }

    return 0;
}
