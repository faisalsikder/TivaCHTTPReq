/*
 * BMP180Representation.h
 *
 *  Modified on: Feb 21, 2015
 *      Author: Faisal Sikder
 */

#ifndef BMP180REPRESENTATION_H_
#define BMP180REPRESENTATION_H_

#include "framework/Template.h"

REPRESENTATION(BMP180Representation)
class BMP180Representation: public BMP180RepresentationBase
{
  public:
    float fTemperature, fPressure, fAltitude;

    BMP180Representation() :
        fTemperature(0), fPressure(0), fAltitude(0)
    {
    }
};

#endif /* BMP180REPRESENTATION_H_ */
