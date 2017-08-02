//
// Created by advanced on 17-5-31.
//
#include "MOPSO.h"

int world_size;
int world_rank;
int *sendCounts = NULL;
int *displaces  = NULL;
MPI_Datatype  mpi_BestParticle_type;
MPI_Datatype mpi_particle_type;

void initial_mpi(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    create_mpi_BestParticle_type(mpi_BestParticle_type, 3);
    create_mpi_particle_type(mpi_particle_type, 17);

    getInputParameter(argv, particle_numbers, MaxIt);       // get particle numbers and maxIterator
    particle_numbers += multiplyNumber;
    initial_Scatterv(sendCounts, displaces, particle_numbers, world_size);      //  get sendCounts and displaces

    set_Address(argv);
}

void initial_Scatterv(int *&sendCounts, int *&displaces, const int number_of_sent_data,
                      const int size_of_process){
    sendCounts = new int[size_of_process];
    displaces = new int [size_of_process];
    int rem = number_of_sent_data % size_of_process;     // elements remaining after division among processes
    int sum = 0;                                // Sum of counts. Used to calculate displacements
    for (int i = 0; i < size_of_process; i++){
        sendCounts[i] = number_of_sent_data / size_of_process;
        if (rem > 0){
            sendCounts[i]++;
            rem--;
        }
        displaces[i] = sum;
        sum += sendCounts[i];
    }
}

void create_mpi_BestParticle_type(MPI_Datatype &mpi_new_type, const int nItems){
    //    每一部分的大小
    int blockLengths[nItems] = {MAX_POSITOIN_SIZE, MAX_ORIGIN_SIZE, objective_Function_Number};
//    每部分的偏移量
    MPI_Aint offsets[nItems];
    offsets[0] = offsetof(BestParticle, Position);
    offsets[1] = offsetof(BestParticle, addO_origin);
    offsets[2] = offsetof(BestParticle, Cost);
//    每部分的类型
    MPI_Datatype types[nItems] = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE};
//    创建自己的mpi_type!
    MPI_Type_struct(nItems, blockLengths, offsets, types, &mpi_new_type);
//    显式加入！
    MPI_Type_commit(&mpi_new_type);

}

// 为结构体particle写一个mpi_particle_type,在MPI_Scatterv里头用到
void create_mpi_particle_type(MPI_Datatype &mpi_new_type, const int nItems){
//    每一部分的大小
    int blockLengths[nItems] = {MAX_ORIGIN_SIZE, MAX_ORIGIN_SIZE, MAX_POSITOIN_SIZE, MAX_POSITOIN_SIZE,
                                MAX_POSITOIN_SIZE, objective_Function_Number, 1, 1, 1, 1, 1, 1, 1, 1,
                                MAX_PARTICLE_SIZE, 1, 1};
//    每部分的偏移量
    MPI_Aint offsets[nItems];
    getParticle_Offsets(offsets);

//    每部分的类型
    MPI_Datatype types[nItems] = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE,
                                  MPI_CXX_BOOL, MPI_INT, MPI_INT, MPI_INT, MPI_INT, MPI_INT, MPI_INT,
                                  MPI_INT, MPI_CHAR, MPI_INT, mpi_BestParticle_type};
//    创建自己的mpi_type!
    MPI_Type_struct(nItems, blockLengths, offsets, types, &mpi_new_type);
//    显式加入！
    MPI_Type_commit(&mpi_new_type);

}

void getParticle_Offsets(MPI_Aint *offsets){
    offsets[0] = offsetof(Particle, origin);
    offsets[1] = offsetof(Particle, addO_origin);
    offsets[2] = offsetof(Particle, Position);
    offsets[3] = offsetof(Particle, old_position);
    offsets[4] = offsetof(Particle, Velocity);
    offsets[5] = offsetof(Particle, Cost);
    offsets[6] = offsetof(Particle, dominated);
    offsets[7] = offsetof(Particle, numAA);
    offsets[8] = offsetof(Particle, numAtom);
    offsets[9] = offsetof(Particle, sizeOfOrigin);
    offsets[10] = offsetof(Particle, sizeOfAddO_origin);
    offsets[11] = offsetof(Particle, sizeOfPosition);
    offsets[12] = offsetof(Particle, sizeOfVelocity);
    offsets[13] = offsetof(Particle, my_Index);
    offsets[14] = offsetof(Particle, seq);
    offsets[15] = offsetof(Particle, startNumber);
    offsets[16] = offsetof(Particle, Best);
}

void set_Address(char **argv) {
    inputAddress = catStrStr(argv[1], "/");
    answerAddress = catStrIntStr(argv[1], "_Answer_", world_rank, "/");
    createNewFold();    //    create answer fold
    logAddress = catStrIntStr(answerAddress, "log", world_rank, ".txt");
    freopen(logAddress, "w", stdout);
}

void finalize_MPI(){
    MPI_Type_free(&mpi_BestParticle_type);
    MPI_Type_free(&mpi_particle_type);
    MPI_Finalize();
}