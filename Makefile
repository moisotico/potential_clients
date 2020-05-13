PWD = $(CURDIR)
.DEFAULT_GOAL := run

compile:
	@mkdir -p $(PWD)/bin
	@g++ -std=c++11 $(PWD)/src/parser.cpp -o bin/files

run: compile
	@cd $(PWD)/bin
	@bin/files

clean: 
	@rm $(PWD)/data/people.out
	@rm $(PWD)/bin/files
		
	



