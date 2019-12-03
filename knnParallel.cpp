#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <omp.h>
#include <parallel/algorithm>

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
  //#pragma omp parallel for schedule(auto)
  for (int i=0;i<size;i++){
    arr[i].distance = std::sqrt((arr[i].x - p.x) * (arr[i].x - p.x) +
                                 (arr[i].y - p.y) * (arr[i].y - p.y));
  }

}

int KNN(std::vector<Point> &trainingArray, int trainingArraySize, int k, Point newPoint){
  // omp_lock_t writelock;
  // omp_init_lock(&writelock);

  euclideanDistance(trainingArray, trainingArraySize, newPoint);

  // uses OpenMP to parallelize the built-in sorting alogrithm
  // __gnu_parallel forces the parallelized version to be used
  clock_t begin, end;
  begin = clock();
  __gnu_parallel::sort(trainingArray.begin(), trainingArray.end(), distanceComparison);
  end = clock();
  std::cout << "parallel sort time: " << ((float)(end - begin)/CLOCKS_PER_SEC) << " seconds" << std::endl;

  int freqNegOne = 0;
  int freqZero = 0;
  int freqOne = 0;

  // #pragma omp parallel for schedule(auto)
  for (int i=0; i < k; i++){
    if (trainingArray[i].val == -1) {
      // omp_set_lock(&writelock);
      freqNegOne++;
      // omp_unset_lock(&writelock);
    }
    else if (trainingArray[i].val == 0) {
      // omp_set_lock(&writelock);
      freqZero++;
      // omp_unset_lock(&writelock);
    }
    else if (trainingArray[i].val == 1) {
      // omp_set_lock(&writelock);
      freqOne++;
      // omp_unset_lock(&writelock);
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

  // could parallelize if a new trainingVector was made for each euclidean distance
  // but that would also slow down the program, and take up more memory

  clock_t begin, end;
  for (int i=0;i<dataVector.size();i++){
    begin = clock();
    int newLabel = KNN(trainingVector, trainingVector.size(), 1000, dataVector[i]);
    end = clock();
    std::cout << "Parallel time for k=1000: " << ((float)(end - begin)/CLOCKS_PER_SEC) << " seconds" << std::endl;

    dataVector[i].val = newLabel;
  }

  // use to check for correctness
  /*
  for (int i=0; i < dataVector.size();i++){
    std::cout << dataVector[i].val << std::endl;
  }
  */

  return 0;
}
