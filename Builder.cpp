#include <iostream>
#include <string>
using namespace std;
// Product
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

// Abstract Builder
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
		if (!toy) {
			toy = new Toy;
		}
	}

	virtual void buildShape() = 0;
	virtual void buildEquipment() = 0;
	virtual void buildSize() = 0;

};

// ConcreteBuilder
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

// ConcreteBuilder
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

// Director
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

// Клиент заказывает две пиццы.
int main()
{
	Director director;

	SuperHeroToyBuilder superHeroToyBuilder;
	director.SetToyBuilder(&superHeroToyBuilder);
	director.ConstructToy();
	Toy * toy = director.GetToy();
	toy->ShowToy();

	DollToyBuilder dollToyBuilder;
	director.SetToyBuilder(&dollToyBuilder);
	director.ConstructToy();
	toy = director.GetToy();
	toy->ShowToy();
	cin.get();
	return 0;
}
