#ifndef Filme_hpp
#define Filme_hpp


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

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
    std:: vector <std::string> vetor_idcinemas;
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


std::vector<Filme> lerArquivoFilmes(const std::string& nomeArquivo) {
    std::vector<Filme> filmes;
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
        std:: vector <std::string> vetor_idcinemas;


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
        std::cout<<"AAAAAAAAQUIIII "<<runtimeMinutes;
        filmes.push_back(filme);

      }

    file.close();
    return filmes;
}
#endif

