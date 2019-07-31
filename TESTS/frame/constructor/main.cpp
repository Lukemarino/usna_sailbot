/** @file TESTS/frame/constructor/main.cpp
    @brief Test of nmea2k::Frame() constructors and nmea2k::~Frame() destructor
    Dennis Evangelista, 2019

    May wish to uncomment the debug() statements to check when
    constructors and destructors are called... 
*/

#include "Frame.h"

#include "mbed.h"
#include "stdio.h"
#include "unity.h"



Serial pc(USBTX,USBRX); 
nmea2k::Frame() f; 



int main(void){
  //pc.printf("nmea2k version ");
  //pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nTest of nmea2k::Frame()\r\n");
  f = nmea2k::Frame();
  pc.printf("f.id = %08x rando junk\r\n",f.id);
  for (int i=0; i<f.len; i++)
    pc.printf("f.data[i] = %02x rando junk\r\n",f.data[i]);
  pc.printf("f.len = %d should be 8\r\n",f.len);
  TEST_ASSERT_EQUAL_MESSAGE(8,f.len,"unexpected f.len");
  TEST_ASSERT_EQUAL_MESSAGE(mbed::CANData,f.type,"unexpected CAN type");
  TEST_ASSERT_EQUAL_MESSAGE(mbed::CANExtended,f.format,"unexpected CAN format");

  pc.printf("now testing destructor\r\n");
  delete f;
  TEST_ASSERT_NULL_MESSAGE(f,"failed destructor");

  pc.printf("testing constructor with data\r\n");
  char counter = 0; 
  f = nmea2k::Frame(1337,&counter,1);
  TEST_ASSERT_EQUAL_MESSAGE(1337,f.id,"failed to set id");
  TEST_ASSERT_EQUAL_MESSAGE(0,f.data[0],"failed to set data");
  TEST_ASSERT_EQUAL_MESSAGE(1,f.len,"failed to set len");
  TEST_ASSERT_EQUAL_MESSAGE(mbed::CANData,f.type,"unexpected CAN type");
  TEST_ASSERT_EQUAL_MESSAGE(mbed::CANExtended,f.format,"unexpected CAN format");

  pc.printf("testing constructor with unsigned char data\r\n");
  unsigned char counter = {7,6,5,4}; 
  f = nmea2k::Frame(1337,&counter,4);
  TEST_ASSERT_EQUAL_MESSAGE(1337,f.id,"failed to set id");
  TEST_ASSERT_EQUAL_MESSAGE(7,f.data[0],"failed to set data");
  TEST_ASSERT_EQUAL_MESSAGE(6,f.data[1],"failed to set data");
  TEST_ASSERT_EQUAL_MESSAGE(5,f.data[2],"failed to set data");
  TEST_ASSERT_EQUAL_MESSAGE(4,f.data[3],"failed to set data");
  TEST_ASSERT_EQUAL_MESSAGE(4,f.len,"failed to set len");
  TEST_ASSERT_EQUAL_MESSAGE(mbed::CANData,f.type,"unexpected CAN type");
  TEST_ASSERT_EQUAL_MESSAGE(mbed::CANExtended,f.format,"unexpected CAN format");
  
  pc.printf("once again, i am become shiva, destroyer of worlds\r\n");
  delete f;
  TEST_ASSERT_NULL_MESSAGE(f,"failed destructor"); 
} // int main(void)