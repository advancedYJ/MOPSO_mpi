#include "MOPSO.h"


int main(int argc, char *argv[])    // argv: [1]input address, [2]number of particles, [3]loop times
{
    multiplyNumber = 3;
    initial_mpi(argc, argv);
    if (world_rank == MASTER){
        preDispose(argv);
        multiplyBetterInput();
        inputParticles(particle);               // Input Data
    }
    updateRep(particle, rep, 0);


    // MOPSO Main Loop
    for (int it = 1; it <= MaxIt; it++) {
        if (world_rank == MASTER){
            printCurrentId(it);
            for (int i = 0; i < particle_numbers; i++) {
                PSOAdaptionForPhi(particle[i], rep, it - 1);            //  apply the PSO formula
                convertRotationToCoordinary(particle[i]);    //  convert rotation to coordinary
            }
        }

        updateRep(particle, rep, it);

        if (world_rank == MASTER){
            updatePBest(particle);                       //      update pBest
            printTime(1, it);
        }
    }

    if (world_rank == MASTER){
        outputAnswer(rep);
        printTime(0, 0);
        freeUpSpace(particle);
    }

    finalize_MPI();
    return 0;
}

/*
./mpirun -n 2 /home/advanced/MOPSO/data/input/TR760 2 2
 */