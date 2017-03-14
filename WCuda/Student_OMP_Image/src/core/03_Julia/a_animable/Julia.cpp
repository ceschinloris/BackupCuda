#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"

#include "Julia.h"
#include "math/JuliaMath.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Julia::Julia(uint w, uint h, uint nMin, uint nMax, float c1, float c2, const DomaineMath& domaineMath) :
	Fractale(w, h, nMin, nMax, domaineMath)
    {
    this->ptrFractaleMath = new JuliaMath(nMin, c1, c2);
    }

Julia::~Julia(void)
    {
    delete this->ptrFractaleMath;
    }

FractaleMath* Julia::getFractaleMath()
    {
    return this->ptrFractaleMath;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

