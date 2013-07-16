
include ../common/Makefile.target.mk

$(OUTDIR)/obj/gen/libraries.cc:
	@mkdir -p $(dir $@)
	@python $(V8TOOL)/js2c.py $@ CORE off $(addprefix $(V8SOURCE)/, $(V8LIBRARIES))

$(OUTDIR)/obj/gen/experimental-libraries.cc:
	@mkdir -p $(dir $@)
	@python $(V8TOOL)/js2c.py $@ EXPERIMENTAL off $(addprefix $(V8SOURCE)/, $(V8EXPERIMENTAL-LIBRARIES))
	
$(OUTDIR)/obj/gen/snapshot.cc: 
	@mkdir -p $(dir $@)
	$(V8MKSNAPSHOT) --log-snapshot-positions --logfile $(OUTDIR)/obj/gen/snapshot.log $(OUTDIR)/obj/gen/snapshot.cc
