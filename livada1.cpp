#include <fstream>
#include <cstring>
using namespace std;
void inspecteazaPom(
    int nrPomiPeRand,
    int soi,
    int soiuri[],
    int & nrSoiuri,
    int & indiceSoi,
    int aparitiiSoi[],
    bool & amGasitSoiMajoritar);
int main()
{
    ifstream citeste("livada1.in");
    ofstream scrie("livada1.out");
    int nrRanduri,
        nrPomiPeRand,
        ultimulSoi,
        nrRanduriCuSoiMajoritar = 0,
        nrMaximPomiConsecutiviDeAcelasiSoi = 1;
    citeste >> nrRanduri
            >> nrPomiPeRand
            >> ultimulSoi;
    while (nrRanduri > 0)
    {
        int soiPomPrecedent,
            indiceSoi,
            soiuri[nrPomiPeRand],
            aparitiiSoi[nrPomiPeRand],
            nrPomiConsecutiviDeAcelasiSoi = 1,
            nrSoiuri = 0;
        bool amGasitSoiMajoritar = 0;
        memset(soiuri, 0, sizeof(soiuri));
        memset(aparitiiSoi, 0, sizeof(aparitiiSoi));
        citeste >> soiPomPrecedent;
        inspecteazaPom(
            nrPomiPeRand,
            soiPomPrecedent,
            soiuri,
            nrSoiuri,
            indiceSoi,
            aparitiiSoi,
            amGasitSoiMajoritar);
        for (int i = 1; i < nrPomiPeRand; i++)
        {
            int soiPomCurent;
            citeste >> soiPomCurent;
            inspecteazaPom(
                nrPomiPeRand,
                soiPomCurent,
                soiuri,
                nrSoiuri,
                indiceSoi,
                aparitiiSoi,
                amGasitSoiMajoritar);
            if (soiPomCurent == soiPomPrecedent)
            {
                nrPomiConsecutiviDeAcelasiSoi++;
            }
            else
            {
                if (nrPomiConsecutiviDeAcelasiSoi
                        > nrMaximPomiConsecutiviDeAcelasiSoi)
                {
                    nrMaximPomiConsecutiviDeAcelasiSoi
                        = nrPomiConsecutiviDeAcelasiSoi;
                }
                nrPomiConsecutiviDeAcelasiSoi = 1;
            }
            soiPomPrecedent = soiPomCurent;
        }
        if (nrPomiConsecutiviDeAcelasiSoi
                > nrMaximPomiConsecutiviDeAcelasiSoi)
        {
            nrMaximPomiConsecutiviDeAcelasiSoi
                = nrPomiConsecutiviDeAcelasiSoi;
        }
        if (amGasitSoiMajoritar)
        {
            nrRanduriCuSoiMajoritar++;
        }
        nrRanduri--;
    }
    citeste.close();
    scrie << nrRanduriCuSoiMajoritar << endl;
    scrie << nrMaximPomiConsecutiviDeAcelasiSoi;
    scrie.close();
    return 0;
}
bool amMaiVazutAcestSoi(
    int soi,
    int soiuri[],
    int nrSoiuri,
    int & indiceSoi)
{
    // caut 'soi' in 'soiuri' folosind cautare binara
    int stanga = -1, dreapta = nrSoiuri;
    while (dreapta - stanga > 1)
    {
        int mijloc = stanga + (dreapta - stanga)/2;
        if (soiuri[mijloc] == soi)
        {
            indiceSoi = mijloc;
            return 1;
        }
        else if (soiuri[mijloc] < soi)
        {
            stanga = mijloc;
        }
        else
        {
            dreapta = mijloc;
        }
    }
    indiceSoi = dreapta;
    return 0;
}
void adaugaAcestSoiLaListaSoiurilorVazute(
    int soi,
    int soiuri[],
    int & nrSoiuri,
    int aparitiiSoi[],
    int indiceSoi)
{
    for (int i = nrSoiuri; i > indiceSoi; i--)
    {
        soiuri[i] = soiuri[i-1];
        aparitiiSoi[i] = aparitiiSoi[i-1];
    }
    soiuri[indiceSoi] = soi;
    aparitiiSoi[indiceSoi] = 1;
    nrSoiuri++;
}
bool esteSoiMajoritar(
    int nrPomiPeRand,
    int indiceSoi,
    int aparitiiSoi[])
{
    return aparitiiSoi[indiceSoi] >= (nrPomiPeRand/2 + 1);
}
void inspecteazaPom(
    int nrPomiPeRand,
    int soi,
    int soiuri[],
    int & nrSoiuri,
    int & indiceSoi,
    int aparitiiSoi[],
    bool & amGasitSoiMajoritar)
{
    if (amMaiVazutAcestSoi(
                soi,
                soiuri,
                nrSoiuri,
                indiceSoi))
    {
        aparitiiSoi[indiceSoi]++;
        if (!amGasitSoiMajoritar
                && esteSoiMajoritar(
                    nrPomiPeRand,
                    indiceSoi,
                    aparitiiSoi))
        {
            amGasitSoiMajoritar = 1;
        }
    }
    else
    {
        adaugaAcestSoiLaListaSoiurilorVazute(
            soi,
            soiuri,
            nrSoiuri,
            aparitiiSoi,
            indiceSoi);
    }
}
