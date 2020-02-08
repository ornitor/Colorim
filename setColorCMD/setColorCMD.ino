//aboborta
String str = "";
String commandbuf[10];

float cor[3];

void setup() 
{
      pinMode(9, OUTPUT);
      pinMode(10, OUTPUT);
      pinMode(11, OUTPUT);
      Serial.begin(115200);
      Serial.println("Colorimetro, Bom dia!");
}

void loop() 
{
    String *com = getCommand();
    if(com != 0){
      //Serial.println(*com);
      interpreta(*com);
    }
    if(true) {  getColorOff(A0,cor); corToConsole() ;delay(1500);};  // corToPLotter()
}


void interpreta(String  c)
{
         split(c.c_str(),", ");
        if(commandbuf[0].compareTo("G1")==0){     
        } else if(commandbuf[0].compareTo("Q1")==0) {  getColorOff(A0,cor); corToConsole();  // identifica o Agente arduino
        } else if(commandbuf[0].compareTo("Q2")==0) {  getColor(A0,cor); corToConsole();  // identifica o Agente arduino
        } else 
            Serial.println("Ahn?");        
        str = "";
}


void corToPLotter()
{
  Serial.print(cor[2]);
  Serial.print("\t");
  Serial.print(cor[0]);
  Serial.print("\t");
  Serial.println(cor[1]);
  }


void corToConsole()
{
  Serial.print(cor[0]);
  Serial.print("\t");
  Serial.print(cor[1]);
  Serial.print("\t");
  Serial.println(cor[2]);
  }

void getColorOff(int port,float cor[])
{
       setColor(255, 0, 0);
       cor[0] = fmap(meanSoftAnalog(port,10,2),2,642,0,100);
       setColor(0, 255, 0);
       cor[1] = fmap(meanSoftAnalog(port,10,2),2,804,0,100);
       setColor(0, 0, 255);
       cor[2] = fmap(meanSoftAnalog(port,10,2),2,706, 0,100);
       setColor(0, 0, 0);

}

void getColor(int port,float cor[])
{
       setColor(255, 0, 0);
       cor[0] = meanSoftAnalog(port,10,2);
       setColor(0, 255, 0);
       cor[1] = meanSoftAnalog(port,10,2);
       setColor(0, 0, 255);
       cor[2] = meanSoftAnalog(port,10,2);
       setColor(0, 0, 0);
}

float getConcentra(int port)  //0 0;33   100 4.94
{
      return map(meanSoftAnalog(port,10,2),0,1024,0,1024);   // *200./1023.-55;
}
 

float meanSoftAnalog(int port, int n, int nd)
{
      unsigned long lbuf[10];
      int temp;
      delay(100);
      for(int i=0;i<n;i++) { 
                  lbuf[i]=analogRead(port);
                  //delay(1);
                  }
      for(int i=0;i<n-1;i++){
            for(int j=i+1;j<n;j++){
                  if(lbuf[i]>lbuf[j]){
                        temp=lbuf[i];
                        lbuf[i]=lbuf[j];
                        lbuf[j]=temp;
                  }
            }
      }
      unsigned long int avgValue =0;
      for(int i=nd;i<n-nd;i++)
            avgValue+=lbuf[i];
      return (float)avgValue/(float)(n-2*nd);
}



void setColor(int r, int g, int b)
{
      analogWrite(10,r);
      analogWrite(11,g);
      analogWrite(12,b);
      
  
}

String *getCommand() // run over and over
{
   while(Serial.available()){
   char c = Serial.read();
   if (c != '\n')
     str = str + c;
   else{
    //Serial.println("chegou: " + str);
    return &str;
   }
  }
  return 0;
}




void split(char * str, char *delimitador)
{
    char *str1, *token;
    char *saveptr1;
    int j=0;
    commandbuf[0] = strtok_r(str, delimitador, &saveptr1);
    for (j = 1;j<10 ; j++) {
        commandbuf[j] = strtok_r(NULL, delimitador, &saveptr1);
        if (commandbuf[j] == NULL)
            break;
    }
}

float fmap(float val,float in1, float in2, float out1, float out2)
{
    return  (val - in1)*(out2-out1)/(in2-in1) + out1;
}
