
#include "version.h"
#include <gtest/gtest.h>


TEST(helloworld_test,Version_test){
	ASSERT_TRUE(Version() > 0);
}
