/*
Copyright 2014 Intel
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

extern const int defaultCostMatrixRowCnt ;

extern const int8_t defaultCostMatrix[] ;

// Needs to be called only once per program to set up static arrays
void init_fast_extend() ;


// The filtering function:
// Inputs: Reference and query sequences,	
//         Initial score (i.e. h0),
//         endBonus (i.e. the extra score if the whole query is aligned)
//         Scoring parameters: mismatchWt, gapWt, gapOpenWt, ambigWt
// Outputs:
//         Alignment length in query
//         Alignment length in reference
//         Alignment score
//         Confidence: For now, it's either 0.0 or 1.0, corresponding to no/full confidence in outputs
// Usage:
//         If confidence == 0.0: Partial alignment - need to rerun ksw_extend(...)
//         If confidence == 1.0
//               if alignedQLen == queryLen: Full alignment
//               if alignedQLen == 0: No alignment
//
void fast_filter(const uint8_t* refSeq, int refLen, const uint8_t* querySeq, int queryLen,
		 int initScore, int endBonus, 
		 int& alignedQLen, int& alignedRLen, int& score, float& confidence,
		 int mismatchWt=4, int gapWt=1, int gapOpenWt=6, int ambigWt=1) ;

// Filter-and-extend function:
// Inputs: Reference and query sequences,	
//         Initial score (i.e. h0),
//         endBonus (i.e. the extra score if the whole query is aligned)
//         zdrop value passed to ksw_extend
//         Cost matrix and gap open and gap extend weights
// Outputs:
//         Alignment length in query
//         Alignment length in reference
//         Alignment score
// Behavior:
//         The filtering function will be called internally first.
//         If there is an obvious result, it will be returned.
//         If not, ksw_extend() will be called with feedback from filtering function,
//         and its result will be returned.
// Notes: 
//        It is assumed that ksw_extend(...) function is in a linked file.
//
void fast_filter_and_extend(const uint8_t* refSeq, int refLen, const uint8_t* querySeq, int queryLen,
			    int initScore, int endBonus, int zdrop,
			    int& alignedQLen, int& alignedRLen, int& score,
			    int costMatrixRowCnt=defaultCostMatrixRowCnt, 
			    const int8_t* costMatrix=defaultCostMatrix,
			    int gapWt=1, int gapOpenWt=6) ;

int (*ksw_extend_16)(int qlen, const uint8_t *query, int tlen, const uint8_t *target, int m, const int8_t *mat, int gapo, int gape, int w, int end_bonus, int zdrop, int h0, int *qle, int *tle, int *gtle, int *gscore, int *max_off) ;
int (*ksw_extend_32)(int qlen, const uint8_t *query, int tlen, const uint8_t *target, int m, const int8_t *mat, int gapo, int gape, int w, int end_bonus, int zdrop, int h0, int *qle, int *tle, int *gtle, int *gscore, int *max_off) ;


// Vectorized implementations of ksw_extend for small bands:
int ksw_extend_sse_8(int qlen, const uint8_t *query, int tlen, const uint8_t *target, int m, const int8_t *mat, int gapo, int gape, int w, int end_bonus, int zdrop, int h0, int *qle, int *tle, int *gtle, int *gscore, int *max_off) ;

int ksw_extend_sse_16(int qlen, const uint8_t *query, int tlen, const uint8_t *target, int m, const int8_t *mat, int gapo, int gape, int w, int end_bonus, int zdrop, int h0, int *qle, int *tle, int *gtle, int *gscore, int *max_off) ;



int ksw_extend_avx2_16(int qlen, const uint8_t *query, int tlen, const uint8_t *target, int m, const int8_t *mat, int gapo, int gape, int w, int end_bonus, int zdrop, int h0, int *qle, int *tle, int *gtle, int *gscore, int *max_off) ;

int ksw_extend_avx2_32(int qlen, const uint8_t *query, int tlen, const uint8_t *target, int m, const int8_t *mat, int gapo, int gape, int w, int end_bonus, int zdrop, int h0, int *qle, int *tle, int *gtle, int *gscore, int *max_off) ;


