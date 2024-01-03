#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include "gset.hpp"

/**
 * @brief Funtore di uguaglianza tra tipi interi.
 *
 * Valuta l'uglianza tra due interi. 
 */
struct funcInt
{
    bool operator()(int a, int b) const
    {
        return a == b;
    }
};

/**
 * @brief Funtore di uguaglianza tra tipi stringa.
 * 
 * Valuta l'uglianza tra due stringhe. 
 */
struct funcStr
{
    bool operator()(const std::string& a, const std::string& b) const
    {
        return a == b;
    }
};

/**
 * @brief Funtore con un predicato di test sugli interi.
 * 
 * @return true Se l'intero è maggiore di 5.
 * @return false Se l'intero non è maggiore di 5.
 */
struct predicateInt
{
    bool operator()(int a) const
    {
        return a > 5;
    }
};

typedef Set<int, funcInt> IntSet;
typedef Set<std::string, funcStr> StringSet;

/**
 * @brief Test dei metodi per set di interi
 * 
 * Test dei metodi per set di interi
 */
void testMetodiIntSet()
{

    std::stringstream ss;

    std::cout << "******** Test metodi del set di interi ********" << std::endl;

    IntSet intSet;  // ctor default

    std::cout << "- Test add degli elementi: { 5, 8, 8, 8, 1, 4 }" << std::endl;

    intSet.add(5); // add 
    intSet.add(8);
    intSet.add(8);
    intSet.add(8);
    intSet.add(1);
    intSet.add(4);

    std::cout << "Stampa di intSet dopo inserimenti:" << std::endl;
    std::cout << intSet << std::endl;  // operator<<
    ss << intSet;
    assert(intSet.getSize() == 4);
    assert(intSet.getCapacity() == 4);
    assert(ss.str() == "4 (5) (8) (1) (4)");
    ss.str("");

    IntSet intSet2(intSet);  // cctor

    std::cout << "Stampa di intSet2 dopo copy constructor:" << std::endl;
    std::cout << intSet2 << std::endl;  // operator<<
    ss << intSet2;
    assert(intSet == intSet2); // operator==
    assert(ss.str() == "4 (5) (8) (1) (4)");
    ss.str("");

    IntSet intSet3;

    intSet3 = intSet; // operator=

    std::cout << "Stampa di intSet3 dopo assegnamento:" << std::endl;
    std::cout << intSet3 << std::endl;  // operator<<
    ss << intSet3;
    assert(intSet == intSet3); // operator==
    assert(ss.str() == "4 (5) (8) (1) (4)");
    ss.str("");

    std::cout << "- Test remove degli elementi: {8, 1, 10}" << std::endl;

    intSet.remove(8); // remove
    intSet.remove(1);
    assert(intSet.remove(10) == false);

    std::cout << "Stampa di intSet dopo rimozione:" << std::endl;
    std::cout << intSet << std::endl;  // operator<<
    ss << intSet;
    assert(ss.str() == "2 (5) (4)");
    ss.str("");

    std::cout << "- Test contains degli elementi: {5, 4, 11, 14}" << std::endl;
    std::cout << "5:\t" << (intSet.contains(5) ? "true" : "false") << std::endl;
    std::cout << "4:\t" << (intSet.contains(4) ? "true" : "false") << std::endl;
    std::cout << "11:\t" << (intSet.contains(11) ? "true" : "false") << std::endl;
    std::cout << "14:\t" << (intSet.contains(14) ? "true" : "false") << std::endl;

    std::cout << "- Costruzione del set tramite iteratori (array contentente {45, 45, 56, 5, 6, 6, 45})" << std::endl;
    int testArray[] = {45, 45, 56, 5, 6, 6, 45};

    Set<int, funcInt> iterSet(testArray, testArray + 7); 
    std::cout << "Stampa di iterSet:" << std::endl;
    std::cout << iterSet << std::endl;
    ss << iterSet;
    assert(ss.str() == "4 (45) (56) (5) (6)");
    ss.str("");
}

/**
 * @brief Test dei metodi per set di stringhe
 * 
 * Test dei metodi per set di stringhe
 */
void testMetodiStringSet()
{

    std::stringstream ss;

    std::cout << "******** Test metodi del set di stringhe ********" << std::endl;

    StringSet stringSet;  // ctor default

    std::cout << "- Test add degli elementi: {E, H, H, H, A, D}" << std::endl;

    stringSet.add("E"); // add 
    stringSet.add("H");
    stringSet.add("H");
    stringSet.add("H");
    stringSet.add("A");
    stringSet.add("D");

    std::cout << "Stampa di stringSet dopo inserimenti:" << std::endl;
    std::cout << stringSet << std::endl;  // operator<<
    ss << stringSet;
    assert(stringSet.getSize() == 4);
    assert(stringSet.getCapacity() == 4);
    assert(ss.str() == "4 (E) (H) (A) (D)");
    ss.str("");

    StringSet stringSet2(stringSet);  // cctor

    std::cout << "Stampa di intSet2 dopo copy constructor:" << std::endl;
    std::cout << stringSet2 << std::endl;  // operator<<
    ss << stringSet2;
    assert(stringSet == stringSet2); // operator==
    assert(ss.str() == "4 (E) (H) (A) (D)");
    ss.str("");

    StringSet stringSet3;

    stringSet3 = stringSet2; // operator=

    std::cout << "Stampa di intSet3 dopo assegnamento:" << std::endl;
    std::cout << stringSet3 << std::endl;  // operator<<
    ss << stringSet3;
    assert(stringSet == stringSet3); // operator==
    assert(ss.str() == "4 (E) (H) (A) (D)");
    ss.str("");

    std::cout << "- Test remove degli elementi: {H, A, J}" << std::endl;

    stringSet.remove("H"); // remove
    stringSet.remove("A");
    assert(stringSet.remove("J") == false);

    std::cout << "Stampa di stringSet dopo rimozione:" << std::endl;
    std::cout << stringSet << std::endl;  // operator<<
    ss << stringSet;
    assert(ss.str() == "2 (E) (D)");
    ss.str("");

    std::cout << "- Test contains degli elementi: {E, D, K, N}" << std::endl;
    std::cout << "E:\t" << (stringSet.contains("E") ? "true" : "false") << std::endl;
    std::cout << "D:\t" << (stringSet.contains("D") ? "true" : "false") << std::endl;
    std::cout << "K:\t" << (stringSet.contains("K") ? "true" : "false") << std::endl;
    std::cout << "N:\t" << (stringSet.contains("N") ? "true" : "false") << std::endl;

    std::cout << "- Costruzione del set tramite iteratori (array contentente {a, a, b, c, d, d, a})" << std::endl;
    std::string testArray[] = {"a", "a", "b", "c", "d", "d", "a"};

    Set<std::string, funcStr> iterSet(testArray, testArray + 7); 
    std::cout << "Stampa di iterSet:" << std::endl;
    std::cout << iterSet << std::endl;
    ss << iterSet;
    assert(ss.str() == "4 (a) (b) (c) (d)");
    ss.str("");
}

class Book
{
public:
    Book(const std::string& ISBN, const std::string& title) : ISBN(ISBN), title(title){}
    Book(const std::string& ISBN, const std::string& title, const std::vector<std::string>& authors) : ISBN(ISBN), title(title), authors(authors){}

    const std::string& getISBN() const { return ISBN; }
    const std::string& getTitle() const { return title; }
    const std::vector<std::string>& getAuthors() const { return authors; }

private:
    std::string ISBN;
    std::string title;
    std::vector<std::string> authors;
};

std::ostream& operator<<(std::ostream& out, const Book& book)
{
    out << book.getISBN() << ": " << book.getTitle();
    return out;
}

struct funcBook
{
    bool operator()(const Book& a, const Book& b) const
    {
        return a.getISBN() == b.getISBN();
    }
};

struct predicateBook
{
    bool operator()(const Book& book) const
    {
        return book.getISBN().length() > 10;
    }
};

typedef Set<Book, funcBook> BookSet;

/**
 * @brief Test dei metodi per set di libri
 * 
 * Test dei metodi per set di libri
 */
void testMetodiBookSet()
{

    std::stringstream ss;

    std::cout << "******** Test metodi del set di libri ********" << std::endl;

    BookSet bookSet;  // ctor default

    std::cout << "- Test add degli elementi: {(9780151660346, 1984), (978349803808, To Kill a Mockingbird), (978349803808, To Kill a Mockingbird), (8869183157, Harry Potter and the Sorcerer's Stone), (9780007203550, The Lord of the Rings), (9780007203550, The Lord of the Rings)}" << std::endl;

    bookSet.add(Book("9780151660346", "1984")); // add 
    bookSet.add(Book("978349803808", "To Kill a Mockingbird"));
    assert(bookSet.add(Book("978349803808", "To Kill a Mockingbird")) == false);
    bookSet.add(Book("8869183157", "Harry Potter and the Sorcerer's Stone"));
    bookSet.add(Book("9780007203550", "The Lord of the Rings"));
    assert(bookSet.add(Book("9780007203550", "The Lord of the Rings")) == false);

    std::cout << "Stampa di bookSet dopo inserimenti:" << std::endl;
    std::cout << bookSet << std::endl;  // operator<<
    ss << bookSet;
    assert(bookSet.getSize() == 4);
    assert(bookSet.getCapacity() == 4);
    assert(ss.str() == "4 (9780151660346: 1984) (978349803808: To Kill a Mockingbird) (8869183157: Harry Potter and the Sorcerer's Stone) (9780007203550: The Lord of the Rings)");
    ss.str("");

    BookSet bookSet2(bookSet);  // cctor

    std::cout << "Stampa di bookSet2 dopo copy constructor:" << std::endl;
    std::cout << bookSet2 << std::endl;  // operator<<
    ss << bookSet2;
    assert(bookSet == bookSet2); // operator==
    assert(ss.str() == "4 (9780151660346: 1984) (978349803808: To Kill a Mockingbird) (8869183157: Harry Potter and the Sorcerer's Stone) (9780007203550: The Lord of the Rings)");
    ss.str("");

    BookSet bookSet3;

    bookSet3 = bookSet2; // operator=

    std::cout << "Stampa di bookSet3 dopo assegnamento:" << std::endl;
    std::cout << bookSet3 << std::endl;  // operator<<
    ss << bookSet3;
    assert(bookSet == bookSet3); // operator==
    assert(ss.str() == "4 (9780151660346: 1984) (978349803808: To Kill a Mockingbird) (8869183157: Harry Potter and the Sorcerer's Stone) (9780007203550: The Lord of the Rings)");
    ss.str("");

    std::cout << "- Test remove degli elementi: {(9780151660346, 1984), (9780007203550, The Lord of the Rings), (1234, AAAA)}" << std::endl;

    bookSet.remove(Book("9780151660346", "1984")); // remove
    bookSet.remove(Book("9780007203550", "The Lord of the Rings"));
    assert(bookSet.remove(Book("1234", "AAAA")) == false);

    std::cout << "Stampa di bookSet dopo rimozione:" << std::endl;
    std::cout << bookSet << std::endl;  // operator<<
    ss << bookSet;
    assert(ss.str() == "2 (978349803808: To Kill a Mockingbird) (8869183157: Harry Potter and the Sorcerer's Stone)");
    ss.str("");

    std::cout << "- Test contains degli elementi: {(9780151660346, 1984), (978349803808, To Kill a Mockingbird), (1234, AAAA), (5678, BBBB)}" << std::endl;
    std::cout << "(9780151660346, 1984):\t" << (bookSet.contains(Book("9780151660346", "1984")) ? "true" : "false") << std::endl;
    std::cout << "(978349803808, To Kill a Mockingbird):\t" << (bookSet.contains(Book("978349803808", "To Kill a Mockingbird")) ? "true" : "false") << std::endl;
    std::cout << "(1234, AAAA):\t" << (bookSet.contains(Book("1234", "AAAA")) ? "true" : "false") << std::endl;
    std::cout << "(5678, BBBB):\t" << (bookSet.contains(Book("5678", "BBBB")) ? "true" : "false") << std::endl;

    std::cout << "- Costruzione del set tramite iteratori (array contentente {(9780151660346, 1984), (978349803808, To Kill a Mockingbird), (978349803808, To Kill a Mockingbird), (8869183157, Harry Potter and the Sorcerer's Stone), (9780007203550, The Lord of the Rings), (9780007203550, The Lord of the Rings)})" << std::endl;
    Book testArray[] = {{"9780151660346", "1984"}, {"978349803808", "To Kill a Mockingbird"}, {"978349803808", "To Kill a Mockingbird"}, {"8869183157", "Harry Potter and the Sorcerer's Stone"}, {"9780007203550", "The Lord of the Rings"}, {"9780007203550", "The Lord of the Rings"}};

    Set<Book, funcBook> iterSet(testArray, testArray + 6); 
    std::cout << "Stampa di iterSet:" << std::endl;
    std::cout << iterSet << std::endl;
    ss << iterSet;
    assert(ss.str() == "4 (9780151660346: 1984) (978349803808: To Kill a Mockingbird) (8869183157: Harry Potter and the Sorcerer's Stone) (9780007203550: The Lord of the Rings)");
    ss.str("");
}

/**
 * @brief Test dei metodi di iterazione per Set generici.
 * 
 * @tparam T Tipo degli elementi nel set..
 * @tparam Equal Funtore per il confronto di uguaglianza. 
 * @param testSet Set oggetto del test.
 */
template<typename T, typename Equal>
void testMetodiDiIterazione(const Set<T, Equal>& testSet)
{
    std::cout << "******** Test metodi di iterazione del set generico ********" << std::endl;

    std::cout << "- Test Operator[]" << std::endl;
    for(int i = 0; i < testSet.getSize(); i++)
    {
        std::cout << i << ": " << testSet[i] << std::endl;
    }

    std::cout << "- Test Const Iterator" << std::endl;
    auto i = testSet.begin();
    auto ie = testSet.end();
    for(; i != ie; ++i)
    {
        std::cout << *i << std::endl;
    }
}

/**
 * @brief Test dei metodi globali.
 * 
 * Test dei metodi globali su interi e su libri.
 * 
 */
void testMetodiGlobali()
{
    std::stringstream ss;

    IntSet intA;
    intA.add(5);
    intA.add(8);
    intA.add(8);
    intA.add(8);
    intA.add(1);
    intA.add(4);

    IntSet intB;
    intB.add(4);
    intB.add(7);
    intB.add(765);
    intB.add(56);
    intB.add(65);
    intB.add(33);
    intB.add(1);
    intB.add(8);

    std::cout << "******** Test metodi globali ********" << std::endl;

    std::cout << "Stampa dei set di test (interi)" << std::endl;

    std::cout << "intA: " << intA << std::endl;
    std::cout << "intB: " << intB << std::endl;

    std::cout << "Test filter_out su intB (true se > 5)" << std::endl;

    auto filtered = filter_out(intB, predicateInt());
    std::cout << filtered << std::endl;
    ss << filtered;
    assert(ss.str() == "6 (7) (765) (56) (65) (33) (8)");
    ss.str("");

    std::cout << "- Test unione tra set" << std::endl;
    auto setUnion = intA + intB;
    std::cout << setUnion << std::endl;
    ss << setUnion;
    assert(ss.str() == "9 (5) (8) (1) (4) (7) (765) (56) (65) (33)");
    ss.str("");

    std::cout << "- Test intersezione tra set" << std::endl;
    auto setIntersection = intA - intB;
    std::cout << setIntersection << std::endl;
    ss << setIntersection;
    assert(ss.str() == "3 (4) (1) (8)");
    ss.str("");


    BookSet bookA;
    bookA.add(Book("9780151660346", "1984"));
    bookA.add(Book("978349803808", "To Kill a Mockingbird"));
    bookA.add(Book("978349803808", "To Kill a Mockingbird"));
    bookA.add(Book("8869183157", "Harry Potter and the Sorcerer's Stone"));
    bookA.add(Book("9780007203550", "The Lord of the Rings"));
    bookA.add(Book("9780007203550", "The Lord of the Rings"));

    BookSet bookB;
    bookB.add(Book("9780151660346", "1984"));
    bookB.add(Book("1234", "AAAA"));
    bookB.add(Book("5678", "BBBB"));

    std::cout << "******** Test metodi globali ********" << std::endl;

    std::cout << "Stampa dei set di test (libri)" << std::endl;

    std::cout << "bookA: " << bookA << std::endl;
    std::cout << "bookB: " << bookB << std::endl;

    std::cout << "Test filter_out su bookA (true se length(ISBN) > 10)" << std::endl;

    auto filteredB = filter_out(bookA, predicateBook());
    std::cout << filteredB << std::endl;
    ss << filteredB;
    assert(ss.str() == "3 (9780151660346: 1984) (978349803808: To Kill a Mockingbird) (9780007203550: The Lord of the Rings)");
    ss.str("");

    std::cout << "- Test unione tra set" << std::endl;
    auto setUnionB = bookA + bookB;
    std::cout << setUnionB << std::endl;
    ss << setUnionB;
    assert(ss.str() == "6 (9780151660346: 1984) (978349803808: To Kill a Mockingbird) (8869183157: Harry Potter and the Sorcerer's Stone) (9780007203550: The Lord of the Rings) (1234: AAAA) (5678: BBBB)");
    ss.str("");

    std::cout << "- Test intersezione tra set" << std::endl;
    auto setIntersectionB = bookA - bookB;
    std::cout << setIntersectionB << std::endl;
    ss << setIntersectionB;
    assert(ss.str() == "1 (9780151660346: 1984)");
    ss.str("");
}

/**
 * @brief Test metodo save.
 * 
 * Test metodo save.
 * 
 */
void testSave()
{
    std::stringstream ss;

    std::cout << "******** Test metodo save ********" << std::endl;

    StringSet stringSet;

    stringSet.add("E");
    stringSet.add("H");
    stringSet.add("H");
    stringSet.add("H");
    stringSet.add("A");
    stringSet.add("D");

    std::cout << "Stampa del set di test" << std::endl;
    std::cout << stringSet << std::endl;

    save(stringSet, "stringSet.txt");
    
    try
    {
        std::ifstream input("stringSet.txt");

        ss << input.rdbuf();
        std::cout << "Stampa del contenuto del file" << std::endl;
        std::cout << ss.str() << std::endl;
        assert(ss.str() == "E\nH\nA\nD\n");
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error("Impossibile aprire il file");
    }
    
}


int main()
{
    testMetodiIntSet();
    std::cout << "\n\n";
    testMetodiStringSet();
    std::cout << "\n\n";
    testMetodiBookSet();
    std::cout << "\n\n";
    IntSet intSet;
    intSet.add(5);
    intSet.add(8);
    intSet.add(8);
    intSet.add(8);
    intSet.add(1);
    intSet.add(4);
    testMetodiDiIterazione(intSet);
    std::cout << "\n\n";

    BookSet bookSet;
    bookSet.add(Book("9780151660346", "1984"));
    bookSet.add(Book("978349803808", "To Kill a Mockingbird"));
    bookSet.add(Book("978349803808", "To Kill a Mockingbird"));
    bookSet.add(Book("8869183157", "Harry Potter and the Sorcerer's Stone"));
    bookSet.add(Book("9780007203550", "The Lord of the Rings"));
    bookSet.add(Book("9780007203550", "The Lord of the Rings"));
    testMetodiDiIterazione(bookSet);

    std::cout << "\n\n";
    testMetodiGlobali();

    testSave();
    return 0;
}
