#include <iostream>
#include <vector>
#include "Filme.hpp"
#include "SortFilmes.hpp"
#include "Cinema.hpp"

// Funções de comparação
// bool compareByOriginalTitle(Filme* a, Filme* b) {
//     return a->getOriginalTitle() < b->getOriginalTitle();
// }

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

    // Ordenar filmes por ano de início
    std::cout << "\nprestes a fazer sort\n" ;
    sort.startYearArrayPtr = sort.merge_sort(sort.startYearArrayPtr, compareByStartYear);
    std::cout << "sort feito\n";

    int seleciona = 0;
    int seleciona1 = 0;

    std::cout << "\ndigite 1 para buscar\n";
    std::cin >> seleciona;
    if (seleciona == 1) {
        // Realizar a busca binária para múltiplos resultados
        int anoParaBuscar = 2017; // Coloque o ano que deseja buscar
        std::cout << "\nindo fazer a busca\n";
        std::vector<Filme*> filmesEncontrados = sort.buscaBinariaMultiplosResultados(sort.startYearArrayPtr, anoParaBuscar, &Filme::getStartYear);
        std::cout << "\nbusca feita\n";

        std::cout << "\ndigite 1 para imprimir a busca\n";
        std::cin >> seleciona1;

        if (seleciona1 == 1) {
            if (filmesEncontrados.empty()) {
                std::cout << "\nimprimindo busca\n";
                std::cout << "Nenhum filme encontrado com o ano de início " << anoParaBuscar << ".\n";
            } else {
                std::cout << "Filmes encontrados com o ano de início " << anoParaBuscar << ":\n";
                for (auto& filme : filmesEncontrados) {
                    std::cout << "ID: " << filme->getTconst() << "\n"
                              << "Título Original: " << filme->getOriginalTitle() << "\n"
                              << "Ano de Início: " << filme->getStartYear() << "\n\n";
                }
            }
        } else {
            return 0;
        }
    } 

    // Exemplo de criação e impressão de um Cinema
    std::vector<std::string> filmesEmExibicao = {"tt0012349", "tt0023456", "tt0034567"}; // IDs dos filmes
    Cinema cinema("001", "Cinema XYZ", 50, 100, 15.5, filmesEmExibicao);

    std::cout << "\nCinema ID: " << cinema.getCinemaID() << "\n"
              << "Nome do Cinema: " << cinema.getNomeDoCinema() << "\n"
              << "Coordenada X: " << cinema.getCoordenadaX() << "\n"
              << "Coordenada Y: " << cinema.getCoordenadaY() << "\n"
              << "Preço do Ingresso: " << cinema.getPrecoIngresso() << "\n"
              << "Filmes em Exibição:\n";
    for (const auto& filme : cinema.getFilmesEmExibicao()) {
        std::cout << "- " << filme << "\n";
    }

    return 0;
}
