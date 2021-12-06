
#include <gtest/gtest.h>
#include <amo/uuid.hpp>

TEST(uuid, to_string) {
	amo::uuid uuid;
	EXPECT_EQ("00000000-0000-0000-0000-000000000000", uuid.to_string());
}


TEST(uuid, nil) {
	amo::uuid uuid = amo::uuid::nil();
	EXPECT_EQ("00000000-0000-0000-0000-000000000000", uuid.to_string());
}

TEST(uuid, from_string) {
	amo::uuid uuid = amo::uuid::from_string("14ff4b28-5162-49b3-91a3-9de0d8426061");
	EXPECT_EQ("14ff4b28-5162-49b3-91a3-9de0d8426061", uuid.to_string());
}