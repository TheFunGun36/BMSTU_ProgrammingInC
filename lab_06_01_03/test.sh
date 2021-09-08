POSITIVES_SUCCEEDED=0
POSITIVES_SUM=0
NEGATIVES_SUCCEEDED=0
NEGATIVES_SUM=0

for file in `ls func_tests`
do
    if [[ $file =~ pos_[0-9]{2}_args.txt ]]
    then
        ((POSITIVES_SUM++))
        i=${file%_args.txt}
        i=${i#pos_}
        ./`cat func_tests/pos_${i}_args.txt` > output.txt
        if [[ $? == 0 ]] && cmp -s "output.txt" "func_tests/pos_${i}_out.txt"
        then
            ((POSITIVES_SUCCEEDED++))
        else
            echo "Failed positive test $i. Program output:"
            cat output.txt
            echo
        fi
    fi
    if [[ $file =~ neg_[0-9]{2}_args.txt ]]
    then
        ((NEGATIVES_SUM++))
        i=${file%_args.txt}
        i=${i#neg_}
        ./`cat func_tests/neg_${i}_args.txt` > output.txt
        if [[ $? != 0 ]]
        then
            ((NEGATIVES_SUCCEEDED++))
        else
            echo "Failed negative test $i."
            cat output.txt
            echo
        fi
    fi
done

rm output.txt
echo "Succeeded positives $POSITIVES_SUCCEEDED/$POSITIVES_SUM"
echo "Succeeded negatives $NEGATIVES_SUCCEEDED/$NEGATIVES_SUM"
