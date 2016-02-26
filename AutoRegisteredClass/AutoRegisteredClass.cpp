#include <iostream>
#include <string>
#include <map>


///Reflect and Register
#define MyType(BASE, TYPE) \
	static Registerer<BASE, TYPE> reg

#define Register(BASE, TYPE) \
	Registerer<BASE, TYPE> TYPE::reg(#TYPE)

template<class B>
class Deduce
{
public:
	static B* from(const std::string& name, B* instance = NULL)
	{
		static std::map<std::string, B*> mapping;
		if(instance != NULL)
		{
			mapping[name] = instance;
			return NULL;
		}
		else//should check if name is in map first
			return mapping[name];
	}
};

template<class B, class D>
class Registerer
{
public:
	Registerer(const std::string& name)
	{
		Deduce<Base>::from(name, new D);//actually add
	}
};
///Deduce and Register


///Class examples implementing Registration
class Base
{
public:
	Base()
	{
		name = "Base Class";
	}
	const std::string& getName()
	{
		return name;
	}
protected:
	std::string name;
};
class Derived1 : public Base
{
public:
	Derived1()
	{
		name = "I am type 1.\n";
	}
	MyType(Base, Derived1);
};
Register(Base, Derived1);

class Derived2 : public Base
{
public:
	Derived2()
	{
		name = "I am type 2.\n";
	}
	MyType(Base, Derived2);
};
Register(Base, Derived2);
///Class examples implementing Registration


int main()
{
	std::string typeString1 = "Derived1";
	std::string typeString2 = "Derived2";

	std::cout << Deduce<Base>::from(typeString1)->getName();
	std::cout << Deduce<Base>::from(typeString2)->getName();

	return 0;
}
