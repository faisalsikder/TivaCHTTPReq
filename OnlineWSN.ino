/*
 * Main file
 *
 *  Created on: Feb 21, 2015
 *      Author: Faisal Sikder
 */

#include <framework/Framework.h>
#include <Ethernet.h>

void setup()
{
  Controller::getInstance().setup(115200/*UART0_baud_rate*/, true/*LPRF*/);
}

void loop()
{
  Controller::getInstance().loop();
  delay(297000);
}


