//
// Project 		SAAB-CDC
//
//
//

#ifndef CDC_H
#define CDC_H

//----------------------------------------------------------------------------
// CLASS
//----------------------------------------------------------------------------

class CDCClass
{
public:
    void print_can_tx_frame();
    void print_can_rx_frame();
    void initialize_atmel_pins();
    void open_can_bus();
    void start_bt_signal(int pin, unsigned long timeout);
    void test_bt();
    void handle_rx_frame();
    void handle_ihu_buttons();
    void handle_steering_wheel_buttons();
    void handle_cdc_status();
    void send_cdc_status(boolean event, boolean remote);
    void send_display_request();
    void send_serial_message(int *msg);
    void send_can_frame(int message_id, int *msg);
    void write_text_on_display(char text[]);
    void update_bt_signal();
};

//----------------------------------------------------------------------------
// VARIABLES
//----------------------------------------------------------------------------

extern CDCClass CDC;

#endif
