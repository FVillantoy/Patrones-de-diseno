#include <iostream>
#include <unordered_map>
using namespace std;

struct Datos{
    string nombre;
    string apellido;
    Datos(const string &nombre_,const string &apellido_): nombre(nombre_),apellido(apellido_){}
    friend ostream &operator<<(ostream &os, const Datos &ss)
    {
        return os << "[ " << ss.nombre << " , " << ss.apellido << " ]";
    }

};
struct Estado{
    string estado;
    string nota;

    Estado(const string &estado_, const std::string &nota_) : estado(estado_), nota(nota_){}

    friend ostream &operator<<(ostream &out, const Estado &es)
    {
        return out << "[ " << es.estado << " , " << es.nota << " ]";
    }
};

class Flyweight
{
private:
    Datos *datosF;
public:
    Flyweight(const Datos *newdatos) : datosF(new Datos(*newdatos)){}
    Flyweight(const Flyweight &newFW) : datosF(new Datos(*newFW.datosF)){}
    ~Flyweight(){
        delete datosF;
    }
    Datos* getDatos(){
        return datosF;
    }
    void Operation(const Estado &est)const{
        cout << "Alumno (" << *datosF << ") estado: (" << est << ")"<<endl;
    }
};
class FlyweightFactory{
private:
    unordered_map<string, Flyweight> flyweights_map;
    string GetKey(const Datos &stg) const
    {
        return stg.nombre + "_" + stg.apellido;
    }
public:
     FlyweightFactory(initializer_list<Datos> datos_lista){
        for (const Datos &lista : datos_lista)
        {
            this->flyweights_map.insert(make_pair<string, Flyweight>(this->GetKey(lista), Flyweight(&lista)));
        }
     }
    Flyweight GetFW(const Datos &datos_get){
            string key = this->GetKey(datos_get);
            if (this->flyweights_map.find(key) == this->flyweights_map.end())
            {
                cout << "FW no encontrado, creando uno...."<<endl;
                this->flyweights_map.insert(make_pair(key, Flyweight(&datos_get)));
            }
            else
            {
                cout << "usando FW de la lista"<<endl;
            }
            return this->flyweights_map.at(key);
        }
    void ListFlyweights() const
    {
        size_t count = this->flyweights_map.size();
        cout << "hay" << count << " flyweight:"<<endl;
        for (pair<string, Flyweight> pair : this->flyweights_map)
        {
            cout << pair.first << endl;
        }
    }
};

void RegistroDeAprobados(FlyweightFactory &FR, const string &nombre_, const string &apellido_,const string &estado_,const string &nota_){
    cout<<endl<<"Accediendo al registro...."<<endl;
    const Flyweight &flyweight = FR.GetFW({nombre_,apellido_});
    flyweight.Operation({estado_,nota_});

}

int main()
{
    FlyweightFactory *factory = new FlyweightFactory({{"Leo", "Gaona"}, {"Kevin", "Rodriguez"}, {"Josue", "Philco"}, {"Fabricio", "Villantoy"}});
    factory->ListFlyweights();
    RegistroDeAprobados(*factory,"Leo", "Gaona","aprobado","19");
    RegistroDeAprobados(*factory,"Juan", "Alvares","desaprobado","05");
    cout<<endl;
    factory->ListFlyweights();
    return 0;
}
