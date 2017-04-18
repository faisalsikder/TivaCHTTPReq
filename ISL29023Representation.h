/*
 * ISL29023Representation.h
 *
 *  Modified on: Feb 21, 2015
 *      Author: Faisal Sikder
 */

#ifndef ISL29023REPRESENTATION_H_
#define ISL29023REPRESENTATION_H_

#include "framework/Template.h"

REPRESENTATION(ISL29023Representation)
class ISL29023Representation: public ISL29023RepresentationBase
{
  public:
    float fAmbient;
    ISL29023Representation() :
        fAmbient(0)
    {
    }

};

#endif /* ISL29023REPRESENTATION_H_ */
