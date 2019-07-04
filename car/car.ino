void setup()
{
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    String inputbuf = "";
    int serialFlag = 0;
    int i;
    int cnt = 0;

    while (Serial.available() > 0)
    {
            serialFlag = 1;
            inputbuf += char(Serial.read());
            cnt++;
            delay(1);
    }

    if (serialFlag)
    {
        for(i = 0; i < cnt; i++)
        {
            switch(inputbuf[i])
            {
                case 'f':   Forward();
                    break;
                case 'b':   Backward();
                    break;
                case 'l':   Turnleft();
                    break;
                case 'r':   TurnRight();
                    break;
                case 's':   Stop();
                    break;
                default:
                    break;
            }

        }

    }

}

void Forward()
{
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
}

void Backward()
{
    digitalWrite(3, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
}

void Turnleft()
{
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
}

void TurnRight()
{
    digitalWrite(3, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
}

void Stop()
{
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
}
