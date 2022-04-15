 
float V_in;
float V_Min;
float V_Max;
float Resistor;
float Capacitancia;
unsigned long periodo;
//unsigned long inicio;
//boolean medir;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  Resistor = 2200.0;

}

void loop() {
  // put your main code here, to run repeatedly:

  float V_Min = 10.23 * ( 5.0 / 1023.0);
  float V_Max = 646.536 * ( 5.0 / 1023.0);
  
  V_in = analogRead(A0) * (5.0 / 1023.0);
  
  if ((V_in >= V_Min) && (V_in <= V_Max)){
    
      periodo = medirConstanteRC(V_Min, V_Max);     
      Serial.print(periodo);
      Serial.write("  miliSegundos");
      Serial.println();
      Capacitancia = calcularCapacitancia(periodo , Resistor );
      Serial.println(Capacitancia);
  }
  
}

unsigned long medirConstanteRC(float v_min, float v_max){
  
  unsigned long start = millis();
  unsigned long intervalo;
     float v_in = analogRead(A0) * (5.0 / 1023.0);

  while(v_in <= v_max){
      
      v_in = analogRead(A0) * (5.0 / 1023.0);      
            
  }
  intervalo = millis();
  intervalo = intervalo - start;
  return intervalo;
}

float calcularCapacitancia(float constanteRC , float resistor){
    float capacitancia;
    float expoente = calcularSubUnidade( constanteRC , resistor );
    constanteRC = constanteRC / 1000; //converter para segundo
    float subUnidade = pow(10.0,expoente);
    capacitancia = (constanteRC * subUnidade)/resistor;
    return capacitancia;
  }

float calcularSubUnidade(float constanteRC , float resistor ){
  float constanteRC_referencia;
  
  constanteRC_referencia = (0.1 * resistor) / 1000000.0;

  if(constanteRC >= constanteRC_referencia){
      return 6.0;
    }else{
      return 9.0;
      }
}
