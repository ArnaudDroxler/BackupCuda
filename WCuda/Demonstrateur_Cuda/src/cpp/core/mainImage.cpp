#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Device.h"
#include "cudaTools.h"

#include "RipplingProvider.h"
#include "MandelbrotProvider.h"
#include "JuliaProvider.h"
#include "RayTracingProvider.h"

#include "Settings_GPU.h"
#include "Viewer_GPU.h"
using namespace gpu;

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainImage(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainImage(Settings& settings)
    {
    cout << "\n[Image] mode" << endl;

    GLUTImageViewers::init(settings.getArgc(), settings.getArgv()); //only once

    GLUTWindowManagers* windowManager = GLUTWindowManagers::getInstance();

    ImageOption zoomable(true, true, false, false);
    ImageOption nozoomable(false, true, false, false);

    // Censé placer toutes les fenetres sur une ligne cote a cote

    Viewer<RipplingProvider> rippling(nozoomable, 0, 0);
    rippling.setSize(480, 270);
    Viewer<MandelbrotProvider> mandelbrot(zoomable, 480, 0);
    mandelbrot.setSize(480, 270);
    Viewer<JuliaProvider> julia(zoomable, 960, 0);
    julia.setSize(480, 270);
    Viewer<RayTracingProvider> rayTracing(nozoomable, 1440, 0);
    rayTracing.setSize(480, 270);

    // Common
    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    cout << "\n[Image] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

