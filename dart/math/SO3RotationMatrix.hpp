/*
 * Copyright (c) 2016, Graphics Lab, Georgia Tech Research Corporation
 * Copyright (c) 2016, Humanoid Lab, Georgia Tech Research Corporation
 * Copyright (c) 2016, Personal Robotics Lab, Carnegie Mellon University
 * All rights reserved.
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_MATH_SO3ROTATIONMATRIX_HPP_
#define DART_MATH_SO3ROTATIONMATRIX_HPP_

#include <Eigen/Eigen>

#include "dart/math/MathTypes.hpp"
#include "dart/math/Geometry.hpp"
#include "dart/math/SO3Base.hpp"

namespace dart {
namespace math {

template <typename S_>
class SO3RotationMatrix : public SO3Base<SO3RotationMatrix<S_>>
{
public:

  using This = SO3RotationMatrix;
  using Base = SO3Base<SO3RotationMatrix>;
  using S = S_;

  using RotationMatrix = typename Base::RotationMatrix;
  using RotationVector = typename Base::RotationVector;

  using RepData = typename Base::RepData;

  using Tangent = typename Base::Tangent;
  using so3 = typename Base::so3;

  using Base::operator =;
  using Base::operator *;
  using Base::operator *=;

//  using Base::getCoordinates;
  using Base::setRepData;
  using Base::getRepData;

  using Base::Exp;
  using Base::setExp;
  using Base::Log;
  using Base::getLog;

  /// \{ \name Constructors

  /// Default constructor. By default, the constructed SO(3) is not identity.
  SO3RotationMatrix() : Base()
  {
    // Do nothing
  }

  /// Copy constructor.
  SO3RotationMatrix(const SO3RotationMatrix& other) : Base(), mRepData(other.mRepData)
  {
    // Do nothing
  }

  /// Move constructor.
  SO3RotationMatrix(SO3RotationMatrix&& other) : Base(), mRepData(std::move(other.mRepData))
  {
    // Do nothing
  }

  /// Construct from other SO3 with different representation.
  template <typename Derived>
  SO3RotationMatrix(const SO3Base<Derived>& other)
    : Base(),
      mRepData(
        detail::so3_operations::so3_convert_impl<S, Derived, This>::run(
          other.getRepData()))
  {
    // Do nothing
  }

  /// Construct from other SO3 with different representation.
  template <typename Derived>
  SO3RotationMatrix(SO3Base<Derived>&& other)
    : Base(),
      mRepData(detail::so3_operations::so3_convert_impl<S, Derived, This>::run(
              std::move(other.getRepData())))
  {
    // Do nothing
  }

  /// Construct from a raw rotation matrix where the dimension is 3x3.
  template <typename Derived>
  SO3RotationMatrix(const Eigen::MatrixBase<Derived>& matrix) : Base(), mRepData(matrix)
  {
    assert(matrix.rows() == 3);
    assert(matrix.cols() == 3);
  }

  /// Construct from a raw rotation matrix where the dimension is 3x3.
  template <typename Derived>
  SO3RotationMatrix(Eigen::MatrixBase<Derived>&& matrix) : Base(), mRepData(std::move(matrix))
  {
    assert(matrix.rows() == 3);
    assert(matrix.cols() == 3);
  }

  /// \} // Constructors

  /// \{ \name Operators

  /// Assign a SO3 with the same representation.
  SO3RotationMatrix& operator=(const SO3RotationMatrix& other)
  {
    mRepData = other.mRepData;
    return *this;
  }

  /// Move in a SO3 with the same representation.
  SO3RotationMatrix& operator=(SO3RotationMatrix&& other)
  {
    mRepData = std::move(other.mRepData);
    return *this;
  }

  template <typename Derived>
  SO3RotationMatrix& operator=(const Eigen::MatrixBase<Derived>& matrix)
  {
    mRepData = matrix;
    return *this;
  }

  template <typename Derived>
  SO3RotationMatrix& operator=(Eigen::MatrixBase<Derived>&& matrix)
  {
    mRepData = std::move(matrix);
    return *this;
  }

  template <typename RotationDerived>
  SO3RotationMatrix& operator=(const Eigen::RotationBase<RotationDerived, Base::Dim>& rot)
  {
    mRepData = rot;
    return *this;
  }

  template <typename RotationDerived>
  SO3RotationMatrix& operator=(Eigen::RotationBase<RotationDerived, Base::Dim>&& rot)
  {
    mRepData = std::move(rot);
    return *this;
  }

  const RotationVector operator*(const RotationVector& vector)
  {
    return mRepData * vector;
  }

  /// Whether \b exactly equal to a SO3.
  bool operator ==(const SO3RotationMatrix& other)
  {
    return mRepData == other.mRepData;
  }

  /// \} // Operators

  /// \{ \name Representation properties

  template <typename Derived>
  void setRotationMatrix(const Eigen::MatrixBase<Derived>& matrix)
  {
    assert(matrix.rows() == 3);
    assert(matrix.cols() == 3);

    mRepData = matrix;
  }

  template <typename Derived>
  void setRotationMatrix(Eigen::MatrixBase<Derived>&& mat)
  {
    assert(mat.rows() == 3);
    assert(mat.cols() == 3);

    mRepData = std::move(mat);
  }

  const RotationMatrix& getRotationMatrix() const
  {
    return mRepData;
  }

  void setRandom()
  {
    *this = Exp(Tangent::Random());
    // TODO(JS): improve
  }

  /// \} // Representation properties

  /// \{ \name SO3 group operations

  void setIdentity()
  {
    mRepData.setIdentity();
  }

  bool isIdentity()
  {
    return mRepData == RepData::Identity();
  }

  void invert()
  {
    mRepData.transposeInPlace();
  }

  const SO3RotationMatrix getInverse() const
  {
    return SO3RotationMatrix(mRepData.transpose());
  }

  /// \} // SO3 group operations

protected:

  template <typename>
  friend class SO3Base;

  RepData mRepData{RepData()};
};

using SO3RotationMatrixf = SO3RotationMatrix<float>;
using SO3RotationMatrixd = SO3RotationMatrix<double>;

extern template
class SO3RotationMatrix<double>;

} // namespace math
} // namespace dart

#endif // DART_MATH_SO3ROTATIONMATRIX_HPP_