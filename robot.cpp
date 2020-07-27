#include <iostream>
#include <memory>

//Drive Interface
class DriveMod {
public:
    //virtual void operator()() = 0;
    virtual ~DriveMod() = default;
    virtual void drive() = 0;

};
//Scan Interface
class SensorMod {
public:
    virtual void operator()() = 0;
    virtual ~SensorMod() = default;
    //virtual double scan() = 0;
};

//Kontext
class Robot {
    std::unique_ptr<SensorMod> sensorMod_;
    std::unique_ptr<DriveMod> driveMod_;


public:
    Robot() : driveMod_(nullptr),sensorMod_(nullptr) {}
    void setDriveMod(std::unique_ptr<DriveMod> driveMod) {driveMod_ = std::move(driveMod);}
    void setSensorMod(std::unique_ptr<SensorMod> sensorMod) {sensorMod_ = std::move(sensorMod);}
    //void getDriveMod() { if (driveMod_) (*driveMod_)(); }
    //void getSensorMod() { if (sensorMod_) (*sensorMod_)(); }
    void getDriveMod() { this->drive(); }
    //void getSensorMod() { if (sensorMod_) (*sensorMod_)(); }
    void drive();
    void scan();

};

//Drivemod(Strategie)
class HighSpeed : public DriveMod {
public:
    //void operator()() override {}
    void drive(){std::cout << "Reisegeschwindigkeit\n";}
};

class AverageSpeed : public DriveMod {
public:
    //void operator()() override {}
    void drive(){std::cout << "Bewegungsgeschwindigkeit\n";}
};

class Slowspeed : public DriveMod {
public:
    //void operator()() override {}
    void drive(){std::cout << "Schrittgeschwindigkeit\n";}

};
class NoMotion : public DriveMod {
public:
    //void operator()() override {drive();}
    void drive() override {std::cout << "Unbeweglich\n";}
};

//SensorMods(Strategie)
class Sensitive : public SensorMod {
public:
    void operator()() override { std::cout << "Empfindlich/Kleiner Radius\n"; }
};

class Average : public SensorMod {
public:
    void operator()() override { std::cout << "Durchschnittliche Reichweite\n"; }
};

class Low : public SensorMod {
public:
    void operator()() override { std::cout << "Unempfindlich/Großer Radius\n"; }
};



int main() {
    Robot Scanner;
    Robot Supplier;
    Robot Explorer;

    Scanner.setDriveMod( std::unique_ptr<DriveMod>(new NoMotion) );
    Scanner.setSensorMod( std::unique_ptr<SensorMod>(new Low) );
    Scanner.getDriveMod();
   // Scanner.getSensorMod();
   //Scanner.drive();

    Supplier.setDriveMod( std::unique_ptr<DriveMod>(new HighSpeed) );
    Supplier.setSensorMod( std::unique_ptr<SensorMod>(new Average) );
    Supplier.getDriveMod();
    //Supplier.getSensorMod();

    Explorer.setDriveMod( std::unique_ptr<DriveMod>(new AverageSpeed) );
    Explorer.setSensorMod( std::unique_ptr<SensorMod>(new Sensitive) );
    Explorer.getDriveMod();
    //Explorer.getSensorMod();

}