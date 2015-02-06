/*
Copyright 2014 Intel
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

#ifndef _FAST_EXTEND_DIST_H
#define _FAST_EXTEND_DIST_H

//
// This class handles the distance computations by reading the probes at BitVec, and
// storing the computed distance values in EDVec.
//
template<class BitVec, class EDVec>
class DistVec {

  EDVec dist_, mask_ ;
  BitVec probeShiftCnt_ ;
  int queryLen_, msWordIndex_, probeOffset_ ;
  
 public: 
  
 DistVec(int queryLen):
  queryLen_(queryLen), msWordIndex_(EDVec::getLastWordIndexFor(queryLen)),
    probeOffset_(EDVec::getProbeOffsetFor(queryLen)) {

    probeShiftCnt_.setAll64BitWords(probeOffset_+1) ;
    mask_.setWordsAsMask() ;
  }

  const EDVec& getVec() const {
    return dist_ ;
  }

  void initDist(int initU0, int initU1) {
    dist_.setWordsAsDist(queryLen_, initU0 - initU1) ;
  }

  void addDist (const BitVec& LP0, const BitVec& LP1) {
 
    dist_ += (EDVec(LP0.shiftProbesRight(probeOffset_, probeShiftCnt_)) & mask_) ;
    dist_ -= (EDVec(LP1.shiftProbesRight(probeOffset_, probeShiftCnt_)) & mask_) ;
  }

  EDVec getDeltaDistVec(const BitVec& LP0, const BitVec& LP1) {
    EDVec r = EDVec(LP0.shiftProbesRight(probeOffset_, probeShiftCnt_)) & mask_ ;
    r -= EDVec(LP1.shiftProbesRight(probeOffset_,probeShiftCnt_)) & mask_ ;

    return r ;
  }

  void addDist (const EDVec& deltaDist) {
    dist_ += deltaDist ;
  }

  int getValidDistCnt() const {
    return msWordIndex_ + 1 ;
  }

  int getProbeColumn(int index) const {
    return EDVec::getDistAt(index, queryLen_) - 1 ;
  }

  int getDist(int index) const {
    return (int) dist_.getWord(index) ;
  }

  int getTotalDist() const {
    return (int) dist_.getWord(msWordIndex_) ;
  }

  void setMin (const DistVec& other) {
    this->dist_.setMin(other.dist_) ;
  }

  friend std::ostream& operator<< (std::ostream& os, const DistVec& d) {
    os << d.dist_ ;
    return os ;
  }

} ;


#endif // #ifndef _FAST_EXTEND_DIST_H
