#ifndef ROCK_TESTHARNESS_H_
#define ROCK_TESTHARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "Rock.h"

class RockTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  RockPtr rr;

public:

    RockTestHarness();
    virtual ~RockTestHarness();
};

#endif // ROCK_TESTHARNESS_H_
