#ifndef SPHERE_H
#define SPHERE_H
#include "cudaTools.h"
#include "MathTools.h"

class Sphere
    {
    public:
	__host__ Sphere(float3 centre, float rayon, float hue)
	    {
	    // Inputs
	    this->centre = centre;
	    this->r = rayon;
	    this->hueStart = hue;
	    // Tools
	    this->rCarre = rayon * rayon;
	    }

	/**
	 * required by example for  new Sphere[n]
	 */
	__host__ Sphere()
	    {
	    // rien
	    }

	__device__
	float hCarre(float x, float y)
	    {
	    float a = (centre.x - x);
	    float b = (centre.y - y);
	    return a * a + b * b;
	    }

	__device__
	bool isEnDessous(float hCarre)
	    {
	    return hCarre < rCarre;
	    }

	__device__
	float dz(float hCarre)
	    {
	    return sqrtf(rCarre - hCarre);
	    }

	__device__
	float brightness(float dz)
	    {
	    return dz / r;
	    }

	__device__
	float distance(float dz)
	    {
	    return centre.z - dz;
	    }

	__device__
	float getHueStart()
	    {
	    return hueStart;
	    }

	__device__
	float hue(float t) // usefull for animation
	    {
	    return 0.5f + 0.5f * sinf(t + hueStart + 3.f * PI_FLOAT / 2.f);
	    }

    private:
	// Inputs
	float r;
	float3 centre;
	float hueStart;

	// Tools
	float rCarre;
    };
#endif
