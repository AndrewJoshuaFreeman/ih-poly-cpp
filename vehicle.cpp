#include <iostream>
#include <string_view>
#include <vector>
#include <memory>

class Vehicle {

public:
    Vehicle(std::string_view make, std::string_view model, int year) 
        : m_make{make}, m_model{model}, m_year{year} {
        std::cout << "Vehicle created: " << m_year << " " << m_make << " " << m_model << '\n';
    }
    
    virtual ~Vehicle() {
        std::cout << "Vehicle destroyed: " << m_year << " " << m_make << " " << m_model << '\n';
    }
    
    virtual void Drive() const = 0;
    
    void DisplayInfo() const {
        std::cout << m_year << " " << m_make << " " << m_model << "\n";
    }
private:
    std::string m_make;
    std::string m_model;
    int m_year;
};

class Car : public Vehicle {
public:
    Car(std::string_view make, std::string_view model, int year) 
        : Vehicle{make, model, year} {
        std::cout << "Car created\n";
    }
    
    ~Car() override {
        std::cout << "Car destroyed\n";
    }
    
    void Drive() const override {
        std::cout << "Driving a car\n";
    }
};

class Truck : public Vehicle {
public:
    Truck(std::string_view make, std::string_view model, int year) 
        : Vehicle{make, model, year} {
        std::cout << "Truck created\n";
    }
    
    ~Truck() override {
        std::cout << "Truck destroyed\n";
    }
    
    void Drive() const override {
        std::cout << "Driving a truck\n";
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(std::string_view make, std::string_view model, int year) 
        : Vehicle{make, model, year} {
        std::cout << "Motorcycle created\n";
    }
    
    ~Motorcycle() override {
        std::cout << "Motorcycle destroyed\n";
    }
    
    void Drive() const override {
        std::cout << "Riding a motorcycle\n";
    }
};

template<typename T>
void addVehicle(std::vector<std::unique_ptr<Vehicle>>& vehicles, 
                const std::string_view make, const std::string_view model, int year) {
    vehicles.push_back(std::make_unique<T>(make, model, year));
}

int main() {
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    std::string type, userMake, userModel;
    int userYear;

    std::cout << "Enter <type> <year> <make> <model>, or <quit> to break\n";
    
    while(std::cin >> type >> userYear >> userMake >> userModel) {
        if (type == "car") {
            addVehicle<Car>(vehicles, userMake, userModel, userYear);
        } else if (type == "truck") {
            addVehicle<Truck>(vehicles, userMake, userModel, userYear);
        } else if (type == "motorcycle") {
            addVehicle<Motorcycle>(vehicles, userMake, userModel, userYear);
        } else if( type == "quit" ) break;
        else{
            std::cout << "Unknown vehicle: " << type << '\n';
        }
    }
    
    for (const auto& vehicle : vehicles) {
        vehicle->DisplayInfo();
        vehicle->Drive();
    }
    
    return 0;
}
