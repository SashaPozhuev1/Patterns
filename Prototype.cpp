//Прототип — это порождающий паттерн проектирования, 
//который позволяет копировать объекты, не вдаваясь в подробности их реализации.
#include <iostream>
#include <string>
using namespace std;

//1)Создадим базовый класс (Канцелярия).
class Chancery 
{
private:
    int size;
    string color;
public:
    Chancery(){};
    Chancery(const Chancery & other) {
        size = other.size;
        color = other.color;
    }
    virtual void Set(int, string const &) = 0;
    virtual Chancery * clone() = 0;
    virtual void info() = 0;
};

//2) Создадим производный класс (Ручки), их может быть несколько.
class Pen : public Chancery
{
private:
    int size;                                      //Приватные поля, которые нельзя скопировать простым методом.     
    string color;
public:
    Pen() {};
	Pen(const Pen   & other) : Chancery (other) {  //Конструктор копирования.
        size = other.size;
        color = other.color;
    }
    
	Pen * clone() override {                        //Как видно, фактически функцию копирования реализует конструктор копирования,
        return new Pen( *this );                    //clone() лишь возвращает созданный при помощи этого конструктора объект.
    }
    
    void Set(int a, string const & b) override {    //Можем задать приватным полям собственные значения. 
        size = a;
        color = b;
    }
    
    void info() override {
        cout << "size: " << size << ";\ncolor: " << color << ";\n";
    }
};

//ПРИМЕР:
int main() {
    Pen *pen = new Pen;                //Создадим указатель на новую ручку и выделем её память.
    pen->Set(1, "RED");                //Зададим её параметры.             
    pen->info();                       //Выведем информацию.
    
    Pen *otherpen = pen->clone();      //Теперь создадим указатель на другую ручку, а старая своим методом копирования вернёт область памяти для другой ручки.
    otherpen->info();                  //Выведем информацию, чтобы удостоверится, что она совпадает.
    return 0;   
}
