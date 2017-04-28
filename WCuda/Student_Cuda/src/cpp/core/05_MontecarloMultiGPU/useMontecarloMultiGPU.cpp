#include <iostream>
#include "Grid.h"
#include "Device.h"
#include "MathTools.h"
#include "Chrono.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "host/MontecarloMultiGPU.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarloMultiGPU(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarloMultiGPU()
    {
    long nbDarts = INT_MAX * 5;
    float m = 20;
    double result;

    // Grid cuda
    int mp = Device::getMPCount();

    dim3 dg = dim3(mp, 1, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    dim3 db = dim3(64, 1, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    Grid grid(dg, db);

    MontecarloMultiGPU montecarloMultiGPU(grid, &result, nbDarts, m);

    Chrono c = Chrono();
    montecarloMultiGPU.run();
    c.stop();
    std::cout<<"Resultat MontecarloMultiGPU = "<<result;
    c.print();

    bool isOk = MathTools::isEquals(result, PI, 1e-1);


    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

