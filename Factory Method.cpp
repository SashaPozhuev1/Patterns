//Фабричный метод — это порождающий паттерн проектирования, который определяет общий интерфейс для создания объектов в суперклассе, 
//позволяя подклассам изменять тип создаваемых объектов.

#include <iostream>
#include <string>
using namespace std;

//Класс Band - базовый, определяет общий интерфейс объектов, которые может произвести создатель и его подклассы, 
//определяет неизменяемые параметры итоговой группы.
class Band{                     
public:
  int members = 2;                                            //Количество участников.
  string language = "Russian";                                //Язык исполнения.
  virtual void info () = 0;                                   //Информация о группе, для каждого вида групп своя.
};

//Наследуемые классы с общим интерфейсом. Представляют собой различные типы создаваемых групп, 
//которые будут различаться инструментальным составом.
class RockBand: public Band{                                  //Создание рок-группы.
public:
  string instrument = "guitar, drum";                         //Состав - гитара и барабаны.
  void info() override {
    cout << "Bands's instruments - " << instrument << endl;   //Переопределенная виртуальная функция с информацией.
  }
};

class ClassicBand: public Band{                               //Создание классической группы.
public:
  string instrument = "saxophone, piano";                     //Состав - саксофон и фортепиано.
  void info() override {
    cout << "Bands's instruments - " << instrument << endl;   //Переопределенная виртуальная функция с информацией.
  }
};

//Класс фабрики с общим интерфейсом для создания определенного вида группы.
class Creator{
public: 
  virtual Band* factoryMethod() = 0;                          //Виртуальный метод создания группы.
};

//Наследуемые классы с общим интерфейсом. Возвращают итоговый продукт (группу) с переопределенным фабричным методом.
class RockBandCreator: public Creator{
public:
  Band* factoryMethod() override {
    return new RockBand;                                      //Собирает Рок-группу.
  }
};

class ClassicBandCreator: public Creator{
public: 
  Band* factoryMethod() override {
    return new ClassicBand;                                   //Собирает Классическую группу.
  }
};

int main()
{
                                            //                Пример создания группы (рок-группы).
  RockBandCreator DeepPurple;               //1) Создаём объект (фабрику рок-группы), с переопределённым фабричным методом.
  Creator * creator1 = &DeepPurple;         //2) Создаём объект руководящей фабрики(указатель на рок-фабрику), так как используем интерфейс (руководящей фабрики).
  Band * band1 = creator1->factoryMethod(); //3) Создаём объект группы, пользуясь фабрикой с переопределённым фабричным методом, 
                                            //   который вернёт объект рок-группы с переопредёленными виртуальными функциями (info()), то есть рок-группу.
  band1->info();                            //4) Выведем информацию о получившейся группе.
  
  
  ClassicBandCreator Orchestra;             //То же самое для классической группы.
  Creator * creator2 = &Orchestra;
  Band * band2 = creator2->factoryMethod();
  band2->info();
  
  return 0;
}
