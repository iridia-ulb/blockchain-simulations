DATAFOLDER=l
last_rep=$(ls $DATAFOLDER -v | tail -1)
#new_rep=$(printf "%03d\n" $(($last_rep+1)))
new_rep=$(printf "%d\n" $(($last_rep+1)))

echo $new_rep
