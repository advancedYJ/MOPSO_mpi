#include "MOPSO.h"

void initializeParticles(Particle *particle){
    for (int j=0; j<particle_numbers; j++){
        //  initialize Velocity
        initializeParticle(particle[j]);
        
    }
}

void initializeParticle(Particle &particle){
    int lenP = particle.sizeOfPosition;
    int lenO = particle.sizeOfAddO_origin;

    for (int i=0; i < lenP; i++)
        particle.Velocity[i] = 0;
    particle.sizeOfVelocity = lenP;


    //  Best

    cpyDoubleArray(particle.Best.Position,particle.Position,lenP);

    cpyDoubleArray(particle.Best.addO_origin,particle.addO_origin, lenO);

    cpyDoubleArray(particle.Best.Cost, particle.Cost, objectiveNumber);
}