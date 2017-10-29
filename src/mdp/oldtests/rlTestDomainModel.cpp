/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "rlTestDomainModel.h"


double RlTestDomainModel::measureReward()
{
	if (xpos > 0 && xpos < 11 && ypos == 0)
		return -100;
	if (xpos == 11 && ypos == 0)
		return 0;
	return -1;

}



