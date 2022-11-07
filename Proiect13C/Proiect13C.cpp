#include <iostream>
using namespace std;

class Vehicul
{
public: 
	char* denumire;
private:
	int nrLocuri;
protected:
	float capCilindrica;
public:
	Vehicul()
	{
		denumire = new char[strlen("Necunoscuta") + 1];
		strcpy(denumire, "Necunoscuta");
		nrLocuri = 0;
		capCilindrica = 0;
	}

	Vehicul(const char* d, int n, float c)
	{
		nrLocuri = n;
		capCilindrica = c;
		denumire = new char[strlen(d) + 1];
		strcpy(denumire, d);
	}

	Vehicul(const Vehicul& v)
	{
		nrLocuri = v.nrLocuri;
		capCilindrica = v.capCilindrica;
		denumire = new char[strlen(v.denumire) + 1];
		strcpy(denumire, v.denumire);
	}

	Vehicul operator=(const Vehicul& v)
	{
		nrLocuri = v.nrLocuri;
		capCilindrica = v.capCilindrica;
		// doar pt pointeri stergem daca aveam deja cv alocat in el
		if (denumire)
		{
			delete[] denumire;
		}
		denumire = new char[strlen(v.denumire) + 1];
		strcpy(denumire, v.denumire);
		return *this;
	}

	~Vehicul()
	{
		cout << "S-a apelat destructorul pentru vehiculul " << this->denumire << endl;

		if (denumire)
		{
			delete[] denumire;
		}
		
	}

	virtual void Deplasare()
	{
		cout << "Vehiculul se deplaseaza." << endl;
	}

	friend ostream& operator<<(ostream&, Vehicul&); // supraincarcare operator de citire pt a putea afisa vehicul

};

ostream& operator<<(ostream& iesire, Vehicul& v)
{
	iesire << "Vehiculul cu denumirea " << v.denumire << " are " << v.nrLocuri << " locuri si o cap cilindrica de " << v.capCilindrica << endl;
	return iesire;
}

// clasa abstracta
class Impozit
{
public:
	virtual float Impozitare() = 0;
};


class Masina : public Vehicul, private Impozit // derivam Masina din Vehicul si Impozit
{
public :
	char nrInmatriculare[8];
	
	Masina()
	{
		strcpy(nrInmatriculare, "AAXXAAA");
	}

	Masina(const char* d, int n, float c, const char* nr) : Vehicul(d, n, c)
	{
		strcpy(nrInmatriculare, nr);
	}

	~Masina()
	{
		cout << "S-a apelat destructorul pentru masina " << this->denumire << endl;
	}

	void Deplasare()
	{
		cout << "Masina se deplaseaza pe uscat." << endl;
	}

	// a trebuit supraincarcata deoarece am pus private Impozit la Masina cand am derivat
	float Impozitare()
	{
		if (this->capCilindrica < 2)
		{
			return 50;
		}
		else
		{
			return 100;
		}
	}

};



void main()
{
	Vehicul v1;
	Vehicul v2("Terestru", 3, 1.2);
	Vehicul v3 = v2;
	Vehicul v4;
	v4 = v1;

	cout << v2;

	Masina m1;
	Masina m2("Logan", 5, 1.6, "B100ABC");
	v1 = m2; // in v1, vom avea ce este in m2, mai putin ultimul parametru, nr de inmatriculare

	// pt functiile virtuale:
	Vehicul* pv = &v2;
	Masina* pm = &m2;
	pv->Deplasare();
	pm->Deplasare();

	pv = pm;
	pv->Deplasare(); // va afisa Masina se deplaseaza pe uscat

	// pt impozitare
	cout << m2.Impozitare()<< endl;

	// Impozit i; // imi da eroare asa, atunci fac pointer
	//Impozit* pi;
	//pi = pm; // nu ma lasa deoarece am pus Impozit private, il pun public daca vreau sa mearga

}
