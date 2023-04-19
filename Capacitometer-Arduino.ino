//  author: Sergio H C Pavão
//  Capacitometer Arduino
//  Versão master funcionou bem. vou elaborar o esquema e layout da placa; 
//  Master version worked fine. I will draw up the schematic and layout of the board.
 
float V_in;
float V_Min;
float V_Max;
float Resistor;
byte indice;
float Capacitancia;
unsigned long periodo;
char *submultiplo[]={"mili","micro","nano","pico"};


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  Resistor = 2200.0;
  

}

void loop(){
  // put your main code here, to run repeatedly:
  float V_Min = 10.23 * ( 5.0 / 1023.0);
  float V_Max = 646.536 * ( 5.0 / 1023.0);
  V_in = analogRead(A0) * (5.0 / 1023.0);
  
  if ((V_in < V_Max)){
    
      periodo = medirConstanteRC(V_Max);     
      Serial.print(periodo);
      Serial.println();
      Capacitancia = calcularCapacitancia(periodo , Resistor );
      Serial.print(Capacitancia);
      Serial.print(" ");
      Serial.print(submultiplo[indice]);
      Serial.println("Farad");
  }
  
}

unsigned long medirConstanteRC(float v_max){
  
    unsigned long start = millis();
    unsigned long intervalo;
    float v_in = 0;

    //Contando o tempo de carga do Capacitor com o "laço do while"
    do{
         v_in = analogRead(A0) * (5.0 / 1023.0);

      }while(v_in < v_max);
  
    intervalo = millis();
    intervalo = intervalo - start;
    return intervalo;
}

float calcularCapacitancia(float constanteRC , float resistor){
    float capacitancia;
    float subMultiplo = calcularSubMultiplo( constanteRC , resistor );
    constanteRC = constanteRC / 1000; //converter para segundo
    float subUnidade = pow(10.0,subMultiplo);
    capacitancia = (constanteRC * subUnidade)/resistor;
    
    if(subMultiplo < 9){
          indice = 1;
    }else{
          indice = 2;
            }
  
    return capacitancia;
  }

float calcularSubMultiplo(float constanteRC , float resistor ){
  float constanteRC_referencia;
  
  constanteRC_referencia = (0.1 * resistor) / 1000000.0;

  if(constanteRC >= constanteRC_referencia){
      return 6.0;
    }else{
      return 9.0;
      }
}
