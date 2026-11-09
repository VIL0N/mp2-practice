#include <gtest.h>
#include "tmatrix.h"
int main(int argc, char **argv)
{
	//TDynamicMatrix<int> m(1,5);
	//cout << m;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
