import time                 #provides timing for benchmarks
from numpy  import *        #provides complex math and array functions
from sklearn import svm     #provides Support Vector Regression
import csv
import os

import mlr
import FromDataFileMLR
import FromFinessFileMLR

class BPSO:
    def __init__(self, numOfPop, numOfFea):
        # Acquires and formats data from Train, Validation, Test .csv files
        self.filedata = FromDataFileMLR.DataFromFile()
        # Performs data analysis on training, validation, and test data
        self.analyzer = FromFinessFileMLR.FitnessResults()
        self.NumIterations = 10000
        self.alpha = 0.5  # starting alpha value
        self.GlobalBestRow = ndarray(numOfFea)  # best-fitting population yet found
        self.GlobalBestFitness = 10000  # fitness of GlobalBestRow, initialized very high
        self.VelocityM = ndarray((numOfPop, numOfFea))  # Velocity matrix
        self.LocalBestM = ndarray((numOfPop, numOfFea))  # local best matrix
        self.LocalBestM_Fit = ndarray(numOfPop)  # local best matrix fitnesses
    #------------------------------------------------------------------------------
    def getRand(self):
        return int.from_bytes(os.urandom(8), byteorder="big") / ((1 << 64) - 1)
    #------------------------------------------------------------------------------
    def CreateInitialVelocity(self, numOfPop, numOfFea):
        # Each element in initial VelocityMatrix is randomly determined
        for i in range(numOfPop):
            for j in range(numOfFea):
                self.VelocityM[i][j] = random.random()
    #------------------------------------------------------------------------------
    def getAValidrow(self, numOfFea, eps=0.015):
        # Returns a row with at least three features
        sum = 0
        while (sum < 5 or sum > 15):
           V = zeros(numOfFea)
           for j in range(numOfFea):
              r = random.uniform(0,1)
              if (r < eps):
                 V[j] = 1
              else:
                 V[j] = 0
           sum = V.sum()
        return V
    #------------------------------------------------------------------------------
    def Create_A_Population(self, numOfPop, numOfFea):
        # Initializes the first population using getAValidRow
        population = random.random((numOfPop,numOfFea))
        for i in range(numOfPop):
            V = self.getAValidrow(numOfFea)
            for j in range(numOfFea):
                population[i][j] = V[j]
        return population
    #------------------------------------------------------------------------------
    # The following creates an output file. Every time a model is created the
    # descriptors of the model, the ame of the model (ex: "MLR" for multiple
    # linear regression of "SVM" support vector machine) the R^2 of training, Q^2
    # of training,R^2 of validation, and R^2 of test is placed in the output file
    def createAnOutputFile(self):
        file_name = None
        algorithm = None

        timestamp = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime())
        if ( (file_name == None) and (algorithm != None)):
            file_name = "{}_{}_gen{}_{}.csv".format(algorithm.__class__.__name__,
                            algorithm.model.__class__.__name__, algorithm.gen_max,timestamp)
        elif file_name==None:
            file_name = "{}.csv".format(timestamp)
        fileOut = open(file_name, 'w')
        fileW = csv.writer(fileOut)

        fileW.writerow(['Descriptor ID', 'Fitness', 'Model','R2', 'Q2',
                'R2Pred_Validation', 'R2Pred_Test'])

        return fileW
    #-------------------------------------------------------------------------------------------
    def createANewPopulation(self, numOfPop, numOfFea, OldPopulation):
        # The following sets the value of NewPopulation to te Old Population to start with:
        NewPopulation = OldPopulation.copy()
        # Then it updates the value of alpha and the value pf "p"
        # Next it will go through the new population and changes the values based on
        # what is given in the algorith. The change will take place using the currrent
        # value of velocity matrix, local bet matrix and global best row.
        
        # Update alpha value - decreases from 0.5 to 0.33 over iterations
        self.alpha -= (0.17/self.NumIterations)  # 0.17 is (0.5 - 0.33)
        
        p = 0.5 * (1 + self.alpha)  # Calculate p based on current alpha
        changecount = 0  # Track number of changes for monitoring convergence
        
        # Update population based on velocity rules
        for i in range(numOfPop):
            for j in range(numOfFea):
                if self.VelocityM[i][j] <= self.alpha:  # Keep old value
                    
                    NewPopulation[i][j] = OldPopulation[i][j]
                elif self.VelocityM[i][j] <= p:     # Use local best value
                    NewPopulation[i][j] = self.LocalBestM[i][j]
                elif self.VelocityM[i][j] <= 1:     # Use global best value
                    NewPopulation[i][j] = self.GlobalBestRow[j]
                else:                               # Keep old value as fallback
                    NewPopulation[i][j] = OldPopulation[i][j]
                    
                if NewPopulation[i][j] != OldPopulation[i][j]:
                    changecount += 1

            # Check if this row is valid (5-15 features)
            # New row is based on Velocity Matrix, may be invalid
            feature_count = sum(NewPopulation[i])
            if feature_count < 5 or feature_count > 15:
                # If invalid, replace with a valid row
                NewPopulation[i] = self.getAValidrow(numOfFea)
        
        #return NewPopulation.copy()
        return NewPopulation.copy(), changecount
    #-------------------------------------------------------------------------------------------
    def FindGlobalBestRow(self):
        # this routine finds the GlobalBetRow and update its fitness if necessary
        IndexOfBest = argmin(self.LocalBestM_Fit)  # Find index of best performing model in local best matrix
        
        # If this is better than current global best, update it
        if self.GlobalBestFitness > self.LocalBestM_Fit[IndexOfBest]:
            self.GlobalBestRow = self.LocalBestM[IndexOfBest].copy()
            self.GlobalBestFitness = self.LocalBestM_Fit[IndexOfBest]
    #-------------------------------------------------------------------------------------------
    def UpdateLocalMatrix(self, NewPopulation, NewPopFitness):
        # this routine finds the LocalBestMatrix and update the fitnesses if necessary
        numOfPop = self.LocalBestM.shape[0]
    
        for i in range(numOfPop):
            # If current model performs better than stored local best
            if NewPopFitness[i] < self.LocalBestM_Fit[i]:
                # Update local best fitness and model
                self.LocalBestM_Fit[i] = NewPopFitness[i]
                self.LocalBestM[i] = NewPopulation[i].copy()

    #-------------------------------------------------------------------------------------------
    def UpdateVelocityMatrix(self, NewPop, c1=2, c2=2, inertiaWeight=0.9):
        # This routine updates the value of velocity matrix using the
        # constants c1, and c2, and local best matrx and global best row. 
        # and returns the value of average velocity. The values of each 
        # Velocity[i][j] must be positive. Therefore, you need to take the 
        # absolute value of the Velocity[i][j]. This function adds all velocity
        # together and returns the average velocity
        
        numOfPop = self.VelocityM.shape[0]
        numOfFea = self.VelocityM.shape[1]
        vcount = 0
        
        for i in range(numOfPop):
            for j in range(numOfFea):
                # Cognitive component (personal best influence)
                cognitive = c1 * random.random() * (self.LocalBestM[i][j] - NewPop[i][j])
                
                # Social component (global best influence)
                social = c2 * random.random() * (self.GlobalBestRow[j] - NewPop[i][j])
                
                # Update velocity using standard PSO equation
                self.VelocityM[i][j] = abs(inertiaWeight * self.VelocityM[i][j] + cognitive + social)
                
                # Add to total for average calculation
                vcount += self.VelocityM[i][j]

        return vcount / (numOfPop * numOfFea) #returning the average velocity
    #-------------------------------------------------------------------------------------------
    def PerformOneMillionIteration(self, numOfPop, numOfFea, population, fitness, model, fileW,
                                TrainX, TrainY, ValidateX, ValidateY, TestX, TestY):
        NumOfGenerations = 1
        waittime = 0  # tracks how many passes have occurred since a certain time X

        while NumOfGenerations < self.NumIterations:
            print("Generation", NumOfGenerations)
            
            # Scatter every 250 generations
            if NumOfGenerations % 250 == 0:
                print(f"Scattering population at generation {NumOfGenerations}")
                population = self.scatter_population(population, numOfPop, numOfFea, fitness)
                # Recalculate fitness for scattered population
                fittingStatus, fitness = self.analyzer.validate_model(model, fileW, population,
                                        TrainX, TrainY, ValidateX, ValidateY, TestX, TestY)
            
            OldPopulation = population.copy()
            population, popchanges = self.createANewPopulation(numOfPop, numOfFea, OldPopulation)
            fittingStatus, fitness = self.analyzer.validate_model(model, fileW, population,
                                    TrainX, TrainY, ValidateX, ValidateY, TestX, TestY)

            self.UpdateLocalMatrix(population, fitness)
            self.FindGlobalBestRow()
            avgV = self.UpdateVelocityMatrix(population)

            NumOfGenerations = NumOfGenerations + 1
        return
    
    def scatter_population(self, population, numOfPop, numOfFea, fitness):
        """
        Randomizes the bottom 50% of the population based on fitness values.
        Returns the new scattered population.
        """
        # Create a copy of the population to modify
        scattered_population = population.copy()
        
        # Get indices sorted by fitness (worst to best)
        sorted_indices = argsort(fitness)
        
        # Get the indices of the bottom 50%
        bottom_half = sorted_indices[numOfPop//2:]
        
        # Randomize these positions
        for idx in bottom_half:
            scattered_population[idx] = self.getAValidrow(numOfFea)
        
        return scattered_population
#end of BPSO class

#--------------------------------------------------------------------------------------------
#Main program
def main():
    # Number of descriptor should be 385 and number of population should be 50 or more
    numOfPop = 50
    numOfFea = 385

    # create an object of Multiple Linear Regression model.
    # The class is located in mlr file
    model = mlr.MLR()
    dataminer = BPSO(numOfPop, numOfFea)

    # create an output file. Name the object to be FileW 
    fileW = dataminer.createAnOutputFile()

    # we continue exhancing the model; however if after 1000 iteration no
    # enhancement is done, we can quit
    unfit = 1000

    # Final model requirements: The following is used to evaluate each model. The minimum
    # values for R^2 of training should be 0.6, R^2 of Validation should be 0.5 and R^2 of
    # test should be 0.5
    R2req_train    = .6 
    R2req_validate = .5
    R2req_test     = .5

    # getAllOfTheData is in FromDataFileMLR file. The following places the data
    # (training data, validation data, and test data) into associated matrices
    TrainX, TrainY, ValidateX, ValidateY, TestX, TestY = dataminer.filedata.getAllOfTheData()
    TrainX, ValidateX, TestX = dataminer.filedata.rescaleTheData(TrainX, ValidateX, TestX)

    fittingStatus = unfit
    # Initializing and finding the fitness of the first population
    population = dataminer.Create_A_Population(numOfPop,numOfFea)
    fittingStatus, fitness = dataminer.analyzer.validate_model(model,fileW, population,
        TrainX, TrainY, ValidateX, ValidateY, TestX, TestY)

    # Initializing the first VelocityMatrix
    dataminer.CreateInitialVelocity(numOfPop, numOfFea)
    # initializing LocalBestMatrix as the initial population
    dataminer.LocalBestM = population.copy()
    # initializing LocalBestMatrix's fitness as the initial population's fitness
    dataminer.LocalBestM_Fit = fitness.copy()
    dataminer.FindGlobalBestRow()

    dataminer.PerformOneMillionIteration(numOfPop, numOfFea, population, fitness, model, fileW,
                               TrainX, TrainY, ValidateX, ValidateY, TestX, TestY)
#main routine ends in here
#------------------------------------------------------------------------------
main()
#------------------------------------------------------------------------------
