//
// Created by Ivan Babayev on 25.07.20.
//

//
// g++ -std=c++11 strategy.cpp -o strategy
//
#include <iostream>
#include <memory>

//Drive Interface
class DriveMod {
public:
    virtual void operator()() = 0;
    virtual ~DriveMod() = default;
    //virtual double scan() = 0;
};
//Scan Interface
class SensorMod {
public:
    virtual void operator()() = 0;
    virtual ~SensorMod() = default;
    //virtual double drive() = 0;
};

//Kontext
class Robot {
    std::unique_ptr<SensorMod> sensorMod_;
    std::unique_ptr<DriveMod> driveMod_;

private:
    double speed = 1.1; //km/h
    long scanRange = 10000; //cm
    int scanInterval = 10; //sec


public:
    Robot() : driveMod_(nullptr),sensorMod_(nullptr) {}
    void setDriveMod(std::unique_ptr<DriveMod> driveMod) {
        driveMod_ = std::move(driveMod);
    }
    void setSensorMod(std::unique_ptr<SensorMod> sensorMod) {
        sensorMod_ = std::move(sensorMod);
    }
    void getDriveMod() { if (driveMod_) (*driveMod_)(); }
    void getSensorMod() { if (sensorMod_) (*sensorMod_)(); }
    void drive(){};
    void scan(){};
};

//Drivemod(Strategie)
class HighSpeed : public DriveMod {
public:
    void operator()() override {
        std::cout << "Reisegeschwindigkeit\n";
        drive();
    }

private:
   double drive()
    {
        return 15.0;
    }

};

class AverageSpeed : public DriveMod {
public:
    void operator()() override {
        std::cout << "Bewegungsgeschwindigkeit\n";

    }
private:
    double drive()
    {
        return 7.5;
    }
};

class Slowspeed : public DriveMod {
public:
    void operator()() override {
        std::cout << "Schrittgeschwindigkeit\n";
        drive();
    }
private:
    double drive()
    {
        return 3.0;
    }
};
class NoMotion : public DriveMod {
public:
    void operator()() override {
        std::cout << "Unbeweglich\n";
    }

private:
    double drive()
    {
        return 0.0;
    }
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
    Scanner.getSensorMod();

    Supplier.setDriveMod( std::unique_ptr<DriveMod>(new HighSpeed) );
    Supplier.setSensorMod( std::unique_ptr<SensorMod>(new Average) );
    Supplier.getDriveMod();
    Supplier.getSensorMod();

    Explorer.setDriveMod( std::unique_ptr<DriveMod>(new AverageSpeed) );
    Explorer.setSensorMod( std::unique_ptr<SensorMod>(new Sensitive) );
    Explorer.getDriveMod();
    Explorer.getSensorMod();

}