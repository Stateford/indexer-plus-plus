// This file is the part of the Indexer++ project.
// Copyright (C) 2016 Anna Krykora <krykoraanna@gmail.com>. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be found in the LICENSE file.

#pragma once

namespace ifind
{

const char* gHelpText = R"(Usage: ifind [path...] [expression]

default path is the current directory; '/' will search the whole system;
expression may consist of tests and actions:

tests (N can be +N or -N or N): 
		-amin N -atime N 
		-cmin N -ctime N
		-mmin N -mtime N
		-iname PATTERN -name PATTERN
		-size N[kMG]  
		'k' for Kilobytes (units of 1024 bytes) (this is default value)
		'M' for Megabytes (units of 1048576 bytes)
		'G' for Gigabytes (units of 1073741824 bytes)
		-type [fd]
  
actions:
	-printf format
	-fprint file
	-fprintf file format)";
    
} //namespace ifind