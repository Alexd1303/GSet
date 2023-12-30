#include <iostream>
#include <cassert>
#include <sstream>
#include "gset.hpp"
#include "dipinto.hpp"

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

struct funcDipinto
{
    bool operator()(const Dipinto& a, const Dipinto& b) const
    {
        return a == b;
    }
};

struct predicateInt
{
    bool operator()(int a) const
    {
        return a > 5;
    }
};

template<typename T>
struct Wrapper
{
    T* value;
};


int main()
{
    //string stream per testare le stampe
    std::stringstream ss;

    Set<int, funcInt> set;
    ss << set;
    assert(ss.str() == "0");

    //test add
    ss.str(std::string());
    assert(set.add(5));
    assert(set.add(4));
    assert(set.add(4) == false);
    assert(set.add(6));
    assert(set.add(7));
    ss << set;
    assert(ss.str() == "4 (5) (4) (6) (7)");

    //test copy
    Set<int, funcInt> copy = set;

    assert(set.getSize() == copy.getSize());
    assert(set.getCapacity() == copy.getCapacity());
    assert(set == copy);

    //test assegnamento
    Set<int, funcInt> empty;
    empty = set;
    assert(empty == set);

    //test creazione da iteratore
    ss.str(std::string());
    std::vector<int> testVec = { 1,2,3,3,3,5,6,6,7,7 };
    Set<int, funcInt> fromIterSet(testVec.begin(), testVec.end());
    ss << fromIterSet;
    assert(ss.str() == "6 (1) (2) (3) (5) (6) (7)");

    //test remove
    ss.str(std::string());
    assert(set.remove(5));
    assert(set.remove(10) == false);
    assert(set.remove(7));
    ss << set;
    assert(ss.str() == "2 (4) (6)");

    //test contains
    assert(set.contains(4));
    assert(set.contains(15) == false);

    //test []
    for(int i = 0; i < copy.getSize(); i++)
    {
        std::cout << copy[i] << std::endl;
    }
    std::cout << std::endl;

    try
    {
        copy[copy.getSize()];
        assert(false);
    }
    catch(...)
    {
        assert(true);
    }
    

    //test +
    ss.str(std::string());
    Set<int, funcInt> tmp;
    tmp.add(9),
    tmp.add(4);
    tmp.add(15);

    auto setUnion = set + tmp;
    ss << setUnion;
    assert(ss.str() == "4 (4) (6) (9) (15)");

    //test -
    ss.str(std::string());

    auto setIntersection = set - tmp;
    ss << setIntersection;
    assert(ss.str() == "1 (4)");

    //test filter_out
    ss.str(std::string());
    predicateInt pred;
    auto res = filter_out(setUnion, pred);
    ss << res;
    assert(ss.str() == "3 (6) (9) (15)");

    //test save
    Set<std::string, funcStr> stringSet;

    stringSet.add("ciao");
    stringSet.add("mondo");
    stringSet.add("ciao");
    stringSet.add("1");
    stringSet.add("2");
    stringSet.add("3");
    stringSet.add("4");

    save(stringSet, "testSet.txt");

    //iteratori
    auto i = setUnion.begin();
    auto ie = setUnion.end();

    for(; i != ie; i++)
    {
        std::cout << *i << std::endl;
    }

    //custom set
    Set<Dipinto, funcDipinto> setDipinti;
    setDipinti.add(Dipinto("a", "b", "c", "d", "e"));
    setDipinti.add(Dipinto("a", "b", "c", "d", "e"));
    setDipinti.add(Dipinto("f", "g", "h", "i", "j"));

    auto id = setDipinti.begin();
    auto ied = setDipinti.end();

    for(; id != ied; id++)
    {
        id->testMethod();
    }
    

    return 0;
}
