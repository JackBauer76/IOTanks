#include <VirtualWire.h>

const int led_pin = 4;
const int transmit_pin = 11;
const int receive_pin = 2;
const int transmit_en_pin = 3;

void setup()
{
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);   // Bits per sec
}

byte count = 1;

void loop()
{
  char msg[7] = {'h','e','l','l','o',' ','#'};

// sending several bytes instead
  uint8_t msg2[7] = {200, 400, 35, 12, 34, 233, 213}; // sending now bytes instead of chars
  byte msg2[7] = {200, 400, 35, 12, 34, 233, 213}; // sending now bytes instead of chars

  msg[6] = count;
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 7);
  
  vw_send((uint8_t *)msg2, 7); //??
  
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  delay(1000);
  count = count + 1;
}
