char num;
void setup()
{
  pinMode(6, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
    while(Serial.available() > 0)
    {
        num=Serial.read();
        num-='0';
        digitalWrite(6,LOW);
        delay(10);
        if(num & 0x01)
            digitalWrite(2,HIGH);
        else
            digitalWrite(2,LOW);

        if((num>>1) & 0x01)
            digitalWrite(3,HIGH);
        else
            digitalWrite(3,LOW);
        if((num>>2) & 0x01)
            digitalWrite(4,HIGH);
        else
            digitalWrite(4,LOW);
        if((num>>3) & 0x01)
            digitalWrite(5,HIGH);
        else
            digitalWrite(5,LOW);
        delay(10);
        digitalWrite(6,HIGH);
        
    }
}