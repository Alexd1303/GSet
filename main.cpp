#include <iostream>
#include <cassert>
#include <sstream>
#include "gset.hpp"

struct funcInt
{
    bool operator()(int a, int b) const
    {
        return a == b;
    }
};

struct funcStr
{
    bool operator()(const std::string& a, const std::string& b) const
    {
        return a == b;
    }
};

struct Point
{
    int x, y;

    Point() = default;
    Point(int x, int y) : x(x), y(y) {}
};

struct funcPoint
{
    bool operator()(const Point& a, const Point& b) const
    {
        return a.x == b.x && a.y == b.y;
    }
};


struct predicateInt
{
    bool operator()(int a) const
    {
        return a > 5;
    }
};

typedef Set<int, funcInt> IntSet;
typedef Set<std::string, funcStr> StringSet;

void testMetodiFondamentaliIntSet()
{

    std::stringstream ss;

    std::cout << "******** Test metodi fondamentali del set di interi ********" << std::endl;

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
}

void testMetodiFondamentaliStringSet()
{

    std::stringstream ss;

    std::cout << "******** Test metodi fondamentali del set di stringhe ********" << std::endl;

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

}

template<typename T, typename Equal>
void testMetodiDiIterazione(const Set<T, Equal>& testSet)
{
    std::cout << "******** Test metodi di iterazione del set generico ********" << std::endl;

    std::cout << "- Operator[]" << std::endl;
    for(int i = 0; i < testSet.getSize(); i++)
    {
        std::cout << i << ": " << testSet[i] << std::endl;
    }

    std::cout << "- Const Iterator" << std::endl;
    auto i = testSet.begin();
    auto ie = testSet.end();
    for(; i != ie; ++i)
    {
        std::cout << *i << std::endl;
    }
}


int main()
{
    testMetodiFondamentaliIntSet();
    std::cout << "\n\n";
    testMetodiFondamentaliStringSet();
    std::cout << "\n\n";
    IntSet intSet;
    intSet.add(5);
    intSet.add(8);
    intSet.add(8);
    intSet.add(8);
    intSet.add(1);
    intSet.add(4);
    testMetodiDiIterazione(intSet);

    return 0;
}
