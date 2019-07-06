# 课程总结
## 第一天：开源硬件入门

- Linux

Linux是一套免费使用和自由传播的类Unix操作系统，是一个基于POSIX和UNIX的多用户、多任务、支持多线程和多CPU的操作系统。它能运行主要的UNIX工具软件、应用程序和网络协议。它支持32位和64位硬件。Linux继承了Unix以网络为核心的设计思想，是一个性能稳定的多用户网络操作系统。
Linux操作系统诞生于1991 年10 月5 日（这是第一次正式向外公布时间）。Linux存在着许多不同的Linux版本，但它们都使用了Linux内核。Linux可安装在各种计算机硬件设备中，比如手机、平板电脑、路由器、视频游戏控制台、台式计算机、大型机和超级计算机。
严格来讲，Linux这个词本身只表示Linux内核，但实际上人们已经习惯了用Linux来形容整个基于Linux内核，并且使用GNU 工程各种工具和数据库的操作系统。

- Arduino

Arduino是一款便捷灵活、方便上手的开源电子原型平台。包含硬件（各种型号的Arduino板）和软件（Arduino IDE)。由一个欧洲开发团队于2005年冬季开发。其成员包括Massimo Banzi、David Cuartielles、Tom Igoe、Gianluca Martino、David Mellis和Nicholas Zambetti等。
它构建于开放原始码simple I/O介面版，并且具有使用类似Java、C语言的Processing/Wiring开发环境。主要包含两个的部分：硬件部分是可以用来做电路连接的Arduino电路板；另外一个则是Arduino IDE，你的计算机中的程序开发环境。你只要在IDE中编写程序代码，将程序上传到Arduino电路板后，程序便会告诉Arduino电路板要做些什么了。
Arduino能通过各种各样的传感器来感知环境，通过控制灯光、马达和其他的装置来反馈、影响环境。板子上的微控制器可以通过Arduino的编程语言来编写程序，编译成二进制文件，烧录进微控制器。对Arduino的编程是通过 Arduino编程语言 (基于 Wiring)和Arduino开发环境(基于 Processing)来实现的。基于Arduino的项目，可以只包含Arduino，也可以包含Arduino和其他一些在PC上运行的软件，他们之间进行通信 (比如 Flash, Processing, MaxMSP)来实现。

- GitHub

GitHub是一个面向开源及私有软件项目的托管平台，因为只支持git 作为唯一的版本库格式进行托管，故名GitHub。
GitHub于2008年4月10日正式上线，除了Git代码仓库托管及基本的 Web管理界面以外，还提供了订阅、讨论组、文本渲染、在线文件编辑器、协作图谱（报表）、代码片段分享（Gist）等功能。目前，其注册用户已经超过350万，托管版本数量也是非常之多，其中不乏知名开源项目 Ruby on Rails、jQuery、python 等。


## 第二天：Arduino入门 摩尔斯编码

- Arduino基本功能

```

1//数字 IO 口辒入辒出模式定义凼数 
pinMode(pin, mode)

2//设置数字 IO 口输出电平定义凼数 
digitalWrite(pin, value)

3//获取 IO 口输出电压凼数
digitalRead(pin, value)

4//获得引脚模拟量电压值
analoRead(pin)

5//延时函数

delay(1)//延时1毫秒

delayMicroseconds(1);//是指延时1微秒


6//初始化串口
Serial.begin() 

7//串口发送数据
Serial.println()
Serial.print()

8//串口接收数据
/*串行数据的输入相对要麻烦点，多了一步判断是否有数据收到的操作，
使用函数Serial.available(),之后使用函数 Serial.read()提取收到的数据。*/
Serial.available()
Serial.read()

```

- led闪烁
```
void setup() 
{
	pinMode(13, OUTPUT);
}
void loop() {
	digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(1000);              // wait for a second
	digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
	delay(1000);              // wait for a second
}
```

- 串口通信
```
int val;
int ledpin=13;

void setup()
{
  Serial.begin(9600);
  pinMode(ledpin,OUTPUT);
}

void loop()
{
  val=Serial.read();
  if(val=='R')
  {
    digitalWrite(ledpin,HIGH);//点亮数字13 口LED。
    delay(500);
    digitalWrite(ledpin,LOW);//熄灭数字13 口LED
    delay(500);
    Serial.println("Hello World!");//显示“Hello World！”字符串
  }
```

## 第三天：控制小车 控制数码管 逻辑芯片
- 小车程序

核心代码:

接收串口命令 控制小车运动
```
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
```

- CD4511驱动7段数码管

>CD4511 是一片 CMOS BCD—锁存/7 段译码/驱动器，用于驱动共阴极 LED （数码管）显示器的 BCD 码-七段码译码器。具有BCD转换、消隐和锁存控制、七段译码及驱动功能的CMOS电路能提供较大的拉电流。可直接驱动共阴LED数码管。

>A0~A3：二进制数据输入端
/BI：输出消隐控制端
LE：数据锁定控制端
/LT：灯测试端
Ya~Yg：数据输出端
VDD：电源正
VSS：接地

控制代码：
```
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
```