#ifndef CINEMA_HPP
#define CINEMA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <locale>
#include "Filme.hpp"
#include "SortFilmes.hpp"

struct FilmesEmCartaz
{
    std::string cinema_ID_Struct;
    Filme filmedocinema;
};

bool compareByTconst(Filme *a, Filme *b)
{
    return a->getTconst() < b->getTconst();
}

// Função para remover espaços em branco no início e no fim da string
std::string trim(const std::string &str)
{
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start))
    {
        start++;
    }

    auto end = str.end();
    do
    {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

class Cinema
{
private:

    std::vector<Cinema> &cinemas; // Referência ao vetor de cinemas

public:
    std::string Cinema_ID;
    std::string Nome_do_Cinema;
    int Coordenada_X;
    int Coordenada_Y;
    float Preco_Ingresso;
   
 std::vector<std::string> Filmes_Em_Exibicao;
    // Construtor que recebe uma referência ao vetor de cinemas
    Cinema(std::vector<Cinema> &cinemasRef)
        : cinemas(cinemasRef) // Inicializa a referência
    {
    }

    // Método para adicionar um novo cinema ao vetor
    void adicionarCinema(const std::string &id, const std::string &nome, int coordX, int coordY, float preco, const std::vector<std::string> &filmes)
    {
        Cinema_ID = id;
        Nome_do_Cinema = nome;
        Coordenada_X = coordX;
        Coordenada_Y = coordY;
        Preco_Ingresso = preco;
        Filmes_Em_Exibicao = filmes;

        // Adiciona o cinema ao vetor de cinemas
        cinemas.push_back(*this);
    }

    // Função para ler o arquivo de cinemas e adicionar ao vetor
    void lerArquivoCinema(const std::string &nomeArquivo)
    {
        std::ifstream file(nomeArquivo);

        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
            return;
        }

        std::string linha;
        // Ignora a primeira linha (cabeçalho)
        std::getline(file, linha);

        while (std::getline(file, linha))
        {
            std::istringstream iss(linha);
            std::string Cinema_ID, Nome_do_Cinema, Coordenada_X_str, Coordenada_Y_str, Preco_Ingresso_str;

            // Limpa o vetor antes de começar a leitura dos filmes de um novo cinema
            Filmes_Em_Exibicao.clear();

            // Lê as partes da linha uma por uma
            std::getline(iss, Cinema_ID, ',');
            std::getline(iss, Nome_do_Cinema, ',');
            std::getline(iss, Coordenada_X_str, ',');
            std::getline(iss, Coordenada_Y_str, ',');
            std::getline(iss, Preco_Ingresso_str, ',');

            Cinema_ID = trim(Cinema_ID);
            Nome_do_Cinema = trim(Nome_do_Cinema);
            Coordenada_X_str = trim(Coordenada_X_str);
            Coordenada_Y_str = trim(Coordenada_Y_str);
            Preco_Ingresso_str = trim(Preco_Ingresso_str);

            int Coordenada_X = -11;
            int Coordenada_Y = -11;
            float Preco_Ingresso = -11.0f;

            try
            {
                Coordenada_X = Coordenada_X_str != "\\N" ? std::stoi(Coordenada_X_str) : -11;
            }
            catch (const std::invalid_argument &)
            {
                Coordenada_X = -11;
            }

            try
            {
                Coordenada_Y = Coordenada_Y_str != "\\N" ? std::stoi(Coordenada_Y_str) : -11;
            }
            catch (const std::invalid_argument &)
            {
                Coordenada_Y = -11;
            }

            try
            {
                Preco_Ingresso = Preco_Ingresso_str != "\\N" ? std::stof(Preco_Ingresso_str) : -11.0f;
            }
            catch (const std::invalid_argument &)
            {
                Preco_Ingresso = -11.0f;
            }

            // Agora vamos pegar todos os filmes restantes
            std::string filmelido;
            while (std::getline(iss, filmelido, ','))
            {
                Filmes_Em_Exibicao.push_back(trim(filmelido));
            }

            // Adiciona o cinema ao vetor usando o método adicionarCinema
            adicionarCinema(Cinema_ID, Nome_do_Cinema, Coordenada_X, Coordenada_Y, Preco_Ingresso, Filmes_Em_Exibicao);
        }

        file.close();
    }
};

// Função para realizar o merge de dois subvetores
void merge(std::vector<FilmesEmCartaz> &vec, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<FilmesEmCartaz> L(n1);
    std::vector<FilmesEmCartaz> R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = vec[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = vec[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].filmedocinema.tconst <= R[j].filmedocinema.tconst)
        {
            vec[k] = L[i];
            i++;
        }
        else
        {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        vec[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        vec[k] = R[j];
        j++;
        k++;
    }
}

// Função para realizar o merge sort
void mergeSort(std::vector<FilmesEmCartaz> &vec, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

#endif
