POSITIVES_SUCCEEDED=0
POSITIVES_MEMORY_SUCCEEDED=0
POSITIVES_SUM=0
NEGATIVES_SUCCEEDED=0
NEGATIVES_MEMORY_SUCCEEDED=0
NEGATIVES_SUM=0

for file in `ls func_tests`
do
    if [[ $file =~ pos_[0-9]{2}_args.txt ]]
    then
        ((POSITIVES_SUM++))
        i=${file%_args.txt}
        i=${i#pos_}
        valgrind -q --log-fd=9 9>valg.txt --leak-check=full ./`cat func_tests/pos_${i}_args.txt` > output.txt
        ret_val=$?
        failed=0

        if [[ $? == 0 ]] && cmp -s "output.txt" "func_tests/pos_${i}_out.txt"
        then
            ((POSITIVES_SUCCEEDED++))
        else
            touch log/log_${i}_out.txt
            cat output.txt >log/log_${i}_out.txt
            echo "Failed positive test $i. Program returned $ret_val, output in log_${i}_out.txt"
            failed=1
        fi

        if [ -s valg.txt ]
        then
            cp valg.txt log/valg${i}_pos.txt
            echo "Leak in positive test $i. Check valg${i}_pos.txt"
            failed=1
        else
            ((POSITIVES_MEMORY_SUCCEEDED++))
        fi

        if [ $failed == 1 ]
        then
            echo
        fi
    fi
    if [[ $file =~ neg_[0-9]{2}_args.txt ]]
    then
        ((NEGATIVES_SUM++))
        i=${file%_args.txt}
        i=${i#neg_}
        failed=0
        valgrind -q --log-fd=9 9>valg.txt --leak-check=full ./`cat func_tests/neg_${i}_args.txt` >/dev/null

        if [[ $? != 0 ]]
        then
            ((NEGATIVES_SUCCEEDED++))
        else
            echo "Failed negative test $i."
            failed=1
        fi

        if [ -s valg.txt ]
        then
            cp valg.txt log/valg${i}_neg.txt
            echo "Leak in negative test $i. Check valg${i}_neg.txt:"
            failed=1
        else
            ((NEGATIVES_MEMORY_SUCCEEDED++))
        fi

        if [ $failed == 1 ]
        then
            echo
        fi
    fi
done

rm output.txt
rm valg.txt
echo "Succeeded positives $POSITIVES_SUCCEEDED/$POSITIVES_SUM (memory: $POSITIVES_MEMORY_SUCCEEDED/$POSITIVES_SUM)"
echo "Succeeded negatives $NEGATIVES_SUCCEEDED/$NEGATIVES_SUM (memory: $NEGATIVES_MEMORY_SUCCEEDED/$NEGATIVES_SUM)"
