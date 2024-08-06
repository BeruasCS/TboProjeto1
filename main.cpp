
#include <iostream>
#include <vector>
#include "Filme.hpp"
#include "SortFilmes.hpp"


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


bool compareByEndYear(Filme* a, Filme* b) {
    return a->getEndYear() < b->getEndYear();
}


bool compareByRuntime(Filme* a, Filme* b) {
    return a->getRuntimeMinutes() < b->getRuntimeMinutes();
}



int main() {
    std::string nomeArquivo = "filmesCrop1.txt";
    std::vector<Filme> filmes = lerArquivoFilmes(nomeArquivo);

    // Criar instância de SortFilmes
    SortFilmes sort(filmes);

    // Atualizar os vetores de ponteiros
    sort.atualizar();

    // Imprimir filmes antes da ordenação
    std::cout << "Antes da ordenação:\n";
    sort.imprimirFilmes();

    // Ordenar filmes por título original
    sort.originalTitleArrayPtr = sort.merge_sort(sort.originalTitleArrayPtr, compareByOriginalTitle);

    // Imprimir filmes após a ordenação
    std::cout << "Após a ordenação por título original:\n";
    sort.imprimirFilmes();

    return 0;
}
