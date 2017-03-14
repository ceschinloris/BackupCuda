#include "MandelbrotV2.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"

#include "math/MandelbrotV2Math.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

MandelbrotV2::MandelbrotV2(uint w, uint h, uint nMin, uint nMax, const DomaineMath& domaineMath) :
	Fractale(w, h, nMin, nMax, domaineMath)
    {
    this->ptrFractaleMath = new MandelbrotV2Math(nMin);
    }

MandelbrotV2::~MandelbrotV2(void)
    {
    delete this->ptrFractaleMath;
    }

FractaleMath* MandelbrotV2::getFractaleMath()
    {
    return this->ptrFractaleMath;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

