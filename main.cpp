#include <iostream>
#include <chrono>
#include <cmath> // Para std::sqrt e std::pow
#include <vector>
#include <set>
#include "Filme.hpp"
#include "SortFilmes.hpp"
#include "Cinema.hpp"

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

std::vector<Filme *> combinarE(const std::vector<Filme *> &vetor1, const std::vector<Filme *> &vetor2)
{
    std::vector<Filme *> intersecao;

    std::set_intersection(
        vetor1.begin(), vetor1.end(),
        vetor2.begin(), vetor2.end(),
        std::back_inserter(intersecao),
        [](Filme *a, Filme *b)
        {
            return a->getTconst() < b->getTconst(); // Comparando por Tconst
        });

    return intersecao;
}
std::vector<Cinema> combinarECinemas(const std::vector<Cinema> &vetor1, const std::vector<Cinema> &vetor2)
{
    std::vector<Cinema> intersecao;

    std::set_intersection(
        vetor1.begin(), vetor1.end(),
        vetor2.begin(), vetor2.end(),
        std::back_inserter(intersecao),
        [](Cinema a, Cinema b)
        {
            return a.Cinema_ID < b.Cinema_ID; // Comparando por Tconst
        });

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
template <typename T>
std::vector<T> combinarOuCinema(const std::vector<T> &v1, const std::vector<T> &v2)
{
    std::set<T> resultadoSet(v1.begin(), v1.end());
    resultadoSet.insert(v2.begin(), v2.end());
    return std::vector<T>(resultadoSet.begin(), resultadoSet.end());
}

// Função para exibir o menu principal
void exibirMenuPrincipal()
{
    std::cout << "O que deseja buscar?\n";
    std::cout << "1: Filmes\n";
    std::cout << "2: Cinemas\n";
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

    std::cout << "Qual busca deseja fazer?\n";
    std::cout << "1. Cinemas que contém filmes de um ou mais tipos (coluna titleType).\n";
    std::cout << "2. Cinemas que contém filmes que pertencem a um ou mais gêneros (colunagenres).\n";
    std::cout << "3. Cinemas que contém filmes com uma duração específica entre um limite inferior e superior em minutos.\n";
    std::cout << "4. Cinemas em uma localização de até uma distância definida de um local.\n";
    std::cout << "5. Cinemas com preços até um limite superior de unidades monetárias. \n";
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
    Cinema cinemaHandler;
    cinemaHandler.lerArquivoCinema(nomeArquivoCinema, cinemas);

    std::vector<Filme *> resultadosFilmes;
    std::vector<Cinema> resultadosCinemas;
    int contadorFilmes = 0;
    int contadorCinemas = 0;

    while (continuar == 0)
    {
        exibirMenuPrincipal();
        int escolha;
        std::cin >> escolha;

        switch (escolha)
        {

        case 1: // Busca de filmes
        {
            int operadorLogico;
            exibirMenuBusca();
            int tipoBusca;
            std::cin >> tipoBusca;

            std::vector<Filme *> novosResultados;

            if (contadorFilmes >= 1)
            {

                // std::cout<<"entrou nesse if"<<"\n";

                novosResultados = resultadosFilmes;

                exibirMenuLogica();

                std::cin >> operadorLogico;
            }

            switch (tipoBusca)
            {
            case 1:
            {
                resultadosFilmes.clear();
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
                resultadosFilmes.clear();
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
                resultadosFilmes.clear();
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
                resultadosFilmes.clear();
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

            if (contadorFilmes >= 1)
            {

                std::vector<Filme *> aux;
                aux.clear();

                if (operadorLogico == 0)
                {
                    // std::cout<<"entramos nessa parte aqui ooooooooooooooooooooooooooo"<<"\n";
                    // std::cout<<resultadosFilmes.size();
                    // std::cout<<novosResultados.size();

                    aux = combinarE(novosResultados, resultadosFilmes);
                    resultadosFilmes = aux;
                }
                if (operadorLogico == 1)
                {

                    aux = combinarOu(novosResultados, resultadosFilmes);
                    resultadosFilmes = aux;
                }
            }

            // Exibe resultados finais
            for (auto filme : resultadosFilmes)
            {
                std::cout << "ID: " << filme->getTconst() << "\n";
                std::cout << "Titulo primario: " << filme->getPrimaryTitle() << "\n";
            }
            contadorFilmes++;
            break;
        }

        case 2: // Busca de cinemas
        {

            int operadorLogico;
            exibirMenuBuscaCinemas();
            int tipoBusca;
            std::cin >> tipoBusca;

            std::vector<Cinema> novosResultadosCinema;

            if (contadorCinemas >= 1)
            {

                // std::cout<<"entrou nesse if"<<"\n";

                novosResultadosCinema = resultadosCinemas;

                exibirMenuLogica();

                std::cin >> operadorLogico;
            }

            switch (tipoBusca)
            {
            case 1:
            { /* Código para buscar cinemas por tipo de filme */
                // // 1. Cinemas que contém filmes de um ou mais tipos (coluna titleType).
                resultadosCinemas.clear();
                std::string tipo;
                std::cout << "Digite o(s) tipo(s) de filme(s): ";
                std::cin >> tipo;

                // Itera sobre cada cinema
                int indexCinema;
                Filme filmeDoCinema;
                for (auto &cinemaASeAnalisar : cinemas)
                {
                    for (const auto &filmeEmCinema : cinemaASeAnalisar.Filmes_Em_Exibicao)
                    {
                        indexCinema = sortFilmes.hashTconst(filmeEmCinema);
                        filmeDoCinema = sortFilmes.buscarFilme(indexCinema);

                        if (filmeDoCinema.getTitleType() == tipo)
                        {
                            // Adiciona o cinema ao vetor de resultados
                            resultadosCinemas.push_back(cinemaASeAnalisar);

                            // Imprime o cinema e o filme correspondente
                            // std::cout << "Cinema: " << cinemaASeAnalisar.Nome_do_Cinema << std::endl;
                            // std::cout << "Filme: " << filmeEmCinema << std::endl;

                            // Opcional: interrompe o loop para evitar duplicações de cinema no vetor
                            break;
                        }
                    }
                }

                break;
            }
            case 2:
            { /* Código para buscar cinemas por gênero de filme */
                resultadosCinemas.clear();

                std::string genero;
                std::cout << "Digite o genero do filme: ";
                std::cin >> genero;

                // Itera sobre cada cinema
                int indexCinema;
                Filme filmeDoCinema;
                int genreIndex = sortFilmes.getGenreIndex(genero);

                // Iterando sobre os cinemas
                for (const auto &cinemaASeAnalisar : cinemas)
                {
                    bool cinemaAdicionado = false;

                    // Iterando sobre os filmes de cada cinema
                    for (const auto &filmeEmCinema : cinemaASeAnalisar.Filmes_Em_Exibicao)
                    {
                        indexCinema = sortFilmes.hashTconst(filmeEmCinema);
                        filmeDoCinema = sortFilmes.buscarFilme(indexCinema);
                        if (genreIndex != -1 && !filmesPorGenero[genreIndex].empty())
                        {
                            for (auto &filme : filmesPorGenero[genreIndex])
                            {
                                if (filmeDoCinema.getTconst() == filme.getTconst())
                                {
                                    // Adiciona o cinema ao vetor de resultados
                                    resultadosCinemas.push_back(cinemaASeAnalisar);
                                    cinemaAdicionado = true; // Marca o cinema como adicionado

                                    break; // Sai do loop que verifica os filmes desse cinema
                                }
                            }
                        }
                        if (cinemaAdicionado)
                            break; // Sai do loop de filmes do cinema atual
                    }
                }

                break;
            }
            case 3:
            { /* Código para buscar cinemas por duração de filme */
                resultadosCinemas.clear();
                int minDuracao, maxDuracao;
                std::cout << "Digite a duração mínima em minutos: ";
                std::cin >> minDuracao;
                std::cout << "Digite a duração máxima em minutos: ";
                std::cin >> maxDuracao;

                int indexCinema;
                Filme filmeDoCinema;
                for (const auto &cinemaASeAnalisar : cinemas)
                {
                    for (const auto &filmeEmCinema : cinemaASeAnalisar.Filmes_Em_Exibicao)
                    {
                        indexCinema = sortFilmes.hashTconst(filmeEmCinema);
                        filmeDoCinema = sortFilmes.buscarFilme(indexCinema);

                        if (filmeDoCinema.getRuntimeMinutes() >= minDuracao && filmeDoCinema.getRuntimeMinutes() <= maxDuracao)
                        {
                            // Adiciona o cinema ao vetor de resultados
                            resultadosCinemas.push_back(cinemaASeAnalisar);

                            // Imprime o cinema e o filme correspondente
                            // std::cout << "Cinema: " << cinemaASeAnalisar.Nome_do_Cinema << std::endl;
                            // std::cout << "Filme: " << filmeEmCinema << std::endl;

                            // Opcional: interrompe o loop para evitar duplicações de cinema no vetor
                            break;
                        }
                    }
                }

                // Agora, buscaResultados contém todos os filmes dentro do intervalo de duração
                break;
            }
            case 4:
            { /* Código para buscar cinemas por localização */
                resultadosCinemas.clear();
                int xReferencia, yReferencia;
                float distanciaMaxima;

                std::cout << "Digite a coordenada X do ponto de referência: ";
                std::cin >> xReferencia;
                std::cout << "Digite a coordenada Y do ponto de referência: ";
                std::cin >> yReferencia;
                std::cout << "Digite a distância máxima: ";
                std::cin >> distanciaMaxima;

                std::vector<Cinema> cinemasProximos;

                for (const auto &cinema : cinemas)
                {
                    float distancia = calcularDistancia(cinema.Coordenada_X, cinema.Coordenada_Y, xReferencia, yReferencia);

                    if (distancia <= distanciaMaxima)
                    {
                        cinemasProximos.push_back(cinema);
                    }
                }

                if (cinemasProximos.empty())
                {
                    std::cout << "Nenhum cinema encontrado dentro da distância especificada.\n";
                }
                else
                {
                    std::cout << "Cinemas encontrados dentro da distância especificada:\n";
                    for (const auto &cinema : cinemasProximos)
                    {
                        resultadosCinemas.push_back(cinema);
                    }
                }

                break;
            }
            case 5:
            {
                resultadosCinemas.clear();
                float maxPreco;
                std::cout << "Digite o preco maximo: ";
                std::cin >> maxPreco;

                // int indexCinema;
                Filme filmeDoCinema;
                for (const auto &cinemaASeAnalisar : cinemas)
                {
                    if (cinemaASeAnalisar.Preco_Ingresso <= maxPreco)
                    {
                        // Adiciona o cinema ao vetor de resultados
                        resultadosCinemas.push_back(cinemaASeAnalisar);
                        // std::cout<<cinemaASeAnalisar.Nome_do_Cinema;
                    }
                }

                // Agora, buscaResultados contém todos os filmes dentro do intervalo de duração
                break;
            }
            case 6:
            {
                resultadosCinemas.clear();
                int anoInicio;
                int anoFim;
                std::cout << "Digite o ano de início: ";
                std::cin >> anoInicio;
                std::cout << "Digite o ano de fim: ";
                std::cin >> anoFim;
                // Itera sobre cada cinema
                int indexCinema;
                Filme filmeDoCinema;

                // iterando sob os cinemas
                for (const auto &cinemaASeAnalisar : cinemas)
                {
                    // iterando sob os filmes dos cinemas
                    for (const auto &filmeEmCinema : cinemaASeAnalisar.Filmes_Em_Exibicao)
                    {
                        indexCinema = sortFilmes.hashTconst(filmeEmCinema);
                        filmeDoCinema = sortFilmes.buscarFilme(indexCinema);
                        // Verifica se o filme tem um startYear e endYear válidos
                        bool temStartYearValido = filmeDoCinema.getStartYear() != -11 && filmeDoCinema.getStartYear() != 0 && filmeDoCinema.getEndYear() != 0 && filmeDoCinema.getEndYear() != -11;
                        // Verifica se o filme está completamente dentro do intervalo de anos
                        bool dentroDoIntervalo = (temStartYearValido && filmeDoCinema.getStartYear() >= anoInicio && filmeDoCinema.getEndYear() <= anoFim);

                        // Inclui o filme se estiver completamente dentro do intervalo
                        if (dentroDoIntervalo)
                        {
                            resultadosCinemas.push_back(cinemaASeAnalisar);
                            // Imprime o cinema e o filme correspondente
                            // std::cout << "Cinema: " << cinemaASeAnalisar.Nome_do_Cinema << std::endl;
                            // std::cout << "Filme: " << filmeEmCinema << std::endl;
                        }
                    }
                }

                // Exibir todos os cinemas encontrados
                std::cout << "Cinemas encontrados:" << std::endl;
                for (const auto &resultadoCinema : resultadosCinemas)
                {
                    std::cout << "nome do cinema: " << resultadoCinema.Nome_do_Cinema << std::endl;
                }
                /* code */
                break;
            }
            default:
                std::cout << "Opção inválida\n";
                continue;
            }
            if (contadorCinemas >= 1)
            {

                std::vector<Cinema> aux;
                aux.clear();

                if (operadorLogico == 0)
                {
                    // std::cout<<"entramos nessa parte aqui ooooooooooooooooooooooooooo"<<"\n";
                    // std::cout<<resultadosFilmes.size();
                    // std::cout<<novosResultados.size();

                    aux = combinarECinemas(novosResultadosCinema, resultadosCinemas);
                    resultadosCinemas = aux;
                }
                if (operadorLogico == 1)
                {

                    aux = combinarOuCinema(novosResultadosCinema, resultadosCinemas);
                    resultadosCinemas = aux;
                }
            }
            // Exibe resultados finais
            for (auto cinema : resultadosCinemas)
            {
                std::cout << "ID: " << cinema.Cinema_ID << "\n";
                std::cout << "Nome do Cinema: " << cinema.Nome_do_Cinema << "\n";
            }
            contadorCinemas++;
            break;
        }
        }
            std::cout << "Deseja continuar? (Sim - 0 / Não - 1): ";
            std::cin >> continuar;
    }

    std::cout << "Programa encerrado.\n";

    return 0;
}
