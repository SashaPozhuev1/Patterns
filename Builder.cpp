//Строитель — это порождающий паттерн проектирования, который позволяет создавать сложные объекты пошагово. 
//Строитель даёт возможность использовать один и тот же код строительства для получения разных представлений объектов.

#include <iostream>
#include <string>
using namespace std;

//Сначала нам требуется определить "скелет" нашего продукта, 
//который может иметь различные представления.
//////////////////////////
//1) 	Продукт - игрушка.
class Toy
{
private:
	string shape;
	string equipment;
	string size;

public:
	Toy() { }
	~Toy() { }

	void SetShape(const string & s) {
		shape = s;
	}
	void SetEquipment(const string & e) {
		equipment = e;
	}
	void SetSize(const string & s) {
		size = s;
	}

	void ShowToy() {
		cout << "Hello!!" << endl
			<< "You new Toy is " << shape
			<< ", with " << equipment << "and "
			<< size << "Size "
			<< " !!! " << endl;
	}
};

//Теперь создадим базовый класс строителя, который будет содержать виртуальные методы (шаги), 
//по которым будет создаваться итоговый продукт.
/////////////////////////////////////////
//2) 	Абстрактный строитель (базовый)
class ToyBuilder
{
protected:
	Toy * toy;
public:
	ToyBuilder() {}
	virtual ~ToyBuilder() {}
	Toy * GetToy() {
		return toy;
	}

	void createNewToyProduct() {
		toy = new Toy;
	}

	virtual void buildShape() = 0;
	virtual void buildEquipment() = 0;
	virtual void buildSize() = 0;

};

//Создадим несколько конкретных строителей, реализующих различные представления игрушек
//и использующие базовый класс. 
/////////////////////////////
//3) 	Конкретные строители.
//		Фигурка героя.
class SuperHeroToyBuilder : public ToyBuilder
{
public:
	SuperHeroToyBuilder() : ToyBuilder() {}
	~SuperHeroToyBuilder() {}

	void buildShape() override {
		toy->SetShape("Superhero with muscule body with wings ");
	}
	void buildEquipment() override {
		toy->SetEquipment("special costume with cloak and mask ");
	}
	void buildSize() override {
		toy->SetSize("middle ");
	}
};

// 		Кукла.
class DollToyBuilder : public ToyBuilder
{
public:
	DollToyBuilder() : ToyBuilder() {}
	~DollToyBuilder() {}

	void buildShape() override {
		toy->SetShape("Pretty Doll with girl body ");
	}
	void buildEquipment() override {
		toy->SetEquipment("shiny dress and purse ");
	}
	void buildSize() override {
		toy->SetSize("small ");
	}
};

//В конце, для удобства, мы можем создать класс Директора, который будет "руководить" 
//процессом сборки итогового продукта (игрушки).
/////////////////
//4) 	Директор.
class Director
{
private:
	ToyBuilder* toyBuilder;
public:
	Director() : toyBuilder(nullptr) {}
	~Director() { }

	void SetToyBuilder(ToyBuilder * b) {
		toyBuilder = b;
	}
	Toy * GetToy() {
		return toyBuilder->GetToy();
	}
	void ConstructToy()
	{
		toyBuilder->createNewToyProduct();
		toyBuilder->buildShape();
		toyBuilder->buildEquipment();
		toyBuilder->buildSize();
	}
};

int main()
{
	// Пример создания игрушек.
	Director director;				//Создаём директора.

	SuperHeroToyBuilder superHeroToyBuilder; 	//Создаём строителя игрушки героя.
	director.SetToyBuilder(&superHeroToyBuilder);	//Передаём строителя директору.
	director.ConstructToy();			//Директор заставляет строителя конструировать игрушку пошагово, как описано в методе. 
	Toy * toy = director.GetToy();			//Создаём объект итогового продкукта и передаём ему игрушку от нашего директора.
	toy->ShowToy();					//Показываем информацию об игрушке.

	// Тоже самое для создания куклы.
	DollToyBuilder dollToyBuilder;
	director.SetToyBuilder(&dollToyBuilder);
	director.ConstructToy();
	toy = director.GetToy();
	toy->ShowToy();
	cin.get();
	return 0;
}
