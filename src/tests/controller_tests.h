#ifndef TESTS_CONTROLLER_TESTS_H_
#define TESTS_CONTROLLER_TESTS_H_

#include <gtest/gtest.h>

#include "controller.h"

namespace {

void CompareMatrices(const model::TransformationMatrix4D& m1,
                     const model::TransformationMatrix4D& m2);

}  // namespace

#endif  // TESTS_CONTROLLER_TESTS_H_
