/**
 *  Copyright 2020 by André Schlinke <schlinke.andre@gmail.com>
 *  
 *  This file is part of brln.
 *  
 *  brln is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  brln is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with brln.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "main.hpp"

// we assume all arguments are integers and we sum them up
// for simplicity we do not verify the type of arguments
int main(int argc, char *argv[]) {
  std::vector<int> integers;
  for (auto i = 1; i < argc; i++) {
    integers.push_back(std::stoi(argv[i]));
  }
  auto sum = sum_integers(integers);

  std::cout << sum << std::endl;
}
