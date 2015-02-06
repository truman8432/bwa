/*
Copyright 2014 Intel
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

#ifndef _FAST_EXTEND_BITV64_H
#define _FAST_EXTEND_BITV64_H

#include <stdint.h>
#include <stdlib.h>
#include <limits>

class BitVec64 {

  uint64_t bitV ;

  explicit BitVec64(uint64_t val): bitV(val) {}

public:
  
  BitVec64(): bitV(0x0) {}

  inline bool getLSB() const {
    return bitV & 0x1 ;
  }
  
  inline uint16_t getLow16Bits() const {
    return (uint16_t) bitV ;
  }

  inline void setAll64BitWords(uint64_t val) {
    bitV = val ;
  }

  inline void setAllOnes () {
    bitV = 0xFFFFFFFFFFFFFFFF ;
  }

  inline void setAllZeroes () {
    bitV = 0x0000000000000000 ;
  }

  inline void setAllBits (bool bit) {
    bitV = bit ? 0xFFFFFFFFFFFFFFFF : 0x0 ;
  }

  inline void setLSBClearRest (bool bit) {
    bitV = bit ;
  }

  inline void setBit(int bitIndex, bool bit) {
    uint64_t mask = ((uint64_t)0x1) << bitIndex ;
    bitV = bit ? (bitV | mask) : (bitV & ~mask) ;
  }

  inline void shiftLeftAndInsert (bool newBit) {
    bitV = (bitV << 1) | ((uint8_t) newBit) ;
  }

  inline void shiftLeft () {
    bitV <<= 1 ;
  }

  inline BitVec64 shiftProbesRight(int probeOffset, const BitVec64& shiftCnt) const {
    // The carryout bit is at location probeOffset+1
    return BitVec64(bitV >> (probeOffset+1)) ;
  }

  void setWord (int index, uint64_t w) {
    bitV = w ;
  }

  inline void orBitAtPosition (bool newBit, int index) {
    bitV |= (((uint64_t)newBit) << index) ;
  }
  
  inline bool getMSB() const {
    return bitV & 0x8000000000000000 ;
  }

  inline BitVec64 operator~ () const {
    return BitVec64(~this->bitV) ;
  }

  inline BitVec64 operator& (const BitVec64& other) const {
    return BitVec64(this->bitV & other.bitV) ;
  }

  inline BitVec64 andnot (const BitVec64& other) const {
    return *this & (~other) ;
  }

  inline BitVec64 operator| (const BitVec64& other) const {
    return BitVec64(this->bitV | other.bitV) ;
  }

  inline BitVec64 operator^ (const BitVec64& other) const {
    return BitVec64(this->bitV ^ other.bitV) ;
  }

  inline BitVec64 operator+ (const BitVec64& other) const {
    return BitVec64(this->bitV + other.bitV) ;
  }

  static bool isQueryLengthOk(int qlen) {
    return qlen < 64 ;
  }

  bool getBit (int index) const {
    return (bitV >> index) & 0x1 ;
  }

  friend std::ostream& operator<< (std::ostream& os, const BitVec64& b) {
    os << b.bitV ;
    return os ;
  }

  friend class EDVec64 ;
  friend class EDVec128Every16 ;
  friend class EDVec64Every8 ;
  friend class EDVec32Every4 ;
  friend class EDVec16Every1 ;
} ;



#endif // #ifndef _FAST_EXTEND_BITV64_H
