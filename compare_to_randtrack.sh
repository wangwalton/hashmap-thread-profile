$1 $2 $3 > temp.out
sort -n temp.out > temp.outs
diff temp.outs rt1.outs > diff.out
cat diff.out
