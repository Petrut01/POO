#include <iostream>
#include <cstring>
#include <time.h>
using namespace std;

///template pentru metodele folosite pe componente
template<class T>
class List {
public:
	List<T> *urm = nullptr;
	static List<T> *prim, *ultim;
	T *ths = nullptr;
	List();
	~List();
	void add(T *obj);
	void close();
	T *obj();
	T *getNthWithTag(int n, char z[1]);
};

template<class T>
List<T> *List<T>::prim;
template<class T>
List<T> *List<T>::ultim = prim;

///Constructor implicit
template<class T>
List<T>::List()
{
}

///Deinitializarea listelor
template<class T>
List<T>::~List()
{
	List<T> *temp = prim;
	List<T> *lst;
	if (temp) {
		do {
			lst = temp;
			temp = temp->urm;
			delete(lst);
		} while (temp->urm);
	}
	delete(temp);
}

///Adauga un element nou de tipul template-ului
template<class T>
void List<T>::add(T *obj)
{
	List<T> *temp = this;
	if (temp->ths)
	{
		while (temp->urm)
		{
			temp = temp->urm;
		}
		temp->urm = new List < T >;
		temp->urm->ths = obj;
		temp->urm->urm = nullptr;
	}
	else
	{
		temp->ths = obj;
	}
}

///Inchide lista legand ultimul element de primul
template<class T>
void List<T>::close()
{
	ultim->next = prim;
}

template<class T>
T *List<T>::obj() {
	return ths;
}

class Material {
public:
	char name[32];
	short unsigned int pret;
	static List<Material> mats;
	Material();
	static void AdaugareMaterial(const char nume[32], short unsigned int cost);
	static Material *find(char input[32]);
private:
	Material(const char nume[32], short unsigned int cost);
};


Material::Material(const char nume[32],short unsigned int cost) {
	strcpy(name, nume);
	pret = cost;
}

List<Material> Material::mats;

void Material::AdaugareMaterial(const char nume[32], short unsigned int cost) {

	mats.add(new Material(nume, cost));
}

Material::Material() {
}

Material *Material::find(char input[32]) {
	List<Material> *temp = &mats;
	input = strlwr(input);
	int ok = 0;
	if (temp->ths)
	{
		do {
			if (strcmp(input, strlwr(temp->ths->name)) == 0) {
				return temp->obj();
			}
			if (temp->urm)
                temp = temp->urm;
            else
                ok = 1;

		} while (ok == 0);
	}
	else
	{
		if (temp->urm)
		{
			temp = temp->urm;
			do {
				if (strcmp(input, strlwr(temp->ths->name)) == 0) {
					return temp->obj();
				}
				if (temp->urm)
                    temp = temp->urm;
                else
					ok = 1;
			} while (ok == 0);
		}
		else return 0;
	}

	return 0;
}


class MatObj{
public:
	Material *mat;
	int nr = 0;
	MatObj(Material *mt, int val)
	{
		nr = val;
		mat = mt;
	}
	MatObj() {};
};

class Problem {
private:
	char name[256];
	char flags[64];
	int efort = 0;
	List<MatObj> lista;
	virtual void getMaterials(const char src[256]);
public:
	Problem(const char nume[256],const char flg[64], int efort,const char materials[256]);
	Problem();
	~Problem();
	virtual void print();
	virtual bool verif(const char z);
};

Problem::Problem(const char nume[256],const char tip[64], int ef,const char materials[256]) {
	strcpy(name, nume);
	strcpy(flags, tip);
	efort = ef;
	getMaterials(materials);
}

Problem::Problem() {

}

Problem::~Problem() {

}

///verifica daca obiectul poate avea un anumit tip de problema
bool Problem::verif(const char z){
	if (strchr(flags, z))
	{
		return true;
	}
	return false;
}

/// template folosit pentru componente
template<typename T>
class Component{
public:
	static List<Problem> problems;
	List<Problem> actualProblems;
	virtual void add(char nume[256], char tip[64], int ef, char materials[256]= "\n");
	virtual void damage(char flag);
	virtual void deviz();
	virtual Problem *getNthWithTag(int n, char z);
	virtual bool tipValid(char flag);
	static void AdaugareProblema(const char nume[256],const char tip[64], int ef,const char materials[256]="\n");
};


template<typename T>
List<Problem> Component<T>::problems;

template<class T>
void Component<T>::add(char nume[256], char tip[64], int ef, char materials[256]){
	Problem aux(nume, tip, ef, materials);
	this->problems.add(&aux);
}

template<class T>
void Component<T>::AdaugareProblema(const char nume[256],const char tip[64], int ef,const char materials[256]) {
	Problem *aux = new Problem(nume, tip, ef, materials);
	Component::problems.add(aux);
}

template<class T>
void Component<T>::damage(char flag)
{
	int i = rand() % 10+1;///alege random
	if (i>3) {
		Problem *aux = nullptr;
		if (tipValid(flag)) {
			aux = getNthWithTag(i, flag);
		}
		if(aux)
		{
			actualProblems.add(aux);
		}

	}

}


template<class T>
bool Component<T>::tipValid(char flag)
{
	List<Problem> *temp = &this->problems;
	while (temp)
	{
		if (temp->obj()->verif(flag))
		{
			return true;
		}
		temp = temp->urm;
	}
	return false;
};

template<class T>
Problem *Component<T>::getNthWithTag(int n, char z)
{
	List<Problem> *frst = &this->problems;
	List<Problem> *temp = &this->problems;
	int ok = 0;
	int i = 1;
	while (i < n)
	{
		if (temp->urm)
		{
			ok = 0;
			while (!ok)
			{
				if (temp->obj()->verif(z))
				{
					ok = 1;
				}
				else
				{
					if (temp->urm)
					{
						temp = temp->urm;
					}
					else
					{
							temp = frst;
					}
				}
			}
			i++;
		}
		else
		{
			i = n;
		}
	}
	return temp->obj();
}

template<class T>
void Component<T>::deviz()
{
	if(actualProblems.obj())
	{
		actualProblems.obj()->print();
	}
}

class Brakes: public Component<Brakes> {
public:
	Brakes() {};
};

class Engine: public Component<Engine> {
public:
	Engine() {};
};

class Direction: public Component<Direction> {
public:
	Direction() {};
};

class Emissions: public Component<Emissions> {
public:
	Emissions() {};
};

class Chassis : public Component<Chassis> {
public:

	Chassis() {};
};

class Vehicle {
public:
	char name[32];
	char tag;
	int year;
	Engine motor;
	Brakes frane;
	Direction directie;
	Chassis caroserie;
	Emissions noxe;
	virtual void damage();
	virtual void deviz();
	void operator=(const Vehicle &v);
};

void Vehicle::damage() {
	motor.damage(tag);
	frane.damage(tag);
	directie.damage(tag);
	caroserie.damage(tag);
	noxe.damage(tag);
}

void Vehicle::deviz() {
	motor.deviz();
	frane.deviz();
	directie.deviz();
	caroserie.deviz();
	noxe.deviz();
}

void Vehicle::operator=(const Vehicle &v)
{
	tag=v.tag;
	strcpy(name, v.name);
	year = v.year;
}


class Atelier {
private:
	static Vehicle Vehicul;
public:
	static int cost_total;
	static int pret_efort;
	Atelier();
	~Atelier();
	static void receive(const Vehicle &obj);
	static void deviz();
};



void Problem::getMaterials(const char src[256]) {
	int n = strlen(src),z=0,v=0;
	char aux[32];
	MatObj *ob;
	for (int i = 0;i < n;i++)
	{
		if (src[i] != ':')
		{
			aux[z] = src[i];
			z++;
		}
		else
		{
			aux[z] = '\0';
			z = 0;
			v = 0;
			if (src[i+1] == 'r') {
				i+=2;
				while (src[i] != '\0' && src[i] != ';')
				{
					v = v*10 + src[i] - '0';
					i++;
				}
			}
			else
			{   i++;
				while (src[i] != ';' || src[i] == '\0')
				{
					v = v * 10 + src[i] - '0';
					i++;
				}
			}
			ob = new  MatObj(Material::find(aux), v);
			lista.add(ob);

		}
	}
}

int Atelier::cost_total = 0;
//int Atelier::pret_efort = 5;

void Problem::print() {
	if (efort != 0) {
		cout<<"Problema: "<<name<<endl;
		cout<<"Ore de lucru: "<<efort<<endl;
		cout<<"Materiale necesare:"<<endl;
		List<MatObj> *temp = &lista;
		while (temp){
			cout<<temp->ths->mat->name<<", ";
			cout<<temp->ths->mat->pret<<" lei/buc, ";
			cout<<"buc:"<<temp->ths->nr<<", ";
			cout<<"pret total: "<<temp->ths->nr*temp->ths->mat->pret<<endl;
			Atelier::cost_total += temp->ths->nr*temp->ths->mat->pret;
			//Atelier::cost_total += Atelier::pret_efort * efort;
			temp = temp->urm;
		}
		cout<<endl;
	}
	else
	{
		cout<<"Problema capitala\n";
	}
}


class Masina : public Vehicle {
public:
	Masina() { tag = 'a';
            strcpy(name, "Masina"); }
};

class Motocicleta : public Vehicle {
public:
	Motocicleta() {
		tag = 'm';
		strcpy(name, "Motocicleta");
	}
};

class Bicicleta : public Vehicle {
public:
	Bicicleta() {
		tag = 'b';
		strcpy(name, "Bicicleta");
	}
};

Vehicle Atelier::Vehicul = Vehicle();

void Atelier::receive(const Vehicle &obj) {
	Vehicul = obj;
	cout<<Vehicul.name<<endl;
	Vehicul.damage();
}

void Atelier::deviz() {
	Vehicul.deviz();
}

int main() {
	//adaugare materiale in lista
	Material::AdaugareMaterial("Suruburi", 2);
	Material::AdaugareMaterial("Ulei", 15);
	Material::AdaugareMaterial("placuta1", 5);
	Material::AdaugareMaterial("placuta2", 4);
	Material::AdaugareMaterial("placuta3", 6);
	Material::AdaugareMaterial("placuta4", 7);
	Material::AdaugareMaterial("Disc", 15);
	Material::AdaugareMaterial("Lant", 5);
	Material::AdaugareMaterial("Motor", 40);
	Material::AdaugareMaterial("Roata", 10);
	Material::AdaugareMaterial("Aripa", 5);
	Material::AdaugareMaterial("Capota", 5);
	Material::AdaugareMaterial("Vopsea", 20);
	Material::AdaugareMaterial("Bara", 5);

	Brakes::AdaugareProblema("Placute fata uzate", "am", 1, "placuta1:1;placuta2:1;suruburi:r10");
	Brakes::AdaugareProblema("Placute spate uzate", "am", 1, "placuta3:1;placuta4:1;suruburi:r10");
	Brakes::AdaugareProblema("Disc uzat", "am", 1, "disc:2;suruburi:r8");
	Brakes::AdaugareProblema("Discuri uzate", "a", 2, "disc:4;suruburi:r16");
	Brakes::AdaugareProblema("Lant tocit", "b", 1, "lant:1;suruburi:r5");
	Brakes::AdaugareProblema("Lant lipsa", "b", 1, "lant:1;suruburi:r5");
	Brakes::AdaugareProblema("Defect capital", "amb", 0);

	Engine::AdaugareProblema("Nivel ulei scazut", "am", 1, "ulei:1;suruburi:r15");
	Engine::AdaugareProblema("Carburator murdar", "a", 2, "suruburi:r15");
	Engine::AdaugareProblema("Motor topit", "am", 5, "motor:1;ulei:r1");
	Engine::AdaugareProblema("Defect capital", "am", 0);

	Direction::AdaugareProblema("Ghidon stramb", "mb", 1, "suruburi:r5");
	Direction::AdaugareProblema("Roata stramba", "amb", 1, "roata:1;suruburi:r6");
	Direction::AdaugareProblema("Defect capital", "amb", 0);

	Emissions::AdaugareProblema("Vehiculul arde ulei", "am", 2, "ulei:1;suruburi:r6");
	Emissions::AdaugareProblema("Vehiculul este anterior anului 2000", "am", 0, "suruburi:r5");
	Emissions::AdaugareProblema("Defect capital", "am", 0);

	Chassis::AdaugareProblema("Caroserie corodata de rugina", "a", 8, "vopsea:1;suruburi:r5");
	Chassis::AdaugareProblema("Caroserie stramba", "a", 3, "aripa:2;bara:1;capota:1;suruburi:r5");
	Chassis::AdaugareProblema("Defect capital", "a", 0);

	int choice;
	cout<<"Se primeste un vehicul: ";
	srand(time(NULL));
	choice = rand() % 3 + 1;
	switch (choice)
	{
	case 1:
		Atelier::receive(Masina());
		break;
	case 2:
		Atelier::receive(Motocicleta());
		break;
	case 3:
		Atelier::receive(Bicicleta());
		break;
	}
	Atelier::deviz();
	cout<<"Total: "<< Atelier::cost_total<<" lei";
	return 0;
}
