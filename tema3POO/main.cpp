#include <iostream>
#include <typeinfo>
#include <cstring>
#include <vector>

using namespace std;

template<class T>
class Gestiune;

template<>
class Gestiune<char*>;

istream& operator>>(istream& in,Gestiune<char*>& ob);
ostream& operator<<(ostream& out,const Gestiune<char*>& ob);

template<class T>
istream& operator>>(istream& in, Gestiune<T> & ob);

template<class T>
ostream& operator<<(ostream& in, const Gestiune<T> & ob);


class Locuinta
{
protected:
    string nume_client;
    float suprafata_utila;
    float discount;
    float chirie;
    float pretm2;//pretul pe metru patrat
public:
    virtual istream& citire(istream&)=0;//citeste
    virtual ostream& afisare(ostream&)const=0;//afiseaza
    virtual void calc_chirie()=0;//functie care calculeaza chiria

    Locuinta();//constructor neparametrizat
    Locuinta(string,float,float,float);//constructor parametrizat
    Locuinta(const Locuinta&);//constructor de copiere
    ~Locuinta(){}

    friend class Gestiune<char*>;
    template<class T>
    friend class Gestiune;

    friend istream& operator>>(istream& in,Gestiune<char*>& ob);
    friend ostream& operator<<(ostream& out,const Gestiune<char*>& ob);
    template<class T>
    friend istream& operator>>(istream& in, Gestiune<T> & ob);
    template<class T>
    friend ostream& operator<<(ostream& in, const Gestiune<T> & ob);

};

class Apartament:public Locuinta
{
    int etaj;
public:
    istream& citire(istream&);//functie de citire supraincarcata
    ostream& afisare(ostream&) const;//functie de afisare supraincarcata
    void calc_chirie();//functie de chirie supraincarcata
    friend istream& operator>>(istream& , Apartament&);//operator de citire supraincarcat
    friend ostream& operator<<(ostream& , const Apartament&);//operator de afisare supraincarcat
    static void ap_incr_nr_loc(){static int numar_ap=0;numar_ap++;}//functie statica care incrementeaza numarul de apartamente create in timpul rularii programului
    Apartament():Locuinta(){this->etaj=0;}//constr de initializare
    Apartament(string nume,float sup_utila,float d,float pm2,int e):Locuinta(nume,sup_utila,d,pm2){this->etaj=e;}//constr de initializare parametrizat
    Apartament(const Apartament &);//constr de copiere
    Apartament operator=(const Apartament&);//operator de atribuire
    ~Apartament(){}
};

class Casa:public Locuinta
{
    float curte;//suprafata curtii
    float pretm2curte;
    int nr_etaje;
    float *et;//retine suprafata utila pentru fiecare etaj in parte
public:
    istream& citire(istream&);//functie de citire supraincarcata
    ostream& afisare(ostream&) const;//functie de afisare supraincarcata
    void calc_chirie();
    friend istream& operator>>(istream& , Casa&);//operator de citire supraincarcat
    friend ostream& operator<<(ostream& , const Casa&);//operator de afisare supraincarcat
    static void casa_incr_nr_loc(){static int numar_case=0;numar_case++;}//functie statica care incrementeaza numarul de case inregistrate in timpul rularii programului
    Casa():Locuinta()
        {this->curte=0; this->pretm2curte=0; this->nr_etaje=0; this->et=NULL; calc_chirie();}//constructor fara parametri
    Casa(string nume,float sup_utila,float d ,float pm2,float c,float pm2curte,int nr_et):Locuinta(nume,sup_utila,d,pm2)
        {this->curte=c; this->pretm2curte=pm2curte; this->nr_etaje=nr_et;
        cout<<"Introduceti suprafata utila pt fiecare etaj in parte:"<<endl;
        this->et=new float[this->nr_etaje];
        for(int i=0;i<this->nr_etaje;i++)
            cin>>this->et[i];
        this->calc_chirie();}//constructor parametrizat
    Casa(const Casa&);//constructor de copiere
    Casa operator=(const Casa&);//constructor de atribuire
    ~Casa(){};

};

///Clasa template Gestiune
template<class T>
istream& operator>>(istream&, Gestiune<T> &);

template<class T>
ostream& operator<<(ostream&, const Gestiune<T>&);

template<class T>
class Gestiune
{
    vector<Locuinta*> p;//vector ce retine locuintele aflate in gestiune
    vector<T> tip_loc ;//vector ce retine casele sau apartamentele aflate in gesitune
    vector<float>chirie;//vector ce retine chiria pentru fiecare apartament/casa ce se afla in gestiune
public:
    Gestiune();//constructor de initializare
    Gestiune(int);//constructor de initializare parametrizat
    Gestiune(const Gestiune<T>&);//constructor de copiere
    Gestiune operator=(const Gestiune<T>&);//operator de atribuire
    Locuinta* operator+=(Locuinta*);//operator += supraincarcat , adauga o locuinta la gestiune
    friend istream& operator >> <T>(istream&, Gestiune<T> &);//operator de citire supraincarcat
    friend ostream& operator << <T>(ostream&, const Gestiune<T>&);//operator de afisare supraincarcat
};

///Definesc metodele clasei Locuinta
Locuinta::Locuinta()//constructor fara parametri
{
    //cout<<"Constr baza";
    this->nume_client="";
    this->suprafata_utila=0;
    this->discount=0;
    this->pretm2=0;
    this->chirie=0;
}
Locuinta::Locuinta(string nume,float sup,float d,float pm2)//constructor parametrizat
{
    //cout<<"Constr baza";
    this->nume_client=nume;
    this->suprafata_utila=sup;
    this->discount=d;
    this->chirie=0;
    this->pretm2=pm2;
}

Locuinta::Locuinta(const Locuinta& ob)//constructor de copiere
{
    this->nume_client=ob.nume_client;
    this->suprafata_utila=ob.suprafata_utila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pretm2=ob.pretm2;
}

///Definesc metodele clasei Apartament
Apartament::Apartament(const  Apartament& ob)//constr de copiere
{
    this->nume_client=ob.nume_client;
    this->suprafata_utila=ob.suprafata_utila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pretm2=ob.pretm2;
    this->etaj=ob.etaj;
}

Apartament Apartament::operator=(const Apartament& ob)//operator de atribuire
{
    if(this != &ob)
    {
    this->nume_client=ob.nume_client;
    this->suprafata_utila=ob.suprafata_utila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pretm2=ob.pretm2;
    this->etaj=ob.etaj;
    }
    return *this;
}

istream& Apartament::citire(istream& in)//functie de citire supraincarcata
{
    cout<<"Se citesc datele unui apartament:"<<endl;
    cout<<" nume client:";
    in>>this->nume_client;//citeste numele clientului
    suprafatautila:
    try//citeste suprafata utila si verifica daca este un nr pozitiv
    {
        cout<<"suprafata utila:";
        in>>this->suprafata_utila;
        if(this->suprafata_utila<=0)
            throw this->suprafata_utila;
        }catch(float err)
        {
            cout<<"Suprafata utila trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
            goto suprafatautila;//se cere reintroducerea suprafetei utile
        }

    discountexceptie:
        try//citeste discountul si verifica daca este >=0 si <=10
        {
            cout<<"discount:";
            in>>this->discount;
            if(this->discount<0 || this->discount>10)
                throw this->discount;
        }catch(float disc)
        {
            cout<<"Discountul trebuie sa fie un nr pozitiv <= 10. Reintroduceti."<<endl;
            goto discountexceptie;//se cere reintroducerea discountului
        }

    pretpem2:
        try//citeste pretul pe metrul patrat si verifica daca este un nr pozitiv
        {
            cout<<"pret pe metru patrat:";
            in>>this->pretm2;
            if(this->pretm2<0)
                throw this->pretm2;
        }catch(float pret)
        {
            cout<<"Pretul pe metru patrat trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
            goto pretpem2;//se cere reintroducerea pretului pe metru patrat
        }

    etajexc:
        try//se citeste etajul la care se afla apartamentul si se verifica daca este un nr pozitiv <=10
        {
            cout<<"etaj:";
            in>>this->etaj;
            if(this->etaj<0 || this->etaj>10)
                throw this->etaj;
        }catch(int et)
        {
            cout<<"Etajul trebuie sa fie un nr pozitiv <=10. Reintroduceti."<<endl;
            goto etajexc;//se cere reintroducerea etajului
        }
    this->calc_chirie();//calculeaza chiria
    cout<<endl;
    Apartament::ap_incr_nr_loc();
    return in;
}

ostream& Apartament::afisare(ostream& out) const//functie de afisare supraincarcata
{
    out<<"Apartament: ";
    out<<"Nume client- "<<this->nume_client<<"; Suprafata utila- "<<this->suprafata_utila<<" mp; Discount- "<<this->discount<<"%; Pret pe metru patrat- "<<this->pretm2<<"lei; Etaj- "<<this->etaj<<endl;
    out<<"Chirie- "<<this->chirie<<" lei"<<endl<<endl;
    return out;
}

void Apartament::calc_chirie()//functia de calculare a chiriei supraincarcata
{
    this->chirie=(this->pretm2 * this->suprafata_utila) * (float(100)-this->discount)/float(100);
}

istream& operator>>(istream& in, Apartament& ob)//operator de citire supraincarcat
{
    return ob.citire(in);
}

ostream& operator<<(ostream& out, const Apartament& ob)//operator de afisare supraincarcat
{
    return ob.afisare(out);
}

///Definesc metodele clasei Casa
istream& Casa::citire(istream& in)//functie de citire supraincarcata
{
    cout<<"Se citesc datele unei case:"<<endl;
    cout<<" Nume client:";
    in>>this->nume_client;

    suprafatautila:
    try//citeste suprafata utila si verifica daca este un nr pozitiv
    {
        cout<<"Suprafata utila:";
        in>>this->suprafata_utila;
        if(this->suprafata_utila<=0)
            throw this->suprafata_utila;
        }catch(float err)
        {
            cout<<"Suprafata utila trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
            goto suprafatautila;//cere reintroducerea suprafetei utile
        }

    discountexceptie:
        try//citeste discountul si verifica daca este un nr pozitiv <10
        {
            cout<<"Discount:";
            in>>this->discount;
            if(this->discount<0 || this->discount>10)
                throw this->discount;
        }catch(float disc)
        {
            cout<<"Discountul trebuie sa fie un nr pozitiv <= 10. Reintroduceti."<<endl;
            goto discountexceptie;//se cere reintroducerea discountul
        }

    pretpemp:
        try//citeste pretul pe metru patrat si verifica daca este un nr pozitiv
        {
            cout<<"Pret pe metru patrat:";
            in>>this->pretm2;
            if(this->pretm2<0)
                throw this->pretm2;
        }catch(float pret)
        {
            cout<<"Pretul pe metru patrat trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
            goto pretpemp;//se cere reintroducerea pretului pe metru patrat
        }

    curteext:
        try//citeste suprafata curtii si verifica daca este un nr pozitiv
        {
            cout<<"Suprafata curte:";
            in>>this->curte;
            if(this->curte<0)
                throw this->curte;
        }catch(float c)
        {
            cout<<"Suprafata curtii trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
            goto curteext;//se cere reintroducerea suprafetei curtii
        }

    pretmpcurteext:
        try//citeste pretul pe metru patrat de curte si verifica daca este pozitiv
        {
            cout<<"Pret pe metru patrat de curte:";
            in>>this->pretm2curte;
            if(this->pretm2curte<0)
                throw this->pretm2curte;
        }catch(float c)
        {
            cout<<"Pretul pe metru patrat de curte trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
            goto pretmpcurteext;//se cere reintroducerea pretului pe metru patrat de curte
        }

    numaretaje:
        try//citeste numarul de etaje si verifica daca este un nr pozitiv
        {
            cout<<"Numar etaje:";
            in>>this->nr_etaje;
            if(this->nr_etaje<0)
                throw this->nr_etaje;
        }catch(int c)
        {
            cout<<"Numarul de etaje trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
            goto numaretaje;//se cere reintroducerea numarului de etaje
        }

    float s=0;
    suprpeetaj:
        try//citeste suprafata utila pe fiecare etaj in parte , verifica daca este un nr pozitiv si daca suma suprafetelor este egala cu suprafata utila totala
        {
            s=0;
            cout<<"Suprafata utila pe fiecare etaj in parte:"<<endl;
            et=new float[nr_etaje];
            for(int i=0;i<nr_etaje;i++)
            {
                in>>et[i];
                if(et[i]<0)
                    throw 1;
                s=s+et[i];
            }
            if(s!=this->suprafata_utila)
                throw s;
        }catch(float sss)
        {
            cout<<"Suma suprafetelor pe etaje trebuie sa fie egale cu suprafata utila totala. Reintroduceti."<<endl;
            goto suprpeetaj;//se cere reintroducerea suprafetei pe etaj
        }catch(int x)
        {
            cout<<"Suprafata pe etaj trebuie sa fie un nr pozitiv.Reintroduceti";
            goto suprpeetaj;//se cere reintroducerea suprafetei pe etaj
        }

    this->calc_chirie();
    cout<<endl;
    Casa::casa_incr_nr_loc();
    return in;
}

ostream& Casa::afisare(ostream& out) const//functie de afisare supraincarcata
{
    out<<"Casa: ";
    out<<"Nume client- "<<this->nume_client<<"; Suprafata utila- "<<this->suprafata_utila<<" mp; Discount- "<<this->discount<<"%; Pret pe metru patrat- "<<this->pretm2<<" lei; Suprafata curte- "<<this->curte<<"; Pret pe metru patrat curte- ";
    out<<this->pretm2curte<<" lei; Nr etaje- "<<this->nr_etaje;
    out<<endl<<"Suprafata pe fiecare etaj in parte:"<<endl;
    for(int i=0;i<this->nr_etaje;i++)
        if(i==0)
            out<<"Parter"<<"-"<<this->et[i]<<endl;
        else out<<"Etajul "<<i<<"-"<<this->et[i]<<endl;
    out<<"Chirie- "<<this->chirie<<" lei"<<endl<<endl;
    return out;
}

void Casa::calc_chirie()//functie de calculare a chiriei supraincarcata
{
    this->chirie=(this->suprafata_utila * this->pretm2) * (float(100)-this->discount)/float(100) + this->curte*this->pretm2curte;
}

Casa::Casa(const Casa& ob)//constructor de copiere
{
    this->nume_client=ob.nume_client;
    this->suprafata_utila=ob.suprafata_utila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pretm2=ob.pretm2;
    this->curte=ob.curte;
    this->pretm2curte=ob.pretm2curte;
    this->nr_etaje=ob.nr_etaje;
    delete [] this->et;
    this->et=new float[nr_etaje];
    for(int i=0;i<this->nr_etaje;i++)
        this->et[i]=ob.et[i];
}
Casa Casa::operator=(const Casa& ob)//constructor de atribuire
{
    if(this != &ob)
    {this->nume_client=ob.nume_client;
    this->suprafata_utila=ob.suprafata_utila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pretm2=ob.pretm2;
    this->curte=ob.curte;
    this->pretm2curte=ob.pretm2curte;
    this->nr_etaje=ob.nr_etaje;
    delete [] this->et;
    this->et=new float[nr_etaje];
    for(int i=0;i<this->nr_etaje;i++)
        this->et[i]=ob.et[i];
    }
    return *this;
}

istream& operator>>(istream& in, Casa& ob)//operator de citire supraincarcat
{
    return ob.citire(in);
}

ostream& operator<<(ostream& out, const Casa& ob)//operator de afisare supraincarcat
{
    return ob.afisare(out);
}


///Definesc metodele clasei template Gestiune

template<class T>
Gestiune<T>::Gestiune()//constructor de initializare
{
    this->p.resize(0);
    this->tip_loc.resize(0);
    this->chirie.resize(0);
}

template<class T>
Gestiune<T>::Gestiune(int nrl)//constructor de initializare parametrizat
{
    cout<<"Un obiect Gestiune cu "<<nrl<<" locuinte este creat."<<endl;

    char opt;

    for(int i=0;i<nrl;i++)//citeste locuintele
    {
        cout<<"Introduceti datele locuintei "<<i+1<<" ( A - apartament , C - casa)"<<endl;
        cin>>opt;
        switch(opt)
        {
        case 'A':
            {
                p.push_back(new Apartament);
                cin>>*(dynamic_cast<Apartament*>(p[i]));
                break;
            }
        case 'C':
            {
                p.push_back(new Casa);
                cin>>*(dynamic_cast<Casa*>(p[i]));
                break;
            }

        }
    }
    T a;//adauga apartamentele sau casele si chiriile aferente in vectorii respectivi
    for(unsigned i=0;i<p.size();i++)
        if(typeid(*p[i]).name() == typeid(a).name())
    {
        tip_loc.push_back(*(dynamic_cast<T*>(p[i])));
        chirie.push_back((tip_loc.end()-1)->chirie);
    }

}

template<class T>
Gestiune<T>::Gestiune(const Gestiune<T>& ob)//constructor de copiere
{
    p.assign(ob.p.begin(),ob.p.end());
    tip_loc.assign(ob.tip_loc.begin(),ob.tip_loc.end());
    chirie.assign(ob.chirie.begin(),ob.chirie.end());

}

template<class T>
Gestiune<T> Gestiune<T>::operator=(const Gestiune<T>& ob)//operator de atribuire
{
    p.assign(ob.p.begin(),ob.p.end());
    tip_loc.assign(ob.tip_loc.begin(),ob.tip_loc.end());
    chirie.assign(ob.chirie.begin(),ob.chirie.end());
    return *this;
}

template<class T>
Locuinta* Gestiune<T>::operator+=(Locuinta* ob)//operator += supraincarcat
{
    Apartament a;
    Casa b;
    if(typeid(*ob).name() == typeid(a).name())//verifica daca pointerul ob pointeaza catre un obiect apartament
    {
        p.push_back(new Apartament);
        *(dynamic_cast<Apartament*>(*(p.end()-1)))=*(dynamic_cast<Apartament*>(ob));
    }
    else
    {   //in cazul in care pointerul ob pointeaza catre un obiect casa
        p.push_back(new Casa);
        *(dynamic_cast<Casa*>(*(p.end()-1)))=*(dynamic_cast<Casa*>(ob));
    }
    T t;
    if(typeid(*ob).name() == typeid(t).name())//verifica daca pointerul ob pointeaza catre un obiect de tipul T
    {
        tip_loc.push_back(*(dynamic_cast<T*>(ob)));
        chirie.push_back((tip_loc.end()-1)->chirie);
    }
    return ob;
}


template<class T>
istream& operator>>(istream& in, Gestiune<T> & ob)//operator de citire supraincarcat
{
    cout<<"Cate locuinte sa se afle in gestiune?";
    int nrl;
    in>>nrl;
    cout<<endl<<"Un obiect Gestiune cu "<<nrl<<" locuinte se creeaza."<<endl;

    char opt;

    for(int i=0;i<nrl;i++)
    {
        cout<<"Introduceti datele locuintei "<<i+1<<" ( A - apartament , C - casa)"<<endl;
        in>>opt;
        switch(opt)
        {
        case 'A':
            {
                ob.p.push_back(new Apartament);
                in>>*(dynamic_cast<Apartament*>(ob.p[i]));
                break;
            }
        case 'C':
            {
                ob.p.push_back(new Casa);
                in>>*(dynamic_cast<Casa*>(ob.p[i]));
                break;
            }
        }
    }
    T a;//adauga apartamentele sau casele si chiriile aferente in vectorii respectivi
    for(unsigned i=0;i<ob.p.size();i++)
        if(typeid(*(ob.p[i])).name() == typeid(a).name())
    {
        ob.tip_loc.push_back(*(dynamic_cast<T*>(ob.p[i])));
        ob.chirie.push_back(ob.tip_loc.end()->chirie);
    }
    return in;
}

template<class T>
ostream& operator<<(ostream& out, const Gestiune<T>& ob)//operator de afisare supraincarcat
{
    out<<"Se afiseaza locuintele aflate in gestiune:"<<endl;
    Apartament a;
    Casa b;
    for(unsigned i=0;i<ob.p.size();i++)
        if(typeid(*(ob.p[i])).name() == typeid(a).name())
            out<<*(dynamic_cast<Apartament*>(ob.p[i]));//verifica daca obiectul este apartament
        else
            out<<*(dynamic_cast<Casa*>(ob.p[i]));//in cazul in care obiectul este casa
    out<<endl;
    return out;
}

int main()
{
    ///Se citesc si se afiseaza n obiecte de tip locuinta
    Gestiune<Casa> g;
    cin>>g;
    cout<<g;
    return 0;
}

