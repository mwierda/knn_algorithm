import random

def makeTrainingData():
    with open("trainingData.txt", 'w') as output:
        for x in range(100000):
            # negative one
            xVal = round(random.uniform(-10,-6), 2)
            yVal = round(random.uniform(6,10), 2)
            output.write(str(xVal) + " " + str(yVal) + " " + "-1"+"\n")
        for x in range(100000):
            # zero
            xVal = round(random.uniform(-2,0), 2)
            yVal = round(random.uniform(0,2), 2)
            output.write(str(xVal) + " " + str(yVal) + " " + "0"+"\n")
        for x in range(100000):
            # one
            xVal = round(random.uniform(6,10), 2)
            yVal = round(random.uniform(-10,-6), 2)
            output.write(str(xVal) + " " + str(yVal) + " " + "1"+"\n")

def makeTestData():
    with open("testData.txt", 'w') as output:
        for x in range(4):
            # negative one
            xVal = round(random.uniform(-10,-6), 2)
            yVal = round(random.uniform(6,10), 2)
            output.write(str(xVal) + " " + str(yVal) + "\n")
            # zero
            xVal = round(random.uniform(-2,0), 2)
            yVal = round(random.uniform(0,2), 2)
            output.write(str(xVal) + " " + str(yVal) + "\n")
            # one
            xVal = round(random.uniform(6,10), 2)
            yVal = round(random.uniform(-10,-6), 2)
            output.write(str(xVal) + " " + str(yVal) + "\n")

def main():
    makeTrainingData()
    makeTestData()


if __name__ == '__main__':
  main()
