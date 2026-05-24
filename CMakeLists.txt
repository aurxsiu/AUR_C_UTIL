# cmake最低版本
cmake_minimum_required(VERSION 4.0)

# 工程名称
project(util_test_project C)
# 确保通过编译,咱们用了GCC的特性
set(CMAKE_C_COMPILER "C:\\msys64\\ucrt64\\bin\\gcc.exe")


# 设置output的位置,PROJECT_SOURCE_DIR指根目录
# set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 所有源码文件保存在SRC这个变量中,不会递归查找
aux_source_directory(src SRC)
# 设置头文件路径,如果头文件和源文件混在src则不需要
# include_directories(include INCLUDE)

aux_source_directory(src/util/aur_util AUR_UTIL)
aux_source_directory(src/util/hash HASH_UTIL)
aux_source_directory(src/util/sds SDS_UTIL)

# 生成的文件和编码文件
add_executable(main ${SRC} ${AUR_UTIL} ${HASH_UTIL} ${SDS_UTIL})

# socket通信
# target_link_libraries(main5 ws2_32)

# bluetooth errorHandle
# target_link_libraries(main5 Bthprops Kernel32)

