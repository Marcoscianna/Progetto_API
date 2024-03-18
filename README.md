# Prova finale del corso Algoritmi e Principi dell'Informatica, anno accademico 2022/2023

Docente: Davide Martineghi

Tempo di esecuzione: ~0,3s

Spazio Occupato: ~34 MiB

Valutazione: 30L/30L

## Il Progetto

Creare un algoritmo efficiente per il calcolo di un percorso, con meno tappe possibili, tra due stazioni di servizio. Le tappe sono fermate ad altre stazioni di servizio aventi un parco auto ciascuna ed ogni parco auto ha a disposizione diverse auto con la propria autonomia.

[Specifica completa](https://github.com/Marcoscianna/Progetto_API_2023/blob/main/Specifica.pdf)

### Valutazione

| Valutazione | Memoria | Tempo |   
|-------------|--------:|------:|
| 18          | 128 MiB | 19 s  | 
| 21          | 118 MiB | 15 s  | 
| 24          | 108 MiB | 10 s  | 
| 27          |  98 MiB |  6 s  |
| 30          |  88 MiB |  4 s  |  
| 30L         |  78 MiB |  1 s  |

### Sviluppo

Al fine di creare un algoritmo efficiente e che occupi poco spazio ho scelto la struttura ad albero, dove ogni nodo é una stazione di servizio

Ambiente di sviluppo fornito: [CLion](https://www.jetbrains.com/clion/) e compilatore [gcc](https://gcc.gnu.org/).

Come OS ho utilizzato Debian 11 per sfruttare gli strumenti Valgrind ed ASan.

Per il debugging mi sono affidato principalmente agli strumenti offerti da Clion.
