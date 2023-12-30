#ifndef GSET_HPP
#define GSET_HPP

#include <string>
#include <ostream>
#include <fstream>
#include <stdexcept>

template<typename T, typename Equal>
class Set
{
public:
    Set() : mData(nullptr), mSize(0), mCapacity(0){}

    Set(const Set& other) : mData(nullptr), mEq(other.mEq), mSize(0), mCapacity(0)
    {
        try
        {
            resize(other.mCapacity);
            mSize = other.mSize;

            for(int i = 0; i < mSize; i++)
            {
                mData[i] = other[i];
            }
        }
        catch(...)
        {
            empty();
            throw;
        }
    }

    template<typename Iter>
    Set(Iter begin, Iter end)
    {
        for(; begin != end; begin++)
        {
            add(static_cast<T>(*begin));
        }
    }

    ~Set()
    {
        empty();
    }

    Set& operator=(const Set& other)
    {
        if(this == &other)
            return *this;

        resize(other.mCapacity);
        mSize = other.mSize;

        for(int i = 0; i < mSize; i++)
        {
            mData[i] = other[i];
        }

        return *this;
    }

    bool add(const T& value)
    {

        for(int i = 0; i < mSize; i++)
        {
            if(mEq(mData[i], value))
                return false; //Elemento già presente
        }

        try
        {
            if(mData == nullptr)
            {
                resize(2);
            }
            if(mSize == mCapacity)
            {
                resize(mCapacity + mCapacity / 2);
            }
        
            mData[mSize] = value;
            mSize++;
        }
        catch(...)
        {
            empty();
            throw;
        }
        
        return true;
    }

    bool remove(const T& value)
    {
        for(int i = 0; i < mSize; i++)
        {
            if(mEq(mData[i], value))
            {
                shiftLeft(i);
                mSize--;
                return true;
            }
        }

        return false; //Elemento assente
    }

    bool contains(const T& value) const
    {
        for(int i = 0; i < mSize; i++)
        {
            if(mEq(mData[i], value))
                return true;
        }

        return false;
    }

    void empty()
    {
        if(mData != nullptr)
        {
            delete[] mData;
            mData = nullptr;
        }
        
        mSize = 0;
        mCapacity = 0;
    }

    T operator[](unsigned int index) const
    {
        if(index < 0 || index >= mSize)
            throw std::logic_error("index out of bounds"); //index out of bounds
        return mData[index];
    }

    bool operator==(const Set& other) const
    {
        if(mSize != other.mSize)
            return false;

        for(int i = 0; i < mSize; i++)
        {
            if(!contains(other[i]))
                return false;
        }

        return true;
    }

    Set operator+(const Set& other) const
    {
        Set res(*this);
        for(int i = 0; i < other.mSize; i++)
        {
            res.add(other[i]);
        }

        return res;
    }

    Set operator-(const Set& other) const
    {
        Set res;
        for(int i = 0; i < other.mSize; i++)
        {
            if(contains(other[i]))
                res.add(other[i]);
        }

        return res;
    }

    friend std::ostream& operator<<(std::ostream& out, const Set& set)
    {
        out << set.mSize;
        for(int i = 0; i < set.mSize; i++)
        {
            out << " (" << set[i] << ")";
        }

        return out;
    }

    unsigned int getSize() const { return mSize; }
    unsigned int getCapacity() const { return mCapacity; }

    ///CONST ITERATOR

    class const_iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer; //LASCIARE TIPO T, NIENTE NODE E SIMILI!!!
		typedef const T&                  reference;

	
		const_iterator() : n(nullptr) {}
		
		const_iterator(const const_iterator &other) : n(other.n) {}

		const_iterator& operator=(const const_iterator &other)
        {
            n = other.n;
			return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const 
        {
            return *n;
        }

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const 
        {
			return n;
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) 
        {
			const_iterator tmp(*this);
            n++;
            return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++()
        {
			n++;
            return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const
        {
			return n == other.n;
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const 
        {
			return !(other == *this);
		}

	private:
		//Dati membro
        const T* n;

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class Set; // !!! Da cambiare il nome!

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const T* nn) : n(nn) { } //PARTE FONDAMENTALE DELL'ITERATORE!!!
		
		// !!! Eventuali altri metodi privati
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const 
    {
		return const_iterator(mData);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const
    {
		return const_iterator(&mData[mSize]);
	}

private:
    void resize(unsigned int newSize)
    {
        T* tmp = new T[newSize];
        
        for(int i = 0; i < mSize; i++)
        {
            tmp[i] = mData[i];
        }

        if(mData != nullptr)
            delete[] mData;
        mCapacity = newSize;
        mData = tmp;
    }

    void shiftLeft(int index)
    {
        for(int i = index; i < mSize - 1; i++)
        {
            mData[i] = mData[i + 1];
        }
    }

private:
    T* mData;               //Puntatore ai dati
    Equal mEq;              //Funtore per confronto elementi
    unsigned int mSize;     //Numero di elementi presenti
    unsigned int mCapacity; //Numero di elementi inseribili
};

template<typename T, typename Equal, typename Pred>
Set<T, Equal> filter_out(const Set<T, Equal>& set, Pred pred)
{
    Set<T, Equal> res;
    for(int i = 0; i < set.getSize(); i++)
    {
        if(pred(set[i]))
            res.add(set[i]);
    }

    return res;
}

template<typename Equal>
void save(const Set<std::string, Equal>& set, const std::string& path)
{
    std::ofstream file(path);
    for(unsigned int i = 0; i < set.getSize(); i++)
    {
        file << set[i] << '\n';
    }
}

#endif