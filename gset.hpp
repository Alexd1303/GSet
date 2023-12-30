#ifndef GSET_HPP
#define GSET_HPP

#include <string>
#include <ostream>
#include <fstream>
#include <stdexcept>

/**
 * @brief Implementazione di un set generico.
 * 
 * @tparam T Tipo degli elementi nel set.
 * @tparam Equal Functore per il confronto di uguaglianza.
 */
template<typename T, typename Equal>
class Set
{
public:
    /**
     * @brief Costruttore di default.
     */
    Set() : mData(nullptr), mSize(0), mCapacity(0){}

    /**
     * @brief Costruttore di copia.
     *
     * @param other Altro set da copiare.
     */
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

    /**
     * @brief Costruttore da coppia generica di iteratori.
     * 
     * @tparam Iter Tipo dell'iteratore.
     * @param begin Iteratore di inizio.
     * @param end Iteratore di fine.
     */
    template<typename Iter>
    Set(Iter begin, Iter end)
    {
        for(; begin != end; begin++)
        {
            add(static_cast<T>(*begin));
        }
    }

    /**
     * @brief Distruttore.
     */
    ~Set()
    {
        empty();
    }

    /**
     * @brief Operatore di assegnamento.
     * 
     * @param other Altro set da assegnare.
     * @return Set& Riferimento al set corrente.
     */
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

    /**
     * @brief Aggiunge un elemento al set.
     * 
     * @param value Valore da aggiungere.
     * @return true Se l'elemento è stato aggiunto con successo.
     * @return false Se l'elemento è già presente nel set.
     */
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

    /**
     * @brief Rimuove un elemento dal set.
     * 
     * @param value Valore da rimuovere.
     * @return true Se l'elemento è stato rimosso con successo.
     * @return false Se l'elemento non è presente nel set.
     */
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

    /**
     * @brief Verifica se un elemento è presente nel set.
     * 
     * @param value Valore da cercare.
     * @return true Se l'elemento è presente.
     * @return false Se l'elemento non è presente.
     */
    bool contains(const T& value) const
    {
        for(int i = 0; i < mSize; i++)
        {
            if(mEq(mData[i], value))
                return true;
        }

        return false;
    }

    /**
     * @brief Svuota il set.
     */
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
    
    /**
     * @brief Operatore di accesso agli elementi del set.
     * 
     * @param index Indice dell'elemento.
     * @return T elemento.
     */
    T operator[](unsigned int index) const
    {
        if(index < 0 || index >= mSize)
            throw std::logic_error("index out of bounds"); //index out of bounds
        return mData[index];
    }

    /**
     * @brief Operatore di confronto di uguaglianza tra set.
     * 
     * @param other Altro set da confrontare.
     * @return true Se i set sono uguali.
     * @return false Se i set non sono uguali.
     */
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

    /**
     * @brief Operatore di unione tra set.
     * 
     * @param other Altro set da unire.
     * @return Set Unione dei due set.
     */
    Set operator+(const Set& other) const
    {
        Set res(*this);
        for(int i = 0; i < other.mSize; i++)
        {
            res.add(other[i]);
        }

        return res;
    }

    /**
     * @brief Operatore di differenza tra set.
     * 
     * @param other Altro set da sottrarre.
     * @return Set Differenza dei due set.
     */
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

    /**
     * @brief Operatore di stream per la stampa del set.
     * 
     * @param out Stream di output.
     * @param set Set da stampare.
     * @return std::ostream& Stream di output.
     */
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
		typedef const T*                  pointer;
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
		friend class Set;

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const T* nn) : n(nn) { }
		
		// !!! Eventuali altri metodi privati
		
	}; // classe const_iterator
	
	/**
     * @brief Ritorna l'iteratore all'inizio della sequenza dati.
     * 
     * @return const_iterator Iteratore all'inizio della sequenza dati.
     */
	const_iterator begin() const 
    {
		return const_iterator(mData);
	}
	
	/**
     * @brief Ritorna l'iteratore alla fine della sequenza dati.
     * 
     * @return const_iterator Iteratore alla fine della sequenza dati.
     */
	const_iterator end() const
    {
		return const_iterator(&mData[mSize]);
	}

private:
    /**
     * @brief Ridimensiona la capacità del set.
     * 
     * @param newSize Nuova dimensione del set.
     */
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

    /**
     * @brief Sposta gli elementi a sinistra a partire dall'indice specificato.
     * 
     * @param index Indice da cui iniziare lo spostamento.
     */
    void shiftLeft(int index)
    {
        for(int i = index; i < mSize - 1; i++)
        {
            mData[i] = mData[i + 1];
        }
    }

private:
    T* mData;               //Puntatore ai dati
    Equal mEq;              //Functore per confronto elementi
    unsigned int mSize;     //Numero di elementi presenti
    unsigned int mCapacity; //Numero di elementi inseribili
};


/**
 * @brief Filtra gli elementi di un set in base a un predicato.
 * 
 * @tparam T Tipo degli elementi nel set.
 * @tparam Equal Functore per il confronto di uguaglianza.
 * @tparam Pred Predicato per il filtraggio.
 * @param set Set di input.
 * @param pred Predicato di filtro.
 * @return Set<T, Equal> Set filtrato.
 */
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

/**
 * @brief Salva un set di stringhe su un file.
 * 
 * @tparam Equal Functore per il confronto di uguaglianza.
 * @param set Set di stringhe di input.
 * @param path Percorso del file per salvare il set.
 */
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