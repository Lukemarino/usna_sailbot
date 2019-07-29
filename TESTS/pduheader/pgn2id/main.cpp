/** 
    TESTS/pduheader/pgn2id/main.cpp
    Test of PGN to CAN ID encoding for PDU header in nmea2k
    Dennis Evangelista, 2019

    This test checks that PduHeader is correctly
    translating between 32(29) bit CAN id and 
    the various ISO11783-3 bit fields. 

    Test cases are drawn from p5 of ISO 11783-3:1998(E) 
    Tractors and machinery for agriculture and forestry --
    serial control and communications data network -- part 3:
    data link layer.
 */

#include "mbed.h"
#include "stdio.h"
#include "unity.h"
#include "nmea2k.h"

Serial pc(USBTX,USBRX);
nmea2k::PduHeader foo; 

int main(void){
  pc.printf("nmea2k version ");
  pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nPduHeader PGN to CAN ID test\r\n");

  pc.printf("Testing PGN 127245 Rudder with different source address SA\r\n");
  foo.set_id(0);
  foo.set_pgn(127245);
  foo.set_sa(0); 
  TEST_ASSERT_EQUAL_MESSAGE(0x01f10d00,foo.id(),"failed to decode id");
  TEST_ASSERT_EQUAL_MESSAGE(127245,foo.pgn(),"failed to decode pgn");
  for (unsigned int i=0; i<256; i++){
    pc.printf("PGN 127245 with SA = %d\r\n",i); 
    foo.set_sa(i);
    TEST_ASSERT_EQUAL_MESSAGE(0x01f10d00+i,foo.id(),"failed to decode id");
    TEST_ASSERT_EQUAL_MESSAGE(127245,foo.pgn(),"failed to decode pgn");
  }

  pc.printf("Testing PGN 130306 Wind Data with different priority P\r\n");
  foo.set_id(0);
  foo.set_pgn(130306);
  foo.set_da(0x41); // should throw warning
  foo.set_da(0xff); // should be ok
  foo.set_sa(0x42); 
  for (unsigned int i=0; i<7; i++){
    pc.printf("PGN 130306 with P = %d\r\n",i);
    foo.set_p(i);
    TEST_ASSERT_EQUAL_MESSAGE(0x01fd0200+(i<<26)+0x42,foo.id(),"failed to decode id");
    TEST_ASSERT_EQUAL_MESSAGE(130306,foo.pgn(),"failed to decode pgn");
  }
    
} // int main(void)

