#include <stdio.h>
#include "util/aur_util/aur_util.h"
#include "util/hash/uthash.h"
#include "util/sds/sds.h"
#include "util/sds/sdsalloc.h"
int main(int argc, char const *argv[])
{
   println("hello");
   println("helloAurxsiu");

   sds str = sdsnew("hello SDS");
   println(str);
   return 0;
}
