/*
Copyright 2014 Intel
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

#ifndef _FAST_EXTEND_VEC_H
#define _FAST_EXTEND_VEC_H

#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>

#ifdef USE_SSE4
#include <tmmintrin.h>
#include <smmintrin.h>

#define BLENDV(__v1, __v2, __pred)		\
  _mm_blendv_epi8(__v1, __v2, __pred)

#else // #ifdef USE_SSE4

#define BLENDV(__v1, __v2, __pred)					\
  _mm_or_si128(_mm_andnot_si128(__pred, __v1), _mm_and_si128(__v2, __pred))

#endif // #ifdef USE_SSE4

using std::cout ;
using std::endl ;

inline void printVec16(const __m128i& v) {
  
  cout << "{" ;
  cout << " " << _mm_extract_epi16(v, 0) ;
  cout << " " << _mm_extract_epi16(v, 1) ;
  cout << " " << _mm_extract_epi16(v, 2) ;
  cout << " " << _mm_extract_epi16(v, 3) ;
  cout << " " <<_mm_extract_epi16(v, 4) ;
  cout << " " <<_mm_extract_epi16(v, 5) ;
  cout << " " <<_mm_extract_epi16(v, 6) ;
  cout << " " <<_mm_extract_epi16(v, 7) ;

  cout << "}" << endl ;
}



#endif // #ifdef _FAST_EXTEND_VEC_H
