# LanParty - (Structuri de Date in C)

Acest proiect implementeaza o simulare a unui turneu eliminatoriu de eSports (LanParty) intre mai multe echipe, folosind si gestionand in mod direct diverse structuri de date in limbajul C.
Proiectul citeste datele echipelor din fisiere de intrare, filtreaza participantii, simuleaza meciurile directe folosind structuri de tip coada si stiva, si creeaza clasamente folosind arbori pentru o cautare si afisare eficienta.

## Arhitectura Proiectului

Solutia este modularizata pe mai multe fisiere sursa pentru o organizare optima a codului:

* **`lanParty.c` (Punctul de intrare):** Contine functia main. Gestioneaza argumentele din linia de comanda pentru deschiderea fisierelor de intrare/iesire, citeste datele de control (cerintele de executat) si apeleaza functiile specifice fiecarui task.
* **`Player.h` (Fisierul antet):** Contine definitiile tuturor structurilor de date utilizate (Player, Team, Queue, Stack, BSTNode, AVLNode) si declaratiile tuturor functiilor.
* **Modulele de Structuri de Date (`liste.c`, `stive.c`, `cozi.c`, `BST.c`, `AVL.c`):** Contin implementarea operatiilor fundamentale specifice fiecarei structuri. Includ, de asemenea, functiile vitale pentru eliberarea corecta a memoriei si prevenirea memory leak-urilor (ex: free_Teams, deleteQueue, free_BST, free_AVL).
* **`Task.c` (Logica principala):** Modulul care contine logica de business specifica fiecarei etape a turneului, structurata in cele 5 task-uri principale (ex: first_task, second_task, etc.).

## Functionalitati si Cerinte

Logica turneului este impartita in 5 etape (cerinte) principale:

* **Task 1 - Crearea listei:** Citirea datelor din fisierul de intrare si afisarea listei initiale a echipelor inscrise. Elementele sunt adaugate la inceputul listei, operatie care asigura o complexitate de tip O(1).
* **Task 2 - Filtrarea echipelor:** Eliminarea echipelor cu cel mai mic punctaj pana cand numarul total de echipe ramase este cea mai mare putere a lui 2, conditie necesara pentru a incepe meciurile eliminatorii. Punctajul se calculeaza ca media aritmetica a punctelor jucatorilor.
* **Task 3 - Simularea meciurilor:** Simuleaza meciurile directe dintre echipe. Foloseste o structura de tip coada pentru a stabili ordinea meciurilor si stive separate pentru castigatori si invinsi. Jucatorii echipei castigatoare primesc cate 1 punct bonus, punctajul echipei este recalculat, iar memoria invinsilor este eliberata. Ultimele 8 echipe ramase sunt pastrate intr-o lista separata, denumita `last_eight`.
* **Task 4 - Clasament prin Arbore Binar de Cautare:** Construieste un arbore binar de cautare folosind cele 8 echipe salvate la pasul anterior. Arborele afiseaza clasamentul in ordine descrescatoare a punctajelor echipelor.
* **Task 5 - Clasament prin Arbore AVL:** Construieste un arbore perfect echilibrat de tip AVL pornind de la echipele din arborele precedent. Se folosesc rotatii simple si duble pentru echilibrare, mai exact rotatii la stanga, la dreapta, stanga-dreapta si dreapta-stanga, dupa care se afiseaza echipele situate exclusiv pe nivelul 2 al arborelui.
