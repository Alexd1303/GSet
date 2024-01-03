/**
 * @file gset.hpp
 * 
 * @brief file header della classe templata Set.
 * 
 * Definizione e implementazione di un set generico.
 */

#ifndef GSET_HPP
#define GSET_HPP

#include <string>
#include <ostream>
#include <fstream>
#include <stdexcept>

/**
 * @brief Classe Set generica.
 * 
 * La classe implementa un generico set di oggetti T, 
 * in cui ogni oggetto può comparire al massimo una volta.
 * La valutazione se due dati di tipo T sono uguali è realizzata
 * tramite un secondo funtore Equal.
 * 
 * @tparam T Tipo degli elementi nel set.
 * @tparam Equal Funtore per il confronto di uguaglianza.
 */
template<typename T, typename Equal>
class Set
{
public:
    /**
     * @brief Costruttore di default.
     * 
     * @post mData = nullptr, mSize = 0, mCapacity = 0.
     */
    Set() : mData(nullptr), mSize(0), mCapacity(0){}

    /**
     * @brief Costruttore di copia.
     *
     * @param other Altro set da copiare.
     * 
     * @throw eccezione di allocazione
     */
    Set(const Set& other) : mData(nullptr), mEq(other.mEq), mSize(0), mCapacity(0)
    {
        try
        {
            resize(other.mCapacity);
            mSize = other.mSize;

            for(int i = 0; i < mSize; i++)
            {
                mData[i] = new T(other[i]);
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
     * 
     * @throw errore di allocazione
     */
    template <typename Iter>
    Set(Iter begin, Iter end) : mData(nullptr), mSize(0), mCapacity(0)
    {
        Iter curr = begin;
        try 
        {
            for(; curr!=end; ++curr)
            {
                add(static_cast<T>(*curr));
            }
        }
        catch(...)
        {
            empty();
            throw;
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
     * 
     * @throw eccezione di allocazione
     */
    Set& operator=(const Set& other)
    {
        if(this == &other)
            return *this;

        try
        {
            resize(other.mCapacity);
            mSize = other.mSize;

            for(int i = 0; i < mSize; i++)
            {
                mData[i] = new T(other[i]);
            }
        }
        catch(...)
        {
            empty();
            throw;
        }

        return *this;
    }

    /**
     * @brief Aggiunge un elemento al set.
     * 
     * Aggiunge un elemento al set, verificando 
     * prima che questo non sia già presente.
     * Nel caso in cui la memoria preallocata non sia sufficiente
     * per ospitare il nuovo elemento viene incrementata la
     * dimensione della struttura sottostante.
     * 
     * @param value Valore da aggiungere.
     * @return true Se l'elemento è stato aggiunto con successo.
     * @return false Se l'elemento è già presente nel set.
     */
    bool add(const T& value)
    {

        if(contains(value))
            return false; //Elemento già presente

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
        
            mData[mSize] = new T(value);
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
            if(mEq(*mData[i], value))
            {
                delete mData[i];
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
     * Verifica se un elemento è presente nel set.
     * Utilizza in funtore di uguaglianza Equal
     * 
     * @param value Valore da cercare.
     * @return true se l'elemento è presente.
     * @return false se l'elemento non è presente.
     */
    bool contains(const T& value) const
    {
        for(int i = 0; i < mSize; i++)
        {
            if(mEq(*mData[i], value))
                return true;
        }

        return false;
    }

    /**
     * @brief Svuota il set.
     * 
     * @post mData = nullptr, mSize = 0, mCapacity = 0
     */
    void empty()
    {
        if(mData != nullptr)
        {
            for(unsigned int i = 0; i < mSize; i++)
            {
                delete mData[i];
            }
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
     * 
     * @throw std::out_of_range se l'indice è fuori dai limit.
     */
    T operator[](unsigned int index) const
    {
        if(index < 0 || index >= mSize)
            throw std::out_of_range("index out of bounds"); //index out of bounds
        return *mData[index];
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
            return **n;
        }

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const 
        {
			return *n;
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
        const T* const* n;

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class Set;

		// Costruttore privato di inizializzazione usato dalla classe container
		const_iterator(const T* const* nn) : n(nn) { }
		
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
        T** tmp = new T*[newSize];
        
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
    T** mData;               //Puntatore ai dati
    Equal mEq;              //Funtore per confronto elementi
    unsigned int mSize;     //Numero di elementi presenti
    unsigned int mCapacity; //Numero di elementi inseribili
};


/**
 * @brief Filtra gli elementi di un set in base a un predicato.
 * 
 * Funzione GLOBALE che ritorna un set contente 
 * gli elementi di set che soddisfano il predicato pred.
 * 
 * @tparam T Tipo degli elementi nel set.
 * @tparam Equal Funtore per il confronto di uguaglianza.
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
 * @brief Operatore di unione tra set.
 * 
 * Funzione GLOBALE che ritorna un set i cui elementi 
 * sono il risultato dell'unione dei due set passati come argomento.
 * 
 * @param set1 Primo set da unire.
 * @param set2 Altro set da unire.
 * @return Set Unione dei due set.
 */
template<typename T, typename Equal>
Set<T, Equal> operator+(const Set<T, Equal>& set1, const Set<T, Equal>& set2)
{
    Set<T, Equal> res(set1);
    for(int i = 0; i < set2.getSize(); i++)
    {
        res.add(set2[i]);
    }

    return res;
}

/**
 * @brief Operatore di intersezione tra set.
 * 
 * Funzione GLOBALE che ritorna un set i cui elementi 
 * sono il risultato dell'intersezione dei due set passati come argomento.
 * 
 * @param set1 Primo set da intersecare.
 * @param set2 Altro set da intersecare.
 * @return Set Intersezione dei due set.
 */
template<typename T, typename Equal>
Set<T, Equal> operator-(const Set<T, Equal>& set1, const Set<T, Equal>& set2)
{
    Set<T, Equal> res;
    for(int i = 0; i < set2.getSize(); i++)
    {
        if(set1.contains(set2[i]))
            res.add(set2[i]);
    }

    return res;
}

/**
 * @brief Salva un set di stringhe su un file.
 * 
 * @tparam Equal Funtore per il confronto di uguaglianza.
 * @param set Set di stringhe di input.
 * @param path Percorso del file per salvare il set.
 */
template<typename Equal>
void save(const Set<std::string, Equal>& set, const std::string& path)
{
    try
    {
        std::ofstream file(path);
        for(unsigned int i = 0; i < set.getSize(); i++)
        {
            file << set[i] << '\n';
        }
    }
    catch(...)
    {
        throw std::runtime_error("Impossibile aprire il file per la scrittura");
    }
}

#endif