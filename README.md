# v0.1
Programos veikimas:
1. Sukuriami 1000 vartotojų ir 10000 transakcijų
2. Iš transakcijų pool'o atsitiktine tvarka atrenkamos 100 transakcijų ir įdedamos į naują bloką.
3. Apskaičiuojamas bloke esančių transakcijų Merkle Tree Hash.
4. Pradedamas Mining procesas, kuris vyksta tol, kol atrandamas hash'as, atitinkantis Difficulty Target reikalavimą.
5. Įvykdomos naujame bloke esančios transakcijos, po to jos yra ištrinamos iš transakcijų pool'o.
6. Naujas blokas pridedamas prie Blockchain.
