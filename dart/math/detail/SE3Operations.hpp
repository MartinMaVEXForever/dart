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

#ifndef DART_MATH_DETAIL_SE3OPERATIONS_HPP_
#define DART_MATH_DETAIL_SE3OPERATIONS_HPP_

#include <Eigen/Eigen>
#include "dart/math/MathTypes.hpp"
#include "dart/math/Geometry.hpp"

namespace dart {
namespace math {

// Forward declarations
template <typename, typename> class SE3;

namespace detail {

//==============================================================================
// traits:
// Traits for all SO3 classes that is agnostic to representation types
//==============================================================================

//==============================================================================
template <typename S_, typename SO3Canonical>
struct traits<SE3<S_, SO3Canonical>>
{
  using S = S_;
  using Rep = SO3Canonical;

  using SE3Canonical = SE3<S, SO3Canonical>;
};

namespace SE3 {

//==============================================================================
// rep_traits:
// Traits for different SE3 representations
//==============================================================================

//==============================================================================
template <typename S, typename Rep_>
struct rep_traits;

//==============================================================================
template <typename S_>
struct rep_traits<S_, SO3RotationMatrix<S_>>
{
  using S = S_;
//  using Rep = SO3RotationMatrix;
  using RepData = Eigen::Matrix<S, 3, 3>;
};

//==============================================================================
template <typename S_>
struct rep_traits<S_, SO3AngleAxis<S_>>
{
  using S = S_;
//  using Rep = SO3AngleAxis;
  using RepData = Eigen::Matrix<S, 3, 1>;
  // TODO(JS): Change to Eigen::AngleAxis<S>
};

//==============================================================================
template <typename S_>
struct rep_traits<S_, SO3Quaternion<S_>>
{
  using S = S_;
//  using Rep = SO3Quaternion;
  using RepData = Eigen::Quaternion<S>;
};

//==============================================================================
template <typename S_>
struct rep_traits<S_, SO3RotationVector<S_>>
{
  using S = S_;
//  using Rep = SO3Quaternion;
  using RepData = Eigen::Matrix<S, 3, 1>;
};

} // namespace SE3
} // namespace detail
} // namespace math
} // namespace dart

#endif // DART_MATH_DETAIL_SE3OPERATIONS_HPP_