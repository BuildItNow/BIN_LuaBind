#include "Example_Table.h"

#include "ExampleManager.h"

#include "Public.hpp"

namespace bin
{
}

void CExample_Table::Do()
{
	printf("Table的接口和Handle类似，参见handle\n");
}

REGISTE_EXAMPLE(CExample_Table);