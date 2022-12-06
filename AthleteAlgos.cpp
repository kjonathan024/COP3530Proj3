#include "AthleteAlgos.h"
#include <iomanip>
using namespace std;

void algo(HashSet &set, Athlete &user,
          unordered_map<string, vector<string>> &map) {
  // use the user info and find athletes ids in the user's sport using the map
  // helper. Then search the ids in the hashset. Store the min and max vals for
  // gender, age, height, weight and if user vals in this range, we'll say they
  // can win a medal if statement for gender (check before taking min and max
  // things if gender matches)
  string gender = user.getSex();
  int maxAge = 0;
  int minAge = 100;
  int maxHeight = 0;
  int minHeight = 400;
  int maxWeight = 0;
  int minWeight = 400;

  int sumAge = 0;
  int sumHeight = 0;
  int sumWeight = 0;

  for (auto iter = map[user.getSport()].begin();
       iter != map[user.getSport()].end(); iter++) {
    auto ath = set.searchID(*iter);
    if (ath->getSex() == gender) {
        // TESTING
      //cout << ath->getName() << endl;
      // get age range
      if (ath->getAge() > maxAge) {
        maxAge = ath->getAge();
      }
      if (ath->getAge() < minAge) {
        minAge = ath->getAge();
      }

      // get height range
      if (ath->getHeight() > maxHeight) {
        maxHeight = ath->getHeight();
      }
      if (ath->getHeight() < minHeight) {
        minHeight = ath->getHeight();
      }

      // get weight range
      if (ath->getWeight() > maxWeight) {
        maxHeight = ath->getHeight();
      }
      if (ath->getWeight() < minWeight) {
        minHeight = ath->getWeight();
      }

      sumAge += ath->getAge();
      sumHeight += ath->getHeight();
      sumWeight += ath->getWeight();
    }
  }
  int numAthletes = map[user.getSport()].size();
  double avgHeight = (double)sumHeight / numAthletes;
  double avgWeight = (double)sumWeight / numAthletes;
  double avgAge = (double)sumAge / numAthletes;

  // val - mean / (max - min)

  double zScoreAge = (double)(user.getAge() - avgAge) / ((maxAge - minAge) / 4.0);

  double zScoreHeight =
      (double)(user.getHeight() - avgHeight) / ((maxHeight - minHeight) / 4.0);
  double zScoreWeight =
      (double)(user.getWeight() - avgWeight) / ((maxWeight - minWeight) / 4.0);

  double probAge;

  //#Referenced https://stackoverflow.com/questions/58371163/how-to-change-the-z-value-to-the-one-from-the-table-z-table-from-normal-distrib
  zScoreAge < 0 ? probAge = 2 * (0.5 * erfc(-zScoreAge * M_SQRT1_2)) : probAge = 2 * (1 - 0.5 * erfc(-zScoreAge * M_SQRT1_2)); 
  double probHeight; 
  zScoreHeight < 0 ? probHeight = 2 * (0.5 * erfc(-zScoreHeight * M_SQRT1_2)) : probHeight = 2 * (1 - 0.5 * erfc(-zScoreHeight * M_SQRT1_2)); 
  double probWeight;
  zScoreWeight < 0 ? probWeight = 2 * (0.5 * erfc(-zScoreWeight * M_SQRT1_2)) : probWeight = 2 * (1 - 0.5 * erfc(-zScoreWeight * M_SQRT1_2)); 

  double probAvg = (probAge + probHeight + probWeight) / 3;
  
  cout << endl;
  // cout << "Probabiliy Given Age: " << probAge << endl;
  // cout << "Probabiliy Given Height: " <<probHeight << endl;
  // cout << "Probabiliy Given Weight: " <<probWeight << endl;
  // cout << endl;
  cout << "Overall Probability of Success: " << setprecision(3)<<probAvg*100 << "%" << endl;
  cout << endl;
  if (probAvg < 0.5) {
    cout << "Better start setting up that LinkedIn and doing some leetcode. This probably won't work out for you..." << endl << endl;
  }
  else if (probAvg >= 0.5) {
    cout << "Congratulations, you actually have a pretty good chance! Get to practicing!" << endl << endl;
  }
    
}

void algo(BnRTree &tree, Athlete &user, unordered_map<string, vector<string>> &map) {
  // use the user info and find athletes ids in the user's sport using the map
  // helper. Then search the ids in the hashset. Store the min and max vals for
  // gender, age, height, weight and if user vals in this range, we'll say they
  // can win a medal
  // if statement for gender (check before taking min and max things if gender
  // matches)
  // helper. Then search the ids in the hashset. Store the min and max vals for
  // gender, age, height, weight and if user vals in this range, we'll say they
  // can win a medal if statement for gender (check before taking min and max
  // things if gender matches)
  string gender = user.getSex();
  int maxAge = 0;
  int minAge = 100;
  int maxHeight = 0;
  int minHeight = 400;
  int maxWeight = 0;
  int minWeight = 400;

  int sumAge = 0;
  int sumHeight = 0;
  int sumWeight = 0;

  for (auto iter = map[user.getSport()].begin();
       iter != map[user.getSport()].end(); iter++) {
    auto ath = tree.searchID(*iter);
    if (ath->getSex() == gender) {
      // TESTING
      //cout << ath->getName() << endl;
      // get age range
      if (ath->getAge() > maxAge) {
        maxAge = ath->getAge();
      }
      if (ath->getAge() < minAge) {
        minAge = ath->getAge();
      }

      // get height range
      if (ath->getHeight() > maxHeight) {
        maxHeight = ath->getHeight();
      }
      if (ath->getHeight() < minHeight) {
        minHeight = ath->getHeight();
      }

      // get weight range
      if (ath->getWeight() > maxWeight) {
        maxHeight = ath->getHeight();
      }
      if (ath->getWeight() < minWeight) {
        minHeight = ath->getWeight();
      }

      sumAge += ath->getAge();
      sumHeight += ath->getHeight();
      sumWeight += ath->getWeight();
    }
  }
  int numAthletes = map[user.getSport()].size();
  double avgHeight = (double)sumHeight / numAthletes;
  double avgWeight = (double)sumWeight / numAthletes;
  double avgAge = (double)sumAge / numAthletes;

  // val - mean / (max - min)

  double zScoreAge = (double)(user.getAge() - avgAge) / ((maxAge - minAge) / 4.0);

  double zScoreHeight =
      (double)(user.getHeight() - avgHeight) / ((maxHeight - minHeight) / 4.0);
  double zScoreWeight =
      (double)(user.getWeight() - avgWeight) / ((maxWeight - minWeight) / 4.0);

  double probAge;

  //#Referenced https://stackoverflow.com/questions/58371163/how-to-change-the-z-value-to-the-one-from-the-table-z-table-from-normal-distrib
  zScoreAge < 0 ? probAge = 2 * (0.5 * erfc(-zScoreAge * M_SQRT1_2)) : probAge = 2 * (1 - 0.5 * erfc(-zScoreAge * M_SQRT1_2)); 
  double probHeight; 
  zScoreHeight < 0 ? probHeight = 2 * (0.5 * erfc(-zScoreHeight * M_SQRT1_2)) : probHeight = 2 * (1 - 0.5 * erfc(-zScoreHeight * M_SQRT1_2)); 
  double probWeight;
  zScoreWeight < 0 ? probWeight = 2 * (0.5 * erfc(-zScoreWeight * M_SQRT1_2)) : probWeight = 2 * (1 - 0.5 * erfc(-zScoreWeight * M_SQRT1_2)); 

  double probAvg = (probAge + probHeight + probWeight) / 3;
  
  cout << endl;
  // cout << "Probabiliy Given Age: " << probAge << endl;
  // cout << "Probabiliy Given Height: " <<probHeight << endl;
  // cout << "Probabiliy Given Weight: " <<probWeight << endl;
  // cout << endl;
  cout << "Overall Probability of Success: " << setprecision(3)<<probAvg*100 << "%" << endl;
  cout << endl;
  if (probAvg < 0.5) {
    cout << "Better start setting up that LinkedIn and doing some leetcode. This probably won't work out for you..." << endl << endl;
  }
  else if (probAvg >= 0.5) {
    cout << "Congratulations, you actually have a pretty good chance! Get to practicing!" << endl << endl;
  }

}