#include"mbed.h"

//Neutral Pulse幅 0.00151 ± 0.0006 s
//サーボモータのトルクによりニュートラル位置がズレていく可能性あり

//-----------------S-270 Malus 操舵システム-------------------
//サーボ角度: -10° ~ +10°
//エレベータ: 10段階
//ラダー: 3段階

//Duty Cicle 100% ?

/*-----------------PC モード用 パルス幅-----------------*/
#define UP_STAGE4    0.000030
#define UP_STAGE3    0.000650  //調整部分
#define UP_STAGE2    0.000770
#define UP_STAGE1    0.001140
#define NEUTRAL_E    0.001510
#define DOWN_STAGE1  0.001880
#define DOWN_STAGE2  0.002250
#define DOWN_STAGE3  0.002370  //調整部分
#define DOWN_STAGE4  0.002990

#define LEFT_STAGE4  0.000030
#define LEFT_STAGE3  0.000650  //調整部分
#define LEFT_STAGE2  0.000770
#define LEFT_STAGE1  0.001140
#define NEUTARL_R    0.001510
#define RIGHT_STAGE1 0.001880
#define RIGHT_STAGE2 0.002250
#define RIGHT_STAGE3 0.002370  //調整部分
#define RIGHT_STAGE4 0.002990

Serial pc(USBTX,USBRX);

PwmOut pwm_ele(p22);
PwmOut pwm_rud(p21);

char start_command;
char pc_command;
char pc_ele_command;
char pc_rud_command;

void pc_control();
void control();

int main()
{
    pc.attach(pc_control,Serial::RxIrq);

    while(1){

    }
}

void pc_control()
{
    start_command = pc.getc();

    if(start_command == '\r'){ //TeraTerm 上でEnterが押されたら, PC mode 突入

        while(1){

            pc.printf("Start PC mode \r\n");
                
            pc.printf("=================================================== \r\n");
            pc.printf("Push the PC key \r\n");
            pc.printf("\r\n");
            pc.printf("Elevator Control : E \r\n");
            pc.printf("Rudder Control : R \r\n");
            pc.printf("Finish PC mode : C \r\n");
            pc.printf("\r\n");

            while(1){

                pc_command = pc.getc();//入力キーのデータ格納

                if(pc_command == 'E'){

                    pc.printf(" 'Elevator Control' selected \r\n");
                    pc.printf("\r\n");

                    pc.printf("Please set pulse width (Elevator) \r\n");
                    pc.printf("\r\n");

                    pc.printf("UP_stage4 : 1 \r\n");
                    pc.printf("UP_stage3 : 2 \r\n");
                    pc.printf("UP_stage2 : 3 \r\n");
                    pc.printf("UP_stage1 : 4 \r\n");

                    pc.printf("Neutral_E : 5 \r\n");

                    pc.printf("DOWN_stage1 : 6 \r\n");
                    pc.printf("DOWN_stage2 : 7 \r\n");
                    pc.printf("DOWN_stage3 : 8 \r\n");
                    pc.printf("DOWN_stage4 : 9 \r\n");

                    pc.printf("Back : 0 \r\n");
                    pc.printf("\r\n");


                    while(1){

                        pc_ele_command = pc.getc();

                        /*---------エレベーター　パルス幅条件分岐---------*/

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

                    while(1){

                        pc.printf("Please set pulse width (Rudder) \r\n");
                        pc.printf("\r\n");

                        pc.printf("LEFT_stage4 : 1 \r\n");
                        pc.printf("LEFT_stage3 : 2 \r\n");
                        pc.printf("LEFT_stage2 : 3 \r\n");
                        pc.printf("LEFT_stage1 : 4 \r\n");

                        pc.printf("Neutral_R : 5 \r\n");

                        pc.printf("RIGHT_stage1 : 6 \r\n");
                        pc.printf("RIGHT_stage2 : 7 \r\n");
                        pc.printf("RIGHT_stage3 : 8 \r\n");
                        pc.printf("RIGHT_stage4 : 9 \r\n");

                        pc.printf("Back : 0 \r\n");
                        pc.printf("\r\n");

                        while(1){

                            pc_rud_command = pc.getc();

                            /*-----------ラダー　パルス幅条件分岐-----------*/

                            if(pc_rud_command == '1'){

                                pc.printf(" 'LEFT_stage4' selected\r\n");
                                pc.printf("\r\n");

                                pwm_rud.pulsewidth(LEFT_STAGE4);

                            } else if(pc_rud_command == '2'){

                                pc.printf(" 'LEFT_stage3' selected\r\n");
                                pc.printf("\r\n");

                                pwm_rud.pulsewidth(LEFT_STAGE3);

                            } else if(pc_rud_command == '3'){

                                pc.printf(" 'LEFT_stage2' selected\r\n");
                                pc.printf("\r\n");

                                pwm_rud.pulsewidth(LEFT_STAGE2);

                            } else if(pc_rud_command == '4'){

                                pc.printf(" 'LEFT_stage1' selected\r\n");
                                pc.printf("\r\n");

                                pwm_rud.pulsewidth(LEFT_STAGE1);

                            } else if(pc_rud_command == '5'){

                                pc.printf(" 'Neutral_R' selected \r\n");
                                pc.printf("\r\n");

                                pwm_rud.pulsewidth(NEUTARL_R);

                            } else if(pc_rud_command == '6'){

                                pc.printf(" 'RIGHT_stage1' selected\r\n");
                                pc.printf("\r\n");

                                pwm_rud.pulsewidth(RIGHT_STAGE1);

                            } else if(pc_rud_command == '7'){

                                pc.printf(" 'RIGHT_stage2' selected\r\n");
                                pc.printf("\r\n");

                                pwm_rud.pulsewidth(RIGHT_STAGE2);

                            } else if(pc_rud_command == '8'){

                                pc.printf(" 'RIGHT_stage3' selected\r\n");
                                pc.printf("\r\n");

                                pwm_rud.pulsewidth(RIGHT_STAGE3);

                            } else if(pc_rud_command == '9'){

                                pc.printf(" 'RIGHT_stage4' selected\r\n");
                                pc.printf("\r\n");

                                pwm_rud.pulsewidth(RIGHT_STAGE4);

                            } else if(pc_rud_command == '0'){
                                pc.printf(" finish 'Rudder Control mode' \r\n");
                                pc.printf("\r\n");

                                break;
                            }
                        }

                        break;
                    }

                } else if(pc_command == 'C'){

                    pc.printf("finish 'PC mode' \r\n");
                    pc.printf("\r\n");

                    break;

                }

            } 
        }
    }
}
