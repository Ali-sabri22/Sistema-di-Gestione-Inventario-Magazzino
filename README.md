# Sistema-di-Gestione-Inventario-Magazzino
Questo progetto è un sistema completo per la gestione di un magazzino, sviluppato in C++ con un'interfaccia a console. Il sistema permette di gestire prodotti, movimenti di stock, ordini e generare report, mantenendo la persistenza dei dati tramite backup su file.

Caratteristiche principali:
Gestione prodotti:

Aggiunta nuovi articoli (codice, nome, quantità, prezzo)

Ricerca prodotti per codice

Capacità massima: 100 prodotti

Movimenti di magazzino:

Registrazione entrate/uscite (con controllo quantità)

Tracciamento data e tipo movimento

Capacità massima: 1000 movimenti

Gestione ordini:

Creazione ordini di riapprovvigionamento

Registrazione data ordine e quantità

Reportistica:

Visualizzazione inventario completo

Lista movimenti storici

Ordini in corso

Formattazione tabellare per migliorare la leggibilità

Backup dati:

Salvataggio automatico in formato tabellare leggibile

Caricamento dati all'avvio

File di backup: "inventario.txt"
