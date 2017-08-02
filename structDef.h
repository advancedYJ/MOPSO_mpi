//
// Created by advanced on 17-5-31.
//

#ifndef MPI_MOPSO_STRUCTDEF_H
#define MPI_MOPSO_STRUCTDEF_H

#include "paraDef.h"

template <typename _MD>
struct commonStruct{
    _MD value;
    int id;
};


struct BestParticle{
    double Position[MAX_POSITOIN_SIZE];
    double addO_origin[MAX_ORIGIN_SIZE];
    double Cost[objective_Function_Number];
};


struct Particle{
    double origin[MAX_ORIGIN_SIZE];                          //    the coordinate(x,y,z) of every atom (not include atom O),
    //  three indexes represent an Atom's position
    double addO_origin[MAX_ORIGIN_SIZE];                   // the coordinate(x,y,z) of every atom (include the atom O)
    double Position[MAX_POSITOIN_SIZE];                      //  the angles
    double old_position[MAX_POSITOIN_SIZE];                  //  used in the calculation of angle change
    double Velocity[MAX_POSITOIN_SIZE];                      //  will be used in the MOPSO
    double Cost[objective_Function_Number] ;                         //  will be used int the MOPSO, store every f(x) the particle have
    bool dominated;                     //   represent if the particle is dominated by some other,
    //  which means it is certainly not the best answer
    int numAA;           // the number of AA
    int numAtom;         //  the number of atoms
    int sizeOfOrigin;
    int sizeOfAddO_origin;
    int sizeOfPosition;
    int sizeOfVelocity;    //  the size of arrays
    int my_Index;
    char seq[MAX_PARTICLE_SIZE];
    int startNumber;
    BestParticle Best;                    //  pBest
};


struct Rep{
    double *Cost;
    double *addO_origin;
    double *Position;
    int sizeOfAddO_origin;
    int iterator;
    char *seq;
    int startNumber;
    int numAA;
};

struct Atom {
    char name[10], group[10];
    int number;
    double x, y, z;
};

struct POINT{
    double x, y;
    int id;
};

struct VECTOR{
    double x, y;
    VECTOR(double x1, double y1){
        x = x1;
        y = y1;
    }
};

struct ANGLE{
    double value;
    int id;
};

struct EnergyValueStruct{
    double value;
    int id;
};


#endif //MPI_MOPSO_STRUCTDEF_H
