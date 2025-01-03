import time                 #provides timing for benchmarks
from numpy  import *        #provides complex math and array functions
from sklearn import svm     #provides Support Vector Regression
import csv

import mlr
import FromDataFileMLR
import FromFinessFileMLR

class DE_BPSO:
    def __init__(self, numOfPop, numOfFea):
        # Acquires and formats data from Train, Validation, Test .csv files
        self.filedata = FromDataFileMLR.DataFromFile()
        # Performs data analysis on training, validation, and test data
        self.analyzer = FromFinessFileMLR.FitnessResults()
        self.NumIterations = 10000
        self.alpha = 0.5 #starting alpha value
        self.GlobalBestRow = ndarray(numOfFea) #best-fitting population yet found
        self.GlobalBestFitness = 10000 #fitness of GlobalBestRow, initialized very high
        self.VelocityM = ndarray((numOfPop, numOfFea)) # Velocity matrix
        self.LocalBestM = ndarray((numOfPop, numOfFea)) # local best matrix
        self.LocalBestM_Fit = ndarray(numOfPop) # local best matrix fitnesses
    #------------------------------------------------------------------------------
    def CreateInitialVelocity(self, numOfPop, numOfFea):
        # Each element in initial VelocityMatrix is randomly determined
        # create the initial velocity
        for i in range(numOfPop):
            for j in range(numOfFea):
                self.VelocityM[i][j] = random.random()
    # -------------------------------------------------------------------------------------------
    def getAValidrow(self, numOfFea, eps=0.015):
        # Returns a row with at least three features
        sum = 0
        while (sum < 5 or sum > 15):
            V = zeros(numOfFea)
            for j in range(numOfFea):
                r = random.uniform(0, 1)
                if (r < eps):
                    V[j] = 1
                else:
                    V[j] = 0
            sum = V.sum()
        return V
    #------------------------------------------------------------------------------
    def InitializePopulation(self, numOfPop, numOfFea, lmbd = 0.01):
        # find the initial population as shown in step 2 of the guide
        # if the number of 1's is less than 5 or greater than 15, call
        # GetAValidRow() to get a row with at least 5 features and at most
        # 15 features
        population = random.random((numOfPop, numOfFea))
        for i in range(numOfPop):
            # Get valid row with 5-15 features
            sum = 0
            while (sum < 5 or sum > 15):
                V = self.getAValidrow(numOfFea)
                sum = V.sum()
            # Copy valid row to population
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
    def createANewPopulation(self, numOfPop, numOfFea, OldPopulation, beta=0.004):
        # This routine finds the new population based on what is given in the guide
        # Initialize new population
        NewPopulation = OldPopulation.copy()
        
        # Update alpha and calculate p
        self.alpha -= (0.17/self.NumIterations)
        p = (0.5)*(1+self.alpha)
        
        changecount = 0
        F = 0.5  # scaling factor
        CR = 0.7  # crossover rate
        
        for i in range(numOfPop):
            # Select three random distinct vectors
            r1, r2, r3 = random.choice(range(numOfPop), 3, replace=False)
            
            for j in range(numOfFea):
                # DE mutation and crossover
                if random.random() < CR:
                    trial = OldPopulation[r1][j] + F * (OldPopulation[r2][j] - OldPopulation[r3][j])
                    
                    # Convert to binary using velocity thresholds
                    if self.VelocityM[i][j] <= self.alpha:
                        NewPopulation[i][j] = OldPopulation[i][j]
                    elif self.VelocityM[i][j] <= p:
                        NewPopulation[i][j] = self.LocalBestM[i][j]
                    else:
                        NewPopulation[i][j] = self.GlobalBestRow[j]
                    
                    if NewPopulation[i][j] != OldPopulation[i][j]:
                        changecount += 1

            # Check if this row is valid (5-15 features)
            feature_count = sum(NewPopulation[i])
            if feature_count < 5 or feature_count > 15:
                # If invalid, replace with a valid row
                NewPopulation[i] = self.getAValidrow(numOfFea)
        
        return NewPopulation.copy(), changecount
#-------------------------------------------------------------------------------------------
    def FindGlobalBestRow(self):
        # Global bet row is updated the same way as you did in the BPSO project
        IndexOfBest = argmin(self.LocalBestM_Fit)
        
        if self.GlobalBestFitness > self.LocalBestM_Fit[IndexOfBest]:
            self.GlobalBestRow = self.LocalBestM[IndexOfBest].copy()
            self.GlobalBestFitness = self.LocalBestM_Fit[IndexOfBest]
#-------------------------------------------------------------------------------------------
    def UpdateLocalMatrix(self, NewPopulation, NewPopFitness):
        # Local best matrix is updated as the one you did in the BPSO project
        numOfPop = self.LocalBestM.shape[0]
        
        for i in range(numOfPop):
            if NewPopFitness[i] < self.LocalBestM_Fit[i]:
                self.LocalBestM_Fit[i] = NewPopFitness[i]
                self.LocalBestM[i] = NewPopulation[i].copy()
#-------------------------------------------------------------------------------------------
    def UpdateVelocityMatrix(self, NewPop, F=0.7, CR=0.7):
        # this section creates a new Velocity as it is shown in the guide
        numOfPop = self.VelocityM.shape[0]
        numOfFea = self.VelocityM.shape[1]
        vcount = 0
        
        for i in range(numOfPop):
            # Select three random distinct vectors for DE
            r1, r2, r3 = random.choice(range(numOfPop), 3, replace=False)
            
            for j in range(numOfFea):
                if random.random() < CR:
                    # DE mutation
                    trial = self.VelocityM[r1][j] + F * (self.VelocityM[r2][j] - self.VelocityM[r3][j])
                    # Keep velocity in [0,1] range
                    self.VelocityM[i][j] = abs(trial) % 1
                vcount += self.VelocityM[i][j]
        
        return vcount / (numOfPop * numOfFea)
#-------------------------------------------------------------------------------------------
    def scatter_population(self, population, numOfPop, numOfFea, fitness):
        """
        Randomizes the bottom 50% of the population based on fitness values.
        This version maintains the DE_BPSO constraints of 5-15 features per solution.
        """
        # Create a copy of the population to modify
        scattered_population = population.copy()
        
        # Get indices sorted by fitness (worst to best)
        sorted_indices = argsort(fitness)
        
        # Get the indices of the bottom 50%
        bottom_half = sorted_indices[numOfPop//2:]
        
        # Randomize these positions using getAValidrow
        # This ensures we maintain the 5-15 features constraint
        for idx in bottom_half:
            scattered_population[idx] = self.getAValidrow(numOfFea)
        
        return scattered_population

    def PerformOneMillionIteration(self, numOfPop, numOfFea, population, fitness, model, fileW,
                                TrainX, TrainY, ValidateX, ValidateY, TestX, TestY):
        NumOfGenerations = 1
        waittime = 0  # tracks how many passes have occurred after a certain time X
        
        while NumOfGenerations < self.NumIterations:
            print("Generation", NumOfGenerations)
            
            # Scatter every 200 generations
            if NumOfGenerations % 250 == 0:
                print(f"Scattering population at generation {NumOfGenerations}")
                population = self.scatter_population(population, numOfPop, numOfFea, fitness)
                # Recalculate fitness for scattered population
                fittingStatus, fitness = self.analyzer.validate_model(model, fileW,
                            population, TrainX, TrainY, ValidateX, ValidateY, TestX, TestY)
            
            OldPopulation = population.copy()
            population, popchanges = self.createANewPopulation(numOfPop, numOfFea, OldPopulation)
            fittingStatus, fitness = self.analyzer.validate_model(model, fileW,
                        population, TrainX, TrainY, ValidateX, ValidateY, TestX, TestY)

            self.UpdateLocalMatrix(population, fitness)
            self.FindGlobalBestRow()
            avgV = self.UpdateVelocityMatrix(population)

            NumOfGenerations = NumOfGenerations + 1
        return
#end of DE_BPSO class

#--------------------------------------------------------------------------------------------
#Main program
def main():
    # Number of descriptor should be 385 and number of population should be 50 or more
    numOfPop = 50
    numOfFea = 385

    # create an object of Multiple Linear Regression model.
    # The class is located in mlr file
    model = mlr.MLR()
    # Creates new populations and updates VelocityMatrix, LocalBestMatrix, and GlobalBestRow
    dataminer = DE_BPSO(numOfPop, numOfFea)

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
    # Creating initial Velocity Matrix
    dataminer.CreateInitialVelocity(numOfPop, numOfFea)
    # Creating initial population based on initial VelocityMatrix
    population = dataminer.InitializePopulation(numOfPop,numOfFea)
    # Determining fitness of initial population
    fittingStatus, fitness = dataminer.analyzer.validate_model(model,fileW, population,
        TrainX, TrainY, ValidateX, ValidateY, TestX, TestY)

    # initializing LocalBestMatrix as the initial population
    dataminer.LocalBestM = population.copy()
    # initializing LocalBestMatrix's fitness values
    dataminer.LocalBestM_Fit = fitness.copy()
    # finding the GlobalBestRow of the initial population
    dataminer.FindGlobalBestRow()

    dataminer.PerformOneMillionIteration(numOfPop, numOfFea, population, fitness, model, fileW,
                               TrainX, TrainY, ValidateX, ValidateY, TestX, TestY)
#main routine ends in here
#------------------------------------------------------------------------------
main()
#------------------------------------------------------------------------------
