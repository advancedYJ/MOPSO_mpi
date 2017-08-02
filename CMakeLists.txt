cmake_minimum_required(VERSION 3.5)
project(mpi_MOPSO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -pthread")

set(SOURCE_FILES
    CMakeLists.txt
    coordinaryTransform.cpp
    fileDisposal.cpp
    initialization.cpp
    main.cpp
    matrixFunction.cpp
    MOPSO.h
    MOPSOAidFunction.cpp
    MOPSOFunction.cpp
        setTime.cpp
        preDispose.cpp
        multiplyBetterInput.cpp
        disposedCodes.cpp
        seiveRep.cpp
        inputParticles.cpp
        createRep.cpp
        checkSimilarity.cpp
        Debug.cpp
        freeUpSpace.cpp
        applyVariables.cpp
        Matrix.cpp
        randFixedSum.cpp mpiFunction.cpp Matrix.h addressDef.cpp paraDef.h structDef.h)

add_executable(mpi_MOPSO ${SOURCE_FILES} setTime.cpp preDispose.cpp multiplyBetterInput.cpp disposedCodes.cpp seiveRep.cpp inputParticles.cpp Matrix.cpp randFixedSum.cpp)

include_directories("/usr/include/mpi")
find_package(MPI REQUIRED)
SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)