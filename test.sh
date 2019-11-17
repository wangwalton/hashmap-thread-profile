$1 $3 $4 > temp1.out
$2 $3 $4 > temp2.out

sort -n temp1.out > temp1.outs
sort -n temp2.out > temp2.outs

diff temp1.outs temp2.outs > diff.out
cat diff.out
