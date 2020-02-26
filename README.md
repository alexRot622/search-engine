# Open Source Search engine
# Compilare
  Pentru a compila codul sursa, folositi comanda make. Sunt folosite biblioteci din standardul POSIX (dirent.h).
# Utilizare
  ```bash
  ./search <DIRNAME> <STRING>
  ```
  Unde DIRNAME este numele directorului in care se va cauta iau STRING este expresia care va fi rezolvata.
  # Descriere
   Proiectul reprezinta o implementare a unui motor simplu de cautare. Programul va primi ca input directorul 
   in care va cauta si o expresie ce reprezinta o schema logica pe baza unor termeni de cautare. Se va afisa
   numele fisierelor care indeplinesc conditia data, sortate in functie de scorul TF-IDF atribuit fiecaruia, urmate
   de acest scor.
   # Exemplu
   In urmatorul exemplu, docs este directorul cu teste dat in enuntul problemei:
   ```bash
   >./search ./docs "programming || C"
   4 results found:
   doc05.txt (tfidf = 0.028156)
   doc08.txt (tfidf = 0.025777)
   doc11.txt (tfidf = 0.019082)
   doc09.txt (tfidf = 0.008301)
   ```
