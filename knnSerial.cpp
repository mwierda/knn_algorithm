#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <vector>

struct Point {
  int val; // value of point
  double x, y; // coordinate
  double distance; // distance from test point
};

bool distanceComparison(Point a, Point b){
  return (a.distance < b.distance);
}

// parallelizable
void euclideanDistance(std::vector<Point> &arr, int size, Point p){
  for (int i=0;i<size;i++){
    arr[i].distance = std::sqrt((arr[i].x - p.x) * (arr[i].x - p.x) +
                                 (arr[i].y - p.y) * (arr[i].y - p.y));
  }
}

int KNN(std::vector<Point> &trainingArray, int trainingArraySize, int k, Point newPoint){

  euclideanDistance(trainingArray, trainingArraySize, newPoint);

  sort(trainingArray.begin(), trainingArray.end(), distanceComparison);

  int freqNegOne = 0;
  int freqZero = 0;
  int freqOne = 0;
  // maybe parallelizable? based on k
  for (int i=0; i < k; i++){
    if (trainingArray[i].val == -1) {
      freqNegOne++;
    }
    else if (trainingArray[i].val == 0) {
      freqZero++;
    }
    else if (trainingArray[i].val == 1) {
      freqOne++;
    }
  }
  if (freqNegOne > freqZero && freqNegOne > freqOne){
    return -1;
  }
  else if (freqZero > freqNegOne && freqZero > freqOne){
    return 0;
  }
  else if (freqOne > freqNegOne && freqOne > freqZero){
    return 1;
  }
  else {
    std::vector<int> freqResults {freqNegOne, freqZero, freqOne};
    sort(freqResults.begin(), freqResults.end());
    return freqResults[0];
  }
}

int main() {

  double xVal, yVal;

  std::vector<Point> dataVector;
  std::ifstream testInput("testData.txt");

  while (testInput >> xVal >> yVal){
    Point testPoint;
    testPoint.x = xVal;
    testPoint.y = yVal;
    dataVector.push_back(testPoint);
  }

  std::vector<Point> trainingVector;
  std::ifstream trainInput("trainingData.txt");

  int label;
  while (trainInput >> xVal >> yVal >> label){
    Point p;
    p.x = xVal;
    p.y = yVal;
    p.val = label;
    trainingVector.push_back(p);
  }

  clock_t begin = clock();

  for (int i=0;i<dataVector.size();i++){
    int newLabel = KNN(trainingVector, trainingVector.size(), 10, dataVector[i]);
    dataVector[i].val = newLabel;
  }

  clock_t end = clock();

  std::cout << "Serial time for 12 points: " << ((float)(end - begin)/CLOCKS_PER_SEC) << " seconds" << std::endl;

  for (int i=0; i < dataVector.size();i++){
    std::cout << dataVector[i].val << std::endl;
  }

  return 0;
}
