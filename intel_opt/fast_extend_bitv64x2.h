/*
Copyright 2014 Intel
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

#ifndef _FAST_EXTEND_BITV64x2_H
#define _FAST_EXTEND_BITV64x2_H

#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std ;

class BitVec64x2 {

  uint64_t bitV[2] ;

public:
  
  BitVec64x2() {
    bitV[0] = 0x0 ;
    bitV[1] = 0x0 ;
  }

  inline bool getLSB() const {
    return bitV[0] & 0x1 ;
  }

  inline uint16_t getLow16Bits() const {
    return (uint16_t) bitV[0] ;
  }

  inline void setAll64BitWords(uint64_t val) {
    bitV[0] = bitV[1] = val ;
  }

  inline void setAllOnes () {
    bitV[0] = 0xFFFFFFFFFFFFFFFF ;
    bitV[1] = 0xFFFFFFFFFFFFFFFF ;
  }

  inline void setAllZeroes () {
    bitV[0] = 0x0000000000000000 ;
    bitV[1] = 0x0000000000000000 ;
  }

  inline void setAllBits (bool bit) {
    if (bit) setAllOnes() ;
    else setAllZeroes() ;
  }

  inline void setLSBClearRest (bool bit) {
    bitV[0] = bit ;
    bitV[1] = 0x0 ;
  }

  inline void shiftLeftAndInsert (bool newBit) {
    bitV[1] <<= 1 ;
    bitV[1] |= (bitV[0] >> 63) ;
    bitV[0] <<= 1 ;
    bitV[0] |= ((uint8_t) newBit) ;
  }

  inline void shiftLeft () {
    bitV[1] <<= 1 ;
    bitV[1] |= (bitV[0] >> 63) ;
    bitV[0] <<= 1 ;
  }

  
  inline BitVec64x2 shiftProbesRight(int probeOffset, const BitVec64x2& shiftCnt) const {
    BitVec64x2 r ;

    r.bitV[0] = bitV[0] >> (probeOffset + 1) ;

    if (probeOffset == 15) 
      r.bitV[0] |= ((bitV[1] & 0x1) << 48) ; 

    r.bitV[1] = bitV[1] >> (probeOffset + 1) ;
    return r ;
  }
  

  void setWord (int index, uint64_t w) {
    bitV[index] = w ;
  }

  inline BitVec64x2 operator~ () const {
    BitVec64x2 r ;
    r.bitV[0] = ~this->bitV[0] ;
    r.bitV[1] = ~this->bitV[1] ;
    return r ;
  }

  inline BitVec64x2 operator& (const BitVec64x2& other) const {
    BitVec64x2 r ;
    r.bitV[0] = this->bitV[0] & other.bitV[0] ;
    r.bitV[1] = this->bitV[1] & other.bitV[1] ;
    return r ;
  }

  inline BitVec64x2 andnot (const BitVec64x2& other) const {
    return *this & (~other) ;
  }

  inline BitVec64x2 operator| (const BitVec64x2& other) const {
    BitVec64x2 r ;
    r.bitV[0] = this->bitV[0] | other.bitV[0] ;
    r.bitV[1] = this->bitV[1] | other.bitV[1] ;
    return r ;
  }

  inline BitVec64x2 operator^ (const BitVec64x2& other) const {
    BitVec64x2 r ;
    r.bitV[0] = this->bitV[0] ^ other.bitV[0] ;
    r.bitV[1] = this->bitV[1] ^ other.bitV[1] ;
    return r ;
  }


  inline BitVec64x2 operator+ (const BitVec64x2& other) const {
    BitVec64x2 r ;
    r.bitV[0] = this->bitV[0] + other.bitV[0] ;
    r.bitV[1] = this->bitV[1] + other.bitV[1] + (r.bitV[0] < this->bitV[0]) ;
    return r ;
  }


  static bool isQueryLengthOk(int qlen) {
    return qlen <= 127 ;
  }

  friend std::ostream& operator<< (std::ostream& os, const BitVec64x2& b) {
    os << "{" << b.bitV[0] << ", " << b.bitV[1] << "}" ;
    return os ;
  }

  friend class EDVec64x2 ;
  friend class EDVec128Every16 ;
} ;



#endif // #ifndef _FAST_EXTEND_BITV64x2_H
