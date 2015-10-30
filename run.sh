#input=/home/zork/data/web-google/glab_in/web-google.txt 
#output=./wg.out.1

input=/scratch1/zork/data/live/glab_in/soc-LiveJournal1.txt
output=/scratch1/zork/data/live/live.out



./pagerank  -input ${input} -output ${output} --logtostderr=1
