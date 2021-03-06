/*
 * Copyright (c) 2012, Sensor Nets Laboratory, University of Geneva.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/**
 * \file
 *      Common service implementation
 * \authors
 *      Kasun Samarasinghe <Kasun.Wijesiriwardana@unige.ch>
 *			Orestis Evangelatos <Orestis.Evangelatos@unige.ch>
 *
 *
 *		Services supported by the light_temp_sens_sens sensor: eg: coap://[IPV6 address]:PORT/light_temp_sens_sens?status=on
 *		light_temp_sens_sens?status=on			> switch on light_temp_sens_sens
 *		light_temp_sens_sens?status=off			> switch off light_temp_sens_sens
 *		on					> switch on light_temp_sens_sens
 *		off					> switch off light_temp_sens_sens
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contiki.h"
#include "contiki-net.h"
#include "erbium.h"

#include "dev/leds.h"

#if WITH_COAP == 12
#include "er-coap-12.h"
#elif WITH_COAP == 7
#include "er-coap-07.h"
#else
#endif 

#include "ero2manager.h"
#include "ero2service.h"
#include "ero2registry.h"

//#include "telosb-sensors.h"
//#include "dev/light_temp_sens-sensor.h"

//int flag=0;
struct ero2_service light_temp_sens_sens_service;
struct ero2_service turnon_service;
struct ero2_service turnoff_service;



RESOURCE(light_temp_sens_sens, METHOD_GET, "light_temp_sens_sens", "title=\"light_temp_sens_sens?status=on/off..\";rt=\"Text\"");
void light_temp_sens_sens_handler(void* request, void* response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[10];
	const char *status = NULL;


	printf("I am printing and toggling\n");
	//leds_toggle(LEDS_BLUE);
	//SetActuator(1);
	//SetActuator(2);

	//light_temp_sens value
	//SENSORS_ACTIVATE(light_temp_sens_sensor);
	//int light_temp_sensValue = 10* light_temp_sens_sensor.value(light_temp_sens_SENSOR_PHOTOSYNTHETIC) /7;
//printf("light_temp_sens value = %d",light_temp_sensValue);
	if ((len=REST.get_query_variable(request, "status", &status))) {
		  PRINTF("status %.*s\n", len, status);


		  if (strncmp(status, "on", len)==0){	
				//ActuatorON(1);
				//ActuatorON(2);
				//flag=1;
				int light_temp_sensValue = 00;
				//sprintf(message,"_sens light_temp_sens_sens= OPEN");
				printf("message is %s\n",message);
				snprintf(message, 4, "%d", GetSensorLightSolar());
				memcpy(buffer, message, 4);
				leds_on(LEDS_GREEN);
				leds_off(LEDS_RED);
				//process_start(&timer_process,NULL);
			}else{
				//ActuatorOFF(1);
				//ActuatorOFF(2);		
				//flag=0;
				//sprintf(message,"light_temp_sens_sens lock= CLOSED");
				printf("message is %s\n",message);
				memcpy(buffer, "OFF", 4);
				leds_off(LEDS_GREEN);
				leds_on(LEDS_RED);
			}
}
  REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
  REST.set_header_etag(response,10, 1);
  REST.set_response_payload(response, buffer, 9);
}



RESOURCE(turnon, METHOD_GET, "turnon", "title=\"turnon.\";rt=\"Text\"");
void turnon_handler(void* request, void* response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[8];
	const char *status = NULL;


	printf("Printing the TURNON\n");
	
	//SetActuator(1);
	//SetActuator(2);

				//ActuatorON(1);
				//ActuatorON(2);
				leds_on(LEDS_GREEN);
				leds_off(LEDS_RED);
				memcpy(buffer, "on", 3);

  REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
  REST.set_header_etag(response,10, 1);
  REST.set_response_payload(response, buffer, 3);
}


RESOURCE(turnoff, METHOD_GET, "turnoff", "title=\"turnoff\";rt=\"Text\"");
void turnoff_handler(void* request, void* response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[8];
	const char *status = NULL;


	//printf("Printing the TURNOFF\n");
	
	//SetActuator(1);
	//SetActuator(2);

				//ActuatorOFF(1);
				//ActuatorOFF(2);
				leds_off(LEDS_GREEN);
				leds_on(LEDS_RED);
				memcpy(buffer, "off", 4);

  REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
  REST.set_header_etag(response,10, 1);
  REST.set_response_payload(response, buffer, 4);
}



void start_app_services()
{
	
	rest_init_engine();
/* light_temp_sens_sens service */
	rest_activate_resource(&resource_light_temp_sens_sens);
	light_temp_sens_sens_service.name="light_temp_sens_sens";	
	light_temp_sens_sens_service.uri="light_temp_sens_sens";
	light_temp_sens_sens_service.request_method="COAP_GET";	
	add_to_local_registry(&light_temp_sens_sens_service);

/* turnon service used for triggering the service from a sensor automatically (distributed way) */
	rest_activate_resource(&resource_turnon);
	turnon_service.name="turnon";	
	turnon_service.uri="turnon";
	turnon_service.request_method="COAP_GET";	
	add_to_local_registry(&turnon_service);
	//printf("turnon service printing");

/* turnoff service used for triggering the service from a sensor automatically (distributed way) */

	rest_activate_resource(&resource_turnoff);
	turnoff_service.name="turnoff";	
	turnoff_service.uri="turnoff";
	turnoff_service.request_method="COAP_GET";	
	add_to_local_registry(&turnoff_service);
	//printf("turnoff service printing");




}
