#ifndef Filme_hpp
#define Filme_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

// Classe Filme permanece inalterada
class Filme {
public:
    std::string tconst;
    std::string titleType;
    std::string primaryTitle;
    std::string originalTitle;
    bool isAdult;
    int startYear;
    int endYear;
    int runtimeMinutes;
    std::vector<std::string> genres;
    std::vector<std::string> vetor_idcinemas;

    Filme()
        : tconst(""), titleType(""), primaryTitle(""), originalTitle(""), isAdult(false),
          startYear(-1), endYear(-1), runtimeMinutes(-1), genres(), vetor_idcinemas() {}

    Filme(std::string tconst, std::string titleType, std::string primaryTitle, std::string originalTitle, bool isAdult,
          int startYear, int endYear, int runtimeMinutes, std::vector<std::string> genres, std::vector<std::string> vetor_idcinemas)
        : tconst(tconst), titleType(titleType), primaryTitle(primaryTitle), originalTitle(originalTitle), isAdult(isAdult),
          startYear(startYear), endYear(endYear), runtimeMinutes(runtimeMinutes), genres(genres), vetor_idcinemas(vetor_idcinemas) {}

    // Getters
    std::string getTconst() const { return tconst; }
    std::string getTitleType() const { return titleType; }
    std::string getPrimaryTitle() const { return primaryTitle; }
    std::string getOriginalTitle() const { return originalTitle; }
    bool getIsAdult() const { return isAdult; }
    int getStartYear() const { return startYear; }
    int getEndYear() const { return endYear; }
    int getRuntimeMinutes() const { return runtimeMinutes; }
    std::vector<std::string> getGenres() const { return genres; }
    std::vector<std::string> getvetor_ID() const { return vetor_idcinemas; }
};

// Função para mapear cada gênero ao índice correspondente na matriz de vetores
int getGenreIndex(const std::string& genre) {
    if (genre == "Action") return 0;
    if (genre == "Adult") return 1;
    if (genre == "Adventure") return 2;
    if (genre == "Animation") return 3;
    if (genre == "Biography") return 4;
    if (genre == "Comedy") return 5;
    if (genre == "Crime") return 6;
    if (genre == "Documentary") return 7;
    if (genre == "Drama") return 8;
    if (genre == "Family") return 9;
    if (genre == "Fantasy") return 10;
    if (genre == "Game-Show") return 11;
    if (genre == "History") return 12;
    if (genre == "Horror") return 13;
    if (genre == "Music") return 14;
    if (genre == "Musical") return 15;
    if (genre == "Mystery") return 16;
    if (genre == "NULL") return 17;
    if (genre == "News") return 18;
    if (genre == "Reality-TV") return 19;
    if (genre == "Romance") return 20;
    if (genre == "Sci-Fi") return 21;
    if (genre == "Short") return 22;
    if (genre == "Sport") return 23;
    if (genre == "Talk-Show") return 24;
    if (genre == "Thriller") return 25;
    if (genre == "War") return 26;
    if (genre == "Western") return 27;

    return -1; // Retorna -1 se o gênero não for encontrado
}

// Função para ler o arquivo de filmes, preencher a matriz de vetores por gênero e retornar o vetor de todos os filmes
std::vector<Filme> lerArquivoFilmes(const std::string& nomeArquivo, std::vector<std::vector<Filme>>& filmesPorGenero) {
    std::vector<Filme> filmes; // Vetor para armazenar todos os filmes
    filmesPorGenero.resize(28); // Redimensiona a matriz com 28 vetores

    std::ifstream file(nomeArquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        return filmes;
    }

    std::string linha;
    // Ignora a primeira linha (cabeçalho)
    std::getline(file, linha);

    while (std::getline(file, linha)) {
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

        try {
            startYear = startYearStr != "\\N" ? std::stoi(startYearStr) : -11;
        } catch (const std::invalid_argument& e) {
            startYear = -11;
        }

        try {
            endYear = endYearStr != "\\N" ? std::stoi(endYearStr) : -11;
        } catch (const std::invalid_argument& e) {
            endYear = -11;
        }

        try {
            runtimeMinutes = runtimeMinutesStr != "\\N" ? std::stoi(runtimeMinutesStr) : -11;
        } catch (const std::invalid_argument& e) {
            runtimeMinutes = -11;
        }

        std::vector<std::string> genres;
        std::istringstream genresStream(genresStr);
        std::string genre;
        while (std::getline(genresStream, genre, ',')) {
            genres.push_back(genre);
        }

        Filme filme(tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres, vetor_idcinemas);

        // Adiciona o filme ao vetor de todos os filmes
        filmes.push_back(filme);

        // Adiciona o filme a cada vetor correspondente ao gênero
        for (const std::string& g : genres) {
            int genreIndex = getGenreIndex(g);
            if (genreIndex != -1) {
                filmesPorGenero[genreIndex].push_back(filme);
            }
        }
    }

    file.close();
    return filmes;
}

#endif
