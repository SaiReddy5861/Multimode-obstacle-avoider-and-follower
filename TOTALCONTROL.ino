#include <Servo.h>       
Servo eyes;
#define trig 2
#define echo 3
int distance = 100;
boolean state = false;

#define leftsensor 7
#define rightsensor 6
int leftstatus, rightstatus;

int received;

void setup(){
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode (trig, OUTPUT);

  eyes.attach(12);
  eyes.write(90);
  delay(2000);}
  
int lookright(){  
  eyes.write(36);
  delay(500);
  int distance = measuredistance();
  delay(100);
  eyes.write(90);
  return distance;}

int lookleft(){
  eyes.write(144);
  delay(500);
  int distance = measuredistance();
  delay(100);
  eyes.write(90);
  return distance;}

int measuredistance(){
  delay(70);
  long distance,duration;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration/2)/29.1;
  if (distance==0){
    distance=250;}
  return distance;}

void measurelength(){
  delay(70);
  long distance,duration;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration/2)/29.1;
  Serial.println(distance);}


void stopmoving(){
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);}

void forward(){
  if(!state){
    state = true;
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);}}

void moveforward(){
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);}
    
void movebackward(){
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);}
  
void backward(){
  state =false;
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);}

void turnleft(){
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);}
  
void spinleft(){
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(300);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);}
  
void spinright(){
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(300);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);}

void turnright(){
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);}

void turnaround(){
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(700);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(11, LOW);}
  
void avoidobstacles(){
  if (distance > 30)
  {forward();}
  else {
  int rightdistance = 0;
  int leftdistance = 0;
    delay(50);
    stopmoving();
    delay(300);
    backward();
    delay(400);
    stopmoving();
    delay(300);
    leftdistance = lookleft();
    delay(300);
    rightdistance = lookright();
    delay(300);
    if (leftdistance > rightdistance){
      spinleft();}
    else if (rightdistance > leftdistance){
      spinright();}
      else {turnaround();}}
    distance = measuredistance();}

void displaysignalpattern(){
  leftstatus = digitalRead(leftsensor);
  rightstatus = digitalRead(rightsensor);
  Serial.print(leftstatus);
  Serial.print("\t");
  Serial.println(rightstatus);
  delay(1000);}
      
void linefollower(){
  leftstatus = digitalRead(leftsensor);
  rightstatus = digitalRead(rightsensor);
  if (leftstatus == 0){
    digitalWrite(10, 1);
    digitalWrite(11, 0);}
  else {
    digitalWrite(10, 0);
    digitalWrite(11, 0);}
if (rightstatus == 0){
    digitalWrite(8, 0);
    digitalWrite(9, 1);}
  else {
    digitalWrite(8, 0);
    digitalWrite(9, 0);}}
    
void avoidedges(){
  leftstatus = digitalRead(leftsensor);
  rightstatus = digitalRead(rightsensor);
  if(leftstatus ==0 && rightstatus == 0){moveforward();}
  else if(leftstatus == 1 && rightstatus == 0){
    stopmoving();
    delay(300);
    backward();
    delay(400);
    spinright();}
  else if(leftstatus == 0 && rightstatus == 1){
    stopmoving();
    delay(300);
    backward();
    delay(400);
    spinleft();}
  else if(leftstatus == 1 && rightstatus ==1){
    stopmoving();
    delay(300);
    backward();
    delay(400);
    turnaround();}} 
  
void totalcontrol(){
  if (Serial.available()){
    received = Serial.read();
    if (received == '8') {moveforward();}
    else if(received == '2') {movebackward();}
    else if(received == '4') {turnleft();}
    else if(received == '6') {turnright();}
    else if(received == '5') {stopmoving();}}
    else if(received == 'L') {linefollower();}
    else if(received == 'O') {avoidobstacles();}
    else if(received == 'm') {avoidedges();}}

void loop() {
 totalcontrol();}
