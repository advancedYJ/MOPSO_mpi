//
// Created by advanced on 17-1-16.
//

#include "MOPSO.h"

void updateRep(Particle *particle, myRep &rep, int loopTimes) {
    getAllParticleCost(particle);
    if (world_rank ==MASTER){
        decideDominated(particle);                        //  decide if particle[i] is dominated
        printParticleCost(particle, loopTimes);
        if (loopTimes == 1) { rep.clear(); }
        putNewParticleIntoRep(particle, rep, loopTimes);          //  put particles into rep
        sieveRep(rep);
    }
}

void putNewParticleIntoRep(Particle * particle, myRep & rep, int iterator){
    for (int i=0; i<particle_numbers; i++)
        if (!particle[i].dominated){
            if (canPutIntoRep(particle[i].Cost, rep)){
                Rep tmp;
                tmp.addO_origin = new double [particle[i].sizeOfAddO_origin];
                tmp.Position = new double [particle[i].sizeOfPosition];
                tmp.Cost = new double [objectiveNumber];
                tmp.seq = new char [sizeof(particle[i].seq)];
                tmp.sizeOfAddO_origin = particle[i].sizeOfAddO_origin;
                tmp.iterator = iterator;
                tmp.numAA = particle[i].numAA;
                memcpy(tmp.seq, particle[i].seq, sizeof(particle[i].seq));
                cpyDoubleArray(tmp.addO_origin, particle[i].addO_origin, particle[i].sizeOfAddO_origin);
                cpyDoubleArray(tmp.Position, particle[i].Position, particle[i].sizeOfPosition);
                cpyDoubleArray(tmp.Cost, particle[i].Cost, objectiveNumber);
                rep.push_back(tmp);
            }
        }
}

bool canPutIntoRep(double *cost, myRep & rep){
    bool flag=1;                                                    // if return true then can put
    myRep::iterator it=rep.begin();
    myRep::iterator tmpIt;
    while (it != rep.end()){
        bool erase=0;
        if (isDominated(cost, it->Cost)){       //      there is at least one element in the rep better than
            flag = 0;                           //  the new particle, so it is also impossible that
            break;                                              //  the new one is better than the remains in the rep
        }
        if (isDominated(it->Cost, cost)){       //  the new one is better then one of the element in rep
            tmpIt = it;
            erase =1;
        }
        it++;
        if (erase) rep.erase(tmpIt);            //  if erase it ... error will occur
    }
    return flag;
}


void sieveRep(myRep & rep){
    while (rep.size() > nRep){
        int h = rouletteWheel(rep);
        myRep ::iterator itr = rep.begin();
        for (int i=0; i<h; i++) itr++;
        rep.erase(itr);
    }
}
