#pragma once

#include "cudaType_CPU.h"
#include "Variateur_CPU.h"
#include "Fractale.h"

#include "math/JuliaMath.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Julia: public Fractale
    {

	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	Julia(uint w, uint h, uint nMin, uint nMax, float c1, float c2, const DomaineMath& domaineMath);

	virtual ~Julia(void);

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
 /*----------------------------------------------------------------------*/
