#include <iostream>
#include <chrono>
#include <cmath> // Para std::sqrt e std::pow
#include <vector>
#include <set>
#include "Filme.hpp"
#include "SortFilmes.hpp"
#include "Cinema.hpp"
#include "ManipularCinema.hpp"

// Funções de comparação
bool compareByTitleType(Filme *a, Filme *b)
{
    return a->getTitleType() < b->getTitleType();
}
bool compareByEndYear(Filme *a, Filme *b)
{
    return a->getEndYear() < b->getEndYear();
}
bool compareByGenres(Filme *a, Filme *b)
{
    return a->getGenres() < b->getGenres();
}
bool compareByIsAdult(Filme *a, Filme *b)
{
    return a->getIsAdult() < b->getIsAdult();
}
bool compareByOriginalTitle(Filme *a, Filme *b)
{
    return a->getOriginalTitle() < b->getOriginalTitle();
}
bool compareByPrimaryTitle(Filme *a, Filme *b)
{
    return a->getPrimaryTitle() < b->getPrimaryTitle();
}
bool compareByRuntimeMinutes(Filme *a, Filme *b)
{
    return a->getRuntimeMinutes() < b->getRuntimeMinutes();
}
bool compareByStartYear(Filme *a, Filme *b)
{
    return a->getStartYear() < b->getStartYear();
}
// bool comparerByTconst(Filme *a, Filme *b)
// {
//     return a->getTconst() < b->getTconst();
// }
// bool compareByPreco(Cinema *a, Cinema *b)
// {
//     return a->getPrecoIngresso() < b->getPrecoIngresso();
// }
void removeCharacter(std::string &str, char charToRemove)
{
    str.erase(remove(str.begin(), str.end(), charToRemove), str.end());
}

int binarySearchTconst(const std::vector<Filme *> &filmes, const std::string &tconst)
{
    int high = 0;
    int low = filmes.size() - 1;

    while (high <= low)
    {
        int meio = high + (low - high) / 2;

        // Obtemos o tconst do filme no meio
        std::string tconstMeio = filmes[meio]->getTconst();

        // Verifica se o tconst no meio é o procurado
        if (tconstMeio == tconst)
        {
            return meio;
        }
        // caso tconst procurado for menor buscamos pela metade high
        else if (tconst < tconstMeio)
        {
            low = meio - 1;
        }
        // caso tconst procurado for maior se busca pela metade direita
        else
        {
            high = meio + 1;
        }
    }

    return -576;
}



std::vector<Filme*> combinarE(const std::vector<Filme*>& vetor1, const std::vector<Filme*>& vetor2) {
    // Cria sets a partir dos vetores para realizar a interseção
    std::set<Filme*> set1(vetor1.begin(), vetor1.end());
    std::set<Filme*> set2(vetor2.begin(), vetor2.end());

    // Vetor para armazenar a interseção
    std::vector<Filme*> intersecao;

    // Realiza a interseção
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                          std::back_inserter(intersecao));

    return intersecao;
}


// Função de combinação "OU"
template <typename T>
std::vector<T *> combinarOu(const std::vector<T *> &v1, const std::vector<T *> &v2)
{
    std::set<T *> resultadoSet(v1.begin(), v1.end());
    resultadoSet.insert(v2.begin(), v2.end());
    return std::vector<T *>(resultadoSet.begin(), resultadoSet.end());
}

// Função para exibir o menu principal
void exibirMenuPrincipal()
{
    std::cout << "O que deseja buscar?\n";
    std::cout << "0: Filmes\n";
    std::cout << "1: Cinemas\n";
}

// Função para exibir o menu de buscas
void exibirMenuBusca()
{
    std::cout << "Qual busca deseja fazer?\n";
    std::cout << "1. Filmes de um ou mais tipos (coluna titleType).\n";
    std::cout << "2. Filmes que pertencem a um ou mais gêneros (coluna genres).\n";
    std::cout << "3. Filmes com uma duração específica entre um limite inferior e superior em minutos.\n";
    std::cout << "4. Filmes lançados em um ano específico ou em um intervalo de anos.\n";
}
void exibirMenuBuscaCinemas()
{

    // 1. Cinemas que contém filmes de um ou mais tipos (coluna titleType).
    // 2. Cinemas que contém filmes que pertencem a um ou mais gêneros (coluna
    // genres).
    // 3. Cinemas que contém filmes com uma duração específica entre um limite inferior e superior em minutos.
    // 4. Cinemas em uma localização de até uma distância definida de um local.
    // 5. Cinemas com preços até um limite superior de unidades monetárias.
    // 6. Cinemas que contém filmes lançados em um ano específico ou em um
    // intervalo de anos.
    std::cout << "Qual busca deseja fazer?\n";
    std::cout << "1. Cinemas que contém filmes de um ou mais tipos (coluna titleType).\n";
    std::cout << "2. Cinemas que contém filmes que pertencem a um ou mais gêneros (colunagenres).\n";
    std::cout << "3. Cinemas que contém filmes com uma duração específica entre um limite inferior e superior em minutos.\n";
    std::cout << "4. Cinemas em uma localização de até uma distância definida de um local.\n";
    std::cout << "5. Cinemas com preços até um limite superior de unidades monetárias.";
    std::cout << "6. Cinemas que contém filmes lançados em um ano específico ou em um intervalo de anos.\n";
}

void exibirMenuCombinar() { std::cout << "Deseja aplicar mais filtros? (Sim - 0 / Não - 1): "; }

// Função para exibir o menu de combinação "E" ou "ou"
void exibirMenuLogica() { std::cout << "Escolha a operação lógica (E - 0 / OU - 1): "; }

int main()
{

    std::cout << "Inicializando programa...\n";
    std::string nomeArquivoFilmes = "filmesCrop.txt";
    std::string nomeArquivoCinema = "cinemas.txt";
    std::vector<FilmesEmCartaz> filmesemcartaz;

    std::cout << "executada essa parte";

    //  std::cout << filmes.size();
    std::cout << "Programa inicializado\n";

    int continuar = 0;
    std::vector<Filme *> resultados;

    // Configuração inicial
    std::vector<std::vector<Filme>> filmesPorGenero;

    std::vector<Filme> filmes;
    SortFilmes sortFilmes(filmes);
    sortFilmes.lerArquivoFilmes(nomeArquivoFilmes, filmesPorGenero);
    sortFilmes.atualizar(); // Carrega e ordena os filmes
    sortFilmes.merge_sort(sortFilmes.titleTypeArrayPtr, compareByTitleType);
    sortFilmes.merge_sort(sortFilmes.runtimeMinutesArrayPtr, compareByRuntimeMinutes);
    sortFilmes.merge_sort(sortFilmes.startYearArrayPtr, compareByStartYear);
    sortFilmes.merge_sort(sortFilmes.genresArrayPtr, compareByGenres);

    std::vector<Cinema> cinemas;
    Cinema cinemaHandler(cinemas);
    cinemaHandler.lerArquivoCinema(nomeArquivoCinema);

    std::vector<Filme *> resultadosFilmes;
    std::vector<Cinema *> resultadosCinemas;
    int contadorFilmes=0;

    while (continuar==0)
    {
        exibirMenuPrincipal();
        int escolha;
        std::cin >> escolha;

        if (escolha == 0) // Busca de filmes
        {
                int operadorLogico;
                exibirMenuBusca();
                int tipoBusca;
                std::cin >> tipoBusca;

                std::vector<Filme *> novosResultados;

                if(contadorFilmes>=1){


                  

                    novosResultados= resultadosFilmes;

                    exibirMenuLogica();

                    std::cin>>operadorLogico;

                }

  switch (tipoBusca)
            {
            case 1:
            {
                std::string tipo;
                std::cout << "Digite o(s) tipo(s) de filme(s): ";
                std::cin >> tipo;
                resultadosFilmes = sortFilmes.buscaLinearMultiplosResultados(
                    sortFilmes.titleTypeArrayPtr, tipo, &Filme::getTitleType);
                resultadosFilmes.size();
                for (const auto x : resultadosFilmes)
                {
                    x->getTitleType();
                }

                break;
            }
            case 2:
            { // Busca por gênero de filme
                std::string genero;
                std::cout << "Digite o gênero de filme: ";
                std::cin >> genero;

                int genreIndex = sortFilmes.getGenreIndex(genero);
                if (genreIndex != -1 && !filmesPorGenero[genreIndex].empty())
                {
                    for (auto &filme : filmesPorGenero[genreIndex])
                    {
                        resultadosFilmes.push_back(&filme);
                    }
                }
                else
                {
                    std::cout << "Nenhum filme encontrado para o gênero " << genero << "\n";
                }

                break;
            }
            case 3:
            {
                int minDuracao, maxDuracao;
                std::cout << "Digite a duração mínima em minutos: ";
                std::cin >> minDuracao;
                std::cout << "Digite a duração máxima em minutos: ";
                std::cin >> maxDuracao;

                std::vector<Filme *> Duracao = sortFilmes.runtimeMinutesArrayPtr;

                // Percorrer o vetor Duracao
                for (auto &film : Duracao)
                {
                    // Verifica se o runtimeMinutes do filme está dentro do intervalo
                    if (film->getRuntimeMinutes() >= minDuracao && film->getRuntimeMinutes() <= maxDuracao)
                    {
                        resultadosFilmes.push_back(film);
                    }
                }

                // Agora, buscaResultados contém todos os filmes dentro do intervalo de duração
                break;
            }
            case 4:
            {
                std::vector<Filme *> startYearArrayPtr = sortFilmes.startYearArrayPtr;
                int anoInicio;
                std::cout << "Digite o ano de início: ";
                std::cin >> anoInicio;

                for (const auto filme : startYearArrayPtr)
                {
                    // Verifica se o filme tem um startYear e endYear válidos
                    bool temStartYearValido = filme->getStartYear() != -11 && filme->getStartYear() != 0;

                    // Verifica se o filme está completamente dentro do intervalo de anos
                    bool dentroDoIntervalo = (temStartYearValido && filme->getStartYear() >= anoInicio);

                    // Inclui o filme se estiver completamente dentro do intervalo
                    if (dentroDoIntervalo)
                    {
                        resultadosFilmes.push_back(filme);
                    }
                }

                // Agora, buscaResultados contém todos os filmes dentro do intervalo de anos
                break;
            }
            default:
                std::cout << "Opção inválida\n";
                continue;
            }

                if(contadorFilmes>=1){
                
                    std::vector<Filme *> aux;
                    aux.clear();

                    if(operadorLogico==0){
                        std::cout<<"entramos nessa parte aqui ooooooooooooooooooooooooooo"<<"\n";
                        std::cout<<resultadosFilmes.size();
                        std::cout<<novosResultados.size();

                        aux =combinarE(novosResultados, resultadosFilmes);
                        resultadosFilmes=aux;
                    }
                    if(operadorLogico==1){

                        aux=combinarOu(novosResultados, resultadosFilmes);
                        resultadosFilmes=aux;

                    }


                }
          
            // Exibe resultados finais
            for (auto filme : resultadosFilmes)
            {
                std::cout << "ID: " << filme->getTconst() << "\n";
                std::cout << "Titulo primario: " << filme->getPrimaryTitle() << "\n";
            }


                contadorFilmes++;
        }
        else if (escolha == 1) // Busca de cinemas
        {
            bool aplicarFiltros = true;
            while (aplicarFiltros)
            {
                exibirMenuBuscaCinemas();
                int tipoBusca;
                std::cin >> tipoBusca;

                std::vector<Cinema *> novosResultados;

                // Realiza a busca específica
                if (tipoBusca == 1)
                { /* Código para buscar cinemas por tipo de filme */
                    // // 1. Cinemas que contém filmes de um ou mais tipos (coluna titleType).
                    // std::string tipo;
                    // std::cout << "Digite o(s) tipo(s) de filme(s): ";
                    // std::cin >> tipo;

                    // // Itera sobre cada cinema
                    // int indexCinema;
                    // Filme filmeDoCinema;
                    // for (const auto &cinemaASeAnalisar : cinemas)
                    // {
                    //     for (const auto &filmeEmCinema : cinemaASeAnalisar.Filmes_Em_Exibicao)
                    //     {
                    //         indexCinema = sortFilmes.hashTconst(filmeEmCinema);
                    //         filmeDoCinema = sortFilmes.buscarFilme(indexCinema);

                    //         if (filmeDoCinema.getTitleType() == tipo)
                    //         {
                    //             // Adiciona o cinema ao vetor de resultados
                    //             resultadosCinemas.push_back(cinemaASeAnalisar);

                    //             // Imprime o cinema e o filme correspondente
                    //             // std::cout << "Cinema: " << cinemaASeAnalisar.Nome_do_Cinema << std::endl;
                    //             // std::cout << "Filme: " << filmeEmCinema << std::endl;

                    //             // Opcional: interrompe o loop para evitar duplicações de cinema no vetor
                    //             break;
                    //         }
                    //     }
                    // }

                    // // Exibir todos os cinemas encontrados
                    // std::cout << "Cinemas encontrados:" << std::endl;
                    // for (const auto &resultadoCinema : resultadosCinemas)
                    // {
                    //     std::cout << "nome do cinema: " << resultadoCinema.Nome_do_Cinema << std::endl;
                    // }

                    // break;
                }
                else if (tipoBusca == 2)
                { /* Código para buscar cinemas por gênero de filme */

                    // std::string genero;
                    // std::cout << "Digite o genero do filme: ";
                    // std::cin >> genero;

                    // // Itera sobre cada cinema
                    // int indexCinema;
                    // Filme filmeDoCinema;
                    // int genreIndex = sortFilmes.getGenreIndex(genero);

                    // // Iterando sobre os cinemas
                    // for (const auto &cinemaASeAnalisar : cinemas)
                    // {
                    //     bool cinemaAdicionado = false;

                    //     // Iterando sobre os filmes de cada cinema
                    //     for (const auto &filmeEmCinema : cinemaASeAnalisar.Filmes_Em_Exibicao)
                    //     {
                    //         indexCinema = sortFilmes.hashTconst(filmeEmCinema);
                    //         filmeDoCinema = sortFilmes.buscarFilme(indexCinema);
                    //         if (genreIndex != -1 && !filmesPorGenero[genreIndex].empty())
                    //         {
                    //             for (auto &filme : filmesPorGenero[genreIndex])
                    //             {
                    //                 if (filmeDoCinema.getTconst() == filme.getTconst())
                    //                 {
                    //                     // Adiciona o cinema ao vetor de resultados
                    //                     buscaResultadosCinema.push_back(cinemaASeAnalisar);
                    //                     cinemaAdicionado = true; // Marca o cinema como adicionado

                    //                     break; // Sai do loop que verifica os filmes desse cinema
                    //                 }
                    //             }
                    //         }
                    //         if (cinemaAdicionado)
                    //             break; // Sai do loop de filmes do cinema atual
                    //     }
                    // }

                    // // Exibir todos os cinemas encontrados
                    // std::cout << "Cinemas encontrados:" << std::endl;
                    // for (const auto &resultadoCinema : buscaResultadosCinema)
                    // {
                    //     std::cout << "nome do cinema: " << resultadoCinema.Nome_do_Cinema << std::endl;
                    // }

                    // break;
                }
                else if (tipoBusca == 3)
                 { /* Código para buscar cinemas por duração de filme */
                //     int minDuracao, maxDuracao;
                //     std::cout << "Digite a duração mínima em minutos: ";
                //     std::cin >> minDuracao;
                //     std::cout << "Digite a duração máxima em minutos: ";
                //     std::cin >> maxDuracao;

                //     int indexCinema;
                //     Filme filmeDoCinema;
                //     for (const auto &cinemaASeAnalisar : cinemas)
                //     {
                //         for (const auto &filmeEmCinema : cinemaASeAnalisar.Filmes_Em_Exibicao)
                //         {
                //             indexCinema = sortFilmes.hashTconst(filmeEmCinema);
                //             filmeDoCinema = sortFilmes.buscarFilme(indexCinema);

                //             if (filmeDoCinema.getRuntimeMinutes() >= minDuracao && filmeDoCinema.getRuntimeMinutes() <= maxDuracao)
                //             {
                //                 // Adiciona o cinema ao vetor de resultados
                //                 buscaResultadosCinema.push_back(cinemaASeAnalisar);

                //                 // Imprime o cinema e o filme correspondente
                //                 // std::cout << "Cinema: " << cinemaASeAnalisar.Nome_do_Cinema << std::endl;
                //                 // std::cout << "Filme: " << filmeEmCinema << std::endl;

                //                 // Opcional: interrompe o loop para evitar duplicações de cinema no vetor
                //                 break;
                //             }
                //         }
                //     }
                //     // Percorrer o vetor Duracao

                //     // Exibir todos os cinemas encontrados
                //     std::cout << "Cinemas encontrados:" << std::endl;
                //     for (const auto &resultadoCinema : buscaResultadosCinema)
                //     {
                //         std::cout << "nome do cinema: " << resultadoCinema.Nome_do_Cinema << std::endl;
                //     }

                //     // Agora, buscaResultados contém todos os filmes dentro do intervalo de duração
                //     break;
                }
                else if (tipoBusca == 4)
                 { /* Código para buscar cinemas por localização */

                //     int xReferencia, yReferencia;
                //     float distanciaMaxima;

                //     std::cout << "Digite a coordenada X do ponto de referência: ";
                //     std::cin >> xReferencia;
                //     std::cout << "Digite a coordenada Y do ponto de referência: ";
                //     std::cin >> yReferencia;
                //     std::cout << "Digite a distância máxima: ";
                //     std::cin >> distanciaMaxima;

                //     std::vector<Cinema> cinemasProximos;

                //     for (const auto &cinema : cinemas)
                //     {
                //         float distancia = calcularDistancia(cinema.Coordenada_X, cinema.Coordenada_Y, xReferencia, yReferencia);

                //         if (distancia <= distanciaMaxima)
                //         {
                //             cinemasProximos.push_back(cinema);
                //         }
                //     }

                //     if (cinemasProximos.empty())
                //     {
                //         std::cout << "Nenhum cinema encontrado dentro da distância especificada.\n";
                //     }
                //     else
                //     {
                //         std::cout << "Cinemas encontrados dentro da distância especificada:\n";
                //         for (const auto &cinema : cinemasProximos)
                //         {
                //             std::cout << "Cinema ID: " << cinema.Cinema_ID << "\n";
                //             std::cout << "Nome: " << cinema.Nome_do_Cinema << "\n";
                //             std::cout << "Coordenadas: (" << cinema.Coordenada_X << ", " << cinema.Coordenada_Y << ")\n";
                //             std::cout << "Preço do Ingresso: " << cinema.Preco_Ingresso << "\n";
                //             std::cout << "Filmes em Exibição: ";
                //             for (const auto &filme : cinema.Filmes_Em_Exibicao)
                //             {
                //                 std::cout << filme << " ";
                //             }
                //             std::cout << "\n\n";
                //         }
                //     }

                //     break;
                }
                else if (tipoBusca == 5)
                {

                    // float maxPreco;
                    // std::cout << "Digite o preco maximo: ";
                    // std::cin >> maxPreco;

                    // int indexCinema;
                    // Filme filmeDoCinema;
                    // for (const auto &cinemaASeAnalisar : cinemas)
                    // {
                    //     if (cinemaASeAnalisar.Preco_Ingresso <= maxPreco)
                    //     {
                    //         // Adiciona o cinema ao vetor de resultados
                    //         buscaResultadosCinema.push_back(cinemaASeAnalisar);
                    //         // std::cout<<cinemaASeAnalisar.Nome_do_Cinema;
                    //     }
                    // }

                    // // Exibir todos os cinemas encontrados
                    // std::cout << "Cinemas encontrados:" << std::endl;
                    // for (const auto &resultadoCinema : buscaResultadosCinema)
                    // {
                    //     std::cout << "nome do cinema: " << resultadoCinema.Nome_do_Cinema << std::endl;
                    // }
                    // // Agora, buscaResultados contém todos os filmes dentro do intervalo de duração
                    // break;
                }

                else if (tipoBusca == 6)
                {
                    // int anoInicio;
                    // int anoFim;
                    // std::cout << "Digite o ano de início: ";
                    // std::cin >> anoInicio;
                    // std::cout << "Digite o ano de fim: ";
                    // std::cin >> anoFim;
                    // // Itera sobre cada cinema
                    // int indexCinema;
                    // Filme filmeDoCinema;

                    // // iterando sob os cinemas
                    // for (const auto &cinemaASeAnalisar : cinemas)
                    // {
                    //     // iterando sob os filmes dos cinemas
                    //     for (const auto &filmeEmCinema : cinemaASeAnalisar.Filmes_Em_Exibicao)
                    //     {
                    //         indexCinema = sortFilmes.hashTconst(filmeEmCinema);
                    //         filmeDoCinema = sortFilmes.buscarFilme(indexCinema);
                    //         // Verifica se o filme tem um startYear e endYear válidos
                    //         bool temStartYearValido = filmeDoCinema.getStartYear() != -11 && filmeDoCinema.getStartYear() != 0 && filmeDoCinema.getEndYear() != 0 && filmeDoCinema.getEndYear() != -11;
                    //         // Verifica se o filme está completamente dentro do intervalo de anos
                    //         bool dentroDoIntervalo = (temStartYearValido && filmeDoCinema.getStartYear() >= anoInicio && filmeDoCinema.getEndYear() <= anoFim);

                    //         // Inclui o filme se estiver completamente dentro do intervalo
                    //         if (dentroDoIntervalo)
                    //         {
                    //             buscaResultadosCinema.push_back(cinemaASeAnalisar);
                    //             // Imprime o cinema e o filme correspondente
                    //             // std::cout << "Cinema: " << cinemaASeAnalisar.Nome_do_Cinema << std::endl;
                    //             // std::cout << "Filme: " << filmeEmCinema << std::endl;
                    //         }
                    //     }
                    // }

                    // // Exibir todos os cinemas encontrados
                    // std::cout << "Cinemas encontrados:" << std::endl;
                    // for (const auto &resultadoCinema : buscaResultadosCinema)
                    // {
                    //     std::cout << "nome do cinema: " << resultadoCinema.Nome_do_Cinema << std::endl;
                    // }
                    // /* code */
                    // break;
                }
                // Combina os resultados com a lógica "E" ou "OU"
                if (!resultadosCinemas.empty())
                {
                    exibirMenuLogica();
                    int escolhaLogica;
                    std::cin >> escolhaLogica;

                   // if (escolhaLogica == 0)
                       // resultadosCinemas = combinarE(resultadosCinemas, novosResultados);
                  //  else
                      //  resultadosCinemas = combinarOu(resultadosCinemas, novosResultados);
                }
                else
                {
                    resultadosCinemas = novosResultados;
                }

                exibirMenuCombinar();
                std::cin >> aplicarFiltros;
            }

            // Exibe resultados finais
            for (auto cinema : resultadosCinemas)
            {
                std::cout << "Nome do cinema: " << cinema->Nome_do_Cinema << "\n";
            }
        }

        std::cout << "Deseja continuar? (Sim - 0 / Não - 1): ";
        std::cin >> continuar;
    }

    std::cout << "Programa encerrado.\n";

    return 0;
}

// // Função para buscar cinemas por tipos de filmes
// std::vector<Filme> buscarCinemasPorTitleType(ManipularCinema& manipular, SortFilmes& sort, std::string tipo, std::vector<FilmesEmCartaz>& filmesParaPesquisa) {
//     std::vector<Filme> cinemasComTipos;

//     // Busca os filmes pelo tipo
//     std::vector<Filme*> filmesEncontrados = sort.buscaBinariaMultiplosResultados(sort.titleTypeArrayPtr, tipo, &Filme::getTitleType);

//         // Criar um conjunto de filmes encontrados (desreferenciando os ponteiros)
//             std::set<FilmesEmCartaz> setFilmesEncontrados;
//             for (const auto& filmePtr : filmesEncontrados) {
//                 if (filmePtr != nullptr) {
//                     setFilmesEncontrados.insert(*filmePtr);
//                 }
//             }
//        // std::set<Filme> setFilmesParaPesquisa(filmesParaPesquisa.begin(), filmesParaPesquisa.end());

//                 // // Calcula a interseção
//                 // std::set_intersection(setFilmesEncontrados.begin(), setFilmesEncontrados.end(),
//                 //                     setFilmesParaPesquisa.begin(), setFilmesParaPesquisa.end(),
//                 //                     std::back_inserter(cinemasComTipos));

//     //        std:: string aux1, aux2;
//     //  for(int a=0,b=0; a < cinemasComTipos.size() && b < filmesParaPesquisa.size();){
//     //     aux1 = filmesParaPesquisa[b].filmedocinema.tconst;
//     //     aux2 = cinemasComTipos[a].tconst;
//     //     removeCharacter(aux1,'t');
//     //     removeCharacter(aux2,'t');
//     //     if(stoi(aux1) == stoi(aux2)){ //Gambiarra pra consertar bug
//     //         filmesParaPesquisa[b].filmedocinema = cinemasComTipos[a];
//     //         cinemasComTipos.push_back(filmesParaPesquisa[b].filmedocinema);
//     //         a++;
//     //         b++;
//     //     }else
//     //     if(stoi(aux1) > stoi(aux2)){
//     //         a++;
//     //     }else{
//     //         b++;
//     //     }
//     // }

//     // Verifica os filmes encontrados e relaciona com os cinemas
//     //         int contador1=0;
//     //         int contador2=0;

//     //         std::cout<<filmesParaPesquisa.size()<< std::endl;
//     //         std::cout<<filmesEncontrados.size()<< std::endl;

//     // for(int i=0, j=0; i < filmesEncontrados.size() && j < filmesParaPesquisa.size() ; ){
//     //         std::cout<<filmesEncontrados[i]->getTconst()<< std::endl;
//     //         std::cout<<filmesParaPesquisa[i].filmedocinema.tconst<< std::endl;
//     //         std::cout<<i<< std::endl;
//     //         std::cout<<j<< std::endl;

//     //     if(filmesEncontrados[i]->getTconst() == filmesParaPesquisa[j].filmedocinema.tconst){

//     //         cinemasComTipos.push_back(filmesParaPesquisa[i].filmedocinema.tconst);
//     //         i++;
//     //         j++;
//     //     }else if(filmesEncontrados[i]->getTconst() < filmesParaPesquisa[j].filmedocinema.tconst){
//     //         i++;
//     //     }else{
//     //         j++;
//     //     }
//     // }

//     // // Remover duplicatas, se necessário
//     // std::sort(cinemasComTipos.begin(), cinemasComTipos.end());
//     // cinemasComTipos.erase(std::unique(cinemasComTipos.begin(), cinemasComTipos.end()), cinemasComTipos.end());

//     // Debugging: Imprimir a quantidade final de cinemas encontrados
//     std::cout << "Total de cinemas encontrados: " << cinemasComTipos.size() << "\n";

//     return cinemasComTipos;
// }