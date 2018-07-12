// Copyright (C) 2018 ETH Zurich
// Copyright (C) 2018 UT-Battelle, LLC
// All rights reserved.
// See LICENSE.txt for terms of usage./
//  See CITATION.md for citation guidelines, if DCA++ is used for scientific publications.
//
// Author: Giovanni Balduzzi (gbalduzz@itp.phys.ethz.ch)
//
//

#ifndef TEST_UNIT_PHYS_DCA_STEP_CLUSTER_SOLVER_CTINT_WALKER_WALKER_WRAPPER_HPP
#define TEST_UNIT_PHYS_DCA_STEP_CLUSTER_SOLVER_CTINT_WALKER_WALKER_WRAPPER_HPP

#include "dca/linalg/device_type.hpp"
#include "dca/phys/dca_step/cluster_solver/ctint/walker/ctint_walker_cpu.hpp"

namespace testing {
namespace phys {
namespace solver {
namespace ctint {
// testing::phys::solver::ctint::

using namespace dca::phys::solver::ctint;
template <class Parameters>
struct WalkerWrapper : public CtintWalker<dca::linalg::CPU, Parameters> {
  using BaseClass = CtintWalker<dca::linalg::CPU, Parameters>;
  using Rng = typename BaseClass::Rng;

  WalkerWrapper(Parameters& parameters_ref, Rng& rng_ref, const InteractionVertices& vertices,
                const DMatrixBuilder<dca::linalg::CPU>& builder)
      : BaseClass(parameters_ref, rng_ref, vertices, builder, 0) {}

  using BaseClass::doStep;
  using BaseClass::tryVertexInsert;
  using BaseClass::tryVertexRemoval;
  using BaseClass::setMFromConfig;
  using BaseClass::getM;

  using Matrix = dca::linalg::Matrix<double, dca::linalg::CPU>;

  void setM(const Matrix& m) {
    BaseClass::getM() = m;
  }

  double getRatio() const {
    return BaseClass::det_ratio_[0] * BaseClass::det_ratio_[1];
  }

  double getAcceptanceProbability() const {
    return BaseClass::acceptance_prob_;
  }

  const auto& getWalkerConfiguration() const {
    return BaseClass::configuration_;
  }

};

}  // ctint
}  // solver
}  // phys
}  // testing

#endif  //  TEST_UNIT_PHYS_DCA_STEP_CLUSTER_SOLVER_CTINT_WALKER_WALKER_WRAPPER_HPP