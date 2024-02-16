# Set Class - Progetto C++

## Autore
Alessandro Dubini  
Matricola: 885957

## Panoramica del Progetto
Questo progetto in C++ include l'implementazione di una classe set generica, con la possibilità di definire un funtore personalizzato per il confronto di uguaglianza tra elementi. Il set supporta operazioni comuni come l'aggiunta, la rimozione, la verifica della presenza di un elemento, l'iterazione e fornisce operatori di unione e intersezione tra set.

## Ambienti Testati
- MSVC 19 (Windows 11)
- Clang++ 15.0.0 (MacOS)
- g++ 9.4.0 (Ubuntu VM)
- g++ 11.4.0 (Ubuntu)

## Scelte di Implementazione
### Struttura dei Dati
L'implementazione utilizza un array di tipo generico T per rispettare i requisiti del progetto. I vantaggi chiave includono: memoria compatta, tempi di accesso più veloci, tempo di aggiunta inferiore senza ridimensionamento e verifica più rapida dell'unicità.

### Considerazioni di Implementazione
- Il tempo per l'aggiunta di un elemento aumenta quando è necessario ridimensionare.
- Aumento del tempo di rimozione dovuto allo spostamento dei dati a sinistra.
- Possibile spreco di memoria se viene rimosso un numero significativo di elementi da un Set grande.

### Requisito del Costruttore
Per utilizzare una struttura ad array e beneficiare dei vantaggi menzionati, tutte le classi utilizzate con questo Set devono definire un costruttore predefinito o un costruttore chiamabile senza argomenti.

### Evitare `add` nel Costruttore di Copia e nell'Operatore di Assegnamento
Per garantire l'unicità degli elementi durante la creazione di un Set da un altro Set, si evita il metodo `add` per evitare controlli ridondanti sull'unicità. Invece, viene eseguita una copia diretta delle strutture interne.

### Fattore di Crescita della Capacità
La capacità del set cresce secondo la formula: `mCapacity = 2` se `mCapacity = 0`, altrimenti `mCapacity + ceil(mCapacity/2)` se `mCapacity >= 2`. Questa scelta mira a fornire spazio sufficiente per le aggiunte successive, limitando le chiamate di ridimensionamento e minimizzando lo spreco di memoria.

### Tipo di Ritorno dei Metodi `add` e `remove`
Entrambi i metodi `add` e `remove` restituiscono un valore booleano che indica il successo dell'operazione (true se riuscita, false altrimenti).

### Aggiunta del Metodo `empty`
Il metodo `empty`, progettato per svuotare il set, garantisce che il set rimanga in uno stato coerente in caso di eccezioni (ad esempio, errori di allocazione di memoria).

### Tipo di Iteratore Costante: Forward Iterator
Dato che il set è una struttura dati in cui l'unica caratteristica distintiva è l'unicità degli elementi e non vi è alcuna garanzia dell'ordine, è scelto un iteratore forward. Altri tipi di iteratori (bidirezionale o casuale) sono considerati superflui e non utili.

**Nota:** L'attuale ordine degli elementi è casuale e potrebbe cambiare nelle implementazioni future.