#include <iostream>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <bitcoin/bitcoin.hpp>

using namespace std;

char raide (int r1, char r11)
{
    if (r1 == 1)
        r11 = 'A';
    else if (r1 == 2)
        r11 = 'a';
    else if (r1 == 3)
        r11 = 'B';
    else if (r1 == 4)
        r11 = 'b';
    else if (r1 == 5)
        r11 = 'C';
    else if (r1 == 6)
        r11 = 'c';
    else if (r1 == 7)
        r11 = 'D';
    else if (r1 == 8)
        r11 = 'd';
    else if (r1 == 9)
        r11 = 'e';
    else
        r11 = 'f';

    return r11;
}

string hashas (string eil)
{
    string pak, hesh;
    int ilgis, ind = 0, r1, ind2 = 0, i, y, z = 0;
    char r11;
    ilgis = eil.length();
    ind = eil[0];
    y = 1;

    for (int i = 1; i < ilgis; i++)
    {
        if (y == 0)
        {
            ind -= eil[i];
            y++;
        }
        else
        {
            ind += eil[i];
            y--;
        }
    }
    ind = abs(ind);

    for (i = 0; i < ilgis; i++)
    {
        if(hesh.length()>=32)
            break;

        else
        {
            r1 = (eil[i] + ind2)%10;
            hesh += to_string(eil[i]+ind2) + raide(r1, r11);
        }
        ind2++;
    }
    int ind3 = ind;
    int ind4 = ind;
    if (i == ilgis)
    {
        while (hesh.length() < 32)
        {
            ind2 = abs(ind2*2 - ind3*2);
            r1 = ind2%10;
            hesh += to_string(ind2) + raide(r1, r11);

            ind2 += 3;
            ind3 -= 3;
        }
    }
    else
    {
        for (int x = i; x < ilgis; x++)
        {
            if (ind4 > 1000)
                ind4 %= 100;

            r1 = (eil[x] + ind4)%10;
            pak = to_string(eil[x]+ind4) + raide(r1, r11);

            if (z >= 32)
                z = 0;

            hesh.replace(hesh.begin() + z, hesh.begin()+ z + pak.length(), pak);
            z += pak.length();

            if (x%2 == 0)
                ind4 += 3;
            else
                ind4 -= 2;
        }
    }
    while (hesh.length() > 32)
        hesh.pop_back();
    while (hesh.length() < 65)
        hesh.push_back('0');

    return hesh;
}

struct users{
    string vardas[1000];
    string raktas[1000];
    int balansas[1000];
};

struct transactions{
    string ID[10000];
    string sraktas[10000];
    string graktas[10000];
    int suma[10000];
};

struct Blokas {
    string trans[100];
    string PrevBlockHash;
    string TimeStamp;
    double Version;
    string MerkleRootHash[50];
    double Nonce;
    string DifficultyTarget;
};

struct Blockchainas {
    string hhash;
    string trans[100];
};

string Mining (Blokas block[], int blcount, Blockchainas blchain[], int chcount, string MerkleHash)
{
    int n = 100000, x;
    string newhash;
    if (blcount == 0)
        block[0].PrevBlockHash = hashas("");
    else
        block[blcount].PrevBlockHash = blchain[chcount-1].hhash;

    block[blcount].TimeStamp = "17:15";
    block[blcount].Version = 2;
    block[blcount].DifficultyTarget = "0";
    x = block[blcount].DifficultyTarget.size();

    srand((unsigned) time(0));
    for (int i = 0; i < n; i++)
    {
        block[blcount].Nonce = rand() % 1000000;
        newhash = hashas(block[blcount].DifficultyTarget + MerkleHash + block[blcount].PrevBlockHash + block[blcount].TimeStamp + to_string(block[blcount].Version) + to_string(block[blcount].Nonce));
        if (newhash.substr(1, x) == block[blcount].DifficultyTarget)
            return newhash;
    }
    cout << "Nepavyko" << endl;
    Mining(block, blcount, blchain, chcount, MerkleHash);

}

bc::hash_digest create_merkle(bc::hash_list& merkle)
{
    if (merkle.empty())
        return bc::null_hash;
    else if (merkle.size() == 1)
        return merkle[0];
    while (merkle.size() > 1)
    {
        if (merkle.size() % 2 != 0)
            merkle.push_back(merkle.back());
        assert(merkle.size() % 2 == 0);
        bc::hash_list new_merkle;
        for (auto it = merkle.begin(); it != merkle.end(); it += 2)
        {
            bc::data_chunk concat_data(bc::hash_size * 2);
            auto concat = bc::serializer<
            decltype(concat_data.begin())>(concat_data.begin());
            concat.write_hash(*it);
            concat.write_hash(*(it + 1));
            bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
            new_merkle.push_back(new_root);
        }
        merkle = new_merkle;
        //cout << "Current merkle hash list:" << endl;
        //for (const auto& hash: merkle)
        //cout << " " << bc::encode_base16(hash) << endl;
        //cout << endl;
    }
    return merkle[0];
}
//void MerkleTree (Blokas block[], int blcount)
//{
//    int m = 50;
//    for (int i = 0; i < 100; i+=2)
//        block[blcount].MerkleRootHash[i/2] = hashas(block[blcount].trans[i] + block[blcount].trans[i+1]);
//
//    while (m != 1)
//        for (int i = 0; i < m; i++)
//        {
//            block[blcount].MerkleRootHash[i] = hashas(block[blcount].MerkleRootHash[i] + block[blcount].MerkleRootHash[i+1]);
//            for(int j = i+1; j < m-1; j++)
//                block[blcount].MerkleRootHash[j] = block[blcount].MerkleRootHash[j+1];
//
//            m--;
//        }
//}

transactions Transakcijos(users userstruct)
{
    transactions trstruct1;

    srand((unsigned) time(0));
    for (int i = 0; i < 10000; i++)
    {
        trstruct1.sraktas[i] = userstruct.raktas[rand() % 999];
        trstruct1.graktas[i] = userstruct.raktas[rand() % 999];
        trstruct1.suma[i] = (rand() % 100) + 1;
        trstruct1.ID[i] = hashas(trstruct1.sraktas[i] + trstruct1.graktas[i] + to_string(trstruct1.suma[i]));
    }

    return trstruct1;
}

users Vartotojai() {
    users userstruct1;
    char Raides[22] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'v', 'z'};
    string vvardas;

    srand((unsigned) time(0));
    for (int i = 0; i < 1000 ; i++)
    {
        vvardas = "";
        for (int j = 0; j < 7; j++)
            vvardas += Raides[(rand() % 21) + 0];

        userstruct1.vardas[i] = vvardas + to_string(i);
        userstruct1.raktas[i] = hashas(userstruct1.vardas[i]);
        userstruct1.balansas[i] = (rand() % 1000) + 10;
    }

    return userstruct1;
}


int main()
{
    ofstream fr ("output.txt");

    int dydis = 10000, blcount = 0, chcount = 0, nr, j, z;
    string eil, newhash;
    users userstruct;
    transactions trstruct;

    userstruct = Vartotojai();
    trstruct = Transakcijos(userstruct);

    Blokas block[5];
    Blockchainas blchain[100];

    while (dydis >= 100)
    {
        z = 0;
        srand((unsigned) time(0));
        for (int i = 0; i < 100; i++)
        {
            nr = rand() % (dydis-1);
            for (j = 0; j < 1000; j++)
                if (trstruct.sraktas[nr] == userstruct.raktas[j])
                    break;

            if (trstruct.suma[nr] >= userstruct.balansas[j] && trstruct.ID[nr] == hashas(trstruct.sraktas[nr] + trstruct.graktas[nr] + to_string(trstruct.suma[nr])))
            {
                block[blcount].trans[z] = trstruct.ID[nr];
                z++;
            }
            else
            {
                for(j = nr; j < (dydis-2) ; j++)
                {
                    trstruct.ID[j] = trstruct.ID[j+1];
                    trstruct.sraktas[j] = trstruct.sraktas[j+1];
                    trstruct.graktas[j] = trstruct.graktas[j+1];
                    trstruct.suma[j] = trstruct.suma[j+1];
                }
                i--;
                dydis--;
            }
        }
        //MerkleTree(block, blcount);
        string transactions[100];
        for (int i = 0; i < 100; i++)
        {
            transactions[i] = hashas(block[blcount].trans[i]);
        }
        bc::hash_list tx_hashes;
        for (int i = 0; i < 100; i++)
        {
            char chars[65];
            strcpy(chars, transactions[i].c_str());
            tx_hashes.push_back(bc::hash_literal(chars));
        }
        const bc::hash_digest merkle_root = create_merkle(tx_hashes);
        string MerkleHash = bc::encode_base16(merkle_root);

        blchain[chcount].hhash = Mining(block, blcount, blchain, chcount, MerkleHash);
        for (int i = 0 ; i < 100; i++)
        {
            int send = 0, get = 0;
            for (int j = 0; j < dydis; j++)
                if (trstruct.ID[j] == block[blcount].trans[i])
                    break;
            for (int k = 0; k < 1000; k++)
            {
                if (userstruct.raktas[k] == trstruct.sraktas[j])
                    send = k;
                else if (userstruct.raktas[k] == trstruct.graktas[j])
                    get = k;
                if (send != 0 && get != 0)
                    break;
            }
            userstruct.balansas[send] -= trstruct.suma[j];
            userstruct.balansas[get] += trstruct.suma[j];
            for(int m = j; m < (dydis-1); m++)
            {
                trstruct.ID[m] = trstruct.ID[m+1];
                trstruct.sraktas[m] = trstruct.sraktas[m+1];
                trstruct.graktas[m] = trstruct.graktas[m+1];
                trstruct.suma[m] = trstruct.suma[m+1];
            }
            dydis--;
        }
        for (int i = 0; i < 100; i++)
            blchain[chcount].trans[i] = block[blcount].trans[i];

        fr << blchain[chcount].hhash << endl;
        chcount++;
    }

    return 0;
}
