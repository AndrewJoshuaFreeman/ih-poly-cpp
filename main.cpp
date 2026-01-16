#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Animal{

public:
    Animal( std::string name ) : m_name(name) { 
        std::cout << "Created Animal\n";
    };
    virtual ~Animal(){/*must be virtual(if allocating on heap) so both Animal and Class animal get destroyed, otherwise, with Animal* a = new <class animal>, the <class animal> part leaks!*/
        std::cout << "Destroyed Animal\n";
    }

    virtual void Speak() const = 0;/*use virtual so compiler chooses based off object, also setting= 0 makes it un-instantiable*/

    void Eat() const {
       getName();
       std::cout << " is eating!\n";
    }

    std::string getName()const{
        return m_name;
    }
private:
    std::string m_name{};

};

class Cat : public Animal {
    
public:
    Cat( std::string name ) : Animal{name} { 
        std::cout << "Created Cat\n";
    };
    ~Cat() override{
        std::cout << "Destroyed Cat\n";
    }

    void Speak() const override{ /*use override to show reader that this is a virtual method and so the compiler knows its an override*/
        std::cout << "Meow!\n";
    }

    void Eat() const{
        getName();
        std::cout << " is eating!\n";
    }
};

class Dog : public Animal{

public:
    Dog( std::string name ) : Animal{name} {
        std::cout << "Created Dog!\n";
    };
    ~Dog() override{
        std::cout << "Destroyed Dog\n";
    }
    void Speak() const override{
        std::cout << "Woof!\n";
    }

};

class Bird : public Animal{

public:
    Bird( std::string name ) : Animal{name} {
        std::cout << "Created Bird\n";
    };
    ~Bird() override{
        std::cout << "Destroyed Bird\n";
    }

    void Speak() const override{
        std::cout << "Chirp!\n";
    }

};

//if these were Cat* c, or Cat& c, we would have to write at least 6 functions
//so it is better to have the same functions for the parent class
void IntakeAnimal( const std::unique_ptr<Animal>& a /*const Animal* a*/ ){
    std::cout << "Intake: " << a->getName() << '\n';
}

void Checkup( Animal& a ){
    std::cout << a.getName() << " goes in for a checkup.\n";
    //without virtual, a.Speak() outputs "Speaking" for each!
    a.Speak();
}

int main(){

/*
Cat cat{"kitty"};

Dog dog{"puppy"};

Bird bird{"birdy"};

//these are stack allocated, so we dont need to call
//virtual destructors on them, since when they go
//out of bound the destructors are automatically called
std::vector<Animal*> animals{&cat,&dog,&bird};
*/
//FIXME: good, but can also push
/*
std::vector<Animal*> animals{ new Cat{"kitty"}, new Dog{"puppy"}, new Bird{"birdy"} };
*/

/*good, but can also use smart pointers!
std::vector<Animal*> animals;
*/
std::vector<std::unique_ptr<Animal>> animals;
animals.push_back(std::make_unique<Cat>("kitty"));
animals.push_back(std::make_unique<Dog>("puppy"));
animals.push_back(std::make_unique<Bird>("birdy"));

for( const auto& a : animals ){
    IntakeAnimal(a);
    Checkup(*a);
}

/*would only destroy Animal if ~Animal was not virtual!
  also we dont need it for unique pointer!
for( const auto& a : animals ){
    delete a;
}


//FIXME: if cat has tail and whiskers, but animal does not
         then this cat looses its tail and whiskers:(
Animal a{cat}; //this is called slicing
*/

return 0;
}
