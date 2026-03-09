#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "RockTestHarness.h"
#include "Rock.h"
#include "RockClient.h"
#include "TextureManager.h"
#include "Maths.h"
#include "Colors.h"

#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

RockTestHarness::RockTestHarness()
{
  rr = nullptr;
}

RockTestHarness::~RockTestHarness()
{
  rr.reset();
}

void RockTestHarness::SetUp()
{
    GameObject*	go = Rock::StaticCreate();
    Rock* r = static_cast<Rock*>(go);
    this->rr.reset(r);
}

void RockTestHarness::TearDown()
{
    this->rr.reset();
    this->rr = nullptr;
}

TEST_F(RockTestHarness,constructor_noArgs)
{
  // Check defaults are set
  // Should be no need to do these as they were tested with the base class.
  EXPECT_TRUE(Maths::Is3DVectorEqual(rr->GetColor(), Colors::White));
  EXPECT_TRUE(Maths::Is3DVectorEqual(rr->GetLocation(), Vector3::Zero));
  EXPECT_FLOAT_EQ(rr->GetCollisionRadius(), 0.5f);
  EXPECT_FLOAT_EQ(rr->GetScale(),1.0f);
  EXPECT_FLOAT_EQ(rr->GetRotation(),0.0f);
  EXPECT_EQ(rr->GetIndexInWorld(), -1);
  EXPECT_EQ(rr->GetNetworkId(), 0);

  EXPECT_TRUE(Maths::Is3DVectorEqual(rr->GetVelocity(), Vector3::Zero));
  EXPECT_EQ(rr->GetRockId(), 0.0f);

  //Initial state is update all
  int check = 0x000F; //Hex - binary 00000000 00000000 00000000 00001111
  EXPECT_EQ(rr->GetAllStateMask(), check);

  //Check our macro has worked.
  EXPECT_EQ(rr->GetClassId(), 'ROCK');
  EXPECT_NE(rr->GetClassId(), 'HELP');

  //Added some getters so I could check these - not an easy class to test.
  EXPECT_FLOAT_EQ(rr->GetMaxLinearSpeed(),  50.0f);
  EXPECT_FLOAT_EQ(rr->GetMaxRotationSpeed(), 5.0f);
  EXPECT_FLOAT_EQ(rr->GetWallRestitution(), 0.1f);
  EXPECT_FLOAT_EQ(rr->GetNPCRestitution(), 0.1f);
  EXPECT_FLOAT_EQ(rr->GetLastMoveTimestamp(), 0.0f);
  EXPECT_FLOAT_EQ(rr->GetThrustDir(), 0.3f);
  EXPECT_EQ(rr->GetHealth(), 3);
  //EXPECT_FALSE(rr->IsShooting());
}


/* Tests Omitted
* There's a good chunk of this which cannot be tested in this limited example,
* however there should be enough to underake some testing of the serialisation code.
*/

TEST_F(RockTestHarness,EqualsOperator1)
{ /* Won't compile - why?
  Player a ();
  Player b ();

  a.SetPlayerId(10);
  b.SetPlayerId(10);

  EXPECT_TRUE(a == b);*/
}

TEST_F(RockTestHarness,EqualsOperator2)
{
  Rock *a = static_cast<Rock*>(Rock::StaticCreate());
  Rock *b = static_cast<Rock*>(Rock::StaticCreate());

  a->SetRockId(10);
  b->SetRockId(10);

  EXPECT_TRUE(*a == *b);
}

/* Need more tests here */

TEST_F(RockTestHarness,EqualsOperator3)
{
  Rock *a = static_cast<Rock*>(Rock::StaticCreate());
  Rock *b = static_cast<Rock*>(Rock::StaticCreate());

  a->SetRockId(10);
  b->SetRockId(30);

  //EXPECT_FALSE(*a == *b);
}

TEST_F(RockTestHarness,EqualsOperator4)
{
  RockPtr b(static_cast<Rock*>(Rock::StaticCreate()));

  rr->SetRockId(10);
  b->SetRockId(10);

  EXPECT_TRUE(*rr == *b);
}

/* Serialistion tests in MemoryBitStreamTestHarness */