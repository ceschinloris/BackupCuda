#include "FractaleMath.h"
#include <math.h>
#include "MathTools.h"

using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
/*--------------------------------------*\
	|*		Constructor		*|
 \*-------------------------------------*/
FractaleMath::FractaleMath(uint n) :
	calibreur(Interval<float>(0, n), Interval<float>(0, 1))
    {
    this->n = n;
    }

FractaleMath::~FractaleMath(void)
    {
    // rien
    }

/*--------------------------------------*\
	|*		Methodes		*|
 \*-------------------------------------*/
void FractaleMath::colorXY(uchar4* ptrColor, float x, float y, float t)
    {
    int z = f(x, y, t);

    if (z == t)
	{
	ptrColor->x = 0;
	ptrColor->y = 0;
	ptrColor->z = 0;
	}
    else
	{
	float hue01 = z;
	calibreur.calibrer(hue01);
	ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
	}

    ptrColor->w = 255; // opaque
    }

bool FractaleMath::isStop(float a, float b)
    {
    return (a * a + b * b > 4);
    }

void FractaleMath::setN(uint n)
    {
    this->n = n;
    }
/*--------------------------------------*\
	|*		Attributs		*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
