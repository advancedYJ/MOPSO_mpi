//
// Created by advanced on 17-1-16.
//

#include "MOPSO.h"

void inputParticles(Particle *particle){
    char *seq;
    seq = inputSeq();                                               //input seq
    setVelMax(seq);

    for (int i = 0; i < particle_numbers; i++) {
        inputParticle(particle[i], i, seq);
    }  // input the particles data
    initializeParticles(particle);                 //  init the velocity, bestCost, bestPosition
}

void inputParticle(Particle &particle, int fileNum, char *seq){
    //  get the size of the protein
    int cntLines = getLines(catStrIntStr(inputAddress, "particleO_", fileNum+1, ".txt"));
    particle.numAA = cntLines/4;                                            // the number of AA
    particle.numAtom = particle.numAA *3;                          // the number of atoms ( not add O)

    // read the file to get the coordinaries
    inputParOrigin(particle, fileNum, cntLines);

    //  read the init angles
    inputParPhi(particle, fileNum);


    particle.my_Index = fileNum;
    memcpy(particle.seq, seq, sizeof(seq));

}

void inputParOrigin(Particle &particle, int fileNum, int cntLines) {
    ifstream inFile;
    char *fileAddress;
    char *filename;
    fileAddress = catStrStr(inputAddress, "particleO_");
    filename = catStrIntStr(fileAddress, fileNum+1, ".txt");
    openFile(filename, inFile);

    int k=0;
    //  read the file by lines
    for (int j=0; j<12 * particle.numAA; j++){
        inFile >> particle.addO_origin[j];
        if (j % 12<9)
            particle.origin[k++] = particle.addO_origin[j];
    }
    particle.sizeOfAddO_origin = particle.numAA*4*3;
    particle.sizeOfOrigin = particle.numAA*3*3;                 //  the totally number of coordinaries
    inFile.close();
    delete filename;
}

void inputParPhi(Particle &particle, int fileNum) {
    ifstream inFile;
    char *fileAddress;
    char *filename;
    fileAddress = catStrStr(inputAddress, "particleO_");
    filename = catStrIntStr(fileAddress, fileNum+1, ".txt");
    fileAddress = catStrStr(inputAddress, "phi");
    filename = catStrIntStr(fileAddress, fileNum+1, ".txt");
    openFile(filename, inFile);

    for (int j=0; j< 3*particle.numAA-5; j+=3){          // last : j=3*numAA-6; j+2=3*numAA-4
        inFile >> particle.Position[j] ;
        particle.Position[j+1] = 180;
        inFile >> particle.Position[j+2] ;
    }

    inFile.close();
    particle.sizeOfPosition = 3*particle.numAA-3;
}