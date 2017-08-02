//
// Created by advanced on 17-5-31.
//

#include "paraDef.h"
#include "MOPSO.h"

//  the address of the input data
const char rootAddress[] = "/home/advanced/MOPSO/";
const char *energyFileAddress = catStrStr(rootAddress, "data/energyFile/");
const char *tempFileAddress   = catStrStr(energyFileAddress, "tempFile/");
const char *defaultFileAddress = catStrStr(energyFileAddress, "defaultFile/");
const char *QUACKoutFileAddress= catStrStr(energyFileAddress, "QUACKoutFile/");
const char *charmmFileAddress = catStrStr(rootAddress, "charmm/exec/gnu/");
const char *refine_1Address   = catStrStr(rootAddress, "refine/");
const char *TM_scoreAddress   = catStrStr(rootAddress, "TM_score/");
const char *scoreAddress      = catStrStr(rootAddress, "rosetta/main/source/bin/score.linuxgccrelease");
const char *databaseAddress   = catStrStr(rootAddress, "rosetta/main/database/");
const char *mybinAddress      = catStrStr(rootAddress, "calRWplus/");
const char *strideAddress     = catStrStr(rootAddress, "stride/");



//const char *answerAddress     = catStrStr(rootAddress, "data/answer/newAnswer/");
//const char *charmmFileAddress = catStrStr(energyFileAddress, "charmmFile/");
//const char inputAddress[]="/home/ws/zzZyj/MOPSO/data/input/test_thread";
//const char *inputAddress      = catStrStr(rootAddress, "data/input/originpdb/");
//const char *mybinAddress      = catStrStr(rootAddress, "mybin/");