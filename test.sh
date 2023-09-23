#!/bin/bash
##################################################
# Copyright(c) 2023 Akito Dataminer
#
# This software is released under the MIT License.
# Refer the accompanying LICENSE.txt or the description
# at the provided URL for details.
# http://opensource.org/licenses/mit-license.php
##################################################
# このスクリプトは、コンパイラと標準規格の組み合わせを変えて
# cmakeを実行し、テストケースと本体をコンパイルする。
# その後、そのテストケースを実行するスクリプトとなっている。
##################################################
# This script runs cmake with different combinations of compilers and
# standards to compile the main source code and test cases.
# After that, this script executes the test cases.
##################################################

declare -rai TARGET_STD=( 17 20 )
declare -ra TARGET_COMPILER=( clang++ g++ )
declare -a BUILD_DIRECTORIES=()
## debug
# declare -p TARGET_STD
# declare -p TARGET_COMPILER

declare -i cnt=0
for c in ${TARGET_COMPILER[*]}; do
  for s in ${TARGET_STD[*]}; do
    # Please note that -D options specified after -P will be ignored.
    echo "Now compiling by ${c} with C++${s}"
    cmake -Dtest=1 -Dcompiler=${c} -Dstd_version=${s} -P build.cmake

    CURRENT=$(cd $(dirname $0);pwd)
    BUILD_DIRECTORIES[cnt]=${CURRENT}/build_for_test/${c}/${s}
    # echo ${BUILD_DIRECTORIES[${cnt}]} # debug

    let ++cnt
    echo -n -e "\n"
  done
done

declare -i PROCESSOR_NUM=`nproc`
for directory in ${BUILD_DIRECTORIES[*]}; do
  ctest --test-dir ${directory} -j${PROCESSOR_NUM}
done
