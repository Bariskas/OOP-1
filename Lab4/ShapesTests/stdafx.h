// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702)
#include <boost/test/unit_test.hpp>

// TODO: reference additional headers your program requires here
#define _USE_MATH_DEFINES
#include <math.h>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/algorithm/string.hpp>
#include "boost/iostreams/stream.hpp"
#include "boost/iostreams/device/null.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>