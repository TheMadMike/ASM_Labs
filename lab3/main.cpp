#include <random>
#include <ctime>

#include "simd.hpp"
#include "sisd.hpp"


#define MAX_RANDOM_VALUE 10000.0f
#define REPETITIONS 100U

//microseconds
#define TIME_US CLOCKS_PER_SEC * 10e6;
//nanoseconds
#define TIME_NS CLOCKS_PER_SEC * 10e9;

// SIMD/SISD arithmetic operation pointer
typedef Vect4f(*OperationPtr)(Vect4f, Vect4f);

const OperationPtr SIMD_OPERATIONS[4] = {
    simd::add, simd::subtract, simd::multiply, simd::divide
};

const OperationPtr SISD_OPERATIONS[4] = {
    sisd::add, sisd::subtract, sisd::multiply, sisd::divide
};

void test(const OperationPtr* operationSet, const char* operationTypeString);

int main(int argc, char** argv) {
    test(SIMD_OPERATIONS, "SIMD");
    test(SISD_OPERATIONS, "SISD");

    return 0;
}


Vect4f* generateSample(unsigned int size);

double performOperations(OperationPtr operation, Vect4f* sample, unsigned int sampleSize);

const char OPERATORS[4] = { '+', '-', '*', '/' };

void test(const OperationPtr* operationSet, const char* operationTypeString) {

    const unsigned int SAMPLE_SIZES[3] = {2048U, 4086U, 8192U};

    //generate data
    Vect4f* sample[3];
    for(unsigned i = 0; i < 3; ++i) {
        sample[i] = generateSample(SAMPLE_SIZES[i]);
    }

    for(unsigned i = 0; i < 3; ++i) {
        double operationTime[4] = {0.0, 0.0, 0.0, 0.0};

        for(unsigned j = 0; j < REPETITIONS; ++j) {

            for(unsigned k = 0; k < 4; ++k) {
                operationTime[k] += performOperations(operationSet[k], sample[i], SAMPLE_SIZES[i]);
            }

        }
        printf("Operations type: %s\n", operationTypeString);
        printf("Number of numbers: %d\n", SAMPLE_SIZES[i] / 2U);
        
        for(unsigned j = 0; j < 4; ++j) {
            printf("%c %lf s\n", OPERATORS[j], operationTime[j] / REPETITIONS);
        }

        for(unsigned k = 0; k < 4; ++k) {
            operationTime[k] = 0.0;
        }
    }

    for(unsigned i = 0; i < 3; ++i) {
        delete[] sample[i];
    }
}

double performOperations(OperationPtr operation, Vect4f* sample, const unsigned int sampleSize) {
    double totalTime = 0.0;
    for(unsigned i = 0; i < sampleSize; i+=2) {
        clock_t start = clock();
        operation(sample[i], sample[i+1]);
        clock_t end = clock();
        totalTime += ((double)(end - start))/TIME_US;
    }

    return totalTime / (double)sampleSize;
}

Vect4f generateRandomVect();

Vect4f* generateSample(unsigned int size) {
    Vect4f* sample = new Vect4f[size];
    
    for(unsigned i = 0; i < size; ++i) {
        sample[i] = generateRandomVect();
    }

    return sample;
}

std::random_device rd;
std::default_random_engine randomEngine(rd());
std::uniform_real_distribution<float> distribution(0.0f, MAX_RANDOM_VALUE);

float generateRandomFloat() {
    return distribution(randomEngine);
}

Vect4f generateRandomVect() {
    return { 
        generateRandomFloat(), 
        generateRandomFloat(), 
        generateRandomFloat(),
        generateRandomFloat()
    };
}