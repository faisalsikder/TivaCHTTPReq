/*
 * HTTPRequestModule.h
 *
 *  Created on: Oct 3, 2015
 *      Author: faisal
 */

#ifndef HTTPREQUESTMODULE_H_
#define HTTPREQUESTMODULE_H_

#include "framework/Template.h"


#include "SHT21Module.h"
#include "BMP180Module.h"
#include "ISL29023Module.h"


MODULE(HTTPRequestModule)
  REQUIRES(ISL29023Representation) 
  REQUIRES(BMP180Representation)   
  REQUIRES(SHT21Representation)
END_MODULE
class HTTPRequestModule: public HTTPRequestModuleBase
{
  public:
    void execute();
	void init();
  private:
	void print_value_in_fraction(float);
	void localLoop();
	void httpRequest();
        void readmac(byte mac[],int32_t user0,int32_t user1);
	
};

#endif /* TESTMODULEPRINTDATA_H_ */
