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
std::vector<const Cinema*> buscarCinemasPorTitleType(ManipularCinema& manipular, SortFilmes& sort, std::string tipo) {


    std::vector<const Cinema*> cinemasComTipos;

        std::vector<Filme*> filmesEncontrados = sort.buscaBinariaMultiplosResultados(sort.titleTypeArrayPtr, tipo, &Filme::getTitleType);
    
    for (const auto& cine : manipular.cinemas) {
         auto filmesEmExibicao = cine.getFilmesEmExibicao();
          
                // Verificando filme exibido
                    for (const auto& filme : filmesEncontrados) {
                        for(const auto& filmeExibido : filmesEmExibicao){

                            if (filme->getTconst() == filmeExibido) {
                            cinemasComTipos.push_back(&cine);
                            break;
                           
                    }


                 }
                      
                     
            }

        }
    

    // //Remover duplicatas, se necessário
    // std::sort(cinemasComTipos.begin(), cinemasComTipos.end());
    // cinemasComTipos.erase(std::unique(cinemasComTipos.begin(), cinemasComTipos.end()), cinemasComTipos.end());

    // Debugging: Imprimir a quantidade final de cinemas encontrados
    std::cout << "Total de cinemas encontrados: " << cinemasComTipos.size() << "\n";

    return cinemasComTipos;
}


// Função para buscar cinemas por tipos de filmes
std::vector<const Cinema*> buscarCinemasPorGenero(ManipularCinema& manipular, SortFilmes& sort, std::string genero) {


    std::vector<const Cinema*> cinemasComGenero;

        std::vector<Filme*> filmesEncontrados = sort.buscarPorGeneroBinario(genero);
    
    for (const auto& cine : manipular.cinemas) {
         auto filmesEmExibicao = cine.getFilmesEmExibicao();
          
                // Verificando filme exibido
                    for (const auto& filme : filmesEncontrados) {
                        for(const auto& filmeExibido : filmesEmExibicao){

                            if (filme->getTconst() == filmeExibido) {//tenho que mexer nessa comparacao.
                                std::cout<<"entrou";
                            cinemasComGenero.push_back(&cine);
                            break;
                           
                    }


                 }
                      
                     
            }

        }
    

    // //Remover duplicatas, se necessário
    // std::sort(cinemasComTipos.begin(), cinemasComTipos.end());
    // cinemasComTipos.erase(std::unique(cinemasComTipos.begin(), cinemasComTipos.end()), cinemasComTipos.end());

    // Debugging: Imprimir a quantidade final de cinemas encontrados
    std::cout << "Total de cinemas encontrados: " << cinemasComGenero.size() << "\n";

    return cinemasComGenero;
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
    std::string tipo = "tvEpisode";



        // Ordenar os filmes por titleType
//     sort.titleTypeArrayPtr = sort.merge_sort(sort.titleTypeArrayPtr, compareByTitleType);

//     int buscasimounao=0;
//     std::cout<<"digite 1 para buscar";
//     std::cin>>buscasimounao;
//     if(buscasimounao==1){
//  std::vector<const Cinema*> cinemasEncontrados = buscarCinemasPorTitleType(manipular, sort, tipo);

//     }
 sort.titleTypeArrayPtr = sort.merge_sort(sort.genresArrayPtr, compareByGenres);

    std::string genero ="Short";
        int buscasimounao=0;
    std::cout<<"digite 1 para buscar";
    std::cin>>buscasimounao;
        std::vector<Filme*> resultados;

    if(buscasimounao==1){
std::vector<const Cinema*> cinemasEncontrados = buscarCinemasPorGenero(manipular, sort, genero);
// std::vector<Filme*> resultados = sort.buscarPorGeneroBinario(genero);

//     // Print the results
//     std::cout << "Filmes com o gênero " << genero << ":" << std::endl;
//     for (auto& filme : resultados) {
//         std::cout << "ID: " << filme->getTconst() << std::endl;
//         std::cout << "Título Original: " << filme->getOriginalTitle() << std::endl;
//         std::cout << "Gêneros: ";
//         for (const auto& g : filme->getGenres()) {
//             std::cout << g << " ";
//         }
//         std::cout << std::endl;
//         std::cout << "Ano de Início: " << filme->getStartYear() << std::endl;
//         std::cout << std::endl;
//     }


    }
   
   
    //     manipular.merge_sort(manipular.Preco, compareByPreco);
    //  std::vector<Cinema*> cinemasComPrecoAteLimite= manipular.buscarCinemasPorPreco(12.50);

    //  for(const auto& cines : cinemas ){
    //     std::cout << cines.getCinemaID() << std::endl;
    //     std::cout << cines.getCoordenadaX() << std::endl;
    //     std::cout << cines.getCoordenadaY() << std::endl;
    //     std::cout << cines.getNomeDoCinema() << std::endl;
    //     std::cout << cines.getPrecoIngresso() << std::endl;


    //  //}

    //  }
    return 0;
}