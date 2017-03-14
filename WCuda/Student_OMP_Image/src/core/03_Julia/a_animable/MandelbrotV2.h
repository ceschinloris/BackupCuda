#pragma once

#include "cudaType_CPU.h"
#include "Variateur_CPU.h"
#include "Fractale.h"

#include "math/MandelbrotV2Math.h"
using namespace cpu;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotV2: public Fractale
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	MandelbrotV2(uint w, uint h, uint nMin, uint nMax, const DomaineMath& domaineMath);

	virtual ~MandelbrotV2(void);

	/*--------------------------------------*\
	 |*		Methode			*|
	 \*-------------------------------------*/

    public:
	virtual FractaleMath* getFractaleMath();


	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/
    };


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
