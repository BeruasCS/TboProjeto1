#include <iostream>
#include <cmath> // Para std::sqrt e std::pow
#include <vector>
#include "Filme.hpp"
#include "SortFilmes.hpp"
#include "Cinema.hpp"
#include "ManipularCinema.hpp"

// Funções de comparação
bool compareByTitleType(Filme* a, Filme* b) {
    return a->getTitleType() < b->getTitleType();
}
bool compareByEndYear(Filme* a, Filme* b) {
    return a->getEndYear() < b->getEndYear();
}
bool compareByGenres(Filme* a, Filme* b) {
    return a->getGenres() < b->getGenres();
}
bool compareByIsAdult(Filme* a, Filme* b) {
    return a->getIsAdult() < b->getIsAdult();
}
bool compareByOriginalTitle(Filme* a, Filme* b) {
    return a->getOriginalTitle() < b->getOriginalTitle();
}
bool compareByPrimaryTitle(Filme* a, Filme* b) {
    return a->getPrimaryTitle() < b->getPrimaryTitle();
}
bool compareByRuntimeMinutes(Filme* a, Filme* b) {
    return a->getRuntimeMinutes() < b->getRuntimeMinutes();
}
bool compareByStartYear(Filme* a, Filme* b) {
    return a->getStartYear() < b->getStartYear();
}
bool compareByTconst(Filme* a, Filme* b) {
    return a->getTconst() < b->getTconst();
}
bool compareByPreco(Cinema* a, Cinema* b) {
    return a->getPrecoIngresso() < b->getPrecoIngresso();
}


// Função para buscar cinemas por tipos de filmes
std::vector<const Cinema*> buscarCinemasPorTitleType(ManipularCinema& manipular, SortFilmes& sort, const std::vector<std::string>& tipos) {

    
    // Ordenar os filmes por titleType
    sort.titleTypeArrayPtr = sort.merge_sort(sort.titleTypeArrayPtr, compareByTitleType);

    std::vector<const Cinema*> cinemasComTipos;

    for (const auto& tipo : tipos) {
        // Realizar a busca binária para encontrar os filmes com o titleType especificado
        std::vector<Filme*> filmesEncontrados = sort.buscaBinariaMultiplosResultados(sort.titleTypeArrayPtr, tipo, &Filme::getTitleType);
        
        // // Debugging: Imprimir quantidade de filmes encontrados
        // std::cout << "Filmes encontrados para tipo " << tipo << ": " << filmesEncontrados.size() << "\n";
        // for (const auto& filme : filmesEncontrados) {
        //     std::cout << "  Filme encontrado: " << filme->getTconst() << "\n";
        // }

    for (const auto& cine : manipular.cinemas) {
        
            //filmes em exibicao e um vector do tipo string
           auto filmesEmExibicao = cine.getFilmesEmExibicao();
        //    std::cout << "Total de filmes em exibição no cinema " << cine.getNomeDoCinema() << ": " << filmesEmExibicao.size() << std::endl;

                
            for (const auto& filmeExibido : filmesEmExibicao) {
                // std::cout << " entrou nesse for aqui";
                // std::cout << " ";
                // std::cout << "tconst:" << filmeExibido<< "\n"; // Imprimir todos os tconst
            

            }

                // Verificando filme exibido
                    for (const auto& filme : filmesEncontrados) {
                        for(const auto& filmeExibido : filmesEmExibicao){

                            std::cout << filme->getTconst() << std::endl;
                            std::cout << filmeExibido << std::endl;


                            if (filme->getTconst() == filmeExibido) {
                          std::cout << "banana";
                            std::cout << "Cinema " << cine.getNomeDoCinema() << " contém o filme com tconst " << filme->getTconst() << "\n";
                            cinemasComTipos.push_back(&cine);
                           
                        }


                    }
                        
                // std::cout << "  Filme encontrado: " << filme->getTconst() << "\n";
    
                // std::cout << "tconst:" << filmeExibido<< "\n"; // Imprimir todos os tconst
                     
                     
                    }

        }
    }

    // Remover duplicatas, se necessário
    // std::sort(cinemasComTipos.begin(), cinemasComTipos.end());
    // cinemasComTipos.erase(std::unique(cinemasComTipos.begin(), cinemasComTipos.end()), cinemasComTipos.end());

    // Debugging: Imprimir a quantidade final de cinemas encontrados
    std::cout << "Total de cinemas encontrados: " << cinemasComTipos.size() << "\n";

    return cinemasComTipos;
}








int main() {
    // Nome dos arquivos
    std::string nomeArquivoFilmes = "filmesCrop1.txt";
    std::string nomeArquivoCinemas = "cinemas.txt";

    // Ler e processar os filmes
    std::vector<Filme> filmes = lerArquivoFilmes(nomeArquivoFilmes);
    SortFilmes sort(filmes);
    sort.atualizar();

    // Ler e processar os cinemas
    std::vector<Cinema> cinemas = lerArquivoCinema(nomeArquivoCinemas);
    ManipularCinema manipular;
    manipular.cinemas = cinemas; // Atribuindo o vetor de cinemas à instância de ManipularCinema

   // Atualizar a lista de filmes em cartaz no ManipularCinema
    manipular.atualizarCinema(nomeArquivoFilmes);

   // Definir tipos de filmes a serem pesquisados
    std::vector<std::string> tipos = {"tvEpisode"};

    //Chamar a função de busca
    std::vector<const Cinema*> cinemasEncontrados = buscarCinemasPorTitleType(manipular, sort, tipos);

    //     manipular.merge_sort(manipular.Preco, compareByPreco);
    //  std::vector<Cinema*> cinemasComPrecoAteLimite= manipular.buscarCinemasPorPreco(12.50);

     for(const auto& cines : cinemas ){
        std::cout << cines.getCinemaID() << std::endl;
        std::cout << cines.getCoordenadaX() << std::endl;
        std::cout << cines.getCoordenadaY() << std::endl;
        std::cout << cines.getNomeDoCinema() << std::endl;
        std::cout << cines.getPrecoIngresso() << std::endl;


     //}

     }
    return 0;
}