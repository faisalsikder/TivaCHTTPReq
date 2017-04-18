/*
 * SHT21Module.h
 *

 *  Modified on: Feb 21, 2015
 *      Author: Faisal Sikder
 */

#include "framework/Template.h"
#include "SHT21Representation.h"

MODULE(SHT21Module)
  PROVIDES(SHT21Representation) //
END_MODULE
class SHT21Module: public SHT21ModuleBase
{
  public:
    void init();
    void update(SHT21Representation& theSHT21Representation);
    double getHumidity();
    double getTemperature();
};

