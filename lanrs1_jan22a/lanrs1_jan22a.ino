const int micPin = A0;
const int outPin = 3; 

float gain = 2; 
int bias = 512;

void setup() {
  ADCSRA &= ~(bit(ADPS0) | bit(ADPS1) | bit(ADPS2)); 
  ADCSRA |= (bit(ADPS2)); 

  pinMode(outPin, OUTPUT);
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS20); 

  long sum = 0;
  for(int i = 0; i < 500; i++) sum += analogRead(micPin);
  bias = sum / 500;
}

void loop() {
  int val = analogRead(micPin);
  
  float amplitude = (float)(val - bias);

  float invertedAmplitude = amplitude * (-gain);
  int outVal = (int)(127 + invertedAmplitude);

  if (outVal > 255) outVal = 255;
  if (outVal < 0) outVal = 0;

  OCR2B = outVal; 
}
