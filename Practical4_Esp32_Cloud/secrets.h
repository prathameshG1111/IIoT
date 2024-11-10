#ifndef SECRETS_H
#define SECRETS_H

#include <pgmspace.h>

#define SECRET
#define THINGNAME "test"

const char WIFI_SSID[] = "PUT UR WIFI SSID";
const char WIFI_PASSWORD[] = "WIFI KA PASSWORD";
const char AWS_IOT_ENDPOINT[] = "AWS DOMAIN THAT YOU COPIED";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";

// Device Certificate                                               
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)KEY";

// Device Private Key                                               
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----
)KEY";

#endif
