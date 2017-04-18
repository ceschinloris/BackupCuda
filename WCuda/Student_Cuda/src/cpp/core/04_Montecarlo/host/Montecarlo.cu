#include "Montecarlo.h"

#include <iostream>

#include "Device.h"
#include <curand_kernel.h>

using std::cout;
using std::endl;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void createGenerator(curandState* tabDevGeneratorGM, int deviceId);
extern __global__ void montecarlo(curandState* tabDevGeneratorGM, long nbDarts, uint m, long* ptrDevNxTotal);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

Montecarlo::Montecarlo(const Grid& grid, long nbDartsTotal, float m)
    {
    this->result = 0;
    this->nbDartsTotal = nbDartsTotal;
    this->m = m;
    this->sizeOctetResultGM = sizeof(long); // octet
    this->sizeOctetGeneratorsGM = Device::nbThread(grid) * sizeof(curandState);
    this->sizeOctetSM = Device::nbThread(grid) * sizeof(uint);

    // MM
	{

	// MM (malloc Device)
	    {
	    Device::malloc(&ptrDevResult, sizeOctetResultGM);
	    Device::memclear(ptrDevResult, sizeOctetResultGM);

	    Device::malloc(&ptrDevGenerators, sizeOctetGeneratorsGM);
	    Device::memclear(ptrDevGenerators, sizeOctetGeneratorsGM);
	    }
	}

    // Grid
	{
	this->dg = grid.dg;
	this->db = grid.db;
	}

    // Generators creation
    createGenerator<<<dg,db>>>(ptrDevGenerators, Device::getDeviceId()); // assynchrone

    // Calculate the number of darts for each threads
    this->nbDarts = nbDartsTotal / Device::nbThread(grid);

    this->nbDartsUnder = 0;
    }

Montecarlo::~Montecarlo(void)
    {
    //MM (device free)
	{
	Device::free(ptrDevResult);
	Device::free(ptrDevGenerators);
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Montecarlo::run()
    {
    Device::lastCudaError("montecarlo (before)"); // temp debug
    montecarlo<<<dg,db, sizeOctetSM>>>(ptrDevGenerators, nbDarts, m, ptrDevResult); // assynchrone
    Device::lastCudaError("montecarlo (after)"); // temp debug

    Device::synchronize(); // Temp,debug, only for printf in  GPU

    long montecarloResult;

    // MM (Device -> Host)
	{
	Device::memcpyDToH(&montecarloResult, ptrDevResult, sizeOctetResultGM); // barriere synchronisation implicite
	}

    nbDartsUnder = montecarloResult;
    result = (double)montecarloResult / (double) nbDartsTotal * m;
    }

long Montecarlo::getNbDartsUnder()
    {
    return nbDartsUnder;
    }

double Montecarlo::getResult()
    {
    return result;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
