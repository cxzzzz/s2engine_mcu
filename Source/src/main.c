
extern int _main_s2chip(void);

extern int dma_test(void);

extern int reg_test(void);

extern int wm_test(void);

extern int fm_test(void);

extern int net_test(void);

extern int sdram_test(void);

extern int basic_test(void);

extern int ofifo_test(void);

extern int pad_power_test(void);


extern int nms_test(void);
int main(){
		//FM_IRQ_Handler();
		//while(1);
		_main_s2chip();
    //dma_test();
    //reg_test();
    //wm_test(); 
    //fm_test();
    //pe_test();
		//ppu_test();
		//net_test();
	  //sdram_test();
		//basic_test();
		//ofifo_test();
		//nms_test();
		//pad_power_test();
}
