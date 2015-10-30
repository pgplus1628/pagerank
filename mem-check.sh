
VAL_LOGFILE="pagerank-memcheck.log"

VAL_FLAGS="--tool=memcheck"
VAL_FLAGS="${VAL_FLAGS} --leak-check=full"
VAL_FLAGS="${VAL_FLAGS} --show-leak-kinds=all"
VAL_FLAGS="${VAL_FLAGS} --undef-value-errors=yes"
VAL_FLAGS="${VAL_FLAGS} --log-file=${VAL_LOGFILE}"

input=/home/zork/data/web-google/glab_in/web-google.txt 
output=./wg.out 

valgrind ${VAL_FLAGS} ./pagerank  -input ${input} -output ${output} --logtostderr=1
