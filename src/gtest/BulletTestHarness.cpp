#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "BulletTestHarness.h"
#include "Bullet.h"
#include "BulletClient.h"
#include "TextureManager.h"
#include "Maths.h"
#include "Colors.h"

#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

BulletTestHarness::BulletTestHarness()
{
  bb = nullptr;
}

BulletTestHarness::~BulletTestHarness()
{
  bb.reset();
}

void BulletTestHarness::SetUp()
{
    GameObject*	go = Bullet::StaticCreate();
    Bullet* b = static_cast<Bullet*>(go);
    this->bb.reset(b);
}

void BulletTestHarness::TearDown()
{
    this->bb.reset();
    this->bb = nullptr;
}

TEST_F(BulletTestHarness,constructor_noArgs)
{
  // Check defaults are set
  // Should be no need to do these as they were tested with the base class.
  EXPECT_TRUE(Maths::Is3DVectorEqual(bb->GetColor(), Colors::White));
  EXPECT_TRUE(Maths::Is3DVectorEqual(bb->GetLocation(), Vector3::Zero));
  EXPECT_FLOAT_EQ(bb->GetCollisionRadius(), 0.5f);
  EXPECT_FLOAT_EQ(bb->GetScale(),1.0f);
  EXPECT_FLOAT_EQ(bb->GetRotation(),0.0f);
  EXPECT_EQ(bb->GetIndexInWorld(), -1);
  EXPECT_EQ(bb->GetNetworkId(), 0);

  EXPECT_TRUE(Maths::Is3DVectorEqual(bb->GetVelocity(), Vector3::Zero));
  EXPECT_EQ(bb->GetBulletId(), 0.0f);

  //Initial state is update all
  int check = 0x000F; //Hex - binary 00000000 00000000 00000000 00001111
  //EXPECT_EQ(bb->GetAllStateMask(), check);

  //Check our macro has worked.
  EXPECT_EQ(bb->GetClassId(), 'BULL');
  EXPECT_NE(bb->GetClassId(), 'HELP');

  //Added some getters so I could check these - not an easy class to test.
  EXPECT_FLOAT_EQ(bb->GetMaxLinearSpeed(),  50.0f);
  EXPECT_FLOAT_EQ(bb->GetMaxRotationSpeed(), 5.0f);
  EXPECT_FLOAT_EQ(bb->GetWallRestitution(), 0.1f);
  EXPECT_FLOAT_EQ(bb->GetNPCRestitution(), 0.1f);
  EXPECT_FLOAT_EQ(bb->GetLastMoveTimestamp(), 0.0f);
  EXPECT_FLOAT_EQ(bb->GetThrustDir(), 5.0f);
  //EXPECT_EQ(bb->GetHealth(), 10);
  //EXPECT_FALSE(bb->IsShooting());
}


/* Tests Omitted
* There's a good chunk of this which cannot be tested in this limited example,
* however there should be enough to underake some testing of the serialisation code.
*/

TEST_F(BulletTestHarness,EqualsOperator1)
{ /* Won't compile - why?
  Player a ();
  Player b ();

  a.SetPlayerId(10);
  b.SetPlayerId(10);

  EXPECT_TRUE(a == b);*/
}

TEST_F(BulletTestHarness,EqualsOperator2)
{
  Bullet *a = static_cast<Bullet*>(Bullet::StaticCreate());
  Bullet *b = static_cast<Bullet*>(Bullet::StaticCreate());

  a->SetBulletId(10);
  b->SetBulletId(10);

  EXPECT_TRUE(*a == *b);
}

/* Need more tests here */

TEST_F(BulletTestHarness,EqualsOperator3)
{
  Bullet *a = static_cast<Bullet*>(Bullet::StaticCreate());
  Bullet *b = static_cast<Bullet*>(Bullet::StaticCreate());

  a->SetBulletId(10);
  b->SetBulletId(30);

  EXPECT_FALSE(*a == *b);
}

TEST_F(BulletTestHarness,EqualsOperator4)
{
  BulletPtr b(static_cast<Bullet*>(Bullet::StaticCreate()));

  bb->SetBulletId(10);
  b->SetBulletId(10);

  EXPECT_TRUE(*bb == *b);
}

/* Serialistion tests in MemoryBitStreamTestHarness */