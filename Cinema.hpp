#ifndef CINEMA_HPP
#define CINEMA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Filme.hpp"
#include "SortFilmes.hpp"

class Cinema {
private:
    std::string Cinema_ID;
    std::string Nome_do_Cinema;
    int Coordenada_X;
    int Coordenada_Y;
    float Preco_Ingresso;
    std::vector<std::string> Filmes_Em_Exibição;

public:
    // Construtor
    Cinema(std::string Cinema_ID, std::string Nome_do_Cinema, int Coordenada_X, int Coordenada_Y, float Preco_Ingresso, std::vector<std::string> Filmes_Em_Exibição)
        : Cinema_ID(Cinema_ID), Nome_do_Cinema(Nome_do_Cinema), Coordenada_X(Coordenada_X), 
          Coordenada_Y(Coordenada_Y), Preco_Ingresso(Preco_Ingresso), Filmes_Em_Exibição(Filmes_Em_Exibição) {}

    // Getters
    std::string getCinemaID() const { return Cinema_ID; }
    std::string getNomeDoCinema() const { return Nome_do_Cinema; }
    int getCoordenadaX() const { return Coordenada_X; }
    int getCoordenadaY() const { return Coordenada_Y; }
    float getPrecoIngresso() const { return Preco_Ingresso; }
    std::vector<std::string> getFilmesEmExibicao() const { return Filmes_Em_Exibição; }

    // Função para ler o arquivo de cinemas e retornar um vetor de objetos Cinema
    static std::vector<Cinema> lerArquivoCinema(const std::string& nomeArquivo) {
        std::vector<Cinema> Cinemas;
        std::ifstream file(nomeArquivo);

        if (!file.is_open()) {
            std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
            return Cinemas;
        }

        std::string linha;
        // Ignora a primeira linha (cabeçalho)
        std::getline(file, linha);

        while (std::getline(file, linha)) {
            std::istringstream iss(linha);
            std::string Cinema_ID, Nome_do_Cinema, Coordenada_X_str, Coordenada_Y_str, Preco_Ingresso_str, Filmes_Em_Exibição_str;

            std::getline(iss, Cinema_ID, '\t');
            std::getline(iss, Nome_do_Cinema, '\t');
            std::getline(iss, Coordenada_X_str, '\t');
            std::getline(iss, Coordenada_Y_str, '\t');
            std::getline(iss, Preco_Ingresso_str, '\t');
            std::getline(iss, Filmes_Em_Exibição_str, '\t');

            int Coordenada_X = -11;
            int Coordenada_Y = -11;
            float Preco_Ingresso = -11.0f;

            try {
                Coordenada_X = Coordenada_X_str != "\\N" ? std::stoi(Coordenada_X_str) : -11;
            } catch (const std::invalid_argument& e) {
                Coordenada_X = -11;
            }

            try {
                Coordenada_Y = Coordenada_Y_str != "\\N" ? std::stoi(Coordenada_Y_str) : -11;
            } catch (const std::invalid_argument& e) {
                Coordenada_Y = -11;
            }

            try {
                Preco_Ingresso = Preco_Ingresso_str != "\\N" ? std::stof(Preco_Ingresso_str) : -11.0f;
            } catch (const std::invalid_argument& e) {
                Preco_Ingresso = -11.0f;
            }

            std::vector<std::string> Filmes;
            std::istringstream FilmesStream(Filmes_Em_Exibição_str);
            std::string filmelido;

            while (std::getline(FilmesStream, filmelido, ',')) {
                Filmes.push_back(filmelido);
            }

            Cinema cinema(Cinema_ID, Nome_do_Cinema, Coordenada_X, Coordenada_Y, Preco_Ingresso, Filmes);
            Cinemas.push_back(cinema);
        }

        file.close();
        return Cinemas;
    }
};

#endif
