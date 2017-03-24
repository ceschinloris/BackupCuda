#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
#include "Calibreur_GPU.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class JuliaMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ JuliaMath(uint n, float c1, float c2) :
		calibreur(Interval<float>(0.f, n), Interval<float>(0.f, 1.f))
	    {
	    this->c1 = c1;
	    this->c2 = c2;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__ ~JuliaMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/
    public:

    	__device__ void colorXY(uchar4* ptrColor, float x, float y, int t)
    	    {
    	    float z = f(x, y, t);

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

    private:
	__device__ float f(float x, float y, int t)
	    {
	    float a = x;
	    float b = y;
	    float aCopy;

	    for (int i = 0; i < t; i++)
		{
		aCopy = a;
		a = (a * a - b * b) + c1;
		b = 2.f * aCopy * b + c2;

		if (a * a + b * b > 4.f)
		    return i;
		}
	    return t;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	float c1;
	float c2;

	// Tools
	Calibreur<float> calibreur;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
