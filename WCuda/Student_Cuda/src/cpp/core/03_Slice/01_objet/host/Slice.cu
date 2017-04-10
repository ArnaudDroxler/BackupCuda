#include "Slice.h"

#include <iostream>

#include "Device.h"

using std::cout;
using std::endl;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void slice(float* ptrDevGMResult, uint nbSlice);

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

Slice::Slice(const Grid& grid, float* ptrResult, int nbSlice)
    {
    this->ptrResult = ptrResult;
    this->nbSlice = nbSlice;
    this->sizeOctetGM = sizeof(float); // octet
    this->sizeOctetSM = grid.db.x * sizeof(float);

    // MM
	{

	// MM (malloc Device)
	    {
	    Device::malloc(&ptrDevResult, sizeOctetGM);
	    Device::memclear(ptrDevResult, sizeOctetGM);
	    }
	}

    // Grid
	{
	this->dg = grid.dg;
	this->db = grid.db;
	}
    }

Slice::~Slice(void)
    {
    //MM (device free)
	{
	Device::free(ptrDevResult);
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Slice::run()
    {
    Device::lastCudaError("slice (before)"); // temp debug
    slice<<<dg,db, sizeOctetSM>>>(ptrDevResult, nbSlice); // assynchrone
    Device::lastCudaError("slice (after)"); // temp debug

    Device::synchronize(); // Temp,debug, only for printf in  GPU

    // MM (Device -> Host)
	{
	Device::memcpyDToH(ptrResult, ptrDevResult, sizeOctetGM); // barriere synchronisation implicite
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
