#include <Arduino.h>
#include <OneWire.h>

#include "log.h"
#include "schedule.h"
#include "output.h"

extern OneWire *ds;
extern struct output outputs[];
extern unsigned char output_count;

void output_init(unsigned char pin)
	{
	unsigned char i;
	struct output *o;

	if (!ds)
		ds = new OneWire(pin);

	for (i = 0; i < output_count; i++)
		{
		o = outputs + i;
		log_msg("Init %u %u", i, o->init);
		set_output(i, o->init);
		switch (o->type)
			{
			case OUTPUT_TYPE_ARDUINO:
			case OUTPUT_TYPE_ESP:
				pinMode(o->pin, OUTPUT);
				break;
			case OUTPUT_TYPE_AVR:
				*(o->data.avr.port) |= (1 << o->pin);
				break;
			case OUTPUT_TYPE_DS2408:
				break;
			default:
				break;
			}
		}
	log_msg("All outputs set up.");
	}

void set_output(unsigned char output_num, unsigned char state)
	{
	struct output *o = outputs + output_num;
	unsigned char mask;

	if (o->type == OUTPUT_TYPE_ARDUINO)
		digitalWrite(o->pin, state);
	else if (o->type == OUTPUT_TYPE_AVR)
		{
		mask = (1 << o->pin);
		if (state)
			*(o->data.avr.port) |= mask;
		else
			*(o->data.avr.port) &= ~mask;
		}
	else if (o->type == OUTPUT_TYPE_ESP)
		{
		if (state)
			GPOS |= (1 << o->pin);
		else
			GPOC |= (1 << o->pin);
		}
	else if (o->type == OUTPUT_TYPE_DS2408)
		{
		ds->reset();
		ds->select(o->data.ds2408_addr);
		ds->write(0xF0, 1);
		ds->write(0x88, 1);
		ds->write(0x00, 1);
		mask = ds->read();
		if (state)
			mask &= ~(1 << o->pin);
		else
			mask |= (1 << o->pin);
		ds->reset();
		ds->select(o->data.ds2408_addr);
		ds->write(0x5A, 1);
		ds->write(mask, 1);
		ds->write(~mask, 1);
		if (ds->read() != 0xAA)
			log_msg("Write failed.");
		else
			ds->read();
		}
	}

