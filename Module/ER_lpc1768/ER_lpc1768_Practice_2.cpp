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

PwmOut pwm_ele(p22);

AnalogIn joy_ele_A(p19);

Ticker t_control;

char start_command;
char pc_command;
char pc_ele_command;

double joy_ele_D;//ジョイスティック_デジタル値

double ele_pwidth = 0.00151;//初期条件: ニュートラルpulse幅
double displace = 0.00002;// pulse幅 変位量

/*-------------プロトタイプ宣言--------------*/
void pc_control();
void control();

int main()
{
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

    /*-----電圧チェック(デジタル信号)------*/
    pc.printf("joy_ele_D: %lf\r\n",joy_ele_D);

    // Pulse幅 0.00141 ~ 0.00161

    if(joy_ele_D < 0.2){

        if(0.00141 <= ele_pwidth){

            ele_pwidth -= displace;

        } else{
            ele_pwidth = ele_pwidth;
        }

    }else if(joy_ele_D > 0.8){

        if(ele_pwidth <= 0.00161){

            ele_pwidth += displace;

        }else {
            ele_pwidth = ele_pwidth;
        }

    } else{
        ele_pwidth = ele_pwidth;
    }

    pwm_ele.pulsewidth(ele_pwidth);
}
