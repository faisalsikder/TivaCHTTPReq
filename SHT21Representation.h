/*
 * SHT21Representation.h
 *
 *  Modified on: Feb 21, 2015
 *      Author: Faisal Sikder
 */

#ifndef SHT21REPRESENTATION_H_
#define SHT21REPRESENTATION_H_

#include "framework/Template.h"

REPRESENTATION(SHT21Representation)
class SHT21Representation: public SHT21RepresentationBase
{
  public:
    float fHumidity;
    float fTemperature;
    SHT21Representation() :
        fHumidity(0), fTemperature(0)
    {
    }
};

#endif /* SHT21REPRESENTATION_H_ */
