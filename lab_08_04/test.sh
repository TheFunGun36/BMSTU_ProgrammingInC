POSITIVES_SUCCEEDED=0
POSITIVES_MEMORY_SUCCEEDED=0
POSITIVES_SUM=0
NEGATIVES_SUCCEEDED=0
NEGATIVES_MEMORY_SUCCEEDED=0
NEGATIVES_SUM=0

for file in `ls func_tests`
do
    if [[ $file =~ pos_[0-9]{2}_in.txt ]]
    then
        ((POSITIVES_SUM++))
        i=${file%_in.txt}
        i=${i#pos_}
        # valgrind -q --log-fd=9 9>valg.txt --leak-check=full ./app.exe < func_tests/pos_${i}_in.txt > output.txt
        ./app.exe < func_tests/pos_${i}_in.txt > output.txt
        ret_val=$?
        failed=0

        if [[ $? == 0 ]] && cmp -s "output.txt" "func_tests/pos_${i}_out.txt"
        then
            ((POSITIVES_SUCCEEDED++))
        else
            touch log/log_${i}_out.txt
            cat output.txt >log/log_${i}_out.txt
            echo -e "\e[31mFailed positive test $i.\e[0m exit_code=$ret_val, output in log_${i}_out.txt"
            failed=1
        fi

        if [ -s valg.txt ]
        then
            cp valg.txt log/valg${i}_pos.txt
            echo -e "\e[1;33mMemory leak in positive test $i.\e[0m Check valg${i}_pos.txt"
            failed=1
        else
            ((POSITIVES_MEMORY_SUCCEEDED++))
        fi

        if [ $failed == 1 ]
        then
            echo
        fi
    fi
    if [[ $file =~ neg_[0-9]{2}_in.txt ]]
    then
        ((NEGATIVES_SUM++))
        i=${file%_in.txt}
        i=${i#neg_}
        failed=0
        
        # valgrind -q --log-fd=9 9>valg.txt --leak-check=full ./app.exe < func_tests/neg_${i}_in.txt >/dev/null
        ./app.exe < func_tests/neg_${i}_in.txt >/dev/null

        if [[ $? != 0 ]]
        then
            ((NEGATIVES_SUCCEEDED++))
        else
            echo -e "\e[31mFailed negative test $i.\e[0m"
            failed=1
        fi

        if [ -s valg.txt ]
        then
            cp valg.txt log/valg${i}_neg.txt
            echo -e "\e[1;33mMemory leak in negative test $i.\e[0m Check valg${i}_neg.txt:"
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

echo -e "Succeeded positives $POSITIVES_SUCCEEDED/$POSITIVES_SUM (memory: $POSITIVES_MEMORY_SUCCEEDED/$POSITIVES_SUM)"

if [[ $POSITIVES_SUCCEEDED == $POSITIVES_SUM && $POSITIVES_MEMORY_SUCCEEDED == $POSITIVES_SUM ]]
then
    echo -e "\e[32mPOSITIVES PASSED\e[0m"
fi

echo "Succeeded negatives $NEGATIVES_SUCCEEDED/$NEGATIVES_SUM (memory: $NEGATIVES_MEMORY_SUCCEEDED/$NEGATIVES_SUM)"

if [[ $NEGATIVES_SUCCEEDED == $NEGATIVES_SUM && $NEGATIVES_MEMORY_SUCCEEDED == $NEGATIVES_SUM ]]
then
    echo -e "\e[32mNEGATIVES PASSED\e[0m"
fi