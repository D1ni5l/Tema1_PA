#include "Player.h"
Task_1

Se va crea o listă cu informațiile din fișierul d.in(lista se va forma prin adaugarea elementelor la inceput - O(1)).

structura (struct Team) retine date din fisierele argv[2] dinfiecarui test referitoare la echipa, precum nume si numarul de jucatori ai echipei
structura (struct Player) retine numele si puncatjul fiecarui jucator din echipa respectiva;

create_list() - primeste ca parametrii elementele: 
    head de tip structura , in care este retinut inceputul listei de echipe 
    si fisierul input unde se gasesc informatiile legate de fiecare dintre cele n echipe;
    in functie sunt citite din fisierul input numele si numarul de jucatori al ecipei, care sunt memorate in campurile destinate
    functia urmeza sa apeleze addAtBeginning_for_Player() pentru a atribui informatiile legate de fiecare jucator al echipei, informatii organizate sub forma de vector (*vect);

print_Team_name() - afiseaza numele fiecarei echipe din lista pe cate un rand in fisierul argv[3];

first_task() - indepineste cerintele primul task , intrucat acesta nu are output compatibil cu celelalte task-uri;

Task_2

 Se vor elimina din lista anterior creată, echipele cu cel mai mic punctaj de echipă (informațiile despre modul de calcul al acestui punctaj se găsesc în cadrul secțiunii Detalii Tehnice)
astfel incat in lista sa ramana n echipe (unde n maxim si n este putere a lui 2).În cazul în care mai multe echipe au acelasi scor se elimina prima echipă gasita in lista. Dupa fiecare 
eliminare se va relua parcurgerea listei de la cap.

second_task() - afiseaza in fisierele asociate un numar de echipe egal cu cea mai mare putere a lui 2 mai mica sau egala cu numarul total de echipe, eliminandu-le pe cele cu cel mai mic punctaj 
 pana cand ajunge la numarul de echipe solicitat.
    Pentru a realiza acest task functia asociaza fecarei echipe puncyajul pe echipa prin media aritmetica a punctajelor fiecarui jucator din echipa respectiva, apoi apleaza funtia Team_deduction(),
    a carei actiuni este de a elimina cate o echipa pe rand( cu punctaj minim ) pana la indeplinirea criteriului, si apoi functia print_Team_name() pentru a fisa numele echipelor ramase, acest lucru 
    fiind realizat pentru toate task-urile de la 2 in sus pentru ca toate solicita acest concept.

    Team_deduction() - cauta echipa cu puncajul minim, si o elimina din lista, eliberand memoria asociata functiei prin apelarea functiilor free_Team(), pana cand in lista ramane un numar maxim de 
     echipe egal cu cea mai mare puere a lui 2 mai mica sau egala cu nr. total de echipe initial.

        functiile free_Team() si free_Teams() au acelasi rol, insa prima face acest lucru doar pentru o echipa anume, celalata facand acelasi lucru, insa pentru taoata lista, functia 
         free_team_members() avand rolul de a elibera mai intai memoria asociata fiecarui jucator  al echipei din vect* pentru a permite eliberarea asociata acestuia in mod corespunzator.

Task_3
 Se vor implementa structurile de date necesare pentru a se efectua meciurile:
 Se va crea o coadă în care se vor pune meciurile dintre echipe.
 Echipele vor forma meciuri în ordinea în care se află în lista de la punctul anterior, primele două echipe vor forma primul meci (și așa mai departe).
 Se vor crea două stive - una pentru învinși și una pentru câștigători - ce vor conține echipele ce au pierdut, respectiv, au câștigat meciul anterior.
 Se vor introduce în stivă echipele în funcție de rezultatul obținut și se va adauga un punct la punctajul de echipă al echipelor ce au câștigat.
 In cazul unui meci in care ambele echipe au acelasi punctaj, se va alege prima echipa adaugata in meciul disputat.
 Se vor șterge echipele ce se găsesc în stiva de învinși. (la finalul fiecărei etape; ex: dintr-o runda cu 8 echipe, stergerea se face dupa ce au fost eliminate toate echipele. In acest caz, dupa 
 ce au fost eliminate 4 dintre echipe, se vor sterge. In runda urmatoare, pe acest exemplu, se vor adauga 2 echipe in stiva de invinsi, dupa care o sa fie eliberata din nou - stiva de invinsi -.)
 Din stiva de câștigători se vor extrage echipele și se va umple din nou coada de meciuri formându-se meciuri cu echipele consecutive (prima echipă scoasă din stivă va juca cu a doua echipa scoasă 
 din stivă primul meci).
 Se vor repeta pașii enumerați pana la aflarea echipelor de pe primele 8 locuri, care vor fi salvate intr-o alta lista, dupa aflarea acestora se vor continua meciurile pana la aflarea echipei 
 castigatoare.

third_task() - functia creaza lista last_eight, necesara ulterior la celelalte taskuri
    functia creaza coada q in care memoreaza pentru fiecare runda toate echipele ramase in turneu, cate 2 consecutive formand un  meci al rundei.
    cat timp nu a rams decat o echipa in turneu, se tot repeta procesul , cea din urma fiind cea castigatoare, dupa dfiecare runda se afiseza castigatorii rundei si se creste puncajul fiecrui membru al echipei,
    ulterior si cel al echipei prin recalcularea punctajului echipei.
    print_Queue() - afiseaza meciurile din runad rspectiva memorate in coada q
    Stack_repartition() - imparte echiple rundei respective in doua stive, una de invinsi si una de pierzatori in functie ce criteriile oferite, ulterior stiva depierzatori este stearsa , iar cea de castigatori 
    este repusa in coad q prin apelarea functiilor create_round_from_stack()/printStack_and_create_Queue()  , care intre timp a fost golita.
    create_round_from_stack() - afiseaza castigatorii rundei respective si pune in coada q echipele ramase pentru a putea crea o noua runda.    
    print_win_team() - afiseaza echipa castigatoare si punctajul sau dupa incrementare.
    printStack_and_create_Queue() - are acelasi rol ca create_round_from_stack(), totodata formand si lista ultimelor echipe ramase in turneu, al caror punctaj ramane neshimbat in urma urmatoarelor 
    runde ( este pastrat cel de la moentul respectiv).

Task_4
Se va realiza un clasament al ultimelor 8 echipe (salvate la subpunctul anterior) sub forma unui BST(Binary Search Tree). Acesta va fi ordonat după punctajul pe echipă și i se va afișa conținutul în 
ordine descrescătoare(in cazul in care doua echipe au acelasi punctaj se vor ordona in functie de nume, descrescator).

fourth_task() - creaza BST cu elementele din lista last_eight si afiseaza in ordine descrescatoare a punctajului echipele puse in BST.
    list_from_BST() - imi cfreaza o lista cu echipele din bst ordonate in ordinea dorita.

Task_5
fiveth_task() - afiseaza nivelul doi din AVL.
