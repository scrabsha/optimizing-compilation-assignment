test_files := $(wildcard *.c)
test_output_dirs := $(test_files:.c=)

main: $(test_output_dirs)

%: %.c
	@echo "[$<]"
	@./run_compiler.sh $<
	@touch $@

clean:
	@rm -rf $(test_output_dirs)