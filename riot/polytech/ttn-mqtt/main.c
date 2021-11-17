#include <string.h>

#include "board.h"
#include "xtimer.h"

#include "net/loramac.h"        /* core loramac definitions */
#include "semtech_loramac.h"    /* package API */

#include "lm75.h"
#include "lm75_params.h"


/* Declare globally the loramac descriptor */
extern semtech_loramac_t loramac;

/* Declare globally the sensor device descriptor */
static lm75_t lm75;

static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


int main(void)
{
    /* initialize the LM75A sensor */
    if (lm75_init(&lm75, &lm75_params[0]) != LM75_SUCCESS) {
        puts("Sensor initialization failed");
        return 1;
    }

    /* configure the device parameters */
    semtech_loramac_set_deveui(&loramac, deveui);
    semtech_loramac_set_appeui(&loramac, appeui);
    semtech_loramac_set_appkey(&loramac, appkey);

    /* change datarate to DR5 (SF7/BW125kHz) */
    semtech_loramac_set_dr(&loramac, 5);

    /* start the OTAA join procedure */
    if (semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA) != SEMTECH_LORAMAC_JOIN_SUCCEEDED) {
        puts("Join procedure failed");
        return 1;
    }
    puts("Join procedure succeeded");


    while (1) {
        /* do some measurements */
        int temperature = 0;
        if (lm75_get_temperature(&lm75, &temperature) != LM75_SUCCESS) {
            puts(" -- failed to read temperature!");
        }

        char message[64];
        sprintf(message, "T:%d.%dC",
                (temperature / 1000), (temperature % 1000));
        printf("Sending message '%s'\n", message);

        /* send the message here */
        if (semtech_loramac_send(&loramac,
                                 (uint8_t *)message, strlen(message)) != SEMTECH_LORAMAC_TX_DONE) {
            printf("Cannot send message '%s'\n", message);
        }
        else {
            printf("Message '%s' sent\n", message);
        }

        /* wait 30 seconds between each message */
        xtimer_sleep(30);
    }

    return 0; /* should never be reached */
}
