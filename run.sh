#!/bin/bash

update_vpz_from_csv(){
    OLDIFS=$IFS
    IFS=","
    while read parameter value
    do
        xmlstarlet ed -L -u "/vle_project/experiment/conditions/condition/port[@name='$parameter']/double" -v $value /home/user01/.vle/pkgs-1.1/lotka-volterra/exp/empty.vpz
    done < $1
    IFS=$OLDIFS
}

update_vpz_from_csv $1
vle -P lotka-volterra empty.vpz
mv test_view.dat $2
awk 'BEGIN {count = 0} {print count",x,"$1",x,"$2 "\n" count+1",y,"$1",y,"$3 } END {count = count + 1}' $2 | head -n -4 |tail -n +3 > tmp.txt && mv tmp.txt $2
