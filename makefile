all: install
test: install-all test-all
install:
		@gcc source/main.c source/libs/*.c -o NetMap
install-all:
		@gcc source/main.c source/libs/*.c -o outputs/output1/NetMap
		@echo "MAKE: compile1   done"
		@gcc source/main.c source/libs/*.c -o outputs/output2/NetMap
		@echo "MAKE: compile2   done"
		@gcc source/main.c source/libs/*.c -o outputs/output3/NetMap
		@echo "MAKE: compile3   done"
		@gcc source/main.c source/libs/*.c -o outputs/output4/NetMap
		@echo "MAKE: compile4   done"
		@gcc source/main.c source/libs/*.c -o outputs/output5/NetMap
		@echo "MAKE: compile5   done"
		@gcc source/main.c source/libs/*.c -o outputs/output6/NetMap
		@echo "MAKE: compile6   done"
test-all:
		@cd outputs/output1 && ./NetMap ../../inputs/input1.txt && cd ../../
		@echo "MAKE: test1      done"
		@cd outputs/output2 && ./NetMap ../../inputs/input2.txt && cd ../../
		@echo "MAKE: test2      done"
		@cd outputs/output3 && ./NetMap ../../inputs/input3.txt && cd ../../
		@echo "MAKE: test3      done"
		@cd outputs/output4 && ./NetMap ../../inputs/input4.txt && cd ../../
		@echo "MAKE: test4      done"
		@cd outputs/output5 && ./NetMap ../../inputs/input5.txt && cd ../../
		@echo "MAKE: test5      done"
		@cd outputs/output6 && ./NetMap ../../inputs/input6.txt && cd ../../
		@echo "MAKE: test6      done"
clear:
		@rm NetMap
