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
std::vector<std::string> buscarCinemasPorTitleType(ManipularCinema& manipular, SortFilmes& sort, std::string tipo, std::vector<FilmesEmCartaz>& filmesParaPesquisa) {
    std::vector<std::string> cinemasComTipos;

    // Busca os filmes pelo tipo
    std::vector<Filme*> filmesEncontrados = sort.buscaBinariaMultiplosResultados(sort.titleTypeArrayPtr, tipo, &Filme::getTitleType);

    // Verifica os filmes encontrados e relaciona com os cinemas
    for (const auto& filme : filmesEncontrados) {
        for (const auto& filmesNapesquisa : filmesParaPesquisa) {


            // std::cout<< filme->getTconst()<<"\n";
            // std::cout<< filmesNapesquisa.filmedocinema.tconst<<"\n";
              
            if (filme->getTconst() == filmesNapesquisa.filmedocinema.tconst ) {

                  

                cinemasComTipos.push_back(filmesNapesquisa.cinema_ID_Struct);
            }
        }
    }

    // Remover duplicatas, se necessário
    std::sort(cinemasComTipos.begin(), cinemasComTipos.end());
    cinemasComTipos.erase(std::unique(cinemasComTipos.begin(), cinemasComTipos.end()), cinemasComTipos.end());

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


std::vector<Filme*> buscarPorAno(SortFilmes& sort, int anoInicio, int anoFim) {
    std::vector<Filme*> filmesComAno;
    for (const auto& filme : sort.startYearArrayPtr) {
        int ano = filme->getStartYear();
        if (ano >= anoInicio && ano <= anoFim) {
            filmesComAno.push_back(filme);
        }
    }
    return filmesComAno;
}




int main() {
    // Nome dos arquivos
    std::string nomeArquivoFilmes = "filmesCrop1.txt";
    std::string nomeArquivoCinemas = "cinemas.txt";

    // Ler e processar os filmes
    std::vector<Filme> filmes = lerArquivoFilmes(nomeArquivoFilmes);
    SortFilmes sort(filmes);
    sort.atualizar();

    // Ordenar os vetores de ponteiros na main
    sort.titleTypeArrayPtr = sort.merge_sort(sort.titleTypeArrayPtr, compareByTitleType);
    sort.genresArrayPtr = sort.merge_sort(sort.genresArrayPtr, compareByGenres);
    sort.runtimeMinutesArrayPtr = sort.merge_sort(sort.runtimeMinutesArrayPtr, compareByRuntimeMinutes);
    sort.startYearArrayPtr = sort.merge_sort(sort.startYearArrayPtr, compareByStartYear);

    // Ler e processar os cinemas
    std::vector<FilmesEmCartaz> filmesParaPesquisa;
    std::vector<Cinema> cinemas = lerArquivoCinema(nomeArquivoCinemas, filmesParaPesquisa);
    ManipularCinema manipular;
    manipular.cinemas = cinemas; // Atribuindo o vetor de cinemas à instância de ManipularCinema

    // Atualizar a lista de filmes em cartaz no ManipularCinema
    manipular.atualizarCinema(nomeArquivoFilmes);

    // // Definir tipos de filmes a serem pesquisados
    // std::string tipo = "tvEpisode";

    // int buscasimounao = 0;
    // std::cout << "Digite 1 para buscar: ";
    // std::cin >> buscasimounao;

    // if (buscasimounao == 1) {
    //     // Chamada da função buscarCinemasPorTitleType
    //     std::vector<std::string> cinemasEncontrados = buscarCinemasPorTitleType(manipular, sort, tipo, filmesParaPesquisa);

    //     // Imprimir os cinemas encontrados
    //     //std::cout << "Cinemas que exibem filmes do tipo '" << tipo << "':\n";
  
    //         std::cout << "banana"<<cinemasEncontrados.size();
        
    // }

    // int anoInicio = 2017;
    // int anoFim = 2018;
    // std::vector<Filme*> resultadosPorAno = buscarPorAno(sort, anoInicio, anoFim);

    // // Imprimir os resultados finais
    // std::cout << "Filmes encontrados entre " << anoInicio << " e " << anoFim << ": " << resultadosPorAno.size() << "\n";
    // for (const auto filme : resultadosPorAno) {
    //     std::cout << "ID: " << filme->getEndYear() << ", Título: " << filme->getPrimaryTitle() << "\n";
    // }

    std::cout << "Conteúdo de filmesParaPesquisa: " << filmesParaPesquisa.size() << "\n";
    for (const FilmesEmCartaz& filmeEmCartaz : filmesParaPesquisa) {
      
        std::cout << "Filme tconst: " << filmeEmCartaz.filmedocinema.tconst << std::endl;
     }

    return 0;
}
