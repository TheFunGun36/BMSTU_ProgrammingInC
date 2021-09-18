POSITIVES_SUCCEEDED=0
POSITIVES_MEMORY_SUCCEEDED=0
POSITIVES_SUM=0
NEGATIVES_SUCCEEDED=0
NEGATIVES_MEMORY_SUCCEEDED=0
NEGATIVES_SUM=0

while read line
do
    ((POSITIVES_SUM++))

    index=`printf '%02d' $POSITIVES_SUM`

    if [ -s log/valg${index}_pos.txt ]
    then
        rm log/valg${index}_pos.txt
    fi

    if [[ $1 == "-m" ]]
    then
        valgrind -q --log-fd=9 9>log/valg${index}_pos.txt --leak-check=full ./build/app.exe $line
    else
        ./build/app.exe $line
    fi

    exit_code=$?

    if [[ "$exit_code" == "0" && "`diff output.txt func_tests/pos_${index}_out.txt`" == "" ]]
    then
        ((POSITIVES_SUCCEEDED++))

        rm output.txt
        if [ -f log/pos$index.txt ]
        then
            rm log/pos$index.txt
        fi
    else
        if [[ "$exit_code" == "0" ]]
        then
            mv output.txt log/pos$index.txt
            echo -e "\e[31mFailed positive $index,\e[0m exit_code=$exit_code. See output in log/pos$index.txt"
        else
            echo -e "\e[31mFailed positive $index, exit_code=$exit_code.\e[0m"
        fi
    fi

    if [ -s log/valg${index}_pos.txt ]
    then
        echo -e "\e[1;33mMemory leak in positive $index.\e[0m Check valg${index}_pos.txt"
    else
        ((POSITIVES_MEMORY_SUCCEEDED++))
        
        if [[ $1 == "-m" ]]
        then
            rm log/valg${index}_pos.txt
        fi
    fi
done < func_tests/argslist_pos.txt

while read line
do
    ((NEGATIVES_SUM++))

    index=`printf '%02d' $NEGATIVES_SUM`

    if [ -s log/valg${index}_neg.txt ]
    then
        rm log/valg${index}_neg.txt
    fi

    if [[ $1 == "-m" ]]
    then
        valgrind -q --log-fd=9 9>log/valg${index}_neg.txt --leak-check=full ./build/app.exe $line
    else
        ./build/app.exe $line
    fi

    exit_code=$?

    if [[ "$exit_code" != "0" ]]
    then
        ((NEGATIVES_SUCCEEDED++))

        if [ -f log/neg$index.txt ]
        then
            rm log/neg$index.txt
        fi
    else
        mv output.txt log/neg$index.txt
        echo -e "\e[31mFailed negative $index,\e[0m exit_code=$exit_code. See output in log/neg$index.txt"
    fi

    if [ -s log/valg${index}_neg.txt ]
    then
        echo -e "\e[1;33mMemory leak in negative $index.\e[0m Check valg${index}_neg.txt"
    else
        ((NEGATIVES_MEMORY_SUCCEEDED++))
        if [[ $1 == "-m" ]]
        then
            rm log/valg${index}_neg.txt
        fi
    fi
done < func_tests/argslist_neg.txt

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
