#ifndef ColetaniaDeFilmes_hpp
#define ColetaniaDeFilmes_hpp

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Filme.hpp"

class ColetaniaDeFilmes
{
public:
    std::vector<Filme> tconstArray;
    std::vector<Filme *> titleTypeArrayPtr;
    std::vector<Filme *> primaryTitleArrayPtr;
    std::vector<Filme *> originalTitleArrayPtr;
    std::vector<Filme *> isAdultArrayPtr;
    std::vector<Filme *> startYearArrayPtr;
    std::vector<Filme *> endYearArrayPtr;
    std::vector<Filme *> runtimeMinutesArrayPtr;
    std::vector<Filme *> genresArrayPtr;
    std::vector<Filme> &filmes;  // Agora é uma referência

    // Construtor que recebe o vetor filmes por referência
    ColetaniaDeFilmes(std::vector<Filme> &filmesRef) : filmes(filmesRef) {

         // Inicializa o array com ponteiros nulos para o hash
        tconstArray.resize(1277665);

    }

     // Função de hash para converter tconst em um índice
int hashTconst(const std::string &tconst)
{
    // Verifica se o tconst tem o prefixo "tt"
    if (tconst.size() > 2 && tconst.substr(0, 2) == "tt")
    {
        try
        {
            // Remove o prefixo "tt" e converte o restante para um número inteiro
            std::string numStr = tconst.substr(2);
            int tconstNum = std::stoi(numStr); // Converte a substring para int
            //std::cout << tconstNum << std::endl; // Para depuração

            return tconstNum - 7917518; // Ajusta o valor conforme a faixa de tconst
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Erro: Argumento inválido na conversão de tconst para int: " << e.what() << std::endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Erro: Valor fora do intervalo na conversão de tconst para int: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cerr << "Erro: tconst deve começar com 'tt'" << std::endl;
    }

    return -1; // Valor padrão para indicar erro
}




// Função para mapear cada gênero ao índice correspondente na matriz de vetores
int getGenreIndex(const std::string &genre)
{
    if (genre == "Action")
        return 0;
    if (genre == "Adult")
        return 1;
    if (genre == "Adventure")
        return 2;
    if (genre == "Animation")
        return 3;
    if (genre == "Biography")
        return 4;
    if (genre == "Comedy")
        return 5;
    if (genre == "Crime")
        return 6;
    if (genre == "Documentary")
        return 7;
    if (genre == "Drama")
        return 8;
    if (genre == "Family")
        return 9;
    if (genre == "Fantasy")
        return 10;
    if (genre == "Game-Show")
        return 11;
    if (genre == "History")
        return 12;
    if (genre == "Horror")
        return 13;
    if (genre == "Music")
        return 14;
    if (genre == "Musical")
        return 15;
    if (genre == "Mystery")
        return 16;
    if (genre == "NULL")
        return 17;
    if (genre == "News")
        return 18;
    if (genre == "Reality-TV")
        return 19;
    if (genre == "Romance")
        return 20;
    if (genre == "Sci-Fi")
        return 21;
    if (genre == "Short")
        return 22;
    if (genre == "Sport")
        return 23;
    if (genre == "Talk-Show")
        return 24;
    if (genre == "Thriller")
        return 25;
    if (genre == "War")
        return 26;
    if (genre == "Western")
        return 27;

    return -1; // Retorna -1 se o gênero não for encontrado
}

// Função para ler o arquivo de filmes, preencher a matriz de vetores por gênero e retornar o vetor de todos os filmes
void lerArquivoFilmes(const std::string &nomeArquivo, std::vector<std::vector<Filme>> &filmesPorGenero)
{
 
    filmesPorGenero.resize(28); // Redimensiona a matriz com 28 vetores

    std::ifstream file(nomeArquivo);
    if (!file.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        
    }

    std::string linha;
    // Ignora a primeira linha (cabeçalho)
    std::getline(file, linha);

    while (std::getline(file, linha))
    {
        std::istringstream iss(linha);
        std::string tconst, titleType, primaryTitle, originalTitle, isAdultStr, startYearStr, endYearStr, runtimeMinutesStr, genresStr;
        std::vector<std::string> vetor_idcinemas;

        std::getline(iss, tconst, '\t');
        std::getline(iss, titleType, '\t');
        std::getline(iss, primaryTitle, '\t');
        std::getline(iss, originalTitle, '\t');
        std::getline(iss, isAdultStr, '\t');
        std::getline(iss, startYearStr, '\t');
        std::getline(iss, endYearStr, '\t');
        std::getline(iss, runtimeMinutesStr, '\t');
        std::getline(iss, genresStr, '\t');

        bool isAdult = isAdultStr == "1";
        int startYear = 0, endYear = 0, runtimeMinutes = 0;

        try
        {
            startYear = startYearStr != "\\N" ? std::stoi(startYearStr) : -11;
        }
        catch (const std::invalid_argument &e)
        {
            startYear = -11;
        }

        try
        {
            endYear = endYearStr != "\\N" ? std::stoi(endYearStr) : -11;
        }
        catch (const std::invalid_argument &e)
        {
            endYear = -11;
        }

        try
        {
            runtimeMinutes = runtimeMinutesStr != "\\N" ? std::stoi(runtimeMinutesStr) : -11;
        }
        catch (const std::invalid_argument &e)
        {
            runtimeMinutes = -11;
        }

        std::vector<std::string> genres;
        std::istringstream genresStream(genresStr);
        std::string genre;
        while (std::getline(genresStream, genre, ','))
        {
            genres.push_back(genre);
        }

        Filme filme(tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres, vetor_idcinemas);

        // Adiciona o filme ao vetor de todos os filmes
        filmes.push_back(filme);

        // Adiciona o filme a cada vetor correspondente ao gênero
        for (const std::string &g : genres)
        {
            int genreIndex = getGenreIndex(g);
            if (genreIndex != -1)
            {
                filmesPorGenero[genreIndex].push_back(filme);
            }
        }
    }

    file.close();

}

    void atualizar()
    {
        //tconstArray.clear();
        titleTypeArrayPtr.clear();
        primaryTitleArrayPtr.clear();
        originalTitleArrayPtr.clear();
        isAdultArrayPtr.clear();
        startYearArrayPtr.clear();
        endYearArrayPtr.clear();
        runtimeMinutesArrayPtr.clear();
        genresArrayPtr.clear();

        for (auto &filme : filmes)
        {
        
          int index = hashTconst(filme.getTconst());
            if (index >= 0 && index < tconstArray.size())
            {
                tconstArray[index] = filme;
            }
           // std::cout<<index<<"\n";
            //std::cout<<tconstArray[1277664].getPrimaryTitle()<<"\n";
            

            titleTypeArrayPtr.push_back(&filme);
            primaryTitleArrayPtr.push_back(&filme);
            originalTitleArrayPtr.push_back(&filme);
            isAdultArrayPtr.push_back(&filme);
            startYearArrayPtr.push_back(&filme);
            endYearArrayPtr.push_back(&filme);
            runtimeMinutesArrayPtr.push_back(&filme);
            genresArrayPtr.push_back(&filme);
        }

    }


    std::vector<Filme *> merge_sort(std::vector<Filme *> array, bool (*compareFilme)(Filme *, Filme *))
    {
        if (array.size() <= 1)
        {
            return array;
        }

        size_t mid = array.size() / 2;
        std::vector<Filme *> arrayOne(array.begin(), array.begin() + mid);
        std::vector<Filme *> arrayTwo(array.begin() + mid, array.end());

        std::vector<Filme *> sortedArrayOne = merge_sort(arrayOne, compareFilme);
        std::vector<Filme *> sortedArrayTwo = merge_sort(arrayTwo, compareFilme);

        return merge(sortedArrayOne, sortedArrayTwo, compareFilme);
    }

    std::vector<Filme *> merge(const std::vector<Filme *> &a, const std::vector<Filme *> &b, bool (*compareFilme)(Filme *, Filme *))
    {
        std::vector<Filme *> c;
        size_t i = 0, j = 0;

        while (i < a.size() && j < b.size())
        {
            if (compareFilme(a[i], b[j]))
            {
                c.push_back(a[i]);
                ++i;
            }
            else
            {
                c.push_back(b[j]);
                ++j;
            }
        }

        while (i < a.size())
        {
            c.push_back(a[i]);
            ++i;
        }

        while (j < b.size())
        {
            c.push_back(b[j]);
            ++j;
        }

        return c;
    }

    template <typename T>
    std::vector<Filme *> buscaLinearMultiplosResultados(const std::vector<Filme *> &array, T key, T (Filme::*getter)() const)
    {
        std::vector<Filme *> resultados;

        for (auto &filme : array)
        {
            if ((filme->*getter)() == key)
            {
                resultados.push_back(filme);
            }
        }

        return resultados;
    }


   Filme buscarFilme(const int index) {
    if (index >= 0 && index < tconstArray.size()) {
       // std::cout<<tconstArray[index].getOriginalTitle();
        return tconstArray[index];
    } else {
        std::cout<< "Filme não encontrado.";
    }
}




};

#endif