#include <iostream>
#include <vector>
#include "Filme.hpp"
#include "SortFilmes.hpp"
#include "Cinema.hpp"
#include "ManipularCinema.hpp"

// Funções de comparação
bool compareByTitleType(Filme* a, Filme* b) {
    return a->getTitleType() < b->getTitleType();
}

// Função para buscar cinemas por tipos de filmes
std::vector<const Cinema*> buscarCinemasPorTitleType(ManipularCinema& manipular, SortFilmes& sort, const std::vector<std::string>& tipos) {
    // Ordenar os filmes por titleType
    sort.titleTypeArrayPtr = sort.merge_sort(sort.titleTypeArrayPtr, compareByTitleType);

    std::vector<const Cinema*> cinemasComTipos;

    for (const auto& tipo : tipos) {
        // Realizar a busca binária para encontrar os filmes com o titleType especificado
        std::vector<Filme*> filmesEncontrados = sort.buscaBinariaMultiplosResultados(sort.titleTypeArrayPtr, tipo, &Filme::getTitleType);
        
        // Debugging: Imprimir quantidade de filmes encontrados
        std::cout << "Filmes encontrados para tipo " << tipo << ": " << filmesEncontrados.size() << "\n";
        for (const auto& filme : filmesEncontrados) {
            std::cout << "  Filme encontrado: " << filme->getTconst() << "\n";
        }

    for (const auto& cine : manipular.cinemas) {
        
            
           auto filmesEmExibicao = cine.getFilmesEmExibicao();
           std::cout << "Total de filmes em exibição no cinema " << cine.getNomeDoCinema() << ": " << filmesEmExibicao.size() << std::endl;

                
            for (const auto& filmeExibido : filmesEmExibicao) {
                // std::cout << " entrou nesse for aqui";
                std::cout << " ";
                std::cout << "tconst:" << filmeExibido<< "\n"; // Imprimir todos os tconst
            }

            
        //     for (const auto& filmeExibido : filmesEmExibicao) {
        //         std::cout << "    Verificando filme exibido: " << filmeExibido << "\n";
        //         for (const auto& filme : filmesEncontrados) {
        //             std::cout << "      Comparando com filme encontrado: " << filme->getTconst() << "\n";
        //             if (filme->getTconst() == filmeExibido) {
        //                 std::cout << "Cinema " << cinema.getNomeDoCinema() << " contém o filme com tconst " << filme->getTconst() << "\n";
        //                 cinemasComTipos.push_back(&cinema);
        //                 break;
        //             }
        //         }
        //     }
        }
    }

    // Remover duplicatas, se necessário
    std::sort(cinemasComTipos.begin(), cinemasComTipos.end());
    cinemasComTipos.erase(std::unique(cinemasComTipos.begin(), cinemasComTipos.end()), cinemasComTipos.end());

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
    std::vector<std::string> tipos = {"tvSeries"};

    //Chamar a função de busca
    std::vector<const Cinema*> cinemasEncontrados = buscarCinemasPorTitleType(manipular, sort, tipos);

    // Exibir resultados
    // std::cout << "Cinemas que contêm filmes dos tipos especificados:\n";
    // for (const auto& cinema : cinemasEncontrados) {
    //     std::cout << "ID do Cinema: " << cinema->getCinemaID() << "\n"
    //               << "Nome do Cinema: " << cinema->getNomeDoCinema() << "\n"
    //               << "Coordenada X: " << cinema->getCoordenadaX() << "\n"
    //               << "Coordenada Y: " << cinema->getCoordenadaY() << "\n"
    //               << "Preço do Ingresso: " << cinema->getPrecoIngresso() << "\n\n";
    // }

    // Imprimir filmes em exibição para cada cinema
    // std::cout << "Filmes em exibição para cada cinema:\n";
    // for (const auto& cinema : cinemas) {
    //     std::cout << "Cinema: " << cinema.getNomeDoCinema() << "\n";
    //     const auto& filmesEmExibicao = cinema.getFilmesEmExibicao();
    //     std::cout << "Filmes em exibição:\n";
    //     for (const auto& filme : filmesEmExibicao) {
    //         std::cout << "  " << filme << "\n";
    //     }
    //     std::cout << "\n";
    // }

    return 0;
}