#ifndef DIPINTO_HPP
#define DIPINTO_HPP

#include <string>

class Dipinto
{
//Scuola,Autore,Soggetto/Titolo,Data,Sala
public:
    Dipinto() = default;

    Dipinto(const std::string& scuola, const std::string& autore, const std::string& titolo, const std::string& data, const std::string& sala)
        :scuola(scuola), autore(autore), titolo(titolo), data(data), sala(sala) {}

    bool operator==(const Dipinto& other) const
    {
        return scuola == other.scuola && autore == other.autore && titolo == other.titolo && data == other.data && sala == other.sala;
    }

    void testMethod() const
    {
        std::cout << "HERE" << std::endl;
    }

private:
    std::string scuola;
    std::string autore;
    std::string titolo;
    std::string data;
    std::string sala;
};

#endif