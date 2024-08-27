#ifndef Filme_hpp
#define Filme_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#define NULL __null

// Classe Filme permanece inalterada
class Filme
{
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

        // Sobrecarga do operador de igualdade
    bool operator==(const Filme& outro) const {
        return tconst == outro.tconst; // Compara usando o tconst, que é único para cada filme
    }

        // Sobrecarga do operador < para uso no std::set
    bool operator<(const Filme& other) const {
        return tconst < other.tconst;
    }

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


#endif
