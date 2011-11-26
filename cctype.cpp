// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// コンパイルおよび実行環境の文字が ASCII 互換であることを前提としたテストをしている。
// ASCII のテストなのだから、本来は 'A' ではなく、0x41 を使うべき。

#include<cassert>
#include<sscrisk/cel/cctype.hpp>

int main()
{
 namespace c = sscrisk::cel;
 {
  constexpr bool test1 = c::isalnum('A');
  assert(test1 == true);
  constexpr bool test2 = c::isalnum('a');
  assert(test2 == true);
  constexpr bool test3 = c::isalnum('0');
  assert(test3 == true);
  constexpr bool test4 = c::isalnum(' ');
  assert(test4 == false);
  constexpr bool test5 = c::isalnum('\a');
  assert(test5 == false);
  constexpr bool test6 = c::isalnum('f');
  assert(test6 == true);
  constexpr bool test7 = c::isalnum(',');
  assert(test7 == false);
  constexpr bool test8 = c::isalnum(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::isalpha('A');
  assert(test1 == true);
  constexpr bool test2 = c::isalpha('a');
  assert(test2 == true);
  constexpr bool test3 = c::isalpha('0');
  assert(test3 == false);
  constexpr bool test4 = c::isalpha(' ');
  assert(test4 == false);
  constexpr bool test5 = c::isalpha('\a');
  assert(test5 == false);
  constexpr bool test6 = c::isalpha('f');
  assert(test6 == true);
  constexpr bool test7= c::isalpha(',');
  assert(test7 == false);
  constexpr bool test8 = c::isalpha(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::isblank('A');
  assert(test1 == false);
  constexpr bool test2 = c::isblank('a');
  assert(test2 == false);
  constexpr bool test3 = c::isblank('0');
  assert(test3 == false);
  constexpr bool test4 = c::isblank(' ');
  assert(test4 == true);
  constexpr bool test5 = c::isblank('\a');
  assert(test5 == false);
  constexpr bool test6 = c::isblank('f');
  assert(test6 == false);
  constexpr bool test7 = c::isblank(',');
  assert(test7 == false);
  constexpr bool test8 = c::isblank(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::iscntrl('A');
  assert(test1 == false);
  constexpr bool test2 = c::iscntrl('a');
  assert(test2 == false);
  constexpr bool test3 = c::iscntrl('0');
  assert(test3 == false);
  constexpr bool test4 = c::iscntrl(' ');
  assert(test4 == false);
  constexpr bool test5 = c::iscntrl('\a');
  assert(test5 == true);
  constexpr bool test6 = c::iscntrl('f');
  assert(test6 == false);
  constexpr bool test7 = c::iscntrl(',');
  assert(test7 == false);
  constexpr bool test8 = c::iscntrl(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::isdigit('A');
  assert(test1 == false);
  constexpr bool test2 = c::isdigit('a');
  assert(test2 == false);
  constexpr bool test3 = c::isdigit('0');
  assert(test3 == true);
  constexpr bool test4 = c::isdigit(' ');
  assert(test4 == false);
  constexpr bool test5 = c::isdigit('\a');
  assert(test5 == false);
  constexpr bool test6 = c::isdigit('f');
  assert(test6 == false);
  constexpr bool test7 = c::isdigit(',');
  assert(test7 == false);
  constexpr bool test8 = c::isdigit(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::isgraph('A');
  assert(test1 == true);
  constexpr bool test2 = c::isgraph('a');
  assert(test2 == true);
  constexpr bool test3 = c::isgraph('0');
  assert(test3 == true);
  constexpr bool test4 = c::isgraph(' ');
  assert(test4 == false);
  constexpr bool test5 = c::isgraph('\a');
  assert(test5 == false);
  constexpr bool test6 = c::isgraph('f');
  assert(test6 == true);
  constexpr bool test7 = c::isgraph(',');
  assert(test7 == true);
  constexpr bool test8 = c::isgraph(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::islower('A');
  assert(test1 == false);
  constexpr bool test2 = c::islower('a');
  assert(test2 == true);
  constexpr bool test3 = c::islower('0');
  assert(test3 == false);
  constexpr bool test4 = c::islower(' ');
  assert(test4 == false);
  constexpr bool test5 = c::islower('\a');
  assert(test5 == false);
  constexpr bool test6 = c::islower('f');
  assert(test6 == true);
  constexpr bool test7 = c::islower(',');
  assert(test7 == false);
  constexpr bool test8 = c::islower(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::isprint('A');
  assert(test1 == true);
  constexpr bool test2 = c::isprint('a');
  assert(test2 == true);
  constexpr bool test3 = c::isprint('0');
  assert(test3 == true);
  constexpr bool test4 = c::isprint(' ');
  assert(test4 == true);
  constexpr bool test5 = c::isprint('\a');
  assert(test5 == false);
  constexpr bool test6 = c::isprint('f');
  assert(test6 == true);
  constexpr bool test7 = c::isprint(',');
  assert(test7 == true);
  constexpr bool test8 = c::isprint(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::ispunct('A');
  assert(test1 == false);
  constexpr bool test2 = c::ispunct('a');
  assert(test2 == false);
  constexpr bool test3 = c::ispunct('0');
  assert(test3 == false);
  constexpr bool test4 = c::ispunct(' ');
  assert(test4 == false);
  constexpr bool test5 = c::ispunct('\a');
  assert(test5 == false);
  constexpr bool test6 = c::ispunct('f');
  assert(test6 == false);
  constexpr bool test7 = c::ispunct(',');
  assert(test7 == true);
  constexpr bool test8 = c::ispunct(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::isspace('A');
  assert(test1 == false);
  constexpr bool test2 = c::isspace('a');
  assert(test2 == false);
  constexpr bool test3 = c::isspace('0');
  assert(test3 == false);
  constexpr bool test4 = c::isspace(' ');
  assert(test4 == true);
  constexpr bool test5 = c::isspace('\a');
  assert(test5 == false);
  constexpr bool test6 = c::isspace('f');
  assert(test6 == false);
  constexpr bool test7 = c::isspace(',');
  assert(test7 == false);
  constexpr bool test8 = c::isspace(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::isupper('A');
  assert(test1 == true);
  constexpr bool test2 = c::isupper('a');
  assert(test2 == false);
  constexpr bool test3 = c::isupper('0');
  assert(test3 == false);
  constexpr bool test4 = c::isupper(' ');
  assert(test4 == false);
  constexpr bool test5 = c::isupper('\a');
  assert(test5 == false);
  constexpr bool test6 = c::isupper('f');
  assert(test6 == false);
  constexpr bool test7 = c::isupper(',');
  assert(test7 == false);
  constexpr bool test8 = c::isupper(EOF);
  assert(test8 == false);
 }
 {
  constexpr bool test1 = c::isxdigit('A');
  assert(test1 == true);
  constexpr bool test2 = c::isxdigit('a');
  assert(test2 == true);
  constexpr bool test3 = c::isxdigit('0');
  assert(test3 == true);
  constexpr bool test4 = c::isxdigit(' ');
  assert(test4 == false);
  constexpr bool test5 = c::isxdigit('\a');
  assert(test5 == false);
  constexpr bool test6 = c::isxdigit('f');
  assert(test6 == true);
  constexpr bool test7 = c::isxdigit(',');
  assert(test7 == false);
  constexpr bool test8 = c::isxdigit(EOF);
  assert(test8 == false);
 }
 {
  constexpr int test1 = c::tolower('A');
  assert(test1 == 'a');
  constexpr int test2 = c::tolower('a');
  assert(test2 == 'a');
  constexpr int test3 = c::tolower('0');
  assert(test3 == '0');
  constexpr int test4 = c::tolower(' ');
  assert(test4 == ' ');
  constexpr int test5 = c::tolower('\a');
  assert(test5 == '\a');
  constexpr int test6 = c::tolower('f');
  assert(test6 == 'f');
  constexpr int test7 = c::tolower(',');
  assert(test7 == ',');
  constexpr int test8 = c::tolower(EOF);
  assert(test8 == EOF);
 }
 {
  constexpr int test1 = c::toupper('A');
  assert(test1 == 'A');
  constexpr int test2 = c::toupper('a');
  assert(test2 == 'A');
  constexpr int test3 = c::toupper('0');
  assert(test3 == '0');
  constexpr int test4 = c::toupper(' ');
  assert(test4 == ' ');
  constexpr int test5 = c::toupper('\a');
  assert(test5 == '\a');
  constexpr int test6 = c::toupper('f');
  assert(test6 == 'F');
  constexpr int test7 = c::toupper(',');
  assert(test7 == ',');
  constexpr int test8 = c::toupper(EOF);
  assert(test8 == EOF);
 }
}
