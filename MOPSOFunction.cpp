#include "MOPSO.h"

extern int particle_numbers;

void PSOAdaptionForPhi(Particle &particle, myRep &rep, int it) {
    double w = getInertiaWeight(it-1, MaxIt);       //  get inertia wight
    int len = particle.sizeOfPosition;
    int h = rouletteWheel(rep);
    cpyDoubleArray(particle.old_position, particle.Position, len);
    myRep ::iterator a = rep.begin();
    for (int i=0; i<h; i++) a++;
    //  calculate the new Velocity
    for (int i=0; i<len; i++){
        double r1 = rand() / double(RAND_MAX) , r2 = rand() / double(RAND_MAX) ;
        if(it==0 && i%3 != 1) particle.Velocity[i] = rand() / double(RAND_MAX);
        particle.Velocity[i] = w * particle.Velocity[i] +
                               c1*r1* (particle.Best.Position[i] - particle.Position[i]) +
                               c2*r2 * (a->Position[i] - particle.Position[i]);
    }

    checkV(particle.Velocity, len);

    //  calculate the new position
    for (int i=0; i<len; i++)   particle.Position[i] += particle.Velocity[i];

    checkP(particle.Position, particle.Velocity, len);
}

void PSOAdaptionForXYZ(Particle &particle, myRep &rep, int it){
    double w = getInertiaWeight(it-1, MaxIt);       //  get inertia wight
    int len = particle.sizeOfAddO_origin;
    int h = rouletteWheel(rep);
    myRep ::iterator a = rep.begin();
    for (int i=0; i<h; i++)
        a++;

    //  calculate the new Velocity
    for (int i=0; i<len; i++){
        double r1 = rand() / double(RAND_MAX) , r2 = rand() / double(RAND_MAX) ;
        if(it==0 && i%3 != 1) particle.Velocity[i] = rand() / double(RAND_MAX);
        particle.Velocity[i] = w * particle.Velocity[i] +
                               c1*r1* (particle.Best.addO_origin[i] - particle.addO_origin[i]) +
                               c2*r2 * (a->addO_origin[i] - particle.addO_origin[i]);
    }
    checkV(particle.Velocity, len);

    //  calculate the new position
    for (int i=0; i<len; i++)   particle.addO_origin[i] += particle.Velocity[i];

    checkOrigin(particle.addO_origin, particle.Velocity, len);
}

void getAllParticleCost(Particle * particle){
    Particle local_particle[sendCounts[world_rank]];
//    mpi分配任务
    MPI_Scatterv(particle, sendCounts, displaces, mpi_particle_type,
                 local_particle, 100, mpi_particle_type,
                 MASTER, MPI_COMM_WORLD);

//    每个子线程计算其分配到的粒子的能量值
    for (int i = 0 ; i < sendCounts[world_rank]; i++) {
        getAParticleCost(&local_particle[i]);
    }
//    每个子线程将其计算结果返回给MASTER
    MPI_Gatherv(local_particle, sendCounts[world_rank], mpi_particle_type,
                particle, sendCounts, displaces, mpi_particle_type,
                MASTER, MPI_COMM_WORLD);
}

void getAParticleCost(Particle *particle){
    printPdb(particle);
    runScwrl(particle->my_Index);

    particle->Cost[0] = getCost0(particle->my_Index);

    particle->Cost[1] = getCost1(particle->my_Index);

    particle->Cost[2] = getCost2(particle->my_Index);

    removeTmp(particle->my_Index);
}

/*void getAllParticleCostForTest(Particle * particle){                   // calculate f(x)
    for (int i=0; i<particle_numbers; i++)
    {
        int len = particle[i].sizeOfAddO_origin;
        double ans1 = 0, ans2=0;
        for (int j=0; j<len; j+=3){
            double x= particle[i].addO_origin[j];
            double y= particle[i].addO_origin[j+1];
            double z= particle[i].addO_origin[j+2];
            ans1 += dis1(x,y,z);
            ans2 += dis2(x, y, z);
        }
        particle[i].Cost[0] = ans1;
        particle[i].Cost[1] = ans2;
    }
}
*/
bool isDominated(double *cost1, double *cost2){
    bool flag = 1;                                          //  if flag is true then  cost1 is dominated by cost2
    //  which means  cost1 >= cost2, for all the f(x)
    bool equal = 1;
    for (int i=0; i<objectiveNumber; i++){
        if (cost1[i] < cost2[i]){   flag = 0;  equal = 0;   break;      }
        if ( !doubleEqual(cost1[i], cost2[i]) )  equal = 0;
    }
    if (equal)  flag  =  1;                             //   if cost1 = cost2 ,for all the f(x), then cost1 is not
    return flag;                                          //dominated by cost2, which means 2 is not better than 1
}                                                       // but it will generate many same paticles in the rep
                                                        // so I change it to true
void decideDominated(Particle * particle){
    for (int i=0; i<particle_numbers; i++)
        particle[i].dominated = 0;

    for (int i=0; i<particle_numbers; i++)
        for (int j=0; j<particle_numbers; j++) {
            if (i==j) continue;
            if (isDominated(particle[i].Cost, particle[j].Cost))
                particle[i].dominated = 1;
        }
}


void updatePBest(Particle * particle){
    for (int i=0; i<particle_numbers; i++){
        int update=0;               //  update=-1  :  pre pBest is better;  update=1: new particle is better
        if (isDominated(particle[i].Cost, particle[i].Best.Cost))  update = -1;
        if (isDominated(particle[i].Best.Cost, particle[i].Cost))  update = 1;

        if (update==0)
            if (rand() % 2 ==1)
                update=1;
        if (update == 1){
            cpyDoubleArray(particle[i].Best.addO_origin, particle[i].addO_origin, particle[i].sizeOfAddO_origin);
            cpyDoubleArray(particle[i].Best.Position, particle[i].Position, particle[i].sizeOfPosition);
            cpyDoubleArray(particle[i].Best.Cost, particle[i].Cost, objectiveNumber);
        }
    }
}