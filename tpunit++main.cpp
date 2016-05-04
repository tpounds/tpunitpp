/**
 * Copyright (c) 2011-2015 Trevor Pounds <trevor.pounds@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "tpunit++.hpp"
#include <string>
#include <set>

void parse_options(int argc, char* argv[], std::set<std::string>& include, std::set<std::string>& exclude) {
   for (int i = 0; i < argc; i++){
      char* arg = argv[i];
      char* in = strstr(arg, "--include=");
      char* ex = strstr(arg, "--exclude=");
      if (in == arg) {
         include.insert(arg + 10);
      }
      else if (ex == arg) {
         exclude.insert(arg + 10);
      }
   }
}

int main(int argc, char* argv[]) {

   std::set<std::string> include, exclude;
   parse_options(argc, argv, include, exclude);

   /**
    * Run all of the registered tpunit++ tests that aren't excluded based on
    * the command line arguments.
    * Returns 0 if all tests are successful, otherwise returns the number of
    * failing assertions.
    */
   return tpunit::Tests::run(include, exclude);
}
