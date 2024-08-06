#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Filme.hpp"

class Cinema{

std::string Cinema_ID;
std::string Nome_do_Cinema;
int Coordenada_X;
int Coordenada_Y;
float Preco_Ingresso;
std::vector<Filme> Filmes_Em_Exibição;


Cinema(std::string Cinema_ID, std::string Nome_do_Cinema, int Coordenada_X, int Coordenada_Y, float Preco_Ingresso, std::vector<Filme> Filmes_Em_Exibição)
    :Cinema_ID(Cinema_ID), Nome_do_Cinema(Nome_do_Cinema), Coordenada_X(Coordenada_X), 
    Coordenada_Y(Coordenada_Y), Preco_Ingresso(Preco_Ingresso), Filmes_Em_Exibição(Filmes_Em_Exibição){}

std::vector<Cinema> lerArquivoCinema(const std::string& nomeArquivo) {
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

        try {
            Coordenada_X = Coordenada_X_str != "\\N" ? std::stoi(Coordenada_X_str) : -11;
        } catch (const std::invalid_argument& e) {
            Coordenada_X = -11;
        }
        try {
            Coordenada_Y_str = Coordenada_Y_str != "\\N" ? std::stoi(Coordenada_Y_str) : -11;
        } catch (const std::invalid_argument& e) {
            Coordenada_Y = -11;
        }
        try {
            Preco_Ingresso = Preco_Ingresso_str != "\\N" ? std::stoi(Preco_Ingresso_str) : -11;
        } catch (const std::invalid_argument& e) {
            Preco_Ingresso = -11;
        }
        std::istringstream Filmes_Em_Exibição_stream(Filmes_Em_Exibição_str);







        //aquyi tenho que buscar o filme no vetor de ponteiros tconst
       Filme filme;
        while (std::getline(Filmes_Em_Exibição_stream, filme, ',')) {
            Filmes_Em_Exibição.push_back(filme);
        }


}           
}
};