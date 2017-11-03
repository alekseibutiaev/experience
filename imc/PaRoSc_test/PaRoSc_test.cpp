#include <gtest\gtest.h>
#include "..\PaRoSc_logic\PaRoSc.h"

struct rarosc_test {};

template<>
rarosc_test parosc::test_accessor<rarosc_test, rarosc_test>(rarosc_test)
{
	enum { Scissors, Rock, Paper };

	EXPECT_EQ(0, party(Scissors, Scissors));
	EXPECT_EQ(0, party(Rock, Rock));
	EXPECT_EQ(0, party(Paper, Paper));

	EXPECT_EQ(1, party(Scissors, Paper));
	EXPECT_EQ(1, party(Rock, Scissors));
	EXPECT_EQ(1, party(Paper, Rock));

	EXPECT_EQ(-1, party(Paper, Scissors));
	EXPECT_EQ(-1, party(Scissors, Rock));
	EXPECT_EQ(-1, party(Rock, Paper));
	return rarosc_test();
}

TEST(rarosc, rarosc_test)
{
	parosc prc(0);
	prc.test_accessor<rarosc_test, rarosc_test>(rarosc_test());
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}