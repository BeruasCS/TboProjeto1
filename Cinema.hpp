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
#include <cmath>



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
public:
    std::string Cinema_ID;
    std::string Nome_do_Cinema;
    int Coordenada_X;
    int Coordenada_Y;
    float Preco_Ingresso;
    std::vector<std::string> Filmes_Em_Exibicao;

    bool operator==(const Cinema& outro) const {
        return Cinema_ID == outro.Cinema_ID;
    }

    bool operator<(const Cinema& other) const {
        return Cinema_ID < other.Cinema_ID;
    }

    Cinema() : Coordenada_X(-11), Coordenada_Y(-11), Preco_Ingresso(-11.0f) {}

    void adicionarCinema(const std::string &id, const std::string &nome, int coordX, int coordY, float preco, const std::vector<std::string> &filmes)
    {
        Cinema_ID = id;
        Nome_do_Cinema = nome;
        Coordenada_X = coordX;
        Coordenada_Y = coordY;
        Preco_Ingresso = preco;
        Filmes_Em_Exibicao = filmes;
    }

    void lerArquivoCinema(const std::string &nomeArquivo, std::vector<Cinema> &cinemas)
    {
        std::ifstream file(nomeArquivo);

        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
            return;
        }

        std::string linha;
        std::getline(file, linha); // Ignora o cabeçalho

        while (std::getline(file, linha))
        {
            std::istringstream iss(linha);
            std::string Cinema_ID, Nome_do_Cinema, Coordenada_X_str, Coordenada_Y_str, Preco_Ingresso_str;

            std::vector<std::string> filmesEmExibicao;

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

            int Coordenada_X = std::stoi(Coordenada_X_str);
            int Coordenada_Y = std::stoi(Coordenada_Y_str);
            float Preco_Ingresso = std::stof(Preco_Ingresso_str);

            std::string filmelido;
            while (std::getline(iss, filmelido, ','))
            {
                filmesEmExibicao.push_back(trim(filmelido));
            }

            Cinema novoCinema;
            novoCinema.adicionarCinema(Cinema_ID, Nome_do_Cinema, Coordenada_X, Coordenada_Y, Preco_Ingresso, filmesEmExibicao);

            cinemas.push_back(novoCinema);
        }

        file.close();
    }
};

float calcularDistancia(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}




#endif
