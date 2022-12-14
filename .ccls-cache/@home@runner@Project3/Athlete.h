#pragma once
#include <string>
using namespace std;

class Athlete { // shell Athlete class
    private:
        string id;
        string playerName;
        string sex;
        int age;
        int height; //in centimeters
        int weight; //in kilograms
        string sport;
        string event;
        string medalType;
        
    public:
        // constructor
        Athlete() {id = "1";}
        Athlete(string id, string playerName, string sex, int age, int height, int weight, string sport, string event, string medalType) {
            this->id = id;
            this->playerName = playerName;
            this->sex = sex;
            this->age = age;
            this->height = height;
            this->weight = weight;
            this->sport = sport;
            this->event = event;
            this->medalType = medalType;
        }

        // accessor functions
        string getID() { return id; }
        string getName() { return playerName; }
        string getSex() { return sex; }
        string getSport() { return sport; }
        string getEvent() { return event; }
        string getMedalType() { return medalType; }
        int getAge() { return age; }
        int getHeight() { return height; }
        int getWeight() { return weight; }

        // modifier functions
        void setSport(string sport) {this->sport = sport;}

        // overloading comparator
        bool operator== (Athlete& ath2) {
    return (this->id == ath2.id);
        }

        
};