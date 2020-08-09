
#include "defs.h"
#include "int_handler.h"


void int_init(){
    //将接口设置为上升沿触发(还是高电平触发?) 

    CM3DS_MPS2_gpio_SetIntHighLevel(CM3DS_MPS2_GPIO0, 7);   //set pin 7 to high level interrupts
    CM3DS_MPS2_gpio_SetIntLowLevel(CM3DS_MPS2_GPIO0, 8);    //set pin 8 to low level interrupts
    CM3DS_MPS2_gpio_SetIntRisingEdge(CM3DS_MPS2_GPIO0, 9);  //set pin 9 to rising edge interrupts
    CM3DS_MPS2_gpio_SetIntFallingEdge(CM3DS_MPS2_GPIO0, 10)

}


