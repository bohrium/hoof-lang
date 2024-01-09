test-list:
	echo "\033[37m"
	gcc test_list.c -o test_list.o
	./test_list.o > test.out
	python3 process_test_output.py test.out temp_a LOUD ; echo "\033[37m"
	python3 process_test_output.py test.ref temp_b QUIET ; echo "\033[37m"
	echo "\033[37m"
	if [ "$(diff temp_a temp_b)" = "" ]; then 	\
		echo "\033[32mPASSED TEST\033[37m";						\
	else	             		            				\
		echo "\033[31mFAILED TEST\033[37m";						\
	fi;
	rm temp*
	echo "\033[36m"
