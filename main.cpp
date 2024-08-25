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

// Função para exibir o menu de combinação de resultados
void exibirMenuCombinar()
{
    std::cout << "Deseja fazer mais alguma busca?\n";
    std::cout << "Sim - 0\n";
    std::cout << "Não - 1\n";
}

// Função para exibir o menu de combinação "E" ou "ou"
void exibirMenuLogica()
{
    std::cout << "\"E\" - 0\n";
    std::cout << "\"ou\" - 1\n";
}
std::vector<Filme *> vetorFilmesPtrAtualizar(std::vector<Filme> &filmes)
{
    std::vector<Filme *> essesFilmes;
    essesFilmes.clear();
    for (auto filme : filmes)
    {
        essesFilmes.push_back(&filme);
    }
    return essesFilmes;
}


int main()
{

    std::cout << "Inicializando programa...\n";
    std::string nomeArquivoFilmes = "filmesCrop.txt";
    std::string nomeArquivoCinema= "cinemas.txt";
    std::vector<FilmesEmCartaz> filmesemcartaz; 
    

    std::vector<std::vector<Filme>> filmesPorGenero;


//vetor a ser passado para receber os filmes
    std::vector<Filme> filmes;

//passando o vetor e criando o sortFilmes, tenho que mudar esses nomes
    SortFilmes sortFilmes(filmes);
    //criando cinema
    std::vector<Cinema> cinema;

    //passando filmes p cinema
    Cinema cinemas(cinema);

    //lendo os arquivos
    cinemas.lerArquivoCinema(nomeArquivoCinema);
    sortFilmes.lerArquivoFilmes(nomeArquivoFilmes, filmesPorGenero);


//chamando a funcao atualizar
    sortFilmes.atualizar();
//verificando se esta sendo preenchido
    // std::cout<<sortFilmes.tconstArray.size()<<"\n";
//testando se to buscandio
    //int filme = sortFilmes.hashTconst("tt9195166");
    //std::cout<<filme<<"\n";
    // Filme pesquisado = sortFilmes.buscarFilmePorTitulo(filme);
    // std::cout<< pesquisado.getPrimaryTitle();
    std::cout<<"executada essa parte";
    
      std::cout<<sortFilmes.tconstArray.size()<<"\n";
   // sortFilmes.atualizar(); // Ordena os vetores de ponteiros
    sortFilmes.merge_sort(sortFilmes.titleTypeArrayPtr, compareByTitleType);
    sortFilmes.merge_sort(sortFilmes.runtimeMinutesArrayPtr, compareByRuntimeMinutes);
    sortFilmes.merge_sort(sortFilmes.startYearArrayPtr, compareByStartYear);
    sortFilmes.merge_sort(sortFilmes.genresArrayPtr, compareByGenres);

  //  std::cout << filmes.size();
    std::cout << "Programa inicializado\n";

    bool continuar = true;
    std::vector<Filme *> resultados;

    while (continuar)
    {
        exibirMenuPrincipal();

        int escolha;
        std::cin >> escolha;



    // 1. Cinemas que contém filmes de um ou mais tipos (coluna titleType).
    // 2. Cinemas que contém filmes que pertencem a um ou mais gêneros (coluna
    // genres).
    // 3. Cinemas que contém filmes com uma duração específica entre um limite inferior e superior em minutos.
    // 4. Cinemas em uma localização de até uma distância definida de um local.
    // 5. Cinemas com preços até um limite superior de unidades monetárias.
    // 6. Cinemas que contém filmes lançados em um ano específico ou em um
    // intervalo de anos.

        if (escolha == 0)
        { // Busca de filmes
            exibirMenuBusca();
            int tipoBusca;
            std::cin >> tipoBusca;

            // Variáveis para armazenar resultados da busca
            std::vector<Filme *> buscaResultados;

            switch (tipoBusca)
            {
            case 1:
            {
                std::string tipo;
                std::cout << "Digite o(s) tipo(s) de filme(s): ";
                std::cin >> tipo;
                buscaResultados = sortFilmes.buscaLinearMultiplosResultados(
                    sortFilmes.titleTypeArrayPtr, tipo, &Filme::getTitleType);
                buscaResultados.size();
                for (const auto x : buscaResultados)
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
                        buscaResultados.push_back(&filme);
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
                        buscaResultados.push_back(film);
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
                        buscaResultados.push_back(filme);
                    }
                }

                // Agora, buscaResultados contém todos os filmes dentro do intervalo de anos
                break;
            }
            default:
                std::cout << "Opção inválida\n";
                continue;
            }

            // Exibir resultados da pesquisa
            std::cout << "Resultados encontrados:\n";
            for (auto filme : buscaResultados)
            {
                std::cout << buscaResultados.size() << "\n";
                std::cout << "ID: " << filme->getTconst() << "\n";
                std::cout << "Titulo primario: " << filme->getPrimaryTitle() << "\n";
                 std::cout << "Cinemas: " << filme->getvetor_ID().size() << "\n"; 
            }

            // Combinação de resultados
            while (true)
            {
                exibirMenuCombinar();
                int maisBuscas;
                std::cin >> maisBuscas;

                if (maisBuscas == 1)
                {
                    continuar = false;
                    break;
                }

                exibirMenuLogica();
                int logica;
                std::cin >> logica;

                exibirMenuBusca();
                int novaBusca;
                std::cin >> novaBusca;

                std::vector<Filme *> resultadosTemp;
                switch (novaBusca)
                {
                case 1:
                {
                    std::string tipo;
                    std::cout << "Digite o(s) tipo(s) de filme(s): ";
                    std::cin >> tipo;
                    resultadosTemp = sortFilmes.buscaLinearMultiplosResultados(
                        sortFilmes.titleTypeArrayPtr, tipo, &Filme::getTitleType);
                    resultadosTemp.size();
                    for (const auto x : resultadosTemp)
                    {
                        x->getTitleType();
                    }

                    break;
                }
                case 2:
                {
                    std::string genero;
                    std::cout << "Digite o gênero de filme: ";
                    std::cin >> genero;

                    int genreIndex = sortFilmes.getGenreIndex(genero);
                    if (genreIndex != -1 && !filmesPorGenero[genreIndex].empty())
                    {
                        for (auto &filme : filmesPorGenero[genreIndex])
                        {
                            resultadosTemp.push_back(&filme);
                        }
                    }
                    else
                    {
                        std::cout << "Nenhum filme encontrado para o gênero " << genero << "\n";
                    }
                }
                break;
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
                            resultadosTemp.push_back(film);
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
                            buscaResultados.push_back(filme);
                        }
                    }

                    // Agora, buscaResultados contém todos os filmes dentro do intervalo de anos
                    break;
                }
                default:
                    std::cout << "Opção inválida\n";
                    continue;
                }

                // Aqui você junta os resultados usando push_back
                if (logica == 0)
                { // "E"

                    std::vector<Filme *> result;
                    int tamanhoresultadostemp = resultadosTemp.size();
                    for (int j = 0; j < tamanhoresultadostemp; j++)
                    {

                        int indice = binarySearchTconst(buscaResultados, resultadosTemp[j]->tconst);
                        if (indice != -576)
                        {
                            // se estiver no vetor, entra nessa concicao, e assim colocamos no vetor de solucao
                            result.push_back(resultadosTemp[j]);
                        }
                    }

                    buscaResultados.clear();
                    buscaResultados = result;
                }
                else if (logica == 1)
                { // "OU"

                    for (auto &filme : resultadosTemp)
                    {

                        buscaResultados.push_back(filme);
                        // resultadosSet.insert(*&filme);
                    }
                }

                // Exibir resultados da pesquisa atualizada
                std::cout << "Resultados combinados encontrados:\n";
                for (auto filme : buscaResultados)
                {
                    std::cout << "ID: " << filme->getTconst() << "\n";
                    std::cout << "Titulo primario: " << filme->getPrimaryTitle() << "\n";
                }
            }
        }
        else if (escolha == 1)
        {
            exibirMenuBuscaCinemas();
            int tipoBusca;
            std::cin >> tipoBusca;


            std::vector<Filme *> buscaResultados;

            switch (tipoBusca)
            {
            case 1:
            {
                // 1. Cinemas que contém filmes de um ou mais tipos (coluna titleType).
                 std::string tipo;
                 std::cout << "Digite o(s) tipo(s) de filme(s): ";
                 std::cin >> tipo;

                // // Busca os filmes correspondentes ao tipo fornecido
                // buscaResultados = sortFilmes.buscaLinearMultiplosResultados(
                //     sortFilmes.titleTypeArrayPtr, tipo, &Filme::getTitleType);

                // Itera sobre cada cinema
                int indexCinema;
                Filme filmeDoCinema;
                for (const auto &cinemaASeAnalisar : cinema)
                {
                    //bool possuiFilmeDoTipo = false;

                    // Verifica se o cinema possui algum filme do tipo buscado
                    //std::cout<<"Cinema: "<<cinemaASeAnalisar.Cinema_ID<<std::endl;
                    for (const auto &filmeEmCinema : cinemaASeAnalisar.Filmes_Em_Exibicao)
                    {
                        indexCinema=sortFilmes.hashTconst(filmeEmCinema);
                        filmeDoCinema=sortFilmes.buscarFilme(indexCinema);
                        if(filmeDoCinema.getTitleType()==tipo){

                            std::cout<<"cinema: "<<cinemaASeAnalisar.Nome_do_Cinema<< std::endl;
                            std::cout<<"Filme: "<<filmeEmCinema<< std::endl;


                        }

                        

                        // // Verifica se o filme está nos resultados da busca
                        // auto it = std::find_if(
                        //     buscaResultados.begin(),
                        //     buscaResultados.end(),
                        //     [&](const Filme *filme)
                        //     {
                        //         return filme->getTconst() == filmeEmCinema;
                        //     });

                        // if (it != buscaResultados.end())
                        // {
                        //     possuiFilmeDoTipo = true;
                        //     break;
                        // }
                    }

                    // Se o cinema possui pelo menos um filme do tipo buscado, imprime as informações
                    // if (possuiFilmeDoTipo)
                    // {
                    //     std::cout << "Cinema ID: " << cinemaASeAnalisar.Cinema_ID << "\n";
                    //     std::cout << "Nome do Cinema: " << cinemaASeAnalisar.Nome_do_Cinema << "\n";
                    //     std::cout << "Filmes em Exibição do tipo '" << tipo << "':\n";

                    //     for (const auto &filmeEmCinema : cinemaASeAnalisar.Filmes_Em_Exibicao)
                    //     {
                    //         auto it = std::find_if(
                    //             buscaResultados.begin(),
                    //             buscaResultados.end(),
                    //             [&](const Filme *filme)
                    //             {
                    //                 return filme->getTconst() == filmeEmCinema;
                    //             });

                    //         if (it != buscaResultados.end())
                    //         {
                    //             std::cout << " - " << (*it)->getPrimaryTitle() << "\n";
                    //         }
                    //     }

                    //     std::cout << "-----------------------------\n";
                    // }
                }

                break;
            }
            case 2:
            {

               /* code */
                break; 
            }
            case 3:
            {

               /* code */
                break; 
            }
            case 4:
            {

               /* code */
                break; 
            }
            case 5:
            {

               /* code */
                break; 
            }
            case 6:
            {

               /* code */
                break; 
            }
                
            
            default:
            std::cout << "Opção inválida\n";
                continue;
                // break;
            }

        }
        else
        {
            std::cout << "Opção inválida\n";
        }
    }

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