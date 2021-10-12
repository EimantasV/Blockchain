# Blockchain

## Turinys
- [Blockchain](#blockchain)
  - [Turinys](#turinys)
  - [Komentarai:](#komentarai)
  - [Veikimas:](#veikimas)
  - [Trukūmai:](#trukūmai)
  - [Pliusai:](#pliusai)
  - [Ateities patobulinimai:](#ateities-patobulinimai)
  - [Instrukcijos:](#instrukcijos)

## Komentarai:
* Nesivarginau daryti "centralizuotą" blockchain, iš karto dariau decentralizuotą ir kad veiktu lygiagrečiai.
* Dėl decentralizacijos negalėjau sukurti vartotojų jau turinčių valiutos "memes".
* Su Wallet.cpp galima atlikti transakcija neegzistuojančiam vartotojui. (Praktiškai vartotojas pradeda egzistuot, jei jo ID yra paminėtas blockchain'e).
* Taip pat, nedariau pasirinktų transakcijų variacijų, nes tai nedraugautu su mano sudėtingumo sistema.


## Veikimas:
* Valiuta sukūrima tik kasant (mining), o kiti vartotojai gali gauti "memes", jei jiems kažkas pervedė juos.
* Vartotojai turi tik vardą (kuris nenaudojamas), ID - vardo hash, ir išsaugotus "memes" (irgi nenaudojama).
* Blockchain mato transakcijas tik iš vieno ID į kitą.
* Vartotojo turimiems "memes" suskaičiuoti yra peržiūrimos visos transakcijos blockchain'e.
* Su Wallet.cpp galima atlikti vartotojo "memes" skaičiavimą ir atlikti transakcijas.
* Naujo block'o sudėtingumas yra skaičiuojamas pagal paskutinių 20 block'ų laikų mediana.
Jei laikas <=10s, tai sudėtingumas padidinamas kitiems 20 block'ų.
Jei leikas >=40s, tai sudėtingumas sumažinamas kitiems 20 block'ų.
* "Miner'iai" prieš įkeldami savo blocką, pažiūri ar jie yra pirmi, jei ne, tai neįkelia savo block'o.
* Mining - hash'o su pirmais 20 nulių suradimas.

## Trukūmai:
* Dabar visas blockchain yra kaip kortų namelis piktavaliams. Labai lengvai galima sugriauti visą blockchain, nes trūksta duomenų verifikacijų.
* Taip pat nėra tikrinama ar block'o formatas yra tinkamas.
* Yra tikimybė, kad jeigu skirtingi vartotojai tiksliai vienu metu iškas block'ą, tai bus "race condition". Nes nėra buffer'ių.
* Nėra transakcijų "signatures", tai bet kas gali apsimesti bet kuo.
* Yra tik 1 globalus Blockchain.txt, o reikėtų, kad visi user'iai turėtų savo kopiją ir dalintųsi duomenimis per tinklą. (Bet čia jau per daug darbo).
* Kadangi vartotojo turimi meme'ai yra visada skaičiuojami, tai jei blockchain labai didelis, tai užtruks ilgą laiką. (Galioja ir vartotojams ir mineriams).
* Jei vartotojas atlieka kelias transakcijas <b>tuo pat metu</b> ir neįperka atlikti visas transakcijas, tai jos visos bus atmestos.
  
## Pliusai:
* Yra transakcijų verifikavimas. Negalima overspend'inti.
* Jei nėra piktavalių, tai viskas gražiai veikia.
* Labai lengvai galima implementuoti "signatures".

## Ateities patobulinimai:
* Transakcijos su "signatures".
* Block'ų verifikacija.
* User'iai dalinasi data per tinklą.

## Instrukcijos:
* Per terminal nueiti i /userN folder'i ir sukompiliuoti failus su (g++ -o Wallet Wallet.cpp -O3) ir (g++ -o Mine Mine.cpp -O3).
* Per terminal įjungti ./Wallet.exe ir ten parašyti savo vartotojo vardą.
* Ten galite pažiūrėti turimus memus ir atlikti transakcijas.
* Tada per kitą terminal galite įjungti ./Mine.exe ir įraše vartotojo vardą prasidės kasimas. (Jei nėra vartotojo, tai programa išsijungs).
* Galite per kitus terminalus kitiems vartotojams įjungti kasimus, taip vyks kasimas lygiagrečiai ir greičiau. (Pasunkėja kasimas, jei per greitai kasama).
* Pažiūrėti block'ams galite įjungti (node Chain.js) ir per naršyklės console pažiūrėti block'us JSON formatu.
* Arba galite pažiūrėti Blockchain.txt, bet sunku susigaudyti.
* Taip pat yra TransactionPool.txt, kur yra transakcijos laukiančios miner'ių.
