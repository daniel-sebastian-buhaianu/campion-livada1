#include <fstream>
#include <cstring>
using namespace std;
bool amMaiVazutAcestSoi(int, int*, int, int&);
bool esteSoiMajoritar(int, int, int*);
void adaugaAcestSoiLaListaSoiurilorVazute(
	int,
	int*,
	int&,
	int*,
	int);
int main()
{
	int nrRanduri,
	    nrPomiPeRand,
	    ultimulSoi;
	ifstream citeste("livada1.in");
	citeste >> nrRanduri
	        >> nrPomiPeRand
		>> ultimulSoi;
	int nrRanduriCuSoiMajoritar = 0,
	    nrMaximPomiConsecutiviDeAcelasiSoi = 1;
	while (nrRanduri > 0)
	{
		int soiPomPrecedent,
		    nrPomiConsecutiviDeAcelasiSoi = 1,
		    soiuri[nrPomiPeRand],
		    nrSoiuri = 0,
		    indiceSoi,
		    aparitiiSoi[nrPomiPeRand];
		bool amGasitSoiMajoritar = 0;
		// initializez vectorii cu 0
		memset(soiuri, 0, sizeof(soiuri));
		memset(aparitiiSoi, 0, sizeof(aparitiiSoi));
		// citesc soiul primului pom de pe rand
		citeste >> soiPomPrecedent;
		if (amMaiVazutAcestSoi(
			soiPomPrecedent,
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
				soiPomPrecedent,
				soiuri,
				nrSoiuri,
				aparitiiSoi,
				indiceSoi);
		}
		for (int i = 1; i < nrPomiPeRand; i++)
		{
			int soiPomCurent;
			citeste >> soiPomCurent;
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
					nrPomiConsecutiviDeAcelasiSoi = 1;
				}
			}
			if (amMaiVazutAcestSoi(
				soiPomCurent,
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
					soiPomCurent,
					soiuri,
					nrSoiuri,
					aparitiiSoi,
					indiceSoi);
			}
			soiPomPrecedent = soiPomCurent;
		}
		if (amGasitSoiMajoritar)
		{
			nrRanduriCuSoiMajoritar++;
		}
		nrRanduri--;
	}
	citeste.close();
	ofstream scrie("livada1.out");
	scrie << nrRanduriCuSoiMajoritar << endl;
	scrie << nrMaximPomiConsecutiviDeAcelasiSoi;
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
