/*
 * ISL29023Module.h
 *
 *  Modified on: Feb 21, 2015
 *      Author: Faisal Sikder
 */

#ifndef ISL29023MODULE_H_
#define ISL29023MODULE_H_

#include "framework/Template.h"
#include "framework/InterruptVectorRepresentation.h"
#include "ISL29023Representation.h"

MODULE(ISL29023Module)
  REQUIRES(InterruptVectorRepresentation) //
  PROVIDES(ISL29023Representation) //
END_MODULE
class ISL29023Module: public ISL29023ModuleBase
{
  public:
    void init();
    void update(ISL29023Representation& theISL29023Representation);
};



#endif /* ISL29023MODULE_H_ */
