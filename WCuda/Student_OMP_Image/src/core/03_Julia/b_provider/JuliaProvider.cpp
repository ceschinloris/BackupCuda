#include "Julia.h"

#include "MathTools.h"

#include "ImageAnimable_CPU.h"
#include "DomaineMath_CPU.h"

#include "JuliaProvider.h"
using namespace cpu;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

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
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Surcharge		*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* JuliaProvider::createAnimable(void)
    {
    DomaineMath domaineMath = DomaineMath(-1.7, -1.2, 1.7, 1.2);

    // Animation
    int nMin = 30;
    int nMax = 100;

    // Dimension
    int dw = 16 * 60 * 2;
    int dh = 16 * 60;

    // Facteur julia
    float c1 = -0.57;
    float c2 = 0.52;

    return new Julia(dw, dh, nMin, nMax, c1, c2, domaineMath);
    }

/**
 * Override
 */
Image_I* JuliaProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageAnimable_RGBA_uchar4(createAnimable(),colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
