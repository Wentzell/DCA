// Copyright (C) 2009-2016 ETH Zurich
// Copyright (C) 2007?-2016 Center for Nanophase Materials Sciences, ORNL
// All rights reserved.
//
// See LICENSE.txt for terms of usage.
// See CITATION.txt for citation guidelines if you use this code for scientific publications.
//
// Author: Peter Staar (taa@zurich.ibm.com)
//         Urs R. Haehner (haehneru@itp.phys.ethz.ch)
//
// This class reads, stores, and writes the model paramters.
// It is templated on the model type and only implemented when specialized for the 2D 2-band model,
// 2D 4-band model, bilayer model, tight-binding model and material models.

#ifndef DCA_PHYS_PARAMETERS_MODEL_PARAMETERS_HPP
#define DCA_PHYS_PARAMETERS_MODEL_PARAMETERS_HPP

#include <iostream>
#include <stdexcept>
#include <string>

#include "dca/phys/models/analytic_hamiltonians/bilayer_lattice.hpp"
#include "dca/phys/models/analytic_hamiltonians/fourband_lattice.hpp"
#include "dca/phys/models/analytic_hamiltonians/twoband_lattice.hpp"
#include "dca/phys/models/material_hamiltonians/material_lattice.hpp"
#include "dca/phys/models/tight_binding_model.hpp"

namespace dca {
namespace phys {
namespace params {
// dca::phys::params::

// Empty class template
template <typename Model>
class ModelParameters {};

// Specialization for 2D 2-band model
#include "model_parameters_2d_2band.inc"

// Specialization for 2D 4-band model
#include "model_parameters_2d_4band.inc"

// Specialization for 2D bilayer model
#include "model_parameters_2d_bilayer.inc"

// Specialization for material models
#include "model_parameters_material.inc"

// Specialization for tight-binding model
#include "model_parameters_tight_binding.inc"

}  // params
}  // phys
}  // dca

#endif  // DCA_PHYS_PARAMETERS_MODEL_PARAMETERS_HPP