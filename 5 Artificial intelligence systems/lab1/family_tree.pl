parent(me, vladimirNegrash).
parent(me, oksanaIsay).

parent(vladimirNegrash, gennadiyNegrash).
parent(vladimirNegrash, irinaShorenko).

parent(oksanaIsay, vladimirIsay).
parent(oksanaIsay, lyubomiraTurko).

parent(gennadiyNegrash, grigoryNegrash).
parent(gennadiyNegrash, evdokiaNegrash).
parent(anatoliyNegrash, grigoryNegrash).
parent(anatoliyNegrash, evdokiaNegrash).
parent(zinaidaNegrash, grigoryNegrash).
parent(zinaidaNegrash, evdokiaNegrash).
parent(ekaterinaNegrash, grigoryNegrash).
parent(ekaterinaNegrash, evdokiaNegrash).
parent(valeriyTimonchev, ivanTimonchev).
parent(valeriyTimonchev, zinaidaNegrash).
parent(elenaTimoncheva, valeriyTimonchev).
parent(elenaTimoncheva, tatyanaTimoncheva).
parent(sergeyEfremov, dmitryEfremov).
parent(sergeyEfremov, elenaTimoncheva).
parent(vladimirEfremov, dmitryEfremov).
parent(vladimirEfremov, elenaTimoncheva).
parent(tatyanaEfremova, dmitryEfremov).
parent(tatyanaEfremova, elenaTimoncheva).
parent(dmitriyGvozdev, gennadiyGvozdev).
parent(dmitriyGvozdev, ekaterinaNegrash).
parent(uriyGvozdev, gennadiyGvozdev).
parent(uriyGvozdev, ekaterinaNegrash).

parent(irinaShorenko, konstantinShorenko).
parent(irinaShorenko, lyudmilaShorenko).
parent(igorShorenko, konstantinShorenko).
parent(igorShorenko, lyudmilaShorenko).
parent(konstantinShorenkoJr, igorShorenko).
parent(konstantinShorenkoJr, natalyaShorenko).
parent(sergeyShorenko, konstantinShorenkoJr).
parent(sergeyShorenko, elenaRyzhikova).
parent(sophiaShorenko, konstantinShorenkoJr).
parent(sophiaShorenko, elenaRyzhikova).

parent(vladimirIsay, andreyIsay).
parent(vladimirIsay, mariaIsay).
parent(vasiliyIsay, andreyIsay).
parent(vasiliyIsay, mariaIsay).
parent(tatyanaIsay, andreyIsay).
parent(tatyanaIsay, mariaIsay).
parent(annaIsay, andreyIsay).
parent(annaIsay, mariaIsay).
parent(viktoriaPedchenko, vladimirPedchenko).
parent(viktoriaPedchenko, tatyanaIsay).
parent(innaPedchenko, vladimirPedchenko).
parent(innaPedchenko, tatyanaIsay).
parent(alekseyPedchenko, vladimirPedchenko).
parent(alekseyPedchenko, tatyanaIsay).
parent(anastasiaMazarchuck, igorMazarchuck).
parent(anastasiaMazarchuck, viktoriaPedchenko).
parent(alinaPedchenko, alekseyPedchenko).
parent(aleksandrIvanchenkoJr, aleksandrIvanchenko).
parent(aleksandrIvanchenkoJr, alinaPedchenko).

parent(lyubomiraTurko, nickolayTurko).
parent(lyubomiraTurko, pelageyaTurko).
parent(myroslavTurko, nickolayTurko).
parent(myroslavTurko, pelageyaTurko).
parent(fedorTurko, nickolayTurko).
parent(fedorTurko, pelageyaTurko).
parent(mariaTurko, nickolayTurko).
parent(mariaTurko, pelageyaTurko).
parent(ekaterinaTurko, nickolayTurko).
parent(ekaterinaTurko, pelageyaTurko).
parent(olegTurko, myroslavTurko).
parent(olegTurko, theodosiaTurko).
parent(vladimirTurko, myroslavTurko).
parent(vladimirTurko, theodosiaTurko).
parent(olegTurkoJr, olegTurko).
parent(olegTurkoJr, irinaTurko).
parent(nazarTurko, olegTurko).
parent(nazarTurko, irinaTurko).
parent(igorTurko, fedorTurko).
parent(igorTurko, olgaTurko).
parent(svyatoslavTurko, igorTurko).
parent(svyatoslavTurko, natalyaTurko).
parent(oksanaKovalyk, fedorKovalyk).
parent(oksanaKovalyk, ekaterinaTurko).
parent(olgaKovalyk, fedorKovalyk).
parent(olgaKovalyk, ekaterinaTurko).
parent(mariana, igorKopytko).
parent(mariana, olgaKovalyk).

spouse(gennadiyNegrash, irinaShorenko).
spouse(vladimirNegrash, oksanaIsay).
spouse(fedorKovalyk, ekaterinaTurko).
spouse(mariaTurko, vasiliyPunda).
spouse(igorTurko, natalyaTurko).
spouse(fedorTurko, olgaTurko).
spouse(olegTurko, irinaTurko).
spouse(myroslavTurko, theodosiaTurko).
spouse(nickolayTurko, pelageyaTurko).
spouse(igorKopytko, olgaKovalyk).
spouse(aleksandrIvanchenko, alinaPedchenko).
spouse(igorMazarchuck, viktoriaPedchenko).
spouse(andreyIsay, mariaIsay).
spouse(vladimirPedchenko, tatyanaIsay).
spouse(konstantinShorenkoJr, elenaRyzhikova).
spouse(igorShorenko, natalyaShorenko).
spouse(konstantinShorenko, lyudmilaShorenko).
spouse(gennadiyGvozdev, ekaterinaNegrash).
spouse(dmitryEfremov, elenaTimoncheva).
spouse(grigoryNegrash, evdokiaNegrash).
spouse(ivanTimonchev, zinaidaNegrash).
spouse(valeriyTimonchev, tatyanaTimoncheva).
spouse(vladimirIsay, lyubomiraTurko).

different(X, Y) :-
   not(X = Y).

sibling(Person, Sibling) :-
      parent(Person, Parent),
      parent(Sibling, Parent),
      different(Person, Sibling).

grandparent(Person, GrandParent) :- 
    parent(Person, Parent), 
    parent(Parent, GrandParent).

grandgrandparent(Person, GGParent) :-
    grandparent(Person, GParent),
    parent(GParent, GGParent).

auntOrUncle(Person, AOrU) :-
    parent(Person, PersonParent),
    sibling(PersonParent, AOrU).

cousin(Person, Cousin) :-
    parent(Person, PersonParent),
    parent(Cousin, CousinParent),
    sibling(PersonParent, CousinParent).

greatAuntOrUncle(Person, GaOru) :-
    grandparent(Person, PersonGParent),
    sibling(PersonGParent, GaOru).

secondCousine(Person, SecondCousine) :-
    grandparent(Person, PersonGParent),
    grandparent(SecondCousine, CousinGParent),
    sibling(PersonGParent, CousinGParent).

greatGreatAuntOrUncle(Person, GGaOru) :-
    grandgrandparent(Person, PersonGGParent),
    sibling(PersonGGParent, GGaOru).

thirdCousine(Person, ThirdCousine) :-
    grandgrandparent(Person, PersonGGParent),
    grandgrandparent(ThirdCousine, CousinGGParent),
    sibling(PersonGGParent, CousinGGParent).

nephewOrNiece(Person, NorN) :-
    parent(NorN, Parent),
    sibling(Parent, Person).

spouseParent(Person, SpouseParent) :-
    spouse(Person, Lovely),
    parent(Lovely, SpouseParent).
