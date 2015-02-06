/*
Copyright 2014 Intel
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/


#include <immintrin.h>

#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

using std::cout ;
using std::endl ;

class EC16BitSSE {
  
public:
  
  typedef __m128i Vec ;
  typedef int16_t Word ;

  static const int MAX_VEC_LEN = 8 ;
  static const int BAD_SCORE = -1000 ;

  
  static inline Vec vec_set(Word* arr) {
    return _mm_set_epi16(arr[7], arr[6], arr[5], arr[4], arr[3], arr[2], arr[1], arr[0]) ;
  }

  static inline Vec vec_set1(Word val) {
    return _mm_set1_epi16(val) ;
  }

  static inline Vec vec_add(const Vec& v1, const Vec& v2) {
    return _mm_add_epi16(v1, v2) ;
  }

  static inline Vec vec_or(const Vec& v1, const Vec& v2) {
    return _mm_or_si128(v1, v2) ;
  }

  static inline Vec vec_max(const Vec& v1, const Vec& v2) {
    return _mm_max_epi16(v1, v2) ;
  }

  static inline Vec vec_compare_eq(const Vec& v1, const Vec& v2) {
    return _mm_cmpeq_epi16(v1, v2) ;
  }

  static inline Vec vec_compare_gt(const Vec& v1, const Vec& v2) {
    return _mm_cmpgt_epi16(v1, v2) ;
  }
  
  static inline Vec vec_blend(const Vec& vFalse, const Vec& vTrue, const Vec& mask) {
    return _mm_blendv_epi8(vFalse, vTrue, mask) ;
  }

  static inline bool vec_test_all_ones(const Vec& v, const Vec& allOnesV) {
    return _mm_test_all_ones(v) ;
  }

  // 0 is inserted to LSW
  static inline __m128i vec_shift_left (const __m128i& vec) {
    return _mm_slli_si128(vec, 2) ;
  }

  // The most significant word (MSW) in words is inserted to LSW of vec
  static inline __m128i vec_shift_left_and_insert (const __m128i& vec, const __m128i& words) {
    return _mm_alignr_epi8(vec, words, 14) ;
  }

  // 0 is inserted to MSW
  static inline __m128i vec_shift_right (const __m128i& vec) {
    return _mm_srli_si128(vec, 2) ;
  }

  // The LSW of words is inserted to the MSW of vec
  static inline __m128i vec_shift_right_and_insert (const __m128i& vec, const __m128i& words) {
    return _mm_alignr_epi8(words, vec, 2) ;
  }

  static void vec_print(const Vec& vec) ;

} ;

void EC16BitSSE::vec_print(const Vec& vec) {
  for(int i = 7; i >= 0; i--)
    cout << std::setw(5) << ((const int16_t*) (&vec))[i] << " " ;

  cout << endl ;
}

