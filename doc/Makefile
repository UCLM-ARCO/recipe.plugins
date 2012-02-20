PROY=plugins
STYLE_SHEET=/usr/share/sgml/docbook/stylesheet/dsssl/ldp/ldp.dsl
JADE_FLAGS=-t sgml -i html


$(PROY).html: $(PROY).sgml
	docbook2html -u $< 

# $(PROY).html: $(PROY).sgml
# 	jade -V nochunks $(JADE_FLAGS) -d $(STYLE_SHEET)\#html $< > $@

# index.html: $(PROY).sgml
# 	jade $(JADE_FLAGS) -d $(STYLE_SHEET)\#html $<

clean:
	$(RM) $(PROY).pdf *~ *.html *.fot
	$(RM) -r $(PROY)
	$(RM) -rf $(PROY).junk
