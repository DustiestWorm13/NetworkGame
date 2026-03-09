#ifndef BULLET_TESTHARNESS_H_
#define BULLET_TESTHARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "Bullet.h"

class BulletTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  BulletPtr bb;

public:

    BulletTestHarness();
    virtual ~BulletTestHarness();
};

#endif // PLAYER_TESTHARNESS_H_
