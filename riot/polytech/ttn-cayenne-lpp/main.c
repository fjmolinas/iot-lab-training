#include <string.h>

#include "xtimer.h"

#include "net/loramac.h"
#include "semtech_loramac.h"

#include "lm75.h"
#include "lm75_params.h"

#include "board.h"

/* TODO: Add the cayenne_lpp header here */


/* Declare globally the loramac descriptor */
extern semtech_loramac_t loramac;

/* Declare globally the sensor device descriptor */
static lm75_t lm75;

/* TODO: Declare globally Cayenne LPP descriptor here */


/* Device and application informations required for OTAA activation */
static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

static void sender(void)
{
    while (1) {
        /* wait 20 secs */
        xtimer_sleep(20);

        /* do some measurements */
        int temperature = 0;
        if (lm75_get_temperature(&lm75, &temperature)!= LM75_SUCCESS) {
            puts(" -- failed to read temperature!");
        }

        /* TODO: prepare cayenne lpp payload here */


        printf("Sending LPP data\n");

        /* send the LoRaWAN message */
        uint8_t ret = semtech_loramac_send(&loramac, (uint8_t *)message, strlen(message));
        if (ret != SEMTECH_LORAMAC_TX_DONE) {
            printf("Cannot send lpp message, ret code: %d\n", ret);
        }

        /* TODO: clear buffer once done here */

    }

    /* this should never be reached */
    return;
}

int main(void)
{
    if (lm75_init(&lm75, &lm75_params[0]) != LM75_SUCCESS) {
        puts("Sensor initialization failed");
        return 1;
    }

    /* use a fast datarate so we don't use the physical layer too much */
    semtech_loramac_set_dr(&loramac, 5);

    /* set the LoRaWAN keys */
    semtech_loramac_set_deveui(&loramac, deveui);
    semtech_loramac_set_appeui(&loramac, appeui);
    semtech_loramac_set_appkey(&loramac, appkey);

    /* start the OTAA join procedure */
    puts("Starting join procedure");
    if (semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA) != SEMTECH_LORAMAC_JOIN_SUCCEEDED) {
        puts("Join procedure failed");
        return 1;
    }

    puts("Join procedure succeeded");

    /* call the sender function */
    sender();

    return 0;
}
