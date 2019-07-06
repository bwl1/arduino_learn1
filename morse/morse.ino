char Morse[][4] = {
    {'.','-',' ',' '},      //A
    {'-','.','.','.'},      //B
    {'-','.','-','.'},      //C
    {'-','.','.',' '},      //D
    {'.',' ',' ',' '},      //E
    {'.','.','-','.'},      //F
    {'-','-','.',' '},      //G
    {'.','.','.','.'},      //H
    {'.','.',' ',' '},      //I
    {'.','-','-','-'},      //J
    {'-','.','-',' '},      //K
    {'.','-','.','.'},      //L
    {'-','-',' ',' '},      //M
    {'-','.',' ',' '},      //N
    {'-','-','-',' '},      //O
    {'.','-','-','.'},      //P
    {'-','-','.','-'},      //Q
    {'.','-','.',' '},      //R
    {'.','.','.',' '},      //S
    {'-',' ',' ',' '},      //T
    {'.','.','-',' '},      //U
    {'.','.','.','-'},      //V
    {'.','-','-',' '},      //W
    {'-','.','.','-'},      //X
    {'-','.','-','-'},      //Y
    {'-','-','.','.'}       //Z
    
}; //摩尔斯码表

int LED = 1; //led端口12
int dotTime = 250; //单位时间0.25s

void setup()
{
    
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    //Initialize all peripherals
}

void loop()
{
   
    String str = "";
    String morse_code = "";
    int i, t,serialFlag = 0， cnt = 0;

    while (Serial.available() > 0)
    {
        serialFlag = 1;
        str += char(Serial.read());
        delay(1);
        cnt++;
    }

    if(serialFlag)
    {
        for (i = 0; i < cnt; i++)
        {
            for (t = 0; t < 4; t++)
            {
                if (str[i] >= 97 && str[i] <= 122) //小写字母
                    morse_code += char(Morse[int(str[i] - 97)][t]); //查表
            }
            morse_code += ' ';
        }
        
        for(i = 0; i < cnt; i++)
        {
            for (t = 0; t < 4; t++)
            {
                switch(morse_code[t+i*4+i-1])
                {
                    case '-': blinkDash(LED, dotTime);
                    case '.': blinkDot(LED, dotTime);
                    case ' ': blink_W_Space(LED, dotTime);
                }
                blink_C_Space(LED, dotTime); //字符结束
            }
        }

    }
    //delay(1);
}

void blinkDot(int _pin, int _dottime)
{
	digitalWrite(_pin,HIGH);
	delay(_dottime);
	digitalWrite(_pin,LOW);
	delay(_dottime);
}

void blinkDash(int _pin, int _dottime)
{
	digitalWrite(_pin,HIGH);
	delay(_dottime*4);
	digitalWrite(_pin,LOW);
	delay(_dottime);
}

void blink_C_Space(int _pin, int _dottime)
{
	digitalWrite(_pin,LOW);
	delay(_dottime*3);
}

void blink_W_Space(int _pin, int _dottime)
{
	digitalWrite(_pin,LOW);
	delay(_dottime*7);
}
