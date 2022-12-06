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

string sportSelect();

void ASCIIDisplay();

Athlete welcomeMessage();

void algoOperation(HashSet &athletes,BnRTree &tree, Athlete &user, unordered_map<string, vector<string>> &sport_to_id, bool &reRun);

void GetDataTSVFile(string fileP, HashSet &athletes, BnRTree &tree,
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
      Athlete *a = new Athlete(id, playerName, sex, age, height, weight, sport, event, medalType);

      athletes.add(athlete);
      tree.insert(a);
      sport_to_id[sport].push_back(id);
    }
  }
}

int main() {
  Athlete user = welcomeMessage();
  HashSet athletes;
  BnRTree tree;
  unordered_map<string, vector<string>> sport_to_id;
/* read in TSV */
  GetDataTSVFile("athlete_events_filtered.tsv", athletes, tree, sport_to_id);
/* run hashset version of algo and time it */
bool reRun = false;
algoOperation(athletes,tree, user, sport_to_id, reRun);

while (reRun) {
    ASCIIDisplay();
    user.setSport(sportSelect());
    algoOperation(athletes,tree, user, sport_to_id, reRun);
}
    
}

Athlete welcomeMessage() {
  sleeperText("   ____  _                                             _   _      ");
  sleeperText("  / __ \\| |                                           | | (_)     ");
  sleeperText(" | |  | | |_   _ _ __ ___  _ __   __ _ _ __ ___   __ _| |_ _  ___ ");
  sleeperText(" | |  | | | | | | '_ ` _ \\| '_ \\ / _` | '_ ` _ \\ / _` | __| |/ __|");
  sleeperText(" | |__| | | |_| | | | | | | |_) | (_| | | | | | | (_| | |_| | (__ ");
  sleeperText("  \\____/|_|\\__, |_| |_| |_| .__/ \\__,_|_| |_| |_|\\__,_|\\__|_|\\___|");
  sleeperText("            __/ |         | |                                     ");
  sleeperText("           |___/          |_|                                     ");

  sleeperText();
  ASCIIDisplay();
  sleeperText("Please enter your information as prompted and we shall see if you have what it takes");
    sleeperText();
    sleeperText();
    
  string name;
  string gender;
  int age;
  int height;
  int weight;
  string sport;
    
  cout << "What is your name?" << endl;
  getline(cin, name);
  sleeperText("",100);
  cout << "What is your gender? (Enter \"M\" for Male. Enter \"F\" for Female)" << endl;
  getline(cin, gender);
  sleeperText("",100);
    
  cout << "What is your age?" << endl;
  string temp;
  getline(cin, temp);
  age = stoi(temp);
  sleeperText("",100);
    
  cout << "What is height? (Enter to the nearest centimeters)" << endl;
  getline(cin, temp);
  height = stoi(temp);
  sleeperText("",100);
    
  cout << "What is weight (Enter to the nearest kilograms)" << endl;
  getline(cin, temp);
  weight = stoi(temp);
  sleeperText("",100);

  sport = sportSelect();

  return Athlete("", name, gender, age, height, weight, sport, "", "");
}

void sleeperText(string s, int time) {
        cout << s << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

string sportSelect() {
  cout << "What sport are you interested in? (Type exactly as seen)";
  cout << endl;
    
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
  string sport;
  getline(cin, sport);
  return sport;
}

void algoOperation(HashSet &athletes,BnRTree &tree, Athlete &user, unordered_map<string, vector<string>> &sport_to_id, bool &reRun)
{
    cout << endl << "Hashmap Implementation of Algorithm: " << endl;
chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  algo(athletes,user,sport_to_id);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    sleeperText(".",300);
    sleeperText(".",300);
    sleeperText(".",300);
    sleeperText("", 300);
cout << "Time for hashmap probability calculation: "
<< chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[μs]" << endl;
sleeperText("",1000);

/* run red-black tree version of algo and time it */
cout << endl << "Red-Black Tree Implementation of Algorithm: " << endl;
    
        begin = chrono::steady_clock::now();
        algo(tree,user,sport_to_id);
        end = chrono::steady_clock::now();
    sleeperText(".",300);
    sleeperText(".",300);
    sleeperText(".",300);
    sleeperText("", 300);
   cout << "Time for Red-Black Tree probability calculation: "
<< chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[μs]" << endl;
    sleeperText("", 300);
    sleeperText(".",300);
    sleeperText(".",300);
    sleeperText(".",300);
    sleeperText("", 300);
    cout << "Would you like to try a new sport? (Enter \"Y\" for Yes. Enter \"N\" for No)" << endl;
    string answer;
    getline(cin,answer);
    answer == "Y" ? reRun = true : reRun = false;

    if (answer == "N") {
        cout << endl << "Thank you for using the..." << endl << endl;
        sleeperText("   ____  _                                             _   _      ");
  sleeperText("  / __ \\| |                                           | | (_)     ");
  sleeperText(" | |  | | |_   _ _ __ ___  _ __   __ _ _ __ ___   __ _| |_ _  ___ ");
  sleeperText(" | |  | | | | | | '_ ` _ \\| '_ \\ / _` | '_ ` _ \\ / _` | __| |/ __|");
  sleeperText(" | |__| | | |_| | | | | | | |_) | (_| | | | | | | (_| | |_| | (__ ");
  sleeperText("  \\____/|_|\\__, |_| |_| |_| .__/ \\__,_|_| |_| |_|\\__,_|\\__|_|\\___|");
  sleeperText("            __/ |         | |                                     ");
  sleeperText("           |___/          |_|                                     ");
  sleeperText();
    }
}

void ASCIIDisplay() {
    int random = rand() % 3;
    if (random == 0) {
        sleeperText("           \\ /");
        sleeperText("       |_O  X  O\\");
        sleeperText("        /`-/ \\-'\\");
        sleeperText("       | \\     / |");
        sleeperText("      /   \\    |  \\");
        sleeperText("",400);
        sleeperText(".",100);
        sleeperText(".",100);
        sleeperText(".",100);
        sleeperText("",100);
    }
        
    else if (random == 1) {
        sleeperText(" o   \\ o /  _ o         __|    \\ /     |__        o _  \\ o /   o");
        sleeperText("/|\\    |     /\\   ___\\o  \\o    |    o/    o/__   /\\     |    /|\\");
        sleeperText("/ \\   / \\   | \\  /)  |    ( \\  /o\\  / )    |  (\\  / |   / \\   / \\");
        sleeperText("",400);
        sleeperText(".",100);
        sleeperText(".",100);
        sleeperText(".",100);
        sleeperText("",100);
    }
        
    else {
        sleeperText("            ___");
        sleeperText("          /`  _\\");
        sleeperText("          |  / 0|--.");
        sleeperText("     -   / \\_|0`/ /.`'._/)");
        sleeperText(" - ~ -^_| /-_~ ^- ~_` - -~ _");
        sleeperText(" -  ~  -| |   - ~ -  ~  -");
        sleeperText("        \\ \\, ~   -   ~");
        sleeperText("         \\_|");
        sleeperText("",400);
        sleeperText(".",100);
        sleeperText(".",100);
        sleeperText(".",100);
        sleeperText("",100);
        
    }
}