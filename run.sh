#input=/home/zork/data/web-google/glab_in/web-google.txt 
#output=./wg1

#input=/scratch1/zork/data/live/glab_in/soc-LiveJournal1.txt
#output=/scratch1/zork/data/live/live.out

#input=./data/small.snap
#output=./data/out

#input=/scratch1/zork/data/tw-small/twitter_rv_15066953.net
#output=/scratch1/zork/data/tw-small/tw-small.out

input=/scratch1/zork/data/twitter/glab_in/twitter_rv.net
output=/scratch1/zork/data/twitter/glab_in/twout



#./pagerank  -input ${input} -output ${output} --logtostderr=1 --order=hilbert --dump_edges=1
./pagerank  -input ${input} -output ${output} --logtostderr=1 --order=all
#./pagerank  -input ${input} -output ${output} --logtostderr=1 --order=all
#numactl --cpubind=1 ./pagerank  -input ${input} -output ${output} --logtostderr=1 --order=hilbert --dump_edges=1
