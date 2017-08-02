HEADERS = paraDef.h structDef.h Matrix.h MOPSO.h

Object =  coordinaryTransform.o    fileDisposal.o    initialization.o \
          main.o    matrixFunction.o    MOPSOAidFunction.o    \
          MOPSOFunction.o    \
	setTime.o     preDispose.o  multiplyBetterInput.o\
       	disposedCodes.o	 seiveRep.o  inputParticles.o  createRep.o\
	Debug.o	freeUpSpace.o	applyVariables.o addressDef.o\
	mpiFunction.o randFixedSum.o Matrix.o

default : MOPSO_mpi

MOPSO_mpi : $(Object)
	mpiCC $(Object) -o MOPSO_mpi

coordinaryTransform.o :
	mpiCC -c coordinaryTransform.cpp -o coordinaryTransform.o

fileDisposal.o :
	mpiCC -c fileDisposal.cpp -o fileDisposal.o
	
initialization.o :
	mpiCC -c initialization.cpp -o initialization.o
	
main.o :
	mpiCC -c main.cpp -o main.o
	
matrixFunction.o :
	mpiCC -c matrixFunction.cpp -o matrixFunction.o
	
MOPSOAidFunction.o :
	mpiCC -c MOPSOAidFunction.cpp -o MOPSOAidFunction.o

MOPSOFunction.o :
	mpiCC -c MOPSOFunction.cpp -o MOPSOFunction.o
	
setTime.o :
	mpiCC -c setTime.cpp -o setTime.o
	
preDispose.o :
	mpiCC -c preDispose.cpp -o preDispose.o
	
multiplyBetterInput.o :
	mpiCC -c multiplyBetterInput.cpp -o multiplyBetterInput.o
	
disposedCodes.o :
	mpiCC -c disposedCodes.cpp -o disposedCodes.o
	
seiveRep.o :
	mpiCC -c seiveRep.cpp -o seiveRep.o

inputParticles.o :
	mpiCC -c inputParticles.cpp -o inputParticles.o
	
createRep.o :
	mpiCC -c createRep.cpp -o createRep.o

Debug.o :
	mpiCC -c Debug.cpp -o Debug.o
	
freeUpSpace.o :
	mpiCC -c freeUpSpace.cpp -o freeUpSpace.o
	
applyVariables.o :
	mpiCC -c applyVariables.cpp -o applyVariables.o
	
Matrix.o :
	mpiCC -c Matrix.cpp -o Matrix.o

randFixedSum.o :
	mpiCC -c randFixedSum.cpp -o randFixedSum.o
	
mpiFunction.o :
	mpiCC -c mpiFunction.cpp -o mpiFunction.o
	
addressDef.o :
	mpiCC -c addressDef.cpp -o addressDef.o

clear :
	-rm *o MOPSO_mpi