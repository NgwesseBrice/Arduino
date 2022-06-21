 const int ledCount = 11;

 int ledPins[] = {2,4,5,6,7,8,9,10,11,12,13};

void setup() {
  // put your setup code here, to run once:


      for(int i = 0; i < ledCount; i++){
           pinMode(ledPins[i], OUTPUT);
      }

}

void loop() {
  // put your main code here, to run repeatedly:


     for(int i = 0; i < ledCount; i++){
  barGraphDisplay(i);
}
}





bool barGraphDisplay(int ledOn){
    for(int i=0; i<ledCount; i++){
        if(i == ledOn){
          digitalWrite(ledPins[i],HIGH);
          delay(500);
          digitalWrite(ledPins[i],LOW);
          delay(500);
        }
    }
}
