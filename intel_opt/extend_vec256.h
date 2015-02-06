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

class EC16BitAvx2 {

public:
  
  typedef __m256i Vec ;
  typedef int16_t Word ;

  static const int MAX_VEC_LEN = 16 ;
  static const int BAD_SCORE = -1000 ;

  
  static inline Vec vec_set(Word* arr) {
    return _mm256_set_epi16(arr[15], arr[14], arr[13], arr[12], arr[11],
			    arr[10], arr[9], arr[8], arr[7], arr[6], arr[5],
			    arr[4], arr[3], arr[2], arr[1], arr[0]) ;
  }

  static inline Vec vec_set1(Word val) {
    return _mm256_set1_epi16(val) ;
  }

  static inline Vec vec_set_last_word(Word val) {
    return _mm256_set_epi16(val, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) ;
  }

  static inline Vec vec_add(const Vec& v1, const Vec& v2) {
    return _mm256_add_epi16(v1, v2) ;
  }

  static inline Vec vec_or(const Vec& v1, const Vec& v2) {
    return _mm256_or_si256(v1, v2) ;
  }

  static inline Vec vec_max(const Vec& v1, const Vec& v2) {
    return _mm256_max_epi16(v1, v2) ;
  }

  static inline Vec vec_compare_eq(const Vec& v1, const Vec& v2) {
    return _mm256_cmpeq_epi16(v1, v2) ;
  }

  static inline Vec vec_compare_gt(const Vec& v1, const Vec& v2) {
    return _mm256_cmpgt_epi16(v1, v2) ;
  }
  
  static inline Vec vec_blend(const Vec& vFalse, const Vec& vTrue, const Vec& mask) {
    return _mm256_blendv_epi8(vFalse, vTrue, mask) ;
  }

  static inline bool vec_test_all_ones(const Vec& v, const Vec& allOnesV) {
    return _mm256_testc_si256(v, allOnesV) ;
  }

  // 0 is inserted to LSW
  static inline __m256i vec_shift_left (const __m256i& vec) {
    return _mm256_alignr_epi8(vec, _mm256_permute2x128_si256(vec, vec, 0x04), 14) ;
  }

  // The most significant word (MSW) in words is inserted to LSW of vec
  static inline __m256i vec_shift_left_and_insert (const __m256i& vec, const __m256i& words) {
    return _mm256_alignr_epi8(vec, _mm256_permute2x128_si256(vec, words, 0x03), 14) ;
  }

  // 0 is inserted to LSW
  static inline __m256i vec_shift_right (const __m256i& vec) {
    return _mm256_alignr_epi8(_mm256_permute2x128_si256(vec, vec, 0x41), vec, 2) ;
  }

  // The LSW of words is inserted to the MSW of vec
  static inline __m256i vec_shift_right_and_insert (const __m256i& vec, const __m256i& words) {
  
    return _mm256_alignr_epi8(_mm256_permute2x128_si256(vec, words, 0x21), vec, 2) ;
  }

  static void vec_print(const Vec& vec) ;

} ;

void EC16BitAvx2::vec_print(const Vec& vec) {
  for(int i = 15; i >= 0; i--)
    cout << std::setw(5) << ((int16_t *)&vec)[i] << " " ;
  cout << endl ;
}

