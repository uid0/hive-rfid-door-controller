#ifndef __CONFIG_H
#define __CONFIG_H

#include "config_local.h"

#define BEEP_PIN  D8
#define D0_PIN    D1
#define D1_PIN    D2
#define LIGHT_PIN D0
#define OPEN_PIN  D3
#define DOOR_PIN  D4

#define LIGHT_INV
#define BEEP_INV

/* Number of ms */
#define DOOR_OPEN_TIME 5000

#define HTTP_HOST "http://intweb.at.hive13.org/api/access"

#endif /* __CONFIG_H */