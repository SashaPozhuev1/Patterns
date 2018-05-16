//Абстрактная фабрика — это порождающий паттерн проектирования, который позволяет создавать 
//семейства связанных объектов, не привязываясь к конкретным классам создаваемых объектов.

#include <iostream>
#include <string>
using namespace std;

//1) Создадим  различные базовые классы различных объектов с которыми будем работать (фильмы и книги).
class Films{                     
public:                               
  virtual void info () = 0;                                   
};

class Books{                     
public:                               
  virtual void info () = 0;                                   
};

//2) Объекты различных типов могут иметь одинаковые жанры (Детектив и Комедия), 
//   поэтому создадим классы объектов различных жанров.
//                            Фильмы:
class NoirFilms: public Films{                                  
public:                        
  void info() override {
    cout << "Made Detective Movie\n" << endl;   
  }
};

class ComedyFilms: public Films{                                  
public:                        
  void info() override {
    cout << "Made Funny Movie\n" << endl;   
  }
};

//                            Книги:
class NoirBooks: public Books{                                  
public:                        
  void info() override {
    cout << "Made Detective Book\n" << endl;   
  }
};

class ComedyBooks: public Books{                                  
public:                        
  void info() override {
    cout << "Made Funny Book\n" << endl;   
  }
};

//3) Теперь нужно создать базовый класс фабрики, интерфейс которой будет объединять фабрики разных жанров. 
class Factory{
public:
  virtual Films* createFilm() = 0; 
  virtual Books* createBook() = 0; 
};

//   Теперь займемся самими фабриками.
//            Фабрика Детективов:
class NoirFactory: public Factory{
public:
  Films* createFilm() override {
    return new NoirFilms;
  }
  Books* createBook() override {
    return new NoirBooks;
  }
};

//            Фабрика Комедии:
class ComedyFactory: public Factory{
public:
  Films* createFilm() override {
    return new ComedyFilms;
  }
  Books* createBook() override {
    return new ComedyBooks;
  }
};

//4) Последним шагом мы создадим класс, 
//   который будет предоставлять пользователю  общий интерфейс, 
//   с возможностью создавать объекты нужного ему жанра (например только детективные книги и фильмы). 
class Application{
 private:
  Films* film = nullptr;
  Books* book = nullptr;
  Factory* factory = nullptr;
 public:
  Application (Factory &other_factory) {  
    factory = &other_factory;             //Определяемся с фабрикой.
  }
  
  void makeFilm() {
     film = factory->createFilm();        //Метод создания фильмов.
  }
  void makeBook() {
    book = factory->createBook();         //Метод создания книг.
  }
  
  void Application_info() {               //Метод, показывающий информацию об объектах в сборнике.
    if (film) {
      film->info();
    }
    if (book) {
      book->info();
    }
  }
};

int main()
{
//В качестве примера возьмем жанр детектива.
  NoirFactory detectivesFactory;                //1)Создадим детективную фабрику, но для пользователя данный шаг можно упростить.
  Application detectives(detectivesFactory);    //2)Создадим некий детективный сборник, в котором объекты будут создаваться в соответсвии с выбранным жанром.
  detectives.makeFilm();                        //3)Теперь можем создать какой-нибудь детективный фильм
  detectives.makeBook();                        //  или роман.
  detectives.Application_info();                //4)Выведем информацию о фильмах и книгах в сборнике.
  
//То же самое для жанра комедии.  
  ComedyFactory funniesFactory;
  Application funnies(funniesFactory);
  funnies.makeFilm();
  funnies.makeBook();
  funnies.Application_info();
  
  return 0; 
}
