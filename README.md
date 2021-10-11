# Blockchain

## Komentarai:
* Nesivarginau daryti "centralizuotą" blockchain, iš karto dariau decentralizuotą ir kad veiktu lygiagrečiai.
* Dėl decentralizacijos negalėjau sukurti vartotojų jau turincių valiutos "memes".
* Su Wallet.cpp galima atlikti transakcija neegzistuojanciam vartotojui. (Praktiškai vartotojas pradeda egzistuot, jei jo ID yra paminėtas blockchain'e).
* Taip pat, nedariau pasirinktų transakcijų variacijų, nes tai nedraugautu su mano sudėtingumo sistema.

## Veikimas:
* Valiuta sukurima tik kasant (mining), o kiti vartotojai gali gauti "memes", jei jiems kažkas pervedė juos.
* Vartotojai turi tik vardą (kuris nenaudojamas), ID - vardo hash, ir išsaugotus "memes" (irgi nenaudojama).
* Blockchain mato transakcijas tik iš vieno ID į kitą.
* Vartotojo turimiems "memes" suskaičiuoti yra peržiurimos visos transakcijos blockchain'e.
* Su Wallet.cpp galima atlikti vartotojo "memes" skaičiavimą ir atlikti transakcijas.
* Naujo block'o sudėtingumas yra skaičiuojamas pagal paskutinių 20 block'ų laikų mediana.
Jei laikas <=10s, tai sudėtingumas padidinamas kitiems 20 block'ų.
Jei leikas >=40s, tai sudėtingumas sumažinamas kitiems 20 block'ų.
* "Miner'iai" prieš įkeldami savo blocką, pažiūri ar jie yra pirmi, jei ne, tai neikelia savo block'o.
* Mining - hash'o su pirmais 20 nulių suradimas.

## Trukūmai:
* Dabar visas blockchain yra kaip kortų namelis piktavaliams. Labai lengvai galima sugriauti visą blockchain, nes trūksta duomenų verifikacijų.
* Taip pat nėra tikrinama ar block'o formatas yra tinkamas.
* Yra tikimybė, kad jeigu skirtingi vartotojai tiksliai vienu metu iškas block'ą, tai bus "race condition". Nes nėra buffer'ių.
* Nėra transakcijų "signatures", tai bet kas gali apsimesti bet kuo.
* Yra tik 1 globalus Blockchain.txt, o reikėtų, kad visi user'iai turėtų savo kopiją ir dalintusi duomenimis per tinklą. (Bet čia jau per daug darbo).
* Kadangi vartotojo turimi meme'ai yra visada skaičiuojami, tai jei blockchain labai didelis, tai užtruks ilgą laiką. (Galioja ir vartotojams ir mineriams).

## Pliusai:
* Yra transakcijų verifikavimas. Negalima overspendinti.
* Jei nėra piktavalių, tai viskas gražiai veikia.
* Labai lengvai galima implementuoti "signatures".

## Ateities patobulinimai:
* Transakcijos su "signatures".
* Block'ų verifikacija.
* User'iai dalinasi data per tinklą.

# Instrukcijos:
* Wait for it.
