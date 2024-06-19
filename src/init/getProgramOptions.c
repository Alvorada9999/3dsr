// This file is part of 3dsr.
// Copyright (C) 2024 Kenedy Henrique Bueno Silva

// 3dsr is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "init.h"

#define OBJ_FILE_OPTION 0
struct programOptions getProgramOptions(int32_t argc, char *argv[]){
  const char *helpMessage = "  -h            This help message\n  --obj         The file path for a wavefront obj\n";
  struct programOptions programOptions;

  struct option longopts[4];
  longopts[0].name = "obj";
  longopts[0].has_arg = required_argument;
  longopts[0].flag = NULL;
  longopts[0].val = OBJ_FILE_OPTION;
  longopts[1].name = NULL;
  longopts[1].has_arg = 0;
  longopts[1].flag = NULL;
  longopts[1].val = 0;
  int32_t longindex;
  int32_t option = 0;
  while((option = getopt_long_only(argc, argv, "h", longopts, &longindex)) != -1) {
    switch (option) {
      case OBJ_FILE_OPTION:
        programOptions.objFilePath = optarg;
        break;
      case 'h':
        printf("%s", helpMessage);
        exit(EXIT_SUCCESS);
        break;
      case '?':
        exit(EXIT_SUCCESS);
    }
  }

  return programOptions;
}
