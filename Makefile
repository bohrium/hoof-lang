clean:
	touch temp
	rm temp*
	rm *.o

SRC_FILE:=tests/test_$(TEST_PREFIX).c
OBJ_FILE:=tests/test_$(TEST_PREFIX).o
OUT_FILE:=tests/test_$(TEST_PREFIX).out
REF_FILE:=tests/test_$(TEST_PREFIX).ref

test-list:
	@echo "\033[36;1m"
	@echo "testing LIST"
	@echo "\033[37;0m"
	@make --no-print-directory test-inner TEST_PREFIX=list VERB=QUIET

test-string:
	@echo "\033[36;1m"
	@echo "testing STRING"
	@echo "\033[37;0m"
	@make --no-print-directory test-inner TEST_PREFIX=string VERB=QUIET

test-lexer:
	@echo "\033[36;1m"
	@echo "testing LEXER"
	@echo "\033[37;0m"
	@make --no-print-directory test-inner TEST_PREFIX=lexer VERB=QUIET

test-all:
	@make --no-print-directory test-list
	@make --no-print-directory test-string
	@make --no-print-directory test-lexer

test-inner:
	@echo "\033[37m"
	gcc -O3 -std=c17 -pedantic 		\
		cstring.c    				\
		lexer.c 					\
		list.c       				\
		preprocessor_tricks.c		\
		rawstring.c  				\
		string.c     				\
		$(SRC_FILE) -o $(OBJ_FILE)
	@./$(OBJ_FILE) no-color > $(OUT_FILE)
	@python3 process_test_output.py $(OUT_FILE) temp_a $(VERB)
	@python3 process_test_output.py $(REF_FILE) temp_b QUIET
	@echo "\033[36;1m"
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
	@echo "\033[37;0m"
	@rm temp*
	@echo "\033[36m"


