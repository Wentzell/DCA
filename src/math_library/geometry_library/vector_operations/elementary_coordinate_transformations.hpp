// Copyright (C) 2009-2016 ETH Zurich
// Copyright (C) 2007?-2016 Center for Nanophase Materials Sciences, ORNL
// All rights reserved.
//
// See LICENSE.txt for terms of usage.
// See CITATION.txt for citation guidelines if you use this code for scientific publications.
//
// Author: Peter Staar (peter.w.j.staar@gmail.com)
//
// Description: TBA
//
// TODO: Make this file const correct.

#ifndef MATH_LIBRARY_GEOMETRY_LIBRARY_VECTOR_OPERATIONS_ELEMENTARY_COORDINATE_TRANSFORMATIONS_HPP
#define MATH_LIBRARY_GEOMETRY_LIBRARY_VECTOR_OPERATIONS_ELEMENTARY_COORDINATE_TRANSFORMATIONS_HPP

#include "comp_library/linalg/linalg.hpp"

namespace VECTOR_OPERATIONS {
template <typename scalar_type>
class coordinate_transformation {
public:
  static void execute(scalar_type* v0, scalar_type* v1, scalar_type* vec, scalar_type* coor);
  static void execute(scalar_type* v0, scalar_type* v1, scalar_type* v2, scalar_type* vec,
                      scalar_type* coor);

  static void execute(std::vector<scalar_type>& v0, std::vector<scalar_type>& v1,
                      std::vector<scalar_type>& vec, std::vector<scalar_type>& coor);
  static void execute(std::vector<scalar_type>& v0, std::vector<scalar_type>& v1,
                      std::vector<scalar_type>& v2, std::vector<scalar_type>& vec,
                      std::vector<scalar_type>& coor);

  coordinate_transformation(int d);
  ~coordinate_transformation();

  // basis-vectors column-wise
  void set_basis(scalar_type* basis);

  // basis-vectors column-wise
  void set_basis(std::vector<std::vector<scalar_type>>& basis);

  void execute(scalar_type* vec, scalar_type* coor);

private:
  int DIMENSION;

  LIN_ALG::matrix<scalar_type, LIN_ALG::CPU> T;
  LIN_ALG::matrix<scalar_type, LIN_ALG::CPU> T_inv;
};

template <typename scalar_type>
void coordinate_transformation<scalar_type>::execute(scalar_type* v0, scalar_type* v1,
                                                     scalar_type* vec, scalar_type* coor) {
  LIN_ALG::matrix<scalar_type, LIN_ALG::CPU> A("A", 2);

  A(0, 0) = v0[0];
  A(1, 0) = v0[1];

  A(0, 1) = v1[0];
  A(1, 1) = v1[1];

  LIN_ALG::GEINV<LIN_ALG::CPU>::execute(A);

  coor[0] = A(0, 0) * vec[0] + A(0, 1) * vec[1];
  coor[1] = A(1, 0) * vec[0] + A(1, 1) * vec[1];
}

template <typename scalar_type>
void coordinate_transformation<scalar_type>::execute(std::vector<scalar_type>& v0,
                                                     std::vector<scalar_type>& v1,
                                                     std::vector<scalar_type>& vec,
                                                     std::vector<scalar_type>& coor) {
  assert(v0.size() == 2);
  assert(v1.size() == 2);
  assert(vec.size() == 2);
  assert(coor.size() == 2);

  execute(&v0[0], &v1[0], &vec[0], &coor[0]);
}

template <typename scalar_type>
void coordinate_transformation<scalar_type>::execute(scalar_type* v0, scalar_type* v1,
                                                     scalar_type* v2, scalar_type* vec,
                                                     scalar_type* coor) {
  LIN_ALG::matrix<scalar_type, LIN_ALG::CPU> A("A", 3);

  A(0, 0) = v0[0];
  A(1, 0) = v0[1];
  A(2, 0) = v0[2];

  A(0, 1) = v1[0];
  A(1, 1) = v1[1];
  A(2, 1) = v1[2];

  A(0, 2) = v2[0];
  A(1, 2) = v2[1];
  A(2, 2) = v2[2];

  LIN_ALG::GEINV<LIN_ALG::CPU>::execute(A);

  coor[0] = A(0, 0) * vec[0] + A(0, 1) * vec[1] + A(0, 2) * vec[2];
  coor[1] = A(1, 0) * vec[0] + A(1, 1) * vec[1] + A(1, 2) * vec[2];
  coor[2] = A(2, 0) * vec[0] + A(2, 1) * vec[1] + A(2, 2) * vec[2];
}

template <typename scalar_type>
void coordinate_transformation<scalar_type>::execute(std::vector<scalar_type>& v0,
                                                     std::vector<scalar_type>& v1,
                                                     std::vector<scalar_type>& v2,
                                                     std::vector<scalar_type>& vec,
                                                     std::vector<scalar_type>& coor) {
  assert(v0.size() == 3);
  assert(v1.size() == 3);
  assert(v2.size() == 3);
  assert(vec.size() == 3);
  assert(coor.size() == 3);

  execute(&v0[0], &v1[0], &v2[0], &vec[0], &coor[0]);
}

template <typename scalar_type>
coordinate_transformation<scalar_type>::coordinate_transformation(int d)
    : DIMENSION(d), T("T", d), T_inv("T_inv", d) {}

template <typename scalar_type>
coordinate_transformation<scalar_type>::~coordinate_transformation() {}

template <typename scalar_type>
void coordinate_transformation<scalar_type>::set_basis(scalar_type* basis) {
  for (int d1 = 0; d1 < DIMENSION; d1++)
    for (int d0 = 0; d0 < DIMENSION; d0++)
      T(d0, d1) = basis[d0 + d1 * DIMENSION];

  T_inv.copy_from(T);

  LIN_ALG::GEINV<LIN_ALG::CPU>::execute(T_inv);
}

template <typename scalar_type>
void coordinate_transformation<scalar_type>::set_basis(std::vector<std::vector<scalar_type>>& basis) {
  set_basis(basis[0][0]);
}

template <typename scalar_type>
void coordinate_transformation<scalar_type>::execute(scalar_type* vec, scalar_type* coor) {
  switch (DIMENSION) {
    case 1:
      coor[0] = T_inv(0, 0) * vec[0];
      break;

    case 2:
      coor[0] = T_inv(0, 0) * vec[0] + T_inv(0, 1) * vec[1];
      coor[1] = T_inv(1, 0) * vec[0] + T_inv(1, 1) * vec[1];
      break;

    case 3:
      coor[0] = T_inv(0, 0) * vec[0] + T_inv(0, 1) * vec[1] + T_inv(0, 2) * vec[2];
      coor[1] = T_inv(1, 0) * vec[0] + T_inv(1, 1) * vec[1] + T_inv(1, 2) * vec[2];
      coor[2] = T_inv(2, 0) * vec[0] + T_inv(2, 1) * vec[1] + T_inv(2, 2) * vec[2];
      break;

    default:

      for (int d0 = 0; d0 < DIMENSION; d0++)
        coor[0] = 0;

      for (int d1 = 0; d1 < DIMENSION; d1++)
        for (int d0 = 0; d0 < DIMENSION; d0++)
          coor[d0] += T_inv(d0, d1) * vec[d1];
  }
}
}  // VECTOR_OPERATIONS

#endif  // MATH_LIBRARY_GEOMETRY_LIBRARY_VECTOR_OPERATIONS_ELEMENTARY_COORDINATE_TRANSFORMATIONS_HPP