test-list:
	@echo "\033[37m"
	@gcc -O3 -std=c17 -pedantic test_list.c -o test_list.o
	@./test_list.o > test_list.out
	@python3 process_test_output.py test_list.out temp_a LOUD
	@python3 process_test_output.py test_list.ref temp_b QUIET
	@if diff temp_a temp_b; then 		\
		echo "\033[32m";								\
		echo "        ===========  ^   ^ ";         	\
		echo "        PASSED TEST  0   0 ";         	\
		echo "        ===========    u    \033[37m";	\
	else	             		            			\
		echo "\033[31m";								\
		echo "        ===========  \\   / ";        	\
		echo "        FAILED TEST {o} {o}";         	\
		echo "        ===========   www  \033[37m";		\
	fi;
	@rm temp*
	@echo "\033[36m"

test-string:
	@echo "\033[37m"
	@gcc -O3 -std=c17 -pedantic test_string.c -o test_string.o
	@./test_string.o > test_string.out
	@python3 process_test_output.py test_string.out temp_a LOUD
	@python3 process_test_output.py test_string.ref temp_b QUIET
	@if diff temp_a temp_b; then 		\
		echo "\033[32m";								\
		echo "        ===========  ^   ^ ";         	\
		echo "        PASSED TEST  0   0 ";         	\
		echo "        ===========    u    \033[37m";	\
	else	             		            			\
		echo "\033[31m";								\
		echo "        ===========  \\   / ";        	\
		echo "        FAILED TEST {o} {o}";         	\
		echo "        ===========   www  \033[37m";		\
	fi;
	@rm temp*
	@echo "\033[36m"
