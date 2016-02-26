#include <iostream>
#include <string>
#include <map>

using namespace std;

///Factory and Register
class Base;
class BaseFactory
{
public:
	static void add(string name, Base* instance)
	{
		mapping[name] = instance;
	}
	static Base* get(string name)
	{
		return mapping[name];
	}

	static map<string, Base*> mapping;
};
map<string, Base*> BaseFactory::mapping = map<string, Base*>();
template<class T>
class Register
{
public:
	Register(std::string name)
	{
		BaseFactory::add(name, new T);
	}
};
///Factory and Register

///Heirarchy
class Base
{
public:
	Base()
	{
		name = "base class";
	}
	string getName()
	{
		return name;
	}
protected:
	string name;
};
class Derived1 : public Base
{
public:
	Derived1()
	{
		name = "derived 1 class";
	}
	static Register<Derived1> reg;
};
Register<Derived1> Derived1::reg("Derived1");
class Derived2 : public Base
{
public:
	Derived2()
	{
		name = "derived 2 class";
	}
	static Register<Derived2> reg;
};
Register<Derived2> Derived2::reg("Derived2");
///Heirarchy

int main()
{
	string type1 = "Derived1";
	string type2 = "Derived2";

	cout << BaseFactory::get(type1)->getName() << endl;
	cout << BaseFactory::get(type2)->getName();

	return 0;
}
