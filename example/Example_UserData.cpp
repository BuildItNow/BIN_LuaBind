#include "Example_UserData.h"

#include "ExampleManager.h"

#include "Public.hpp"

namespace bin
{
}

void CExample_UserData::Do()
{
	printf("UserData的接口和Table类似，参见table\n");
}

REGISTE_EXAMPLE(CExample_UserData);