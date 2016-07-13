Mironica Paul-Ciprian 332CA


Pentru aceasta tema am creat o clasa care se ocupa de majoritatea logicii programului "class Scene".
Aceasta clasa deseneaza raza, tine minte toate obiectele si multe altele (generare obiecte random, afisare comenzi, ...).

Pe langa aceasta clasa exista un mic arbore de clase cu clasa radacina "class Shape" care contine meshul, centrul si culoarea.
Aceasta clasa are cateva functii simple cum ar fi desenarea, dar si o functie virtuala pentru detectarea coliziunilor care va fi suprascrisa.

Mostenitorii clasei Shape sunt CircleShape, RectangleShape si Triangle(construit doar pentru camera).
Toate din cele trei clase primesc si incarca singure mesh-ul si suprascriu functia virtuala a clasei shape pentru detectarea coliziunilor.

Stilul de desenare a razei este prin desenarea la fiecare frame a unei noi particule de raza la o pozitie viitoare in functie de viteza razei;