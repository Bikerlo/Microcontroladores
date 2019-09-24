#define estadoTarea 0
#define estacion 1
#define caja 2

//pos 0 para tarea lista
//pos 1 para estacion
//pos 2 para caja B/N

int tareas[3][3]={{0,0,0},{0,0,0},{0,0,0}};

char output[10]=" ";
int recieve[5]={0,0,0,0,0};
char mensaje=' ';
int i=0,j=0;
int tarea=0;



void enviar(char send[30]){
     UART1_Write_Text(send);
     Uart1_write(10);
     Uart1_write(13);
}

char esperarLetra(){
     int esperar=1;
     enviar("Esperando Letra");
     do{
        if (UART1_Data_Ready()!=0){
           mensaje=UART1_read();
           esperar=0;
        }
     }while(esperar);
     return mensaje;
}

void esperarInicio(){
     int iniciar=1;
     
     portD.f0=0;
     portD.f1=0;
     portD.f2=0;
     portD.f3=0;
     
     enviar("Press I to start");
     do{
        if (UART1_Data_Ready()!=0){
           mensaje=UART1_read();
           if (mensaje=='i' || mensaje=='I'){
              iniciar=0;
           }else{iniciar=1;}
        }
     }while(iniciar);
}

void enviarEstadoTareas(){
     for (i=0;i<3;i++){
         switch (tareas[i][estadoTarea]){
                case 1:
                     if (i==0){
                        enviar("Tarea 1 Activa");
                     }
                     if (i==1){
                        enviar("Tarea 2 Activa");
                     }
                     if (i==2){
                        enviar("Tarea 3 Activa");
                     }
                     if (tareas[i][estacion]==1){
                        enviar("Estacion 1");   
                     }
                     if (tareas[i][estacion]==2){
                        enviar("Estacion 2");   
                     }
                     if (tareas[i][estacion]==3){
                        enviar("Estacion 3");   
                     }
                     if (tareas[i][estacion]==4){
                        enviar("Estacion 4");   
                     }
                     if (tareas[i][estacion]==5){
                        enviar("Estacion 5");   
                     }
                     if (tareas[i][caja]==1){
                        enviar("Caja Blanca");   
                     }
                     if (tareas[i][caja]==0){
                        enviar("Caja Negra");   
                     }
                     break;
                case 0:
                     if (i==0){
                        enviar("Tarea 1 Inactiva");
                     }
                     if (i==1){
                        enviar("Tarea 2 Inactiva");
                     }
                     if (i==2){
                        enviar("Tarea 3 Inactiva");
                     }
                     break;
         }
     }
}

void configTareas(int tarea) {
     int listo=0;
     tarea=tarea-1;
     enviar("Como configurar?");
     enviar("ejemplo: 31OK");
     enviar("primer caracter indica la estacion ");
     enviar("Min 1, Max 5");
     enviar("Segundo caracter indica la caja");
     enviar("1 para blanco");
     enviar("0 para negro");
     enviar("En mayusculas");
     enviar("seguido de un OK para confirmar");
     if (tarea==0){
        enviar("configurando T1");
        tareas[tarea][estadoTarea]=1;
     }
     if (tarea==1){
        enviar("configurando T2");
        tareas[tarea][estadoTarea]=1;
     }
     if (tarea==2){
        enviar("configurando T3");
        tareas[tarea][estadoTarea]=1;
     }

     do{
        if (UART1_Data_Ready() == 1) {          // if data is received
           UART1_Read_Text(output, "OK", 4);    // reads text until 'OK' is found
           recieve[0]=(output[0]-48);
           recieve[1]=(output[1]-48);
           switch (recieve[0]){
                  case 1:
                       tareas[tarea][estacion]=1;
                       enviar("Estacion 1");
                       break;
                  case 2:
                       tareas[tarea][estacion]=2;
                       enviar("Estacion 2");
                       break;
                  case 3:
                       tareas[tarea][estacion]=3;
                       enviar("Estacion 3");
                       break;
                  case 4:
                       tareas[tarea][estacion]=4;
                       enviar("Estacion 4");
                       break;
                  case 5:
                       tareas[tarea][estacion]=5;
                       enviar("Estacion 5");
                       break;
                  default:
                          tareas[tarea][estacion]=1;
                          enviar("Estacion por defecto");
           }
           switch (recieve[1]){
                  case 1:
                       tareas[tarea][caja]=1;
                       enviar("Caja Blanca");
                       break;
                  case 0:
                       tareas[tarea][caja]=0;
                       enviar("Caja Negra");
                       break;
                  default:
                          tareas[tarea][caja]=0;
                          enviar("Caja por defecto");
           }
           listo=1;
        }
     }while(listo==0);
}

void menuPrincipal(){
     char opc=' ';
     int inicio=1;
     do{
        enviar("HOLA USUARIO");
        enviar("soy Colombianita");
        enviar("¿que desea Hacer?");
        enviar("A. configurar Tareas");
        enviar("B. ver estado de tareas");
        enviar("C. iniciar tareas");
        opc=esperarLetra();
        if (opc=='A' || opc=='a'){
           enviar("cuantas Tareas?");
           enviar("minimo 0");
           enviar("maximo 3");
           opc=esperarLetra();
           if (opc=='0'){
              enviar("Quien quiere 0 tareas?");
              enviar("no me agradas");
           }
           if (opc == '1'){
              configTareas(1);
           }
           if (opc == '2'){
              configTareas(1);
              configTareas(2);
           }
           if (opc == '3'){
              configTareas(1);
              configTareas(2);
              configTareas(3);
           }
        }
        if (opc=='b' || opc=='B'){
           enviarEstadoTareas();
        }
        if (opc=='c' || opc=='C'){
           if (tareas[0][estadoTarea]==1 || tareas[1][estadoTarea]==1 || tareas[2][estadoTarea]==1){
              inicio=0;
           }else{
                 enviar("Yo no tengo nada que hacer");
                 enviar("Dejame aqui quietesita mejor");
           }
        }
     }while(inicio);
}
void menuSegundario(){
     char opc=' ';
     int inicio=1;
     do{
        enviar("Que desea hacer?");
        enviar("A. seguir camellando");
        enviar("B. agregar tarea");
        enviar("C. modificar tarea");
        enviar("D. ver estado de tareas");
        opc=esperarLetra();
        if (opc=='a' || opc=='A'){
           inicio=0;
        }
        if (opc=='b' || opc=='B'){
           if (tareas[0][estadoTarea]==1 && tareas[1][estadoTarea]==1 && tareas[2][estadoTarea]==1){
              enviar("No puedes agregar tareas");
              enviar("Ya estan estas tareas");
              enviarEstadoTareas();
           }
           if (tareas[0][estadoTarea]==0 && tareas[1][estadoTarea]==1 && tareas[2][estadoTarea]==1){
              enviar("Agregamos Tarea 1");
              configTareas(1);
           }
           if (tareas[0][estadoTarea]==0 && tareas[1][estadoTarea]==0 && tareas[2][estadoTarea]==1){
              enviar("Agregamos Tarea 1 y 2");
              configTareas(1);
              configTareas(2);
           }
           if (tareas[0][estadoTarea]==0 && tareas[1][estadoTarea]==0 && tareas[2][estadoTarea]==0){
              enviar("Agregamos Tarea 1, 2 y 3");
              configTareas(1);
              configTareas(2);
              configTareas(3);
           }
           if (tareas[0][estadoTarea]==1 && tareas[1][estadoTarea]==0 && tareas[2][estadoTarea]==0){
              enviar("Agregamos Tarea 2");
              configTareas(2);
           }
           if (tareas[0][estadoTarea]==1 && tareas[1][estadoTarea]==1 && tareas[2][estadoTarea]==0){
              enviar("Agregamos Tarea 2");
              configTareas(3);
           }
           
        }
        if (opc=='c' || opc=='C'){
           enviarEstadoTareas();
           enviar("Cual desea modificar?");
           enviar("1. Tarea 1");
           enviar("2. Tarea 2");
           enviar("3. Tarea 3");
           opc=esperarLetra();
           if (opc=='1'){
              configTareas(1);
           }
           if (opc=='2'){
              configTareas(2);
           }
           if (opc=='3'){
              configTareas(3);
           }
           if (tareas[0][estadoTarea]==1){
              tarea=0;
           }
           if (tareas[0][estadoTarea]==0 && tareas[1][estadoTarea]==1){
              tarea=1;
           }
           if (tareas[0][estadoTarea]==0 && tareas[1][estadoTarea]==0 && tareas[2][estadoTarea]==1){
              tarea=2;
           }
        }
        if (opc=='d' || opc=='D'){
           enviarEstadoTareas();
        }
     }while(inicio);
}

double red,green,blue,Of;           //  sensor color
int pass=0;                          //
const pmwinit=5000;                  //

int aux=0,cnt_estacion=0;                                           //    servos
int color=0,auxrojo=0,auxama=0,auxazul=0,auxverde=0; //

void sensado_color();
void seguidor();
void compartimiento();
void reversa();

void Interrupt(){
  if(TMR0IF_bit){
    T0CON.TMR0on=0;
    Of= Of + 1.0;
    TMR0IF_bit=0;
    T0CON.TMR0on=1;
  }
}

void seguidor(){                //b7 derecho y b6 izquierdo
    if (!PORTB.f7 && !PORTB.f6){    //adelante
     portD.f0=1;
     portD.f1=0;
     portD.f2=1;
     portD.f3=0;
    }

    if (!PORTB.f7 && PORTB.f6){
     portD.f0=1;
     portD.f1=0;
     portD.f2=0;
     portD.f3=1;
    }

    if (PORTB.f7 && !PORTB.f6){
       portD.f0=0;
       portD.f1=1;
       portD.f2=1;
       portD.f3=0;
    }

    if (PORTB.RB7 && PORTB.RB6){  //FINAL DE LÍNEA
       portD.f0=0;
       portD.f1=0;
       portD.f2=0;
       portD.f3=0;
       enviar("Final de pista");
       esperarInicio();
    }
}


float freq_lec(){
      double ol=0.0, sensado=0.0;
      TMR0L=0;
      portA.f5=0;
      T0CON.TMR0ON=1;
      Of=0.0;
      delay_ms(100);
      T0CON.TMR0ON=0;
      portA.f5=1;
      ol = (double) TMR0L;
      sensado = (ol + Of*256.0)*0.01;
      Of=0.0;
      return(sensado);
}
void servo1(int color, int aux){

 switch(color){
  case 1: //para 45 grados y regresar a 90 rojo primer servo
    while(aux<=10){
     PORTB.F3=1;
     delay_us(1780);
     PORTB.F3=0;
     delay_us(18220);
     aux++;
    }
    aux=0;
    delay_ms(300);
    while(aux<=10){
     PORTB.F3=1;
     delay_us(1500);
     PORTB.F3=0;
     delay_us(18500);
     aux++;
    }
  break;
  case 2: //para 135 y regresar a 90 verde primer servo
    while(aux<=10){
     PORTB.F3=1;
     delay_us(1220);
     PORTB.F3=0;
     delay_us(18780);
     aux++;
    }
    aux=0;
    delay_ms(300);
    while(aux<=10){
     PORTB.F3=1;
     delay_us(1500);
     PORTB.F3=0;
     delay_us(18500);
     aux++;
    }
  break;

  case 3: //para 45 grados y regresar a 90 amarillo segundo servo
    while(aux<=10){
     PORTB.F4=1;
     delay_us(1780);
     PORTB.F4=0;
     delay_us(18220);
     aux++;
    }
    aux=0;
    delay_ms(300);
    while(aux<=10){
     PORTB.F4=1;
     delay_us(1500);
     PORTB.F4=0;
     delay_us(18500);
     aux++;
    }
  break;

  case 4: //para 135 y regresar a 90 azul segundo servo
    while(aux<=10){
     PORTB.F4=1;
     delay_us(1220);
     PORTB.F4=0;
     delay_us(18780);
     aux++;
    }
    aux=0;
    delay_ms(300);
    while(aux<=10){
     PORTB.F4=1;
     delay_us(1500);
     PORTB.F4=0;
     delay_us(18500);
     aux++;
    }
  break;
 }
}

void servo2(int color, int aux){   //para los colores que se repiten

switch(color){
 case 5: //para 0 del primer servo rojo repetido
   while(aux<=15){
    PORTB.F3=1;
    delay_us(2300);
    PORTB.F3=0;
    delay_us(17700);
    aux++;
   }
    aux=0;
   delay_ms(300);
   while(aux<=10){
    PORTB.F3=1;
    delay_us(1500);
    PORTB.F3=0;
    delay_us(18500);
    aux++;
   }
 break;

 case 6: //para 180 del primer servo verde repetido
   while(aux<=15){
    PORTB.F3=1;
    delay_us(750);
    PORTB.F3=0;
    delay_us(19250);
    aux++;
   }
   aux=0;
   delay_ms(300);
   while(aux<=10){
    PORTB.F3=1;
    delay_us(1500);
    PORTB.F3=0;
    delay_us(18500);
    aux++;
   }
 break;

 case 7: //para 0 del segundo servo amarillo repetido
   while(aux<=15){
    PORTB.F4=1;
    delay_us(2200);
    PORTB.F4=0;
    delay_us(17800);
    aux++;
   }
   aux=0;
   delay_ms(300);
   while(aux<=10){
    PORTB.F4=1;
    delay_us(1500);
    PORTB.F4=0;
    delay_us(18500);
    aux++;
   }
  break;

  case 8: //para 180 del segundo servo azul repetido
   while(aux<=15){
    PORTB.F4=1;
    delay_us(850);
    PORTB.F4=0;
    delay_us(19150);
    aux++;
   }
   aux=0;
   delay_ms(300);
   while(aux<=10){
    PORTB.F4=1;
    delay_us(1500);
    PORTB.F4=0;
    delay_us(18500);
    aux++;
   }
  break;
 }
}

void Canicas(){
     if (red>green && red>blue && green<blue){     //ROJO
        enviar("Color Rojo");
        if (auxrojo==0){
           color=1;
           auxrojo++;
           servo1(color, aux);
        }else{
              if (auxrojo==1){     //color repetido rojo
                 color=5;
                 servo2(color, aux);
                 auxrojo=0;
              }
        }
 }
 if( (red<70 && blue>red && blue<50 && green>30)||(green>red && green>blue) ){     //VERDE
  enviar("Color Verde");
  if(auxverde==0){
   color=2;
   auxverde++;
   servo1(color, aux);
  }else{
   if(auxverde==1){ //color repetido verde
    color=6;
    servo2(color, aux);
    auxverde=0;
   }
  }
 }

 if(red>blue && green>blue && red>green && red>140 && green>80){     //AMARILLO
 enviar("Color Amarillo");
  if(auxama==0){
   color=3;
   auxama++;
   servo1(color, aux);
  }else{
   if(auxama==1){ //color repetido amarillo
    color=7;
    servo2(color, aux);
    auxama=0;
   }
  }
 }

 if(blue>red && blue>green && blue>70){     //AZUL
  enviar("Color Azul");
  if(auxazul==0){
   color=4;
   auxazul++;
   servo1(color, aux);
  }else{
   if(auxazul==1){ //color repetido azul
    color=8;
    servo2(color, aux);
    auxazul=0;
   }
  }
 }
 delay_ms(2000);
}

int Validador_color(){                                ////////////////////////////////////////////////////////
  int ok=0;

  if(red>green && red>blue && green<blue){     //ROJO
   ok=1;
   delay_ms(500);

  }

  if( (red<70 && blue>red && blue<50 && green>30)||(green>red && green>blue) ){     //VERDE
   ok=1;
   delay_ms(500);

  }

 if(red>blue && green>blue && red>green && red>140 && green>80){     //AMARILLO
   ok=1;
   delay_ms(500);

  }

  if(blue>red && blue>green && blue>70){     //AZUL
   ok=1;
   delay_ms(500);

  }

  if((red>100 && green>100 && blue>100)||(red<30 && green<30 && blue<30)){  // fuera de rango
   ok=0;
   delay_ms(500);

  }

  return(ok);
}

void compartimiento(){
 PWM1_Start();                       // start PWM1
 PWM2_Start();                       // start PWM2
 //

  if (tareas[tarea][caja] == 1){                          //blanco
     if (!RE0_bit && RE1_bit){
       while (RE1_bit){
           seguidor();
       }
    }
  }
  if (tareas[tarea][caja] == 0){
     if (RE0_bit && !RE1_bit){     //negro
        while (!RE1_bit){
              seguidor();
        }
     }
  }

 portD.f0=0;
 portD.f1=0;
 portD.f2=0;
 portD.f3=0;
 delay_ms(100);

 portD.f0=0;
 portD.f1=1;
 portD.f2=0;
 portD.f3=1;
 delay_ms(150);

 PWM1_Stop();                       // stop PWM1
 PWM2_Stop();                       // stop PWM2
}

void sensado_color(){

 do{
    red=0.0;
    green=0.0;
    blue=0.0;

        //rojo
    portA.f2=0;                //s2
    portA.f3=0;                //s3
    delay_us(50);
    red= freq_lec();

         //verde
    portA.f2=1;                //s2
    portA.f3=1;                //s3
    delay_us(50);
    green=freq_lec();

          //azul
    portA.f2=0;                //s2
    portA.f3=1;                //s3
    delay_us(50);
    blue=freq_lec();

    pass=Validador_color();

  }while(pass==0);
  pass=0;
  delay_ms(100);

}

void timer0_init(){
  GIE_bit = 1;
  TMR0IE_bit = 1;
  T0CON = 0b01101000;
}


void select_duty(){
  PWM1_Init(pmwinit);
  PWM2_Init(pmwinit);
  PWM1_Start();                     // start PWM1
  PWM2_Start();                     // start PWM2

  PWM1_Set_Duty(105);        // Set current duty for PWM1
  PWM2_Set_Duty(105);        // Set current duty for PWM2

}

void conf_channels(){ //Conf. Sensor color
  TRISA=0B00010000;
  /*TRISA.ra0=0; //S0 sensor color
  TRISA.ra1=0; //S1 sensor color
  TRISA.ra2=0; //S2 sensor color
  TRISA.ra3=0; //S3 sensor color
  TRISA.ra4=1; //Recepcion señal sensor color
  TRISA.ra5=0; //Enable sensor color
  */
  //Conf. modulo motores
  TRISC=0b11110001;
  TRISD=0b11110000;
  /*TRISC.rc1=0; //PWM 2
  TRISC.rc2=0; //PWM 1
  TRISD.rd0=0; //N1
  TRISD.rd1=0; //N2
  TRISD.rd2=0; //N3
  TRISD.rd3=0; //N4
  */
  // Conf. CNY´s y sensores de proximidad
  TRISB=0b11000111;
 /* TRISB.rb7=1; //CNY 1 derecha
  TRISB.rb6=1; //CNY 2 izquierda
  TRISC.rc0=1; //CNY 3 detector de estación
  TRISC.rc4=1; //Sensor prox. 1
  TRISC.rc5=1; //Sensor prox. 2
  */
  //Conf. sensor bluetooth
  /*TRISC.rc6=1; //TX a RX del bluetooth
  TRISC.rc7=1; //RX a TX del bluetooth
  */
  //Conf. servos
 /* TRISB.rb3=0;
  TRISB.rb4=0;
  TRISB.rb5=0;
  */
  //Conf. canales libres
 /* TRISB.rb0=0;
  TRISB.rb1=0;
  TRISB.rb2=0;
  TRISD.rd4=1;
  TRISD.rd5=0;
  TRISD.rd6=0;
  TRISD.rd7=0;*/
  TRISE.f0=1;       //sensor prox.2
  TRISE.f1=1;       //sensor prox.1
  TRISE.f2=1;
}

void parada(){

  portD.f0=0;
  portD.f1=0;
  portD.f2=0;
  portD.f3=0;
  delay_ms(50);

  portD.f0=0;
  portD.f1=1;
  portD.f2=0;
  portD.f3=1;
  delay_ms(100);

  PWM1_Stop();                       // stop PWM1
  PWM2_Stop();                       // stop PWM2

  sensado_color();

  compartimiento();                                 //compartimient0

  Canicas();

  PWM1_Start();                       // start PWM1
  PWM2_Start();                       // start PWM2
}


void main() {
     int tmp_muerto=0;

     Adcon1=0x0f;
     conf_channels();
     timer0_init();
     select_duty();
     UART1_Init(9600);
     delay_ms(100);

     PORTA=0;
     PORTB=0;
     PORTC=0;
     PORTD=0;
     PORTE=0;

     //frecuencia del sensor de color y disable
      portA.f0=1;                       //S0
      portA.f1=1;                       //S1
      portA.f5=1;                       //enable

      while (aux<11){                  //angulo inicial
            PORTB.F3=1; //para iniciar el primer servo en 90°
            delay_us(1500);
            PORTB.F3=0;
            delay_us(18500);
            PORTB.F4=1;  //para iniciar el segundo servo en 90°
            delay_us(1500);
            PORTB.F4=0;
            delay_us(18500);
            aux++;
      }
      aux=0;
      while (1){
            menuPrincipal();
            enviar("mientras camello usted puede:");
            enviar("T. ver estado de tareas");
            enviar("E. parada de emergencia");
            enviar("VAMO' A DARLE");
            
            while (tareas[0][estadoTarea]==1 || tareas[1][estadoTarea]==1 || tareas[2][estadoTarea]==1){
                  seguidor();
                  if (RC0_bit){
                     cnt_estacion ++;
                     enviar("pase por");
                     if(cnt_estacion==1){enviar("Estacion 1");}
                     if(cnt_estacion==2){enviar("Estacion 2");}
                     if(cnt_estacion==3){enviar("Estacion 3");}
                     if(cnt_estacion==4){enviar("Estacion 4");}
                     if(cnt_estacion==5){enviar("Estacion 5");}
                     if (cnt_estacion==tareas[tarea][estacion] && tareas[tarea][estadoTarea]==1){
                        if (tarea==0){
                           enviar("Haciendo tarea 1");
                           tareas[tarea][estadoTarea]=0;
                        }
                        if (tarea==1){
                           enviar("Haciendo tarea 2");
                           tareas[tarea][estadoTarea]=0;
                        }
                        if (tarea==2){
                           enviar("Haciendo tarea 3");
                           tareas[tarea][estadoTarea]=0;
                        }
                        parada();
                        tarea++;
                        if (tarea>2){tarea=0;};
                        enviar("tarea completa");
                     }
                     if (cnt_estacion>4){
                        cnt_estacion=0;
                     }
                      while (tmp_muerto<=200){
                              seguidor();
                              delay_ms(10);
                              tmp_muerto ++;
                      }
                   tmp_muerto=0;
                  }
                  if (UART1_Data_Ready()==1){
                     mensaje=UART1_read();
                     if (mensaje=='t' || mensaje=='T' ){
                        enviarEstadoTareas();
                     }
                     if (mensaje=='e' || mensaje=='E' ){
                        enviar("parada de emergencia");
                        menuSegundario();
                        esperarInicio();
                        enviar("VAMO' A DARLE");
                     }
                  }
            }
            enviar("Tareas Completadas");
            enviar("ire al final");
            portD.f0=0;
            portD.f1=0;
            portD.f2=0;
            portD.f3=0;
            if (cnt_estacion<=5){
               do{
                  seguidor();
                  if (RC0_bit){
                     cnt_estacion++;
                     if(cnt_estacion<6){enviar("pase por");}
                     if(cnt_estacion==1){enviar("Estacion 1");}
                     if(cnt_estacion==2){enviar("Estacion 2");}
                     if(cnt_estacion==3){enviar("Estacion 3");}
                     if(cnt_estacion==4){enviar("Estacion 4");}
                     if(cnt_estacion==5){enviar("Estacion 5");}
                      while (tmp_muerto<=200){
                              seguidor();
                              delay_ms(10);
                              tmp_muerto ++;
                      }
                      tmp_muerto=0;
                  }
               }while(cnt_estacion<5);
               if (cnt_estacion==5){
                  cnt_estacion=0;
                  enviar("Llevame al inicio");
               }
            }
      }
}