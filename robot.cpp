//

//
// g++ -std=c++11 strategy.cpp -o strategy
//
#include <iostream>
#include <memory>

//Drive Interface
class DriveMod {
public:
    virtual void drive() = 0;
    virtual ~DriveMod() = default;
    //virtual double scan() = 0;
};

//Scan Interface
class SensorMod {
public:
    virtual void sense() = 0;
    virtual ~SensorMod() = default;
    //virtual double drive() = 0;
};

//Kontext
class Robot {
    std::unique_ptr<SensorMod> sensorMod_;
    std::unique_ptr<DriveMod> driveMod_;



public:
    Robot() :
            driveMod_(nullptr),
            sensorMod_(nullptr) {}

    void setDriveMod(std::unique_ptr<DriveMod> driveMod) {driveMod_ = std::move(driveMod);}
    void setSensorMod(std::unique_ptr<SensorMod> sensorMod) {sensorMod_ = std::move(sensorMod);}
    void drive() {driveMod_->drive();}
    void sense() {sensorMod_->sense();}
};

//Drivemod(Strategie)
class HighSpeed : public DriveMod {
public:
    void drive() override {
        std::cout << "Reisegeschwindigkeit\n";
    }
};

class AverageSpeed : public DriveMod {
public:
    void drive() override {
        std::cout << "Bewegungsgeschwindigkeit\n";
    }
};

class Slowspeed : public DriveMod {
public:
    void drive() override {
        std::cout << "Schrittgeschwindigkeit\n";
    }
};
class NoMotion : public DriveMod {
public:
    void drive() override {
        std::cout << "Unbeweglich\n";
    }
};

//SensorMods(Strategie)
class Sensitive : public SensorMod {
public:
    void sense() override { std::cout << "Empfindlich/Kleiner Radius\n"; }
};

class Average : public SensorMod {
public:
    void sense() override { std::cout << "Durchschnittliche Reichweite\n"; }
};

class Low : public SensorMod {
public:
    void sense() override { std::cout << "Unempfindlich/Großer Radius\n"; }
};



int main() {
    Robot Scanner;

    Scanner.setDriveMod(std::unique_ptr<DriveMod>(new NoMotion));
    Scanner.setSensorMod(std::unique_ptr<SensorMod>(new Low));

    Robot Supplier;

    Supplier.setDriveMod(std::unique_ptr<DriveMod>(new HighSpeed));
    Supplier.setSensorMod(std::unique_ptr<SensorMod>(new Average));

    Robot Explorer;

    Explorer.setDriveMod(std::unique_ptr<DriveMod>(new AverageSpeed));
    Explorer.setSensorMod(std::unique_ptr<SensorMod>(new Sensitive));


    Scanner.drive();
    Scanner.sense();


    Supplier.drive();
    Supplier.sense();

    Explorer.drive();
    Explorer.sense();

}