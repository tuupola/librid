SUBDIRS = auth basic_id location message message_pack operator_id self_id json system validate

all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

run:
	@for dir in $(SUBDIRS); do \
		echo "=== Running $$dir ==="; \
		$(MAKE) -C $$dir run; \
		echo ""; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

.PHONY: all run clean
