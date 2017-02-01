/*
 * Copyright 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "type_mutators/ProtoFuzzerStructMutator.h"

namespace android {
namespace vts {

VariableSpecificationMessage ProtoFuzzerStructMutator::RandomGen(
    const VariableSpecificationMessage &var_spec) {
  VariableSpecificationMessage result{};
  result.set_name(var_spec.predefined_type());
  result.set_type(TYPE_STRUCT);

  const VariableSpecificationMessage &blueprint =
      FindPredefinedType(result.name());
  for (const auto &struct_value : blueprint.struct_value()) {
    *result.add_struct_value() = mutator_->RandomGen(struct_value);
  }
  return result;
}

VariableSpecificationMessage ProtoFuzzerStructMutator::Mutate(
    const VariableSpecificationMessage &var_spec) {
  VariableSpecificationMessage result{var_spec};

  size_t size = var_spec.struct_value_size();
  size_t idx = rand_(size);
  *result.mutable_struct_value(idx) =
      mutator_->Mutate(var_spec.struct_value(idx));
  return result;
}

}  // namespace vts
}  // namespace android
