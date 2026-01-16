#include <iostream>
#include <string_view>
#include <memory> 


class Vehicle{

public:
    Vehicle( std::string_view brand, int year ) : m_brand{brand}, m_year{year}
    {
        std::cout << "Vehicle created!\n";
    };

    virtual ~Vehicle(){
        std::cout << "Vehicle destroyeed!\n";
    }

    void Info(){
        std::cout << m_year << " " << m_brand << '\n';
    }

//    virtual void Drive() const = 0;


private:
    std::string_view m_brand;
    int m_year;

};


class Car : public Vehicle{

public:
    Car( std::string_view name, int year ) : Vehicle{name, year}{
        std::cout << "Created car!\n"; 
    };

    ~Car(){
        std::cout << "Car destroyed!\n";
    }

};


int main(){

/*use smart pointer when you can
Vehicle* pCar{ new Car{"Nissan", 2008} };
delete pCar;
*/
    std::unique_ptr<Vehicle> pCar{std::make_unique<Car>("Nissan",2008)};

}
