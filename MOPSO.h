#ifndef MOPSO_H
#define MOPSO_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <list>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <mpi.h>
#include <stddef.h>
#include "Matrix.h"
#include "paraDef.h"
#include "structDef.h"

using namespace std;


typedef list<Rep> myRep;            //   a wonderful list, the data struct of the repositpry, which
typedef const char CONCH;

extern myRep rep;
extern Particle *particle;
extern ANGLE *angle;

// fileDisposal
    // Input Data

int getLines(char *address);
void getAtom(Atom *atom, int cntLines, int &atomNum, char *address);        // find the word "ATOM" in the file

char * inputSeq();
void setVelMax(char *seq);
void inputParticle(Particle &particle, int k, char *seq);
void inputParticles(Particle *particle);
void inputParOrigin(Particle &particle, int fileNum, int cntLines);
void inputParPhi(Particle &particle, int fileNum);
    // a function that will open file and throw error if it can't open file
void openFile(const char fileDir[10000], ifstream &infile);
    // a function that will remove file and throw error if it can't remove file
void removeFile(const char * str);

    // for the object function
void printPdb(Particle * particle);
void printParticle(Particle * particle);
void printPdb(list<Rep>::iterator it, const int &repNum);
    // for debug
        // print rep in several files
void printRep(myRep & rep, int len);
        // print the particles' status in one file
void printParticleCost(Particle * particle, int iterator);
    // print answer rep
    void outputAnswer(myRep &rep);
    //  print run time
    void printTime(const int choice, const int loopTimes);
    //  create a new fold for the answer
void createNewFold();

//  multiply better input
void multiplyBetterInput();
void multiplyParticle(Particle particle, int repNum);
void get_VelMax(char *seq);

void runScwrl(int index);                   //  run scwrl program after print .pdb
void removeTmp(int index);

// get the cost for the object function 1 and 2
double getCost0(int i);
double getCost1(int i);
double getCost2(int i);
void rewriteTemplate(int i, const char *templateFile, const char *tmpIFile, const char *tmpI);
double getEnergyValue(const char *fileName);
void printCurrentId(int id);

// initialize particle
void initializeParticles(Particle *particle);
void initializeParticle(Particle &particle);

// put input particles into rep
void updateRep(Particle *particle, myRep &rep, int loopTimes);

//  MOPSOFunction
    //  apply the formulation of PSO
void PSOAdaptionForPhi(Particle &particle, myRep &rep, int it);
void PSOAdaptionForXYZ(Particle &particle, myRep &rep, int it);

    //  decide if particle[i] is dominated, for all i
void decideDominated(Particle * particle);

    //  compare the new position with the pBest and update it
void updatePBest(Particle * particle);

    // calculate f(x)
void getAllParticleCostForTest(Particle * particle);
void getAllParticleCost(Particle * particle);

void getAParticleCost(Particle *particle);

    //if the result is true, then cost1 is dominated by cost2
bool isDominated(double *cost1, double *cost2);

    //    add the new non-dominated particles into rep / eliminate some in the rep that is not so good now
void putNewParticleIntoRep(Particle * particle, myRep & rep, int iterator);

    //decide whether particle[i] can be put into rep or not, as well as eliminate the rep particles
    //which are dominated by particle[i]
    // if return true then can put
bool canPutIntoRep(double *Cost, myRep & rep);

void sieveRep(myRep & rep);         //  if there are too many paticles in rep, restrict it in a set value


//  MOPSOAidFunction
    //  cat c1-ss-c2  e.g. :  "mj" , 520 , "forever"  ->  mj520forever        used to conbine file name
char *catStrIntStr(const char *c1, int ss, const char *c2);
char *catStrIntStr(const char *c1, const char *c2, int ss, const char *c3);

    //  cat c1-c2
char *catStrStr(CONCH *c1, CONCH *c2);
char *catStrStr(CONCH *c1, CONCH *c2, CONCH *c3);
char *catStrStr(CONCH *c1, CONCH *c2, CONCH *c3, CONCH *c4);
char *catStrStr(CONCH *c1, CONCH *c2, CONCH *c3, CONCH *c4, CONCH *c5);
char *catStrStr(CONCH *c1, CONCH *c2, CONCH *c3, CONCH *c4, CONCH *c5, CONCH *c6);
char *catStrStr(CONCH *c1, CONCH *c2, CONCH *c3, CONCH *c4, CONCH *c5, CONCH *c6, CONCH *c7);
char *catStrStr(CONCH *c1, CONCH *c2, CONCH *c3, CONCH *c4, CONCH *c5, CONCH *c6, CONCH *c7, CONCH *c8);

    //  copy p2 to p1
void cpyDoubleArray(double *p1, double *p2, int n);

    //  check if V is out of range
void checkV(double *tmp, int n);

//  check if position is out of range
void checkOrigin(double *tmp, double *tmpV, int n);

    //  check if position is out of range
void checkP(double *tmp, double *tmpV, int n);

    //  get the right rep_h for this update time
int rouletteWheel(myRep & rep);

    //  get the w
double getInertiaWeight(double it,double MaxIt);

    //  for test object function
double dis1(double x, double y, double z);
double dis2(double x, double y, double z);

    //  get the AA that pr represent
char * getRelativeAA(char pr);

void strReplace(char *src, const char *shortStr, const int start, const int length);

int strToInt(char *str);

int getInputParameter(char **argv, int &nPop, int &MaxIt);

int getMax(int a, int b);

bool doubleEqual(double a, double b);

//  help to print parameters
void printPara(char *s, int k);
void printPara(char *s, double d);
void printPara(char *s, char *str);

//  convert rotation to coordinary
void convertRotationToCoordinary(Particle &particle);


//  Matrix Function
    //  ans = a*b
void matrixProduct(double a[4][4], double b[4][4], double ans[4][4]);

    //  set a[4][4] to be full of 0
void initialize_0(double a[4][4]);

    //  dan wei(chinese) matrix
void initialize_1(double a[4][4]);

    //  get the R in the paper
void getR(int it, double * a, double theta, double R[4][4]);

    //  get the new coordinate for itAtom
void getNewCoordinary(int itAtom, double R[4][4], double * a);

void cpyOriginTOAddO_origin(int it, double * x, double * xAddO);

void getNewCoordinaryForO(int it, double R[4][4], double * xAddO, int numAtom);

    //  newR = preR
void cpyMatrix(double preR[4][4], double newR[4][4]);

    //   dan wei hua (chinese)
void unitization(double v[3]);

    //set Q[3][3] the paper used
void getQ(double Q[4][4], double v[3], double theta);


//  get the best reps
void sortRepByAngle(myRep &rep, ANGLE *angle);
void sortRepByLambda(myRep &rep);
void getCostInUnit(myRep &rep, double **costInUnit);
void getAngle(int i, const POINT *point, ANGLE *angle);
double vectorDot(VECTOR u, VECTOR v);
double cross(VECTOR u, VECTOR v);
double length(VECTOR u);
bool pdPlusPi(POINT first, POINT second, POINT third);
void angleQsort(int l, int r, ANGLE *a);
void energyQsort(int l, int r, EnergyValueStruct *a);
void pointQsort(int l, int r, POINT *a);

// setTime
void setTime();
void getEndTime();

// dispose the input parameters and files previously
void preDispose(char **argv);
void disposePDB();
void createSeqTxt();
void createParticleTxt(int k);
void createPhi(int k);
bool isImportantAtom(const Atom atom);
char getAbbreviation(char *str);
void getArgv();

// check similarity
void checkAllParticleSimilarity(Particle *particle);
void *checkOneParticleSimilarity(void *p);
void checkOneParticleSimilarity(Particle &particle);
void runTM_score(int index);                //  run TM_score to get the similarity of 2 particle
double getTM_score(int index);
bool particleSimilarity(double TM_scrore);      // if return 1 then two particles are similar
void becomeInitialParticle(Particle &particle);

//free up space
void freeUpSpace(Particle *& particle);

// apply variables
void applyVariable();
// release space
void releaseSpace(double **x, const int &n);
void releaseSpace(double *x);

//   mpi function
void initial_mpi(int argc, char **argv);
void initial_Scatterv(int *&sendCounts, int *&displaces, const int number_of_sent_data,
                      const int size_of_process);
void create_mpi_BestParticle_type(MPI_Datatype &mpi_new_type, const int nItems);
void create_mpi_particle_type(MPI_Datatype &mpi_new_type, const int nItems);
void getParticle_Offsets(MPI_Aint *offsets);
void set_Address(char **argv);
void finalize_MPI();

// code for Debug
void printIn(int option);
void printOut(int option);


#endif // MOPSO_H
