//更新 2021年 6月7日

#include"mbed.h"

// 制御角 -60° ~ +60°
// Pulse幅 0.00091 ~ 0.00211
// Neutral 0.00151 ? 

// 指定制御角 -10° = +10°
// Pulse幅 0.00141 ~ 0.00161
// Neutral 0.00151 ?

/*-----------------PC モード用 パルス幅-----------------*/
#define UP_STAGE4    0.001590  
#define UP_STAGE3    0.001570  
#define UP_STAGE2    0.001550  
#define UP_STAGE1    0.001530
#define NEUTRAL_E    0.001510
#define DOWN_STAGE1  0.001490
#define DOWN_STAGE2  0.001470
#define DOWN_STAGE3  0.001450  
#define DOWN_STAGE4  0.001430  

#define LEFT_STAGE4  0.001430  
#define LEFT_STAGE3  0.001450  
#define LEFT_STAGE2  0.001470
#define LEFT_STAGE1  0.001490
#define NEUTARL_R    0.001510
#define RIGHT_STAGE1 0.001530
#define RIGHT_STAGE2 0.001550
#define RIGHT_STAGE3 0.001570 
#define RIGHT_STAGE4 0.001590  



Serial pc(USBTX,USBRX);
Serial to_main(p9,p10);
Serial to_meter(p13,p14);

PwmOut pwm_ele(p22);
PwmOut pwm_rud(p21);

AnalogIn joy_ele_A(p19);
AnalogIn joy_rud_A(p20);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

Ticker t_control;

char start_command;
char pc_command;
char pc_ele_command;
char pc_rud_command;

char send_ele_data, send_rud_data;

double joy_ele_D;//ジョイスティック_デジタル値
double joy_rud_D;

double ele_pwidth = 0.00151;//初期条件: ニュートラルpulse幅
double rud_pwidth = 0.00151;
double displace = 0.00002;// pulse幅 変位量

/*-------------プロトタイプ宣言--------------*/
void pc_control();
void control();
void make_send_data();
void to_meter_communication();
void to_main_communication();

int main()
{
    to_main.baud(115200);
    to_meter.baud(115200);

    to_meter.putc('5');//エレベータニュートラル
    to_meter.putc('5');//ラダーニュートラル

    pc.attach(pc_control,Serial::RxIrq);
    t_control.attach(&control,0.25);

    while(1){

    }
}

void pc_control()
{
    start_command = pc.getc();

    if(start_command == '\r'){ //teraterm上でEnterが押されたら, PC mode突入

        while(1){

            pc.printf("Start PC mode \r\n");
            
            pc.printf("==========================================\r\n");
            pc.printf("Push the PC key \r\n");
            pc.printf("\r\n");
            pc.printf("Elevator Control : E \r\n");
            pc.printf("Rudder Control : R \r\n");
            pc.printf("Finish PC mode : C \r\n");
            pc.printf("\r\n");

            while(1){

                pc_command = pc.getc();

                if(pc_command == 'E'){

                    pc.printf(" 'Elevator Control' selected \r\n");
                    pc.printf("\r\n");

                    pc.printf("Please set pulse width (Elevator) \r\n");
                    pc.printf("\r\n");

                    pc.printf("UP_stage4 : 1 \r\n");
                    pc.printf("UP_stage3 : 2 \r\n");
                    pc.printf("UP_stage2 : 3 \r\n");
                    pc.printf("UP_stage1 : 4 \r\n");
                    
                    pc.printf("\r\n");

                    pc.printf("Neutral_E : 5 \r\n");

                    pc.printf("\r\n");

                    pc.printf("DOWN_stage1 : 6 \r\n");
                    pc.printf("DOWN_stage2 : 7 \r\n");
                    pc.printf("DOWN_stage3 : 8 \r\n");
                    pc.printf("DOWN_stage4 : 9 \r\n");

                    pc.printf("\r\n");

                    pc.printf("Back : 0 \r\n");

                    pc.printf("\r\n");


                    while(1){

                        pc_ele_command = pc.getc();

                        /*----------エレベータ pulse幅条件分岐---------*/

                        if(pc_ele_command == '1'){

                            pc.printf(" 'UP_stage4' selected\r\n");
                            pc.printf("\r\n");

                            pwm_ele.pulsewidth(UP_STAGE4);

                        } else if(pc_ele_command == '2'){

                            pc.printf(" 'UP_stage3' selected\r\n");
                            pc.printf("\r\n");

                            pwm_ele.pulsewidth(UP_STAGE3);

                        } else if(pc_ele_command == '3'){

                            pc.printf(" 'UP_stage2' selected\r\n");
                            pc.printf("\r\n");

                            pwm_ele.pulsewidth(UP_STAGE2);

                        } else if(pc_ele_command == '4'){

                            pc.printf(" 'UP_stage1' selected\r\n");
                            pc.printf("\r\n");

                            pwm_ele.pulsewidth(UP_STAGE1);

                        } else if(pc_ele_command == '5'){

                            pc.printf(" 'Neutral_E' selected\r\n");
                            pc.printf("\r\n");

                            pwm_ele.pulsewidth(NEUTRAL_E);

                        } else if(pc_ele_command == '6'){

                            pc.printf(" 'Down_stage1' selected\r\n");
                            pc.printf("\r\n");

                            pwm_ele.pulsewidth(DOWN_STAGE1);

                        } else if(pc_ele_command == '7'){

                            pc.printf(" 'Down_stage2' selected\r\n");
                            pc.printf("\r\n");

                            pwm_ele.pulsewidth(DOWN_STAGE2);

                        } else if(pc_ele_command == '8'){

                            pc.printf(" 'Down_stage3' selected\r\n");
                            pc.printf("\r\n");

                            pwm_ele.pulsewidth(DOWN_STAGE3);

                        } else if(pc_ele_command == '9'){

                            pc.printf(" 'Down_stage4' selected\r\n");
                            pc.printf("\r\n");

                            pwm_ele.pulsewidth(DOWN_STAGE4);

                        } else if(pc_ele_command == '0'){

                            pc.printf(" finish 'Elevator Control mode' \r\n");
                            pc.printf("\r\n");

                            break;
                        }                        

                    }

                    break;

                } else if(pc_command == 'R'){

                    pc.printf(" 'Rudder Control' selected \r\n");
                    pc.printf("\r\n");

                    pc.printf("Please set pulse width (Rudder) \r\n");
                    pc.printf("\r\n");

                    pc.printf("LEFT_stage4 : 1 \r\n");
                    pc.printf("LEFT_stage3 : 2 \r\n");
                    pc.printf("LEFT_stage2 : 3 \r\n");
                    pc.printf("LEFT_stage1 : 4 \r\n");
                    
                    pc.printf("\r\n");

                    pc.printf("Neutral_R : 5 \r\n");

                    pc.printf("\r\n");

                    pc.printf("RIGHT_stage1 : 6 \r\n");
                    pc.printf("RIGHT_stage2 : 7 \r\n");
                    pc.printf("RIGHT_stage3 : 8 \r\n");
                    pc.printf("RIGHT_stage4 : 9 \r\n");

                    pc.printf("\r\n");

                    pc.printf("Back : 0 \r\n");

                    pc.printf("\r\n");


                    while(1){

                        pc_rud_command = pc.getc();

                        /*----------エレベータ pulse幅条件分岐---------*/

                        if(pc_rud_command == '1'){

                            pc.printf(" 'Left_stage4' selected\r\n");
                            pc.printf("\r\n");

                            pwm_rud.pulsewidth(LEFT_STAGE4);

                        } else if(pc_rud_command == '2'){

                            pc.printf(" 'Left_stage3' selected\r\n");
                            pc.printf("\r\n");

                            pwm_rud.pulsewidth(LEFT_STAGE3);

                        } else if(pc_rud_command == '3'){

                            pc.printf(" 'Left_stage2' selected\r\n");
                            pc.printf("\r\n");

                            pwm_rud.pulsewidth(LEFT_STAGE2);

                        } else if(pc_rud_command == '4'){

                            pc.printf(" 'Left_stage1' selected\r\n");
                            pc.printf("\r\n");

                            pwm_rud.pulsewidth(LEFT_STAGE1);

                        } else if(pc_rud_command == '5'){

                            pc.printf(" 'Neutral_E' selected\r\n");
                            pc.printf("\r\n");

                            pwm_rud.pulsewidth(NEUTRAL_E);

                        } else if(pc_rud_command == '6'){

                            pc.printf(" 'Right_stage1' selected\r\n");
                            pc.printf("\r\n");

                            pwm_rud.pulsewidth(RIGHT_STAGE1);

                        } else if(pc_rud_command == '7'){

                            pc.printf(" 'Right_stage2' selected\r\n");
                            pc.printf("\r\n");

                            pwm_rud.pulsewidth(RIGHT_STAGE2);

                        } else if(pc_rud_command == '8'){

                            pc.printf(" 'Right_stage3' selected\r\n");
                            pc.printf("\r\n");

                            pwm_rud.pulsewidth(RIGHT_STAGE3);

                        } else if(pc_rud_command == '9'){

                            pc.printf(" 'Right_stage4' selected\r\n");
                            pc.printf("\r\n");

                            pwm_rud.pulsewidth(RIGHT_STAGE4);

                        } else if(pc_rud_command == '0'){

                            pc.printf(" finish 'Rudder Control mode' \r\n");
                            pc.printf("\r\n");

                            break;
                        }                        

                    }

                    break;

                } else if(pc_command == 'C'){

                pc.printf("finish 'PC mode' \r\n");
                pc.printf("\r\n");

                break;

            } else{

                pc.printf("Error!\r\n");

                }
            }
        }

    }
}

void control()
{
    //12bitのADコンバータ内蔵 ⇒ 2^12 = 4096の解像度 ⇒ 0 ~ 1の間で4096の分解能

    joy_ele_D = joy_ele_A.read();
    joy_rud_D = joy_rud_A.read();

    /*-----電圧チェック(デジタル信号)------*/
    //pc.printf("joy_ele_D: %lf\r\n",joy_ele_D);
    pc.printf("joy_rud_A: %lf\r\n",joy_rud_D);

    // Pulse幅 0.00141 ~ 0.00161

    if(joy_ele_D < 0.3){

        if(0.00143 <= ele_pwidth){

            ele_pwidth -= displace;

        } else{
            ele_pwidth = ele_pwidth;
        }

    }else if(joy_ele_D > 0.7){

        if(ele_pwidth <= 0.00159){

            ele_pwidth += displace;

        }else {
            ele_pwidth = ele_pwidth;
        }

    } else{
        ele_pwidth = ele_pwidth;
    }


    if(joy_rud_D < 0.3){

        if(0.00143 <= rud_pwidth){

            rud_pwidth -= displace;

        } else{
            rud_pwidth = rud_pwidth;
        }

    }else if(joy_rud_D > 0.7){

        if(rud_pwidth <= 0.00159){

            rud_pwidth += displace;

        }else {
            rud_pwidth = rud_pwidth;
        }

    } else{
        rud_pwidth = rud_pwidth;
    }

    //pc.printf("ele_pwidth: %lf\r\n",ele_pwidth);
    pc.printf("rud_pwidth: %lf\r\n",rud_pwidth);
    
    /*-------------サーボモータ制御--------------*/
    pwm_ele.pulsewidth(ele_pwidth);
    pwm_rud.pulsewidth(rud_pwidth);

    /*---------シリアル通信用データ作成----------*/
    make_send_data();

    /*--------------舵角計に送信----------------*/
    to_meter_communication();

    /*-----------main lpc1768に送信-------------*/
    to_main_communication();
}

void make_send_data()
{
    if(0.00142 <= ele_pwidth && ele_pwidth < 0.00144){
        send_ele_data = '1';
    } else if(0.00144 <= ele_pwidth && ele_pwidth < 0.00146){
        send_ele_data = '2';
    } else if(0.00146 <= ele_pwidth && ele_pwidth < 0.00148){
        send_ele_data = '3';
    } else if(0.00148 <= ele_pwidth && ele_pwidth < 0.00150){
        send_ele_data = '4';
    } else if(0.00150 <= ele_pwidth && ele_pwidth < 0.00152){
        send_ele_data = '5';
    } else if(0.00152 <= ele_pwidth && ele_pwidth < 0.00154){
        send_ele_data = '6';
    } else if(0.00154 <= ele_pwidth && ele_pwidth < 0.00156){
        send_ele_data = '7';
    } else if(0.00156 <= ele_pwidth && ele_pwidth < 0.00158){
        send_ele_data = '8';
    } else if(0.00158 <= ele_pwidth && ele_pwidth < 0.00160){
        send_ele_data = '9';
    }

    if(0.00142 <= rud_pwidth && rud_pwidth < 0.00144){
        send_rud_data = '1';
    } else if(0.00144 <= rud_pwidth && rud_pwidth < 0.00146){
        send_rud_data = '2';
    } else if(0.00146 <= rud_pwidth && rud_pwidth < 0.00148){
        send_rud_data = '3';
    } else if(0.00148 <= rud_pwidth && rud_pwidth < 0.00150){
        send_rud_data = '4';
    } else if(0.00150 <= rud_pwidth && rud_pwidth < 0.00152){
        send_rud_data = '5';
    } else if(0.00152 <= rud_pwidth && rud_pwidth < 0.00154){
        send_rud_data = '6';
    } else if(0.00154 <= rud_pwidth && rud_pwidth < 0.00156){
        send_rud_data = '7';
    } else if(0.00156 <= rud_pwidth && rud_pwidth < 0.00158){
        send_rud_data = '8';
    } else if(0.00158 <= rud_pwidth && rud_pwidth < 0.00160){
        send_rud_data = '9';
    }
}

void to_meter_communication()
{
    led1 = 0;

    //pc.printf("Send_ele_data: %c\r\n",send_ele_data);
    pc.printf("Send_rud_data: %c\r\n",send_rud_data);

    to_meter.putc(send_ele_data);
    to_meter.putc(send_rud_data);
    wait(0.01);

    led1 = 1;

}

void to_main_communication()
{
    led2 = 0;

    to_main.putc(send_ele_data);
    to_main.putc(send_rud_data);
    wait(0.01);

    led1 = 1;
}
