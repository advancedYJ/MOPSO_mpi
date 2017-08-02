//
// Created by advanced on 17-5-31.
//

#ifndef MPI_MOPSO_PARADEF_H
#define MPI_MOPSO_PARADEF_H

#include <cmath>
#include <ctime>
#include <list>
#include <mpi.h>


//  Address Settings
extern const char rootAddress[];
extern char *inputAddress;
extern char *logAddress;
extern const char *energyFileAddress;
extern const char *tempFileAddress;
extern const char *defaultFileAddress;
extern const char *QUACKoutFileAddress;
extern const char *charmmFileAddress;
extern const char *refine_1Address;
extern const char *TM_scoreAddress;
extern char *answerAddress;
extern const char *draftAddress;
extern const char *scoreAddress;
extern const char *databaseAddress;
extern const char *mybinAddress;
extern const char *strideAddress;


// Problem Definition
const int nVar = 183;
const double VarMax = 180;
const double VarMin = -180;
//const double VelMax = 0.7;             //  =20 without rama_map

// MOPSO Settings
const int tidSize =2;
const int objectiveNumber = 3; //  Multiple Obejectives settings, the size of objective function
const double TM_scoreThreshold = 0.13;
const int nRep = 50;                // Repository Size
const double Criterion = 0.000001;
const int lambdaLoopTimes = 1000;

const int answerRepNumber = 10;
//const int  MaxIt = 1;          // Maximum Number of Iterations
//const int particle_numbers = 2;                  // Population Size


const double phi1 = 2.05;
const double phi2 = 2.05;
const double phi = phi1 + phi2;
const double chi = 2 / ( phi - 2 + sqrt( phi * phi - 4 * phi ) );    // 0.73
const int bufferLen = 2048;

const double wMin = chi;                        // =chi  Inertia Weight
const double wMax = 1.2;
const double wDamp=1;                       //  Inertia Weight Damping Ratio
const double c1 = chi*phi1;                 //  Personal Learning Coefficient
const double c2 = chi*phi2;                 //  Global Learning Coefficient

const double Alpha = 0.1;       //Grid Inflation Parameter
const int nGrid = 10;               //Number of Grids per each Dimension
const int Beta = 4;                   //Leader Selection Pressure Parameter
const int Gamma = 2;             // Extra (to be deleted) Repository Member Selection Pressure

const double PI = M_PI;
const double INF=100000000;
const double realMax = 100000000;
const double tiny = 0.0000000001;

//    mpi settings
const int MASTER = 0;
const int objective_Function_Number = 3; //  Multiple Obejectives settings, the size of objective function
const int MAX_PARTICLE_SIZE = 500;
const int MAX_ORIGIN_SIZE = MAX_PARTICLE_SIZE * 4 * 3;
const int MAX_POSITOIN_SIZE = MAX_PARTICLE_SIZE * 3;

extern double VelMax;             //  =20 without rama_map


// MOPSO Settings
extern int particle_numbers;                  // Population Size
extern int  MaxIt;          // Maximum Number of Iterations
extern int multiplyNumber; // copy the best input particle
extern time_t starTime;
extern time_t endTime;

// my tools

extern int *sortAns;

// mpi settings
extern int world_size;
extern int world_rank;
extern int *sendCounts;
extern int *displaces;
extern MPI_Datatype  mpi_BestParticle_type;
extern MPI_Datatype mpi_particle_type;

#endif //MPI_MOPSO_PARADEF_H
