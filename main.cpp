#include "AthleteAlgos.h"
#include "BnRTree.h"
#include "HashSet.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

/*

Use STL helper maps in addition to the self-made algorithms to speed up
searching for specific characteristics in the hashset and red black tree. Ex:
sport map that has sport as key and id as value

*/
void sleeperText(string s = "", int time = 50);


Athlete welcomeMessage();

void GetDataTSVFile(string fileP, HashSet &athletes,
                    unordered_map<string, vector<string>> &sport_to_id) {
  ifstream file(fileP);
  if (file.is_open()) {
    // get rid of the title line from 3file
    // essentially read and then ignore.
    string line;
    getline(file, line);
    //cout << line << endl;
    while (getline(file, line)) {
      // create stream from line of data
      istringstream stream(line);

      string id;
      string playerName;
      string sex;
      int age;
      int height; // in centimeters
      int weight; // in kilograms
      string sport;
      string event;
      string medalType;

      getline(stream, id, '\t');
      getline(stream, playerName, '\t');
      //cout << id << ": " << playerName << endl;
      getline(stream, sex, '\t');
      
      string tempA;
      getline(stream, tempA, '\t');
      age = stoi(tempA);

      string tempH;
      getline(stream, tempH, '\t');
      height = stoi(tempH);

      string tempW;
      getline(stream, tempW, '\t');
      weight = stoi(tempW);

      getline(stream, sport, '\t');
      getline(stream, event, '\t');
      getline(stream, medalType, '\t');

      Athlete athlete(id, playerName, sex, age, height, weight, sport, event,
                      medalType);

      athletes.add(athlete);
      sport_to_id[sport].push_back(id);
    }
  }
}
int main() {
  Athlete user = welcomeMessage();
  HashSet athletes;
  unordered_map<string, vector<string>> sport_to_id;
/* read in TSV */
  GetDataTSVFile("athlete_events_filtered.tsv", athletes, sport_to_id);
/* run hashset version of algo and time it */
chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  algo(athletes,user,sport_to_id);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

cout << "Time for hashmap probability calculation: "
<< chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[μs]" << endl;
}

Athlete welcomeMessage() {
  /*cout << "------------- ( ^ O ^ ) Welcome to the Olympamatic ( ^ O ^ ) -------------" << endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  cout << "Could you be an olympic athlete with your current physical "
          "characteristics?"
       << endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  cout << endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(300));*/
  sleeperText("   ____  _                                             _   _      ");
  sleeperText("  / __ \\| |                                           | | (_)     ");
  sleeperText(" | |  | | |_   _ _ __ ___  _ __   __ _ _ __ ___   __ _| |_ _  ___ ");
  sleeperText(" | |  | | | | | | '_ ` _ \\| '_ \\ / _` | '_ ` _ \\ / _` | __| |/ __|");
  sleeperText(" | |__| | | |_| | | | | | | |_) | (_| | | | | | | (_| | |_| | (__ ");
  sleeperText("  \\____/|_|\\__, |_| |_| |_| .__/ \\__,_|_| |_| |_|\\__,_|\\__|_|\\___|");
  sleeperText("            __/ |         | |                                     ");
  sleeperText("           |___/          |_|                                     ");
  sleeperText("Please enter your information as prompted and we shall see if you have what it takes");
  sleeperText("");
  sleeperText("");
  sleeperText("");
    
  string name;
  string gender;
  int age;
  int height;
  int weight;
  string sport;
    
  cout << "What is your name?" << endl;
  getline(cin, name);
    
  cout << "What is your gender? (Enter \"M\" for Male. Enter \"F\" for Female)" << endl;
  getline(cin, gender);
    
  cout << "What is your age?" << endl;
  string temp;
  getline(cin, temp);
  age = stoi(temp);
    
  cout << "What is height? (Enter to the nearest centimeters)" << endl;
  getline(cin, temp);
  height = stoi(temp);
    
  cout << "What is weight (Enter to the nearest kilograms)" << endl;
  getline(cin, temp);
  weight = stoi(temp);
    
  cout << "What sport are you interested in? (Type exactly as seen)";
    
  sleeperText("Alpine Skiing           Cycling             Luge                          Speed Skating",100);
  sleeperText("Archery                 Diving              Modern Pentathlon             Swimming",100);
  sleeperText("Art Competitions        Equestrianism       Nordic Combined               Syncronized Swimming",100);
  sleeperText("Athletics               Fencing             Rhythmic Gymnastics           Table Tennis",100);
  sleeperText("Badminton               Figure Skating      Rowing                        Taekwondo",100);
  sleeperText("Baseball                Football            Rugby                         Tennis",100);
  sleeperText("Basketball              Freestyle Skiing    Rugby Sevens                  Trampolining",100);
  sleeperText("Beach Volleyball        Golf                Sailing                       Triathlon",100);
  sleeperText("Biathlon                Gymnastics          Shooting                      Tug-Of-War",100);
  sleeperText("Bobsleigh               Handball            Short Track Speed Skating     Volleyball" ,100);
  sleeperText("Boxing                  Hockey              Skeleton                      Water Polo",100);
  sleeperText("Canoeing                Ice Hockey          Ski Jumping                   Weightlifting",100);
  sleeperText("Cross Country Skiing    Judo                Snowboarding                  Wrestling",100);
  sleeperText("Curling                 Lacrosse            Softball     ",100);
  cout << endl;
  getline(cin, sport);

  return Athlete("", name, gender, age, height, weight, sport, "", "");
}

void sleeperText(string s, int time) {
        cout << s << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}