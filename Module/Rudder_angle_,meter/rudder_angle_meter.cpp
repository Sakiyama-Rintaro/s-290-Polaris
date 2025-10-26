#include"mbed.h"

#define WAIT 0.00001

DigitalOut control1(dp17);
DigitalOut control2(dp14);
DigitalOut leds[9] = {
    DigitalOut(dp1),
    DigitalOut(dp2),
    DigitalOut(dp4),
    DigitalOut(dp5),
    DigitalOut(dp6),
    DigitalOut(dp9),
    DigitalOut(dp10),
    DigitalOut(dp11),
    DigitalOut(dp13),
};

Serial from_main(dp16, dp15);

char data_packet[4];

char char_ele, char_rud;
int int_ele, int_rud;

/*-------プロトタイプ宣言------*/
void judge();
void led_ele();
void led_rud();

int main()
{
    from_main.baud(115200);

    /*--Rudder用led, Elevator用ledに逆方向電圧(-3.3V)をかける----*/
    for(int i = 0; i < 9; i++){
        leds[i] = 1;
    }

    from_main.attach(judge, Serial::RxIrq);

    while(1){

        /*-------ダイナミック点灯-------*/
        led_ele();
        wait(WAIT);
        led_rud();
        wait(WAIT);
    }

}

void judge()
{

    char_ele = from_main.getc();
    char_rud = from_main.getc();

    int_ele = char_ele - '0';
    int_rud = char_rud - '0';

}

void led_ele()
{
    control1 = 1;//Elevator用ledに順方向電圧(3.3V)をかける
    control2 = 0;

    leds[int_ele - 1] = 0;//led点灯
    wait(0.001);
    leds[int_ele - 1] = 1;//led消灯
}

void led_rud()
{
    control1 = 0;
    control2 = 1;//Rudder用ledに順方向電圧(3.3V)をかける

    leds[int_rud - 1] = 0;//led点灯
    wait(0.001);
    leds[int_rud - 1] = 1;//led消灯
}
