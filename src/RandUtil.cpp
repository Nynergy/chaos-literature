#include "RandUtil.h"

namespace RandUtil {

	int randBetween(int min, int max) {
		return min + (rand() % (max - min));
	}

}
