test_files := $(wildcard *.c)
test_output_dirs := $(test_files:.c=)

main: $(test_output_dirs)

%: %.c
	@echo "[$<]"
	@mkdir -p $@
	@touch $@
	@./run_compiler.sh $<

clean:
	@rm -rf $(test_output_dirs)