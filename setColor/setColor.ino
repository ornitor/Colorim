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
      setColor(255, 0, 0);
      Serial.print(map(meanSoftAnalog(A0,10,2),2,623,0,100));
      Serial.print("\t");
      delay(1);
      setColor( 0, 255,  0);
      Serial.print(map(meanSoftAnalog(A0,10,2),2,804,0,100));
      Serial.print("\t");
      delay(1);
      setColor(0, 0, 255);
      Serial.print(map(meanSoftAnalog(A0,10,2),2,708,0,100));
      Serial.print("\t");
      delay(1);
      setColor(255, 255, 255);
      Serial.println(map(meanSoftAnalog(A0,10,2),2,872,0,100));
      Serial.print("");
      setColor(0,0,0);
     delay(1000);
 }



float getConcentra(int port)  //0 0;33   100 4.94
{
      return map(meanSoftAnalog(port,10,2),0,1024,0,1024);   // *200./1023.-55;
}
 

float meanSoftAnalog(int port, int n, int nd)
{
     unsigned long lbuf[10];
     int temp;
delay(30);
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
      analogWrite(9,r);
      analogWrite(10,g);
      analogWrite(11,b);
      
  
}
