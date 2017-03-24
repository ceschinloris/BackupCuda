#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"
#include "IndiceTools_GPU.h"
#include "DomaineMath_GPU.h"

#include "math/JuliaMath.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void julia(float c1, float c2, uchar4* ptrDevPixels, uint w, uint h, float t, DomaineMath domaineMath);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void julia(float c1, float c2, uchar4* ptrDevPixels, uint w, uint h, float t, DomaineMath domaineMath)
    {
    JuliaMath juliaMath = JuliaMath(t, c1, c2);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    int s = TID;
    int i, j;
    double x, y;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j);
	domaineMath.toXY(i, j, &x, &y);

	juliaMath.colorXY(&ptrDevPixels[s], x, y, t);

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

